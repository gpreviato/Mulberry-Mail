/*
 *  CWebKitActiveScrolling.cpp
 *  MulberryXcode
 *
 *  Created by gpreviato on 4/23/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

//#include "CWebKitControlImp.h"
#include "CWebKitActiveScroller.h"
#include "CWebKitUtils.h"

#include "MyCFString.h"

#include <UControlMgr.h>

#include <CoreFoundation/CoreFoundation.h>

PP_Begin_Namespace_PowerPlant

extern int debug;



// ———————————————————————————————————————————————————————————————————————————
//	• CWebKitActiveScroller						Default Constructor		  [public]
// ———————————————————————————————————————————————————————————————————————————

CWebKitActiveScroller::CWebKitActiveScroller(LStream*	inStream)
:  LActiveScroller(inStream)
{
	mThumbControl	  = nil;
	mVertThumbAction  = nil;
	mHorizThumbAction = nil;
	AssignThumbProcs();
}



// ———————————————————————————————————————————————————————————————————————————
//	• CWebKitActiveScroller						Destructor				  [public]
// ———————————————————————————————————————————————————————————————————————————

CWebKitActiveScroller::~CWebKitActiveScroller()
{
	if (mVertThumbAction != nil) {
		DisposeDragGrayRgnUPP(mVertThumbAction);
	}
	
	if (mHorizThumbAction != nil) {
		DisposeDragGrayRgnUPP(mHorizThumbAction);
	}
}



void CWebKitActiveScroller::FinishCreate()
{
	if(debug)
		printf("CWebKitActiveScroller::FinishCreate()\n");
    
	
    
	StFocusAndClipIfHidden	focus(mControlPane);
	WindowPtr		macWindowP = mControlPane->GetMacWindow();
	HIRect cgr;
	
	
	if (macWindowP == nil) {
		if(debug)
			printf("macWindowP is nil...\n");
		macWindowP = UQDGlobals::GetCurrentWindowPort();
	}
	
	// Check if there is a root control
	// ControlHandle	rootControl;
	
	OSErr	err = ::GetRootControl(macWindowP, &rootControl);
	
	
	if(debug)
		printf("Defined the Window control in 'rootControl'\n");
	HIViewRef viewRef = NULL;
	if(debug)
		printf("Create the HiWebView\n");
	
	OSStatus status = ::CreateHIWebView(&viewRef);
	
	// Get the current Bounds...
	HIViewGetBounds(rootControl, &cgr);
	if(debug) {
		printf("Actual windows rect: height=%f, width=%f, origin_x=%f, origin_y=%f\n", cgr.size.height, cgr.size.width, cgr.origin.x, cgr.origin.y);
	}
	//	cgr.origin.x=0.0;
	//	cgr.origin.y=0.0;
	
	HIViewSetFrame( viewRef, &cgr );
	//	HIViewMoveBy(viewRef, -10000, 10000);
	
	
	
	if (status != noErr)
		throw "HIWebViewCreate failed";
	// the rootControl is the Windows that have to contain the Views. But 
	//	status = ::HIViewAddSubview(rootControl, viewRef);
	if (status != noErr)
		throw "HIWebViewCreate failed";
	
}


void CWebKitActiveScroller::SetURL(const cdstring& urltxt)
{
	MyCFString cfstring(urltxt, kCFStringEncodingUTF8);
	CFURLRef url = CFURLCreateWithString( NULL, cfstring, NULL );
	URLToWebView(mViewRef, url);
	CFRelease(url);
}

void CWebKitActiveScroller::SetData(const cdstring& datatxt)
{
	MyCFString cfstring(datatxt, kCFStringEncodingUTF8);
	DataToWebView(mViewRef, cfstring);
}


PP_End_Namespace_PowerPlant
