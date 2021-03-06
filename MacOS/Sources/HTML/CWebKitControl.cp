/*
    Copyright (c) 2007 Cyrus Daboo. All rights reserved.
    
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

// ===========================================================================
//	CWebKitControl.cp				PowerPlant 2.2.2	�1997-2001 Metrowerks Inc.
// ===========================================================================

#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "CWebKitControl.h"

#include "CWebKitControlImp.h"

#include <LControlImp.h>
#include <LStream.h>
#include <PP_Messages.h>
#include <UAppearance.h>

PP_Begin_Namespace_PowerPlant
extern int debug;


// ---------------------------------------------------------------------------
//	� CWebKitControl							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CWebKitControl::CWebKitControl(
							   LStream*	inStream,
							   ClassIDT	inImpID)

: LControlView(inStream, inImpID)
{
	InitCWebKitControl();
}


// ---------------------------------------------------------------------------
//	� CWebKitControl							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CWebKitControl::CWebKitControl(
							   const SPaneInfo&	inPaneInfo,
							   const SViewInfo&	inViewInfo,
							   MessageT			inMessage,
							   SInt16				inControlKind,
							   ClassIDT			inImpID)

: LControlView(inPaneInfo, inViewInfo, inImpID,
			   inControlKind, Str_Empty, 0, inMessage)
{
	InitCWebKitControl();
}


// ---------------------------------------------------------------------------
//	� ~CWebKitControl							Destructor				  [public]
// ---------------------------------------------------------------------------

CWebKitControl::~CWebKitControl()
{
}


// ---------------------------------------------------------------------------
//	� InitTabsControl												 [private]
// ---------------------------------------------------------------------------

void
CWebKitControl::InitCWebKitControl()
{
	//SetURL("http://www.apple.com");
}

void CWebKitControl::SetURL(const cdstring& url)
{
	if(debug>10)
		printf("CWebKitControl::SetURL\n");
	static_cast<CWebKitControlImp*>(mControlSubPane->GetControlImp())->SetURL(url);
}

void CWebKitControl::SetData(const cdstring& data)
{
	if(debug>10)
		printf("CWebKitControl::SetData\n");
	
	static_cast<CWebKitControlImp*>(mControlSubPane->GetControlImp())->SetData(data);
}

void CWebKitControl::AdjustMouseSelf(
									 Point				/* inPortPt */,
									 const EventRecord&	/* inMacEvent */,
									 RgnHandle			/* ioMouseRgn */)
									 {
	// Do nothing
	if(debug)
		printf("CWebKitControl::AdjustMouseSelf\n");
									 }
									 
void CWebKitControl::FinishCreate()
{
	if(debug)
		printf("CWebKitControl::FinishCreate\n");
	
}

Boolean CWebKitControl::ClickStillDown(const Point& OnClickMouseLoc, const Point&	UpdMouseLoc, const Point&	DeltaMouseLoc)
{
	if(debug)
		printf("CWebKitControl::ClickStillDown\n");
	static_cast<CWebKitControlImp*>(mControlSubPane->GetControlImp())->ClickStillDown(DeltaMouseLoc);
}



void CWebKitControl::Click(SMouseDownEvent	&inMouseDown)
{
	if(debug)
		printf("CWebKitControl::Click to CWebKitControlImp\n");
    static_cast<CWebKitControlImp*>(mControlSubPane->GetControlImp())->Click(inMouseDown);
}


void CWebKitControl::ClickSelf()
{	
	if(debug)
		printf("CWebKitControl::ClickSelf()\n");
	
	
}




PP_End_Namespace_PowerPlant
									 