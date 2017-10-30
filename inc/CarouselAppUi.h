/*
 ============================================================================
 Name		: CarouselAppUi.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __CAROUSELAPPUI_h__
#define __CAROUSELAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CCarouselAppView;

// CLASS DECLARATION
/**
 * CCarouselAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CCarouselAppUi : public CAknAppUi
    {
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CCarouselAppUi.
     * C++ default constructor. This needs to be public due to
     * the way the framework constructs the AppUi
     */
    CCarouselAppUi();

    /**
     * ~CCarouselAppUi.
     * Virtual Destructor.
     */
    virtual ~CCarouselAppUi();

private:
    // Functions from base classes

    /**
     * From CEikAppUi, HandleCommandL.
     * Takes care of command handling.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL(TInt aCommand);

    /**
     *  HandleResourceChangeL.
     *  Called by the framework when the application status pane
     *  size is changed.
     */
    void HandleResourceChangeL( TInt aType );

private:
    // Data

    /**
     * The application view
     * Owned by CCarouselAppUi
     */
    CCarouselAppView* iAppView;

    };

#endif // __CAROUSELAPPUI_h__
// End of File
