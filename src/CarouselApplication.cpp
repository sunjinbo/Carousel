/*
 ============================================================================
 Name		: CarouselApplication.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "Carousel.hrh"
#include "CarouselDocument.h"
#include "CarouselApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCarouselApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CCarouselApplication::CreateDocumentL()
    {
    // Create an Carousel document, and return a pointer to it
    return CCarouselDocument::NewL(*this);
    }

// -----------------------------------------------------------------------------
// CCarouselApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CCarouselApplication::AppDllUid() const
    {
    // Return the UID for the Carousel application
    return KUidCarouselApp;
    }

// End of File
