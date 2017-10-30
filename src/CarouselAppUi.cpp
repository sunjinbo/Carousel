/*
 ============================================================================
 Name		: CarouselAppUi.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : CCarouselAppUi implementation
 ============================================================================
 */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>

#include <carousel_0xe3732b5d.rsg>
#include "Carousel.hrh"
#include "Carousel.pan"
#include "CarouselApplication.h"
#include "CarouselAppUi.h"
#include "CarouselAppView.h"


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CCarouselAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCarouselAppUi::ConstructL()
    {
    // Initialise app UI with standard value.
    BaseConstructL(CAknAppUi::EAknEnableSkin);

    // Create view object
    iAppView = CCarouselAppView::NewL(ClientRect());

    AddToStackL(iAppView);
    }

// -----------------------------------------------------------------------------
// CCarouselAppUi::CCarouselAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCarouselAppUi::CCarouselAppUi()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CCarouselAppUi::~CCarouselAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CCarouselAppUi::~CCarouselAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack( iAppView );
        delete iAppView;
        iAppView = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CCarouselAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CCarouselAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;
        case EAbout:
            {
            CAknMessageQueryDialog* dlg =
                    new (ELeave) CAknMessageQueryDialog();
            dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
            HBufC* title = iEikonEnv->AllocReadResourceLC(
                    R_ABOUT_DIALOG_TITLE);
            dlg->QueryHeading()->SetTextL(*title);
            CleanupStack::PopAndDestroy(); //title
            HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
            dlg->SetMessageTextL(*msg);
            CleanupStack::PopAndDestroy(); //msg
            dlg->RunLD();
            }
            break;
        default:
            Panic( ECarouselUi);
            break;
        }
    }

// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CCarouselAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknAppUi::HandleResourceChangeL( aType );
    iAppView->SetRect( ClientRect() );
    }

// End of File
