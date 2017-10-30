/*
 ============================================================================
 Name		: CarouselApplication.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __CAROUSELAPPLICATION_H__
#define __CAROUSELAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "Carousel.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidCarouselApp =
    {
    _UID3
    };

// CLASS DECLARATION

/**
 * CCarouselApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CCarouselApplication is the application part of the
 * AVKON application framework for the Carousel example application.
 */
class CCarouselApplication : public CAknApplication
    {
public:
    // Functions from base classes

    /**
     * From CApaApplication, AppDllUid.
     * @return Application's UID (KUidCarouselApp).
     */
    TUid AppDllUid() const;

protected:
    // Functions from base classes

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CCarouselDocument document object. The returned
     * pointer in not owned by the CCarouselApplication object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();
    };

#endif // __CAROUSELAPPLICATION_H__
// End of File
