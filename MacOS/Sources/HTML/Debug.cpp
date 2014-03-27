/*
 *  Debug.cpp
 *  MulberryXcode
 *
 *  Created by gpreviato on 4/22/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Debug.h"

#define	DEBUG_BASIC		1
#define	DEBUG_EVENTS	99

int debug=DEBUG_EVENTS;

// ---------------------------------------------------------------------------
//	• MyDebug						 Constructor		  [public]
// ---------------------------------------------------------------------------
//	Do not access inStream. It may be nil. Read Stream data in Init()

MyDebug::MyDebug()
{
}


// ---------------------------------------------------------------------------
//	• ~MyDebug						Destructor				  [public]
// ---------------------------------------------------------------------------

MyDebug::~MyDebug()
{
}

void MyDebug::_Log(char * message)
{
	if (debug>0)
		printf("%s", message);
	
}
