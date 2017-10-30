/*
 ============================================================================
 Name		: CarouselItem.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCarouselItem implementation
 ============================================================================
 */

#include <bitstd.h>
#include "CarouselItem.h"
#include "OrbitInterface.h"

// CONSTANTS
const TInt KMaxOpacity = 255;
const TInt KBaseOpacity = 150;
const TInt KItemWidth = 28;
const TInt KItemHeight = 36;
const TInt KItemWidthGrow = KItemWidth * 0.6; // KItemWidth * 60%
const TInt KItemHeightGrow = KItemHeight * 0.6; // KItemHeight * 60%

CCarouselItem::CCarouselItem( CFbsBitGc*& aGc, MOrbitInterface& aOrbitInterface )
: iBmpContext( aGc ), iOrbitInterface( aOrbitInterface ), iClockwise( EClockwise )
    {
    // No implementation required
    }

CCarouselItem::~CCarouselItem()
    {
    }

CCarouselItem* CCarouselItem::NewLC( 
        CFbsBitGc*& aGc, 
        MOrbitInterface& aOrbitInterface )
    {
    CCarouselItem* self = new (ELeave) CCarouselItem( aGc, aOrbitInterface );
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CCarouselItem* CCarouselItem::NewL( 
        CFbsBitGc*& aGc, 
        MOrbitInterface& aOrbitInterface )
    {
    CCarouselItem* self = CCarouselItem::NewLC( aGc, aOrbitInterface );
    CleanupStack::Pop(); // self;
    return self;
    }

void CCarouselItem::Draw()
    {
    TRgb color( iColor );
    color.SetAlpha( iOpacity );
    TRgb borderColor( KRgbWhite );
    borderColor.SetAlpha( iOpacity );
    iBmpContext->SetPenStyle( CGraphicsContext::ESolidPen );
    iBmpContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBmpContext->SetPenColor( borderColor );
    iBmpContext->SetBrushColor( color );
    iBmpContext->DrawRect( iCarouselItemRect );
    }

void CCarouselItem::Move()
    {
    if ( iClockwise != EClockwise )
        {
        ( iOrbitIndex + 1 == iOrbitInterface.OrbitPointCount() ) ? iOrbitIndex = 0 : ++iOrbitIndex;
        }
    else
        {
        ( iOrbitIndex == 0 ) ? iOrbitIndex = iOrbitInterface.OrbitPointCount() - 1 : --iOrbitIndex;
        }
    TOrbitPoint orbitPoint = iOrbitInterface.OrbitPoint( iOrbitIndex );
    iY = orbitPoint.iPosition.iY;
    iOpacity = orbitPoint.iScaleFactor * ( KMaxOpacity - KBaseOpacity ) + KBaseOpacity;
    TInt width = KItemWidth + KItemWidthGrow * orbitPoint.iScaleFactor;
    TInt height = KItemHeight + KItemHeightGrow * orbitPoint.iScaleFactor;
    iCarouselItemRect.SetSize( TSize( width, height ) );
    SetCenter( orbitPoint.iPosition );
    }

void CCarouselItem::SetOrbitIndex( TInt aOrbitIndex )
    {
    iOrbitIndex = aOrbitIndex;
    }

void CCarouselItem::SetClockwise( TWise aClockwise )
    {
    iClockwise = aClockwise;
    }

void CCarouselItem::SetColor( const TRgb& aColor )
    {
    iColor = aColor;
    }

TInt CCarouselItem::Compare( const CCarouselItem& aFirst, const CCarouselItem& aSecond )
    {
    if ( aFirst.iY > aSecond.iY )
        return 1; 
    if ( aFirst.iY < aSecond.iY )
        return -1;
    return 0;
    }

void CCarouselItem::ConstructL()
    {
    iCarouselItemRect.SetSize( TSize( KItemWidth, KItemHeight ) );
    }

void CCarouselItem::SetCenter( const TPoint& aCenterPos )
    {
    TPoint tl;
    tl.iX = aCenterPos.iX - iCarouselItemRect.Width() / 2;
    tl.iY = aCenterPos.iY - iCarouselItemRect.Height() / 2;
    iCarouselItemRect.SetRect( tl, iCarouselItemRect.Size() );
    }
