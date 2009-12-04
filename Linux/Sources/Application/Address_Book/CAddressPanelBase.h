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


// Header for CAddressPanelBase class

#ifndef __CADDRESSPANELBASE__MULBERRY__
#define __CADDRESSPANELBASE__MULBERRY__

#include "CTabPanel.h"

#include <vector>

// Classes
class CAdbkAddress;

class CAddressPanelBase : public CTabPanel
{
public:
				CAddressPanelBase(JXContainer* enclosure,
							 const HSizingOption hSizing, const VSizingOption vSizing,
							 const JCoordinate x, const JCoordinate y,
							 const JCoordinate w, const JCoordinate h);
	virtual 	~CAddressPanelBase();

	virtual void	SetData(void* data);				// Set data
	virtual bool	UpdateData(void* data);				// Force update of data

	virtual void	Focus() = 0;

protected:
	CAdbkAddress* mAddress;

	virtual void	SetFields(const CAdbkAddress* addr) = 0;	// Set fields in dialog
	virtual bool	GetFields(CAdbkAddress* addr) = 0;			// Get fields from dialog
};

typedef std::vector<CAddressPanelBase*> CAddressPanelList;

#endif