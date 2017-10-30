/*
 ============================================================================
 Name		: CarouselDocument.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __CAROUSELDOCUMENT_h__
#define __CAROUSELDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CCarouselAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CCarouselDocument application class.
 * An instance of class CCarouselDocument is the Document part of the
 * AVKON application framework for the Carousel example application.
 */
class CCarouselDocument : public CAknDocument
    {
public:
    // Constructors and destructor

    /**
     * NewL.
     * Two-phased constructor.
     * Construct a CCarouselDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CCarouselDocument.
     */
    static CCarouselDocument* NewL(CEikApplication& aApp);

    /**
     * NewLC.
     * Two-phased constructor.
     * Construct a CCarouselDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CCarouselDocument.
     */
    static CCarouselDocument* NewLC(CEikApplication& aApp);

    /**
     * ~CCarouselDocument
     * Virtual Destructor.
     */
    virtual ~CCarouselDocument();

public:
    // Functions from base classes

    /**
     * CreateAppUiL
     * From CEikDocument, CreateAppUiL.
     * Create a CCarouselAppUi object and return a pointer to it.
     * The object returned is owned by the Uikon framework.
     * @return Pointer to created instance of AppUi.
     */
    CEikAppUi* CreateAppUiL();

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CCarouselDocument.
     * C++ default constructor.
     * @param aApp Application creating this document.
     */
    CCarouselDocument(CEikApplication& aApp);

    };

#endif // __CAROUSELDOCUMENT_h__
// End of File
