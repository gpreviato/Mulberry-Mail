//#define AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#include <Cocoa/Cocoa.h>
#include <WebKit/WebKit.h>
#include <WebKit/HIWebView.h>
#include <WebKit/CarbonUtils.h>
#include <stdio.h>
#include <stdlib.h>


#include "CWebKitUtils.h"

extern int debug;


void InitWebKit()
{
	if(debug)
		printf("InitWebKit\n");
	
	
	// Init webkit
	WebInitForCarbon();
}

OSStatus CreateHIWebView(HIViewRef *viewref)
{
	InitWebKit();
	// Now associate a right HICocoaView to the viewref
//	WebView *MulberryCocoaView=[[WebView alloc] init];
//	HICocoaViewCreate (MulberryCocoaView, 0, viewref);
	return HIWebViewCreate(viewref);	
}

void URLToWebView(HIViewRef inView, CFURLRef inURL)
{
	WebView*		nativeView;
    NSURLRequest*	request;
    WebFrame* 		mainFrame;
	
	nativeView = HIWebViewGetWebView( inView );
	request = [NSURLRequest requestWithURL:(NSURL*)inURL];
	mainFrame = [nativeView mainFrame];
	[mainFrame loadRequest:request];
}

void DataToWebView(HIViewRef inView, CFStringRef inData)
{
	WebView*		nativeView;
    WebFrame* 		mainFrame;
	
	FILE *filehtml;
	
	if(debug>0)
		printf("CWebKitUtils->DataToWebView\n");
	
	char *filename ="/tmp/page_html.tmp";
	
	if((filehtml=fopen(filename, "w"))==NULL && debug > 10) {
			printf("Error opening file %s\n", filename);
	} else if (debug>10) {
		printf("Writing the message content to file %s\n", filename);
		
		const char *cstring=[(NSString *) inData UTF8String];
		unsigned n,i;
		
		i=CFStringGetLength(inData);
		printf("Writing the message content - %d bytes - to file %s\n", i, filename);
		
		for (n=0;n<i; n++)
			fputc((int) cstring[n], filehtml);
		

		fclose(filehtml);
		
	}
	
	
	nativeView = HIWebViewGetWebView( inView );
	mainFrame = [nativeView mainFrame];
	[mainFrame loadHTMLString:(NSString*)inData baseURL:nil];
}

void DoWKClick(HIViewRef inView,  CGFloat x, CGFloat y)
{
   WebView*		nativeView;
	NSPoint		where;
	
	where.x=x;
	where.y=y;
	
	NSGraphicsContext *context = [NSGraphicsContext currentContext];
	NSEvent* mouseDownEvent = [NSEvent mouseEventWithType:NSLeftMouseDown location:where modifierFlags:(int) nil timestamp:GetCurrentEventTime() windowNumber: 0 context:context eventNumber:(int) nil clickCount:1 pressure:(int)nil];
	NSEvent* mouseUpEvent = [NSEvent mouseEventWithType:NSLeftMouseUp location:where modifierFlags:(int) nil timestamp:GetCurrentEventTime() windowNumber: 0 context:context eventNumber:(int)nil clickCount:1 pressure:(int)nil];
	
	
	//if the mouse is in an active area then just perform the default operation
	    nativeView = HIWebViewGetWebView( inView );
	    NSView * subView=[nativeView hitTest: [mouseUpEvent locationInWindow]];
	if(subView) {
		[subView mouseDown: mouseDownEvent];
		[subView mouseUp: mouseUpEvent];
	} else {
		NSLog(@"hitTest returned nil");
		if(debug==1)
			printf("hitTest returned nil");
	
	}
}

