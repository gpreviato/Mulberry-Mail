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
//	CWebKitControlImp.cp			PowerPlant 2.2.2	¬¨¬®¬¨¬Æ¬¨¬®¬¨√Ü¬¨¬®¬¨¬Æ¬¨¬®‚àö√ú¬¨¬®¬¨¬Æ¬¨¬®¬¨√Ü¬¨¬®¬¨¬Æ¬¨¬®¬¨¬©1997-2001 Metrowerks Inc.
// ===========================================================================
//
//	Implementation for Appearance Manager EditText item.
//
//	The class does not create a ControlHandle and it inherits from
//	LControlImp rather than LAMControlImp.
//
//	The LEditText ControlPane handles everything related to the text.
//	The only thing this class does is draw the frame and focus ring
//	around the text area.
/*
 Mostly that's just not the model that we use in a compositing window. The standard handler always calls HIViewGetViewForMouseEvent 
 and directs the click specifically to the view that is returned. 
 It's a much simpler and cleaner model than having one view know that it needs to redirect clicks to 
 another view contained within it. 
 
 So if the click is intended for the scrollbars, I could call CallNextEventHandler and let it be handled. 
 Otherwise, if the click is for the db, I can keep calling HandleControlClick. 
 That seems to work, and I still get the column header part code that I want when it's clicked. 
 
 Sounds good.
*/



#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "CWebKitControlImp.h"

#include "CWebKitUtils.h"

#include "MyCFString.h"

#include <UControlMgr.h>
#include <CarbonEvents.h>
#include "cdstring.h"
//#include <CGEvent.h>


#include <CoreFoundation/CoreFoundation.h>

PP_Begin_Namespace_PowerPlant
extern int debug;

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
//	Do not access inStream. It may be nil. Read Stream data in Init()

CWebKitControlImp::CWebKitControlImp(
									 LStream*	inStream)

