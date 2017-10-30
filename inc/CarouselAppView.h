/*
 ============================================================================
 Name		: CarouselAppView.h
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __CAROUSELAPPVIEW_h__
#define __CAROUSELAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>
#include "CarouselSceneObserver.h"
#include "CarouselUtils.h"

// FORWARD DECLARATIONS
class CCarouselScene;

// CLASS DECLARATION
class CCarouselAppView : public CCoeControl, public MCarouselSceneObserver
    {
public:
    // New methods

    /**
     * NewL.
     * Two-phased constructor.
     * Create a CCarouselAppView object, which will draw itself to aRect.
     * @param aRect The rectangle this view will be drawn to.
     * @return a pointer to the created instance of CCarouselAppView.
     */
    static CCarouselAppView* NewL(const TRect& aRect);

    /**
     * NewLC.
     * Two-phased constructor.
     * Create a CCarouselAppView object, which will draw itself
     * to aRect.
     * @param aRect Rectangle this view will be drawn to.
     * @return A pointer to the created instance of CCarouselAppView.
     */
    static CCarouselAppView* NewLC(const TRect& aRect);

    /**
     * ~CCarouselAppView
     * Virtual Destructor.
     */
    virtual ~CCarouselAppView();

public:
    // Functions from base classes

    /**
     * From CoeControl, SizeChanged.
     * Called by framework when the view size is changed.
     */
    virtual void SizeChanged();

    /**
     * From CoeControl, HandlePointerEventL.
     * Called by framework when a pointer touch event occurs.
     * Note: although this method is compatible with earlier SDKs, 
     * it will not be called in SDKs without Touch support.
     * @param aPointerEvent the information about this event
     */
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    virtual void HandleResourceChange( TInt aType );

private:
    // Function from MCarouselSceneObserver
    void StateChanged( TInt aNewState );

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     * Perform the second phase construction of a
     * CCarouselAppView object.
     * @param aRect The rectangle this view will be drawn to.
     */
    void ConstructL(const TRect& aRect);

    /**
     * CCarouselAppView.
     * C++ default constructor.
     */
    CCarouselAppView();

private: 
    // New functions
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    static TInt TimerCallback( TAny* aPtr );
    void Stop();
    void DoFrame();
    void DoDraw();
    void CalcOrbitRect( TRect& aOrbitRect );
    void HandleDirectionEventL( TDirection aDirection );

private:
    // Memeber data
    CCarouselScene* iScene; // owned
    CFbsBitmap* iBitmap; // owned
    CFbsBitmapDevice* iBitmapDevice; // owned
    CFbsBitGc* iBitmapGc; // owned
    CPeriodic* iPeriodic; // owned
    TRect iOrbitRect;
    TPoint iStartPoint;
    TBool iKeyLongPressed;
    TInt iDragCount;
    };

#endif // __CAROUSELAPPVIEW_h__

// End of File
