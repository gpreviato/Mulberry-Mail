/*
 *  CAttachmentRawList.h
 *  MulberryXcode
 *
 *  Created by gpreviato on 3/13/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#define member_size(type, member) sizeof(((type *)0)->member

#include "cdstring.h"


	// Classes



class CAttachmentRawList 
{
	
public:
	typedef struct RawAttachments
	{
		char cid[255];
		char cont_type[80];
		char *attch;
		RawAttachments *Next;
	} RawAttachments;

	

	CAttachmentRawList();

	~CAttachmentRawList();
	
	RawAttachments *SearchCid(char *cid);
	int GetAttachmentList(const cdstring &RawMessage);	

	
protected:
	RawAttachments *_List, *_LPointer, *_Llast;
private:
	static int _QtyAttch;

	
	int _AddToList(RawAttachments *ListElem);
	RawAttachments *_SearchCid(char *cid);
	RawAttachments *_CreateElem(char *cid, char *cont_type, char *Attach);
	char * CAttachmentRawList::_ParseHeader(const cdstring &RawMessage);

};