: LAMControlImp(inStream)
{
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

CWebKitControlImp::~CWebKitControlImp()
{
}

/*
static const EventTypeSpec kBoundsChangedEvent = {
kEventClassControl, kEventControlBoundsChanged
};
 */

//-------------------------------------------------------------------------------------
//	ContentBoundsChanged
//-------------------------------------------------------------------------------------
//	A handler on the content view that looks for bounds changed. When so, we resize our
//	web view accordingly. Just busy work. Panther introduces the concept of HILayout,
//	which would eliminate the need for this function.
//
/*
static OSStatus
ContentBoundsChanged( EventHandlerCallRef inCallRef, EventRef inEvent, void* inUserData )
{
	HIViewRef		webView = (HIViewRef)inUserData;
	ControlRef		contentView;
	HIRect			bounds;
	WindowRef		window = GetControlOwner( webView );
	
	HIViewFindByID( HIViewGetRoot( window ), kHIViewWindowContentID, &contentView );
	
	HIViewGetBounds( contentView, &bounds );
	HIViewSetFrame( webView, &bounds );
	
	return noErr;
}
 */

// ---------------------------------------------------------------------------
//	‚Äö√Ñ√∂‚àö√ë‚àö‚àÇ‚Äö√†√∂‚àö√´‚Äö√†√∂‚Äö√†√á‚Äö√Ñ√∂‚àö‚Ä†‚àö‚àÇ‚Äö√†√∂‚àö¬¥‚Äö√Ñ√∂‚àö‚Ä†‚àö‚àÇ‚Äö√Ñ√∂‚àö‚Ä†‚àö√°‚Äö√Ñ√∂‚àö√ë‚àö‚àÇ‚Äö√†√∂‚Äö√Ñ‚Ä†‚Äö√†√∂‚Äö√†√á‚Äö√Ñ√∂‚àö‚Ä†‚àö‚àÇ‚Äö√†√∂¬¨¬•¬¨¬®¬¨¬Æ¬¨¬®¬¨√Ü¬¨¬®¬¨¬Æ¬¨¬®¬¨¬¢ MakeMacControl											   [protected]
// ---------------------------------------------------------------------------

void
CWebKitControlImp::MakeMacControl(
								  ConstStringPtr	inTitle,
								  SInt32			inRefCon)
{
	
	
	if(debug)
		printf("CWebKitControlImp::MakeMacControl\n");
	
	Rect	frame;					// Get Frame in Local coordinates
	if (!CalcLocalFrameRect(frame)) {
		
		if(debug)
			printf("Calculating frame...\n");
		
		// Frame is outside of QuickDraw space. NewControl requires
		// a rectangle in QuickDraw space, so we have to use an
		// artificial location. The Control won't get drawn until
		// its SuperView scrolls it into view.
		
		SDimension16	frameSize;
		mControlPane->GetFrameSize(frameSize);
		
		::MacSetRect(&frame, 0, 0, frameSize.width, frameSize.height);
	}
	
	StFocusAndClipIfHidden	focus(mControlPane);
	
	// Controls must be created within a Window. First
	// try the port containing the ControlPane. If that's
	// nil, the ControlPane hasn't been installed yet so
	// we use the current port and make it the responsibility
	// of the caller to set the port correctly.
	
	macWindowP = mControlPane->GetMacWindow();
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
	
	if (err == errNoRootControl) {
		
		// There is no root control, so we must create one.
		// This happens for the first AM control in a window.
		
		err = ::CreateRootControl(macWindowP, &rootControl);
		
		if (err == errControlsAlreadyExist) {
			
			// This error (-30589) means that a Standard (old-style)
			// Toolbox control was created in the window before the
			// first Appearance Toolbox control. If you are mixing old
			// and new style Toolbox controls in the same window, you
			// must create a new style one first.
			//
			// If you are creating a window from a PPob resource, you
			// can satisfy this requirement by opening the PPob in
			// Constructor and choosing "Show Object Hierarchy" from
			// the Layout menu. In the Hierarchy window, arrange the
			// Panes via drag-and-drop so that an Appearance control
			// is created before any old-style control.
			//
			// Note that LListBox and LScroller will create old-style
			// scroll bar controls, and that the Appearance EditText
			// pane is not a new-style controls (since it doesn't
			// actually use a ControlHandle). Use LScrollerView
			// in place of LScroller/LActiveScroller.
			//
			// If you are installing controls at runtime, create an
			// Appearance control first, or call ::CreateRootControl()
			// yourself before creating any Toolbox controls.
			//
			// This workaround is not necessary on Mac OS X, where all
			// windows automatically get a root control.
			
			SignalStringLiteral_("Must create an Appearance control before "
						 		 "creating an old-style control. See comments "
								 "in the source file.");
		}
		
		ThrowIfOSErr_(err);
	}
	
	// Create Toolbox Control. During construction Panes are
	// always invisible and disabled, so we pass "false" for
	// the "visible" parameter to NewControl. Since NewControl
	// always creates enabled controls, we then explicitly
	// disable the control.
	
	


	
	HIViewRef viewRef = NULL;
	if(debug)
		printf("Creating the HiWebView\n");
	
	OSStatus status = ::CreateHIWebView(&viewRef);
//	HIViewFindByID( HIViewGetRoot( macWindowP ), kHIViewWindowContentID, &contentView );
	
	// contentView i.o. rootControl...
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
	status = ::HIViewAddSubview(rootControl, viewRef);
	if (status != noErr)
		throw "HIWebViewCreate failed";
	
	
//	InstallControlEventHandler( rootControl, ContentBoundsChanged, 1, &kBoundsChangedEvent, viewRef, NULL );
	
	mViewRef = mMacControlH = viewRef;
	
	ThrowIfNil_(mMacControlH);
	
	::DeactivateControl(mMacControlH);
	
	// We need to create a custom control color proc in order to
	// set up the correct background and text color when drawing
	// a control. However, this isn't supported on Mac OS 68K.
	
	
	if (mTextTraitsID != 0) {				// Use custom text traits
		ResIDT	saveID = mTextTraitsID;		// Save and set member var to 0
		mTextTraitsID = 0;					//   so SetTextTraits() knows
		SetTextTraitsID(saveID);			//   the value is changing
	}
 
}


void CWebKitControlImp::FinishCreate()
{
	if(debug)
		printf("CWebKitControlImp::FinishCreate\n");
	
}

void CWebKitControlImp::SetURL(const cdstring& urltxt)
{
	MyCFString cfstring(urltxt, kCFStringEncodingUTF8);
	CFURLRef url = CFURLCreateWithString( NULL, cfstring, NULL );
	URLToWebView(mViewRef, url);
	CFRelease(url);
	if(debug)
		printf("CWebKitControlImp::SetURL\n");
	
}

void CWebKitControlImp::SetData(const cdstring& datatxt)
{

	MyCFString cfstring(datatxt, kCFStringEncodingUTF8);
	DataToWebView(mViewRef, cfstring);
}


Boolean CWebKitControlImp::ClickStillDown(const Point&	DeltaMouseLoc)
{
	if(debug)
		printf("CWebKitControl::ClickStillDown\n");
    CGEventRef	CGevent;
	
	CGevent=CGEventCreateScrollWheelEvent(NULL, kCGScrollEventUnitPixel, 2, DeltaMouseLoc.v*5, DeltaMouseLoc.h*5);
	
	
	
	if( CGevent == NULL)
		printf("Error creating event kCGEventScrollWheel\n");
	CGEventPost(kCGHIDEventTap, CGevent);
	CFRelease(CGevent);	
}



void CWebKitControlImp::Click(SMouseDownEvent	&inMouseDown)
{

	EventRef	theEvent;
	UInt16		DeltaFin=15;
	
	HIPoint		thePos;
	CGEventRef	CGevent;
	
	OSStatus	OSres;
	UInt16 mbutton = kEventMouseButtonPrimary;
	
	thePos.x=inMouseDown.macEvent.where.h;
	thePos.y=inMouseDown.macEvent.where.v;

	HIRect cgrt;
	Rect grt;
	
	
	
	WindowRef theTargetWindow;
	FindWindow(inMouseDown.macEvent.where, &theTargetWindow);
	
	GetWindowBounds(theTargetWindow, kWindowContentRgn, &grt);
	//EventTargetRef target = GetControlEventTarget(theTargetWindow);
//	HIWindowGetAvailablePositioningBounds(kCGNullDirectDisplay, kHICoordSpaceScreenPixel, &grt);
	
	if(debug>10) {
		printf("CWebKitControlImp::Click ->Actual windows rect: top=%d, left=%d, bottom=%d, right=%d\n", grt.top, grt.left, grt.bottom, grt.right);
		printf("CWebKitControlImp::Click ->Actual Mouse pos: x=%f, y=%f\n", thePos.x, thePos.y);
	}
	
//	DoWKClick(mViewRef, ( CGFloat) thePos.x, ( CGFloat) thePos.y);
	
	
	// try to send a 'mouse scroll'
	
	UInt32 axis=kEventMouseWheelAxisY;
	UInt32 delta=-10;
/*	
	OSres=CreateEvent(NULL, kEventClassMouse, kEventMouseWheelMoved, 0, kEventAttributeUserEvent, &theEvent);
	if(debug)
		printf("CWebKitControlImp - Create Event. Res= %d\n", (int) OSres);
	OSres=SetEventParameter(theEvent, kEventParamMouseButton, typeMouseButton, sizeof(mbutton), &mbutton);
	OSres=SetEventParameter(theEvent, kEventParamWindowMouseLocation, typeHIPoint, sizeof(thePos), &thePos);
//	OSres=SetEventParameter(theEvent, kEventParamWindowRef, typeWindowRef, sizeof(mViewRef), &mViewRef);
	OSres=SetEventParameter(theEvent, kEventParamMouseWheelAxis, typeMouseWheelAxis, sizeof(axis), &axis);
	OSres=SetEventParameter(theEvent, kEventParamMouseWheelDelta, typeSInt32, sizeof(delta), &delta);
	
	
	if(debug) {
		printf("CWebKitControlImp::Click - sending a scroll-down to mViewRef - SendEventToEventTargetWithOption.\n");
		printf("Mouse position is x=%f, y=%f\n",thePos.x, thePos.y);
	}
//	OSStatus res=HIViewClick(mViewRef, theEvent);
	OSres=PostEventToQueue(GetCurrentEventQueue(), theEvent,kEventPriorityHigh);
//	OSres=SendEventToEventTargetWithOptions(theEvent, target, kEventTargetSendToAllHandlers);
//	OSres=SendEventToEventTarget(theEvent, target);
//	OSres=SendEventToWindow(theEvent, theTargetWindow);
	OSStatus res=-99;
//    OSStatus res=HIViewClick(mViewRef, theEvent);
	if(debug)
		printf("HiViewClick returned: %d\n",(int) OSres);
*/
	// Ok, try another strategy... we will use CGEventCreateMouseEvent
	int ScrollUnitsY=0;
	int ScrollUnitsX=0;
	
//	DoWKClick(mViewRef,  thePos.x, thePos.y);
	
	if (thePos.y <= (grt.bottom - DeltaFin) && thePos.y >= (grt.bottom - (2 * DeltaFin)) && 
		thePos.x <= (grt.right) && thePos.x  >= (grt.right - (DeltaFin))) {
		ScrollUnitsY=-1;
		if(debug==1)
			printf("thePos.y=%f  > %d and < %d\n", thePos.y, (grt.bottom - (2 * DeltaFin)), (grt.bottom - DeltaFin));
	} else if (thePos.y <= (grt.bottom - (2* DeltaFin)) && thePos.y >= (grt.bottom - (3 * DeltaFin))  && 
			   thePos.x <= (grt.right) && thePos.x  >= (grt.right - (DeltaFin))) {
		ScrollUnitsY=1;
		if(debug==1)
			printf("thePos.y=%f  > %d and < %d\n", thePos.y, (grt.bottom - (3 * DeltaFin)), (grt.bottom - (2*DeltaFin)));

	} else if (thePos.x <= (grt.right - (2* DeltaFin)) && thePos.x >= (grt.right - (3 * DeltaFin))  && 
			   thePos.y <= (grt.bottom) && thePos.y  >= (grt.bottom - (DeltaFin))) {
		ScrollUnitsX=1;
		if(debug==1)
			printf("thePos.x=%f  > %d and < %d\n", thePos.x, (grt.right - (3 * DeltaFin)), (grt.right - (2*DeltaFin)));
		
	} else if (thePos.x <= (grt.right - (DeltaFin)) && thePos.x >= (grt.right - (2 * DeltaFin))  && 
			   thePos.y <= (grt.bottom) && thePos.y  >= (grt.bottom - (DeltaFin))) {
		ScrollUnitsX=-1;
		if(debug==1)
			printf("thePos.x=%f  > %d and < %d\n", thePos.x, (grt.right - (3 * DeltaFin)), (grt.right - (2*DeltaFin)));
		
	}
	
	
	CGevent=CGEventCreateScrollWheelEvent(NULL, kCGScrollEventUnitLine, 2, ScrollUnitsY, ScrollUnitsX);
 
	

	if( CGevent == NULL)
		printf("Error creating event kCGEventScrollWheel\n");
	CGEventPost(kCGHIDEventTap, CGevent);
	CFRelease(CGevent);
	
}


void CWebKitControlImp::ClickSelf()
{	
	if(debug)
		printf("CWebKitControlImp::ClickSelf()\n");
	
	
}

/*
OSStatus CWebKitControlImp::ApplyBindToControlLayout(HIViewRef webView, HIViewRef toView) {
	OSStatus err;
	
	HILayoutInfo layoutInfo;
	layoutInfo.version = kHILayoutInfoVersionZero;
	err = HIViewGetLayoutInfo(webView, &layoutInfo);
	
	layoutInfo.binding.top.toView = toView;  // NULL means parent
	layoutInfo.binding.top.kind = kHILayoutBindTop;
	layoutInfo.binding.left.toView = toView;
	layoutInfo.binding.left.kind = kHILayoutBindLeft;
	layoutInfo.binding.bottom.toView = toView;
	layoutInfo.binding.bottom.kind = kHILayoutBindBottom;
	layoutInfo.binding.right.toView = toView;
	layoutInfo.binding.right.kind = kHILayoutBindRight;
	
	err = HIViewSetLayoutInfo( webView, &layoutInfo );
	
	return err;
}

*/




PP_End_Namespace_PowerPlant
