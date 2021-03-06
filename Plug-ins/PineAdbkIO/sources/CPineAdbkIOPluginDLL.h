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

// CPineAdbkIOPluginDLL.h
//
// Copyright 2006, Cyrus Daboo.  All Rights Reserved.
//
// Created: 13-Jan-1998
// Author: Cyrus Daboo
// Platforms: Mac OS, Win32
//
// Description:
// This class implements Pine addressbook import DLL based plug-in for use in Mulberry.
//
// History:
// 13-Jan-1998: Created initial header and implementation.
//

#ifndef __PINEADBKIO_PLUGIN_MULBERRY__
#define __PINEADBKIO_PLUGIN_MULBERRY__

#include "CAdbkIOPluginDLL.h"

// Classes
class CPineAdbkIOPluginDLL : public CAdbkIOPluginDLL
{
public:

	// Actual plug-in class

	CPineAdbkIOPluginDLL();
	virtual ~CPineAdbkIOPluginDLL();
	
	// Entry codes
	virtual void	Initialise(void);					// Initialisation
	virtual bool	CanRun(void);						// Test whether plug-in can run

	// Registration
	virtual bool UseRegistration(unsigned long* key);	// Does plug-in need to be registered
	virtual bool CanDemo(void);							// Can plug-in run as demo

	// Entry codes
	virtual long	ExportAddress(SAdbkIOPluginAddress* addr);	// Export an address
	virtual long	ExportGroup(SAdbkIOPluginGroup* grp);		// Export a group

protected:
	// These should be returned by specific sub-class
	virtual const char* GetName(void) const;			// Returns the name of the plug-in
	virtual long GetVersion(void) const;				// Returns the version number of the plug-in
	virtual EPluginType GetType(void) const;			// Returns the type of the plug-in
	virtual const char* GetManufacturer(void) const;	// Returns manufacturer of plug-in
	virtual const char* GetDescription(void) const;		// Returns description of plug-in

	virtual long	ImportAddresses(char* data);			// Do the actual import - pure virtual - must do in subclass
	
private:
	virtual void	UnfoldLines(char* text);				// RFC822 unfold lines
	virtual char	SkipTerm(char** txt);					// Skip chars for termination
};

#endif
