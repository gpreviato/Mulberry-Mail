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


// Source for CBaseView class

#include "CBaseView.h"

#include "C3PaneWindow.h"

// __________________________________________________________________________________________________
// C L A S S __ C M A I L B O X W I N D O W
// __________________________________________________________________________________________________

BEGIN_MESSAGE_MAP(CBaseView, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// C O N S T R U C T I O N / D E S T R U C T I O N  M E T H O D S

// Default constructor
CBaseView::CBaseView()
{
	mOwnerWindow = NULL;
	mIs3Pane = false;
}

// Default destructor
CBaseView::~CBaseView()
{
}

// O T H E R  M E T H O D S ____________________________________________________________________________

int CBaseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set initial size for control repositioner
	InitResize(lpCreateStruct->cx, lpCreateStruct->cy);

	// Get window that owns this one
	CWnd* super = GetParent();
	while(super && !dynamic_cast<CView*>(super))
		super = super->GetParent();

	mOwnerWindow = super;
	mIs3Pane = (mOwnerWindow == C3PaneWindow::s3PaneWindow);

	return 0;
}

// Resize sub-views
void CBaseView::OnSize(UINT nType, int cx, int cy)
{
	// Do inherited
	CWnd::OnSize(nType, cx, cy);

	// Resize child windows
	SizeChanged(cx, cy);
}

// Check that close is allowed
bool CBaseView::TestClose()
{
	// Always allowed to close
	return true;
}

// Close it
void CBaseView::DoClose()
{
	// Set status
	SetClosing();

	// Add info to prefs (must do while mbox open)
	SaveState();

	// Set status
	SetClosed();
}

void CBaseView::RefreshToolbar() const
{
	// Broadcast selection change to force toolbar refresh
	Broadcast_Message(eBroadcast_ViewSelectionChanged, (void*) this);
}
