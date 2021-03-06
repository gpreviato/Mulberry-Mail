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


// Source for CAddressPaneOptions class

#include "CAddressPaneOptions.h"

#include "CAddressViewOptions.h"
#include "CDivider.h"
#include "CUserActionOptions.h"

#include <JXColormap.h>
#include <JXStaticText.h>
#include <JXTextCheckbox.h>
#include <JXUpRect.h>

#include <cassert>

// Static members

// Do various bits
void CAddressPaneOptions::OnCreate()
{
// begin JXLayout1

    mListPreview1 =
        new CUserActionOptions(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 0,40, 200,120);
    assert( mListPreview1 != NULL );

    JXUpRect* obj1 =
        new JXUpRect(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 0,0, 200,25);
    assert( obj1 != NULL );

    JXStaticText* obj2 =
        new JXStaticText("Address Book Manager Pane", obj1,
                    JXWidget::kHElastic, JXWidget::kVElastic, 5,5, 158,15);
    assert( obj2 != NULL );
    obj2->SetFontSize(10);
    const JFontStyle obj2_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj2->SetFontStyle(obj2_style);

    JXStaticText* obj3 =
        new JXStaticText("To Preview an Address Book", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 5,25, 155,15);
    assert( obj3 != NULL );
    obj3->SetFontSize(10);
    const JFontStyle obj3_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj3->SetFontStyle(obj3_style);

    CDivider* obj4 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 160,30, 35,2);
    assert( obj4 != NULL );

    mListFullView1 =
        new CUserActionOptions(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 0,180, 200,120);
    assert( mListFullView1 != NULL );

    JXStaticText* obj5 =
        new JXStaticText("To Open an Address Book", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 5,165, 175,15);
    assert( obj5 != NULL );
    obj5->SetFontSize(10);
    const JFontStyle obj5_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj5->SetFontStyle(obj5_style);

    CDivider* obj6 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 180,170, 15,2);
    assert( obj6 != NULL );

    mItemsPreview1 =
        new CUserActionOptions(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 200,40, 200,120);
    assert( mItemsPreview1 != NULL );

    JXUpRect* obj7 =
        new JXUpRect(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 200,0, 200,25);
    assert( obj7 != NULL );

    JXStaticText* obj8 =
        new JXStaticText("Address Book Pane", obj7,
                    JXWidget::kHElastic, JXWidget::kVElastic, 5,5, 148,15);
    assert( obj8 != NULL );
    obj8->SetFontSize(10);
    const JFontStyle obj8_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj8->SetFontStyle(obj8_style);

    JXStaticText* obj9 =
        new JXStaticText("To Preview an Address", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 205,25, 160,15);
    assert( obj9 != NULL );
    obj9->SetFontSize(10);
    const JFontStyle obj9_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj9->SetFontStyle(obj9_style);

    CDivider* obj10 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 365,30, 30,2);
    assert( obj10 != NULL );

    mItemsFullView1 =
        new CUserActionOptions(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 200,180, 200,120);
    assert( mItemsFullView1 != NULL );

    JXStaticText* obj11 =
        new JXStaticText("To Open an Address", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 205,165, 150,15);
    assert( obj11 != NULL );
    obj11->SetFontSize(10);
    const JFontStyle obj11_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj11->SetFontStyle(obj11_style);

    CDivider* obj12 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 350,170, 45,2);
    assert( obj12 != NULL );

    JXUpRect* obj13 =
        new JXUpRect(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 400,0, 200,25);
    assert( obj13 != NULL );

    JXStaticText* obj14 =
        new JXStaticText("Address Preview", obj13,
                    JXWidget::kHElastic, JXWidget::kVElastic, 5,5, 148,15);
    assert( obj14 != NULL );
    obj14->SetFontSize(10);
    const JFontStyle obj14_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj14->SetFontStyle(obj14_style);

    JXStaticText* obj15 =
        new JXStaticText("Preview Options", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 405,25, 110,15);
    assert( obj15 != NULL );
    obj15->SetFontSize(10);
    const JFontStyle obj15_style(kTrue, kFalse, 0, kFalse, (GetColormap())->GetBlackColor());
    obj15->SetFontStyle(obj15_style);

    CDivider* obj16 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 515,30, 80,2);
    assert( obj16 != NULL );

    mAddressSelect =
        new JXTextCheckbox("Select when Previewed", this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 405,40, 180,20);
    assert( mAddressSelect != NULL );

    CDivider* obj17 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 200,30, 2,335);
    assert( obj17 != NULL );

    CDivider* obj18 =
        new CDivider(this,
                    JXWidget::kHElastic, JXWidget::kVElastic, 400,30, 2,335);
    assert( obj18 != NULL );

// end JXLayout1

    mListPreview1->OnCreate();
    mListFullView1->OnCreate();
    mItemsPreview1->OnCreate();
    mItemsFullView1->OnCreate();

    mListPreview = mListPreview1;
    mListFullView = mListFullView1;
    mItemsPreview = mItemsPreview1;
    mItemsFullView = mItemsFullView1;
}

void CAddressPaneOptions::SetData(const CUserAction& listPreview,
									const CUserAction& listFullView,
									const CUserAction& itemsPreview,
									const CUserAction& itemsFullView,
									const CAddressViewOptions& options,
									bool is3pane)
{
	SetCommonViewData(listPreview, listFullView, itemsPreview, itemsFullView, is3pane);

	mAddressSelect->SetState(JBoolean(options.GetSelectAddressPane()));
}

void CAddressPaneOptions::GetData(CUserAction& listPreview,
									CUserAction& listFullView,
									CUserAction& itemsPreview,
									CUserAction& itemsFullView,
									CAddressViewOptions& options)
{
	GetCommonViewData(listPreview, listFullView, itemsPreview, itemsFullView);

	options.SetSelectAddressPane(mAddressSelect->IsChecked());
}
