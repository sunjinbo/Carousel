/*
 ============================================================================
 Name		: CarouselDocument.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : CCarouselDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "CarouselAppUi.h"
#include "CarouselDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCarouselDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCarouselDocument* CCarouselDocument::NewL(CEikApplication& aApp)
    {
    CCarouselDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CCarouselDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCarouselDocument* CCarouselDocument::NewLC(CEikApplication& aApp)
    {
    CCarouselDocument* self = new (ELeave) CCarouselDocument(aApp);

    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CCarouselDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCarouselDocument::ConstructL()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CCarouselDocument::CCarouselDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCarouselDocument::CCarouselDocument(CEikApplication& aApp) :
    CAknDocument(aApp)
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CCarouselDocument::~CCarouselDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CCarouselDocument::~CCarouselDocument()
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CCarouselDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CCarouselDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it;
    // the framework takes ownership of this object
    return new (ELeave) CCarouselAppUi;
    }

// End of File
