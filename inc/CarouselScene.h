/*
 ============================================================================
 Name		: CarouselScene.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCarouselScene declaration
 ============================================================================
 */

#ifndef CCAROUSELSCENE_H
#define CCAROUSELSCENE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "OrbitInterface.h"
#include "CarouselUtils.h"

// FORWARD DECLARATIONS
class MCarouselSceneObserver;
class CFbsBitGc;
class CCarouselItem;

// CLASS DECLARATION

/**
 *  CCarouselScene
 * 
 */
class CCarouselScene : public CBase, public MOrbitInterface
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CCarouselScene();

    /**
     * Two-phased constructor.
     */
    static CCarouselScene* NewL( 
            MCarouselSceneObserver& aObserver, 
            CFbsBitGc*& aGc,
            const TRect& aOrbitRect
            );

    /**
     * Two-phased constructor.
     */
    static CCarouselScene* NewLC( 
            MCarouselSceneObserver& aObserver, 
            CFbsBitGc*& aGc,
            const TRect& aOrbitRect
            );

public:
    // New functions
    void Draw();
    void SetOrbitRect( const TRect& aOrbitRect );
    void AccelerateL( TWise aClockwise );

private:
    // from MOrbitInterface class
    const TOrbitPoint& OrbitPoint( TInt aOrbitIndex ) const;
    TInt OrbitPointCount() const;

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CCarouselScene( 
            MCarouselSceneObserver& aObserver, 
            CFbsBitGc*& aGc,
            const TRect& aOrbitRect
            );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // New functions
    static TInt TimerCallback( TAny* aPtr );
    static TInt AccelerateCallback( TAny* aPtr );
    void Stop();
    void DoMove();
    void DoAccelerate();
    TReal Cos( TReal aSrc ) const;
    TReal Sin( TReal aSrc ) const;
    TReal Mod( TReal aSrc, const TReal &aModulus ) const;
    void InitializeOrbit();
    void InitializeCarouselItemL();
    TInt Rand( TInt aRange ) const;
    void Sort();

private:
    // Member data
    MCarouselSceneObserver& iObserver;
    CFbsBitGc*& iBmpContext; // not owned
    CPeriodic* iPeriodic; // owned.
    CPeriodic* iAccelerateTimer; // owned.
    RPointerArray<CCarouselItem> iCarouselItemList;
    RArray<TOrbitPoint> iOrbitPointList;
    TRect iOrbitRect;
    TInt iAccelerateFactor;
    };

#endif // CCAROUSELSCENE_H
