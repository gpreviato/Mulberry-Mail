/*
 *  CWebKitActiveScrolling.h
 *  MulberryXcode
 *
 *  Created by gpreviato on 4/23/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _H_CWebKitActiveScroller
#define _H_CWebKitActiveScroller
#pragma once

#include <LActiveScroller.h>
#include <LAMControlImp.h>
#include "cdstring.h"

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CWebKitActiveScroller : public LActiveScroller {
public:
	CWebKitActiveScroller( LStream* inStream = nil );
	
	virtual				~CWebKitActiveScroller();
	
	void SetURL(const cdstring& url);
	void SetData(const cdstring& data);
	void FinishCreate();
	//	OSStatus ApplyBindToControlLayout(HIViewRef webView, HIViewRef toView);
	
protected:
	HIViewRef	mViewRef;
	ControlHandle	rootControl;
	LControlPane* mControlPane;
	
	
};

PP_End_Namespace_PowerPlant

#endif
