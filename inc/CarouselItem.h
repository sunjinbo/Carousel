/*
 ============================================================================
 Name		: CarouselItem.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCarouselItem declaration
 ============================================================================
 */

#ifndef CAROUSELITEM_H
#define CAROUSELITEM_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "CarouselUtils.h"

// CLASS DECLARATION
class CFbsBitGc;
class MOrbitInterface;

/**
 *  CCarouselItem
 * 
 */
class CCarouselItem : public CBase
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    ~CCarouselItem();

    /**
     * Two-phased constructor.
     */
    static CCarouselItem* NewL( 
            CFbsBitGc*& aGc, 
            MOrbitInterface& aOrbitInterface
            );

    /**
     * Two-phased constructor.
     */
    static CCarouselItem* NewLC( 
            CFbsBitGc*& aGc, 
            MOrbitInterface& aOrbitInterface
            );

public:
    // New functions
    void Draw();
    void Move();
    void SetOrbitIndex( TInt aOrbitIndex );
    void SetClockwise( TWise aClockwise );
    void SetColor( const TRgb& aColor );
    static TInt Compare( const CCarouselItem& aFirst, const CCarouselItem& aSecond );

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CCarouselItem( 
            CFbsBitGc*& aGc, 
            MOrbitInterface& aOrbitInterface
            );

    /**
     * EPOC default constructor for performing 2nd stage construction
     */
    void ConstructL();

private:
    // New functions
    void SetCenter( const TPoint& aCenterPos );

private:
    // Member data
    CFbsBitGc*& iBmpContext; // Not own
    MOrbitInterface& iOrbitInterface;
    TWise iClockwise;
    TInt iOrbitIndex;
    TInt iY;
    TRect iCarouselItemRect;
    TInt iOpacity;
    TRgb iColor;
    };

#endif // CAROUSELITEM_H
