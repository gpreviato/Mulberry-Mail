/*
 Copyright (c) 2007-2009 Cyrus Daboo. All rights reserved.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */ 





	//	CAttachmentRawList.cp

#include "CAttachmentRawList.h"
#include "cdstring.h"
#include <iostream> 

using namespace std;

int CAttachmentRawList::_QtyAttch;


	//static int _QtyAttch;
	//static CAttachmentRawList::RawAttachments *_List, *_LPointer, *_Llast;

	// Default constructor
CAttachmentRawList::CAttachmentRawList()
{
	_QtyAttch=0;
	_List=NULL;
	_LPointer=NULL;
	_Llast=NULL;
	
}

	// Default destructor
CAttachmentRawList::~CAttachmentRawList()
{
}





int CAttachmentRawList::_AddToList(RawAttachments *ListElem)
{
	if (_QtyAttch==0) {
		_List=ListElem;					
	}
	else {
		CAttachmentRawList::_Llast->Next=ListElem;	
	}
	CAttachmentRawList::_Llast=ListElem;
	CAttachmentRawList::_Llast->Next=NULL;
	CAttachmentRawList::_QtyAttch++;

}






CAttachmentRawList::RawAttachments *CAttachmentRawList::SearchCid(char *cid)
{
	RawAttachments *p, *r;
	int i=0;
	
	r=NULL;
	p=_List;
	if (p!=NULL) 		
		do {
			if(!strcmp(cid, p->cid)){
				r=p;
				break;
			} else {			
				i+=1;
				p=p->Next;
			}
		} while (p!=NULL);
	
	return (r);
}




CAttachmentRawList::RawAttachments *CAttachmentRawList::_CreateElem(char *cid, char * cont_type, char *Attach)
{
	RawAttachments *NewElem, *r;
	char *a;
	
	r=NULL;
	
	if((NewElem=(RawAttachments *)calloc(1, sizeof(RawAttachments)))==NULL) {
		return (r);
	} else {
		NewElem->Next=NULL;
		strncpy(NewElem->cid, cid, sizeof(NewElem->cid));
		strncpy(NewElem->cont_type, cont_type, sizeof(NewElem->cont_type));
		if((a=calloc(1, strlen(Attach)+2))==NULL) {
			free(NewElem);
			return(NULL);
		} else {
			strcpy(a, Attach);
			NewElem->attch=a;
			r=NewElem;
		}
	}
	
	return(r);
			   
}


	// Parse the header of the message and return the Boundary if Present, or Null
char * CAttachmentRawList::_ParseHeader(const cdstring &RawMessage)
{
	static char boundary[255];
	
	char Buff[2048], pBuff[2048];
	char *ct="Content-Type:", *bound="boundary=";
	int i, k, BNum, SearchIntoTheBody=0;
	
	while (BNum=RawMessage.SaS_readline(Buff, sizeof(Buff))!=EOF) {
		i=0; k=0;
		if (!strncmp(Buff, ct, sizeof(ct))) {
			i=strlen(ct);
			while (Buff[i]!='\n' && Buff[i]!='\0' && Buff[i]!=';' && Buff[i]!=':') {
				if (Buff[i]!=' ') pBuff[k++]=Buff[i];
				i++;
			} 
					
			pBuff[k]='\0'; // Ok, in pBuff we have the type of content

			if (!strcmp(pBuff, "multipart/related") || !strcmp(pBuff, "multipart/mixed")) { // is a multipart related message... We have to find out the boundary
																							//				i=0; no: i is already the right one!
																							// if it's a multimart/mixed, we need to discover, into the Body, the 				
																							// multipart related...
				if (!strcmp(pBuff, "multipart/mixed")) {
					SearchIntoTheBody=1;
					continue;
				}
				
				while (Buff[i]!='\0') {
					if(!strncmp(&Buff[i], bound, strlen(bound))) { //found the boundary!
						k=0; i+=strlen(bound);
						while (Buff[i]!='\n' && Buff[i]!='\0' && Buff[i]!=';' && Buff[i]!=':') {
							if (Buff[i]!=' ' && Buff[i]!='\t' && Buff[i]!='"') boundary[k++]=Buff[i];
							i++;
						} 
						boundary[k]='\0';
						return ((char *) &boundary);
					}
					else {
						i++;
					}
				} // if here, it can be on the next line...
				if (BNum=RawMessage.SaS_readline(Buff, sizeof(Buff))!=EOF) {
					i=0;
					while (Buff[i]!='\0') {
						if(!strncmp(&Buff[i], bound, strlen(bound))) { //found the boundary!
							k=0;i+=strlen(bound);
							while (Buff[i]!='\n' && Buff[i]!='\0' && Buff[i]!=';' && Buff[i]!=':') {
								if (Buff[i]!=' '  && Buff[i]!='\t' && Buff[i]!='"') boundary[k++]=Buff[i];
								i++;
							} 
							boundary[k]='\0';
							return ((char *) &boundary);
						}
						else {
							i++;
						}
					} // if here, the boundary tag was missing!!!
					return (NULL);
					
				}
				
			}
		} else if (strlen(Buff)==0 && SearchIntoTheBody==0){
			return (NULL); // End of the header...
		}
		
	}
	return (NULL); // if we arrive here, we are working with a marformend mail...		
}




