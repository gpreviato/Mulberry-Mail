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


// Header for C3PaneMailAccount class

#ifndef __C3PANEMAILACCOUNT__MULBERRY__
#define __C3PANEMAILACCOUNT__MULBERRY__

#include "C3PaneViewPanel.h"

// Classes
class CServerView;

class C3PaneMailAccount : public C3PaneViewPanel
{
public:
					C3PaneMailAccount(JXContainer* enclosure,
								const HSizingOption hSizing, const VSizingOption vSizing,
								const JCoordinate x, const JCoordinate y,
								const JCoordinate w, const JCoordinate h);
	virtual 		~C3PaneMailAccount();

	virtual void	OnCreate();

	virtual CBaseView*	GetBaseView() const;
	CServerView*	GetServerView() const
		{ return mServerView; }

protected:
	CServerView*	mServerView;
};

#endif