int CAttachmentRawList::GetAttachmentList(const cdstring &RawMessage)
{
	char boundary[255], Buff[2048], LastLine[2048], c_type[80], cid_val[255];
	char *ct="Content-Type:", *fb, *cid_id="Content-ID:", *bound;
	int i, k, CidFound=0, StartAppend=0;
	int BNum, line=0, ssize=RawMessage.length(), SearchBoundary=1, MarkAttachStart=0;
	
	
	
	
	
	RawMessage.InitStream();
	
	LastLine[0]='\0';
	strcpy(boundary, "--"); // the boundary prefix
							//	*fb='\0'; initialization missed
	
	
	bound=_ParseHeader(RawMessage);
	
	if (bound!=NULL) {
		strcat(boundary, bound);		
	} else {
		boundary[0]='\0';
		return(_QtyAttch); // Not to be parsed....
	}
	
		// FIne, we have the boundary, we can go throw the message
	
	if((fb=malloc(ssize))==NULL){
			// errore allocando la Mem per il buffer di parcheggio attachments;
	}

	while (BNum=RawMessage.SaS_readline(Buff, sizeof(Buff))!=EOF) {
		line++;
		strcpy(LastLine, Buff);

		if (strlen(boundary)>0) { // Only if WE HAVE a boundary...
				// We have some attachemnts to find out, the one delimited by the boundary, that exist...
			if (!strncmp(Buff, boundary, strlen(boundary)) && strlen(boundary)>0 && MarkAttachStart==0) {
				MarkAttachStart=1;
				
			} else if (MarkAttachStart==1) {
				if(!strncmp(Buff, ct, strlen(ct))) { // we have found the tag - Content-Type.
					k=0;
					for (i=strlen(ct); Buff[i]!='\n' && Buff[i]!='\0' && Buff[i]!=';'; i++) 
						if (Buff[i]!=' ') c_type[k++]=Buff[i];					
					c_type[k]='\0';
						//					if(!strncmp(c_type, "image", strlen(image))){ //we have found an image... 						
						//					}
															
				} else if (!strncmp(Buff, cid_id, strlen(cid_id))) { // we have found the tag - Content-ID.
					k=0;
					for (i=strlen(cid_id); Buff[i]!='\n' && Buff[i]!='\0' && Buff[i]!=';'; i++) 
						if (Buff[i]!=' ' && Buff[i]!='<' && Buff[i]!='>') cid_val[k++]=Buff[i];					
					cid_val[k]='\0';
					CidFound=1;
					
				} else if (CidFound==1) {
					if (strlen(Buff)==0) {
						
						StartAppend=1;
						continue;
					
					}
					else if (strncmp(Buff, boundary, strlen(boundary)) && StartAppend==1 ) {						
						if ((strlen(fb)+strlen(Buff))<ssize)
								strcat(fb, Buff); // append Buff to str1
						

					} 
					else if (!strncmp(Buff, boundary, strlen(boundary))) {
						StartAppend=0;
						CidFound=0;
						MarkAttachStart=0;
						RawMessage.SaS_rewind(1);	// back of one line
													//Ok, we have in fb the attachment...
						_AddToList(_CreateElem(cid_val,  c_type, fb)); // creating and attaching an element ot the list
						*fb='\0';
						_QtyAttch++;
					}
				
				 } else if (strlen(Buff)==0 && MarkAttachStart==1 && CidFound==0) {
					 MarkAttachStart=0; 
					 
				 }

			}
			
		}
	}

	free(fb);
	return(_QtyAttch);
}

	// Recursively search cache for mbox with requested name
/* As an example....
unsigned long CAttachmentList::FetchIndexOf(const CAttachment* attach) const
{
	CAttachmentList::const_iterator found = find(begin(), end(), (CAttachment*) attach);
	
	if (found != end())
	{
		return (found - begin()) + 1;
	}
	else
		return 0;
}
*/




