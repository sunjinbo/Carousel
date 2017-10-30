/*
 ============================================================================
 Name		: CarouselScene.cpp
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCarouselScene implementation
 ============================================================================
 */

#include <e32math.h>
#include <bitstd.h>
#include "CarouselScene.h"
#include "CarouselSceneObserver.h"
#include "CarouselItem.h"

// CONSTANTS
const TReal KPI = 3.1415926;
const TInt KSetps = 144;
const TInt KAngle = 360;
const TInt KMaxItemNumber = 16;
const TInt KMaxPigment = 255;
const TInt KDelayTimeout = 0;
const TInt KFrameUpdateTimeout = 50000;
const TInt KAccelerateDelay = 0;
const TInt KAccelerateTimeout = 200000;
const TInt KDefaultAccelerateFactor = 1;
const TInt KFastAccelerateFactor = 6;

// ----------------------------------------------------------------------------
// CCarouselScene::CCarouselScene
// ----------------------------------------------------------------------------
//
CCarouselScene::CCarouselScene( 
 MCarouselSceneObserver& aObserver, CFbsBitGc*& aGc, const TRect& aOrbitRect )
: iObserver( aObserver ), 
    iBmpContext( aGc ), 
    iOrbitRect( aOrbitRect ), 
    iAccelerateFactor( KDefaultAccelerateFactor )
    {
    // No implementation required
    }

// ----------------------------------------------------------------------------
// CCarouselScene::~CCarouselScene
// ----------------------------------------------------------------------------
//
CCarouselScene::~CCarouselScene()
    {
    Stop(); // iPeriodic
    iCarouselItemList.ResetAndDestroy();
    iCarouselItemList.Close();
    iOrbitPointList.Close();
    }

// ----------------------------------------------------------------------------
// CCarouselScene::NewLC
// ----------------------------------------------------------------------------
//
CCarouselScene* CCarouselScene::NewLC( 
        MCarouselSceneObserver& aObserver, 
        CFbsBitGc*& aGc,
        const TRect& aOrbitRect )
    {
    CCarouselScene* self 
        = new (ELeave) CCarouselScene( aObserver, aGc, aOrbitRect );
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::NewL
// ----------------------------------------------------------------------------
//
CCarouselScene* CCarouselScene::NewL( 
        MCarouselSceneObserver& aObserver, 
        CFbsBitGc*& aGc,
        const TRect& aOrbitRect )
    {
    CCarouselScene* self 
        = CCarouselScene::NewLC( aObserver, aGc, aOrbitRect );
    CleanupStack::Pop(); // self;
    return self;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::ConstructL
// ----------------------------------------------------------------------------
//
void CCarouselScene::ConstructL()
    {
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                KDelayTimeout,
                KFrameUpdateTimeout,
                TCallBack( TimerCallback, this ) );

    InitializeOrbit();
    InitializeCarouselItemL();
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Draw
// ----------------------------------------------------------------------------
//
void CCarouselScene::Draw()
    {
    Sort();

    for ( TInt i = 0; i < iCarouselItemList.Count(); i++ )
        {
        iCarouselItemList[i]->Draw();
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::SetOrbitRect
// ----------------------------------------------------------------------------
//
void CCarouselScene::SetOrbitRect( const TRect& aOrbitRect )
    {
    iOrbitRect = aOrbitRect;
    InitializeOrbit();
    }

// ----------------------------------------------------------------------------
// CCarouselScene::AccelerateL
// ----------------------------------------------------------------------------
//
void CCarouselScene::AccelerateL( TWise aClockwise )
    {
    if ( !iAccelerateTimer )
        {
        iAccelerateTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        iAccelerateTimer->Cancel();
        iAccelerateTimer->Start(
                    KAccelerateDelay,
                    KAccelerateTimeout,
                    TCallBack( AccelerateCallback, this ) );
        }

    iAccelerateFactor = KFastAccelerateFactor;

    for ( TInt i = 0; i < iCarouselItemList.Count(); i++ )
        {
        iCarouselItemList[i]->SetClockwise( aClockwise );
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::OrbitPoint
// ----------------------------------------------------------------------------
//
const TOrbitPoint& CCarouselScene::OrbitPoint( TInt aOrbitIndex ) const
    {
    TInt index = Mod( Abs( aOrbitIndex ), iOrbitPointList.Count() );
    return iOrbitPointList[index];
    }

// ----------------------------------------------------------------------------
// CCarouselScene::OrbitPointCount
// ----------------------------------------------------------------------------
//
TInt CCarouselScene::OrbitPointCount() const
    {
    return iOrbitPointList.Count();
    }

// ----------------------------------------------------------------------------
// CCarouselScene::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CCarouselScene::TimerCallback( TAny* aPtr )
    {
    CCarouselScene* self = static_cast<CCarouselScene*> ( aPtr );
    self->DoMove();
    return 0;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::AccelerateCallback
// ----------------------------------------------------------------------------
//
TInt CCarouselScene::AccelerateCallback( TAny* aPtr )
    {
    CCarouselScene* self = static_cast<CCarouselScene*> ( aPtr );
    self->DoAccelerate();
    return 0;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Stop
// ----------------------------------------------------------------------------
//
void CCarouselScene::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    if ( iAccelerateTimer )
        {  
        iAccelerateTimer->Cancel();
        delete iAccelerateTimer;
        iAccelerateTimer = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::DoMove
// ----------------------------------------------------------------------------
//
void CCarouselScene::DoMove()
    {
    for ( TInt i = 0; i < iCarouselItemList.Count(); i++ )
        {
        for ( TInt j = 0; j < iAccelerateFactor; j++ )
            {
            iCarouselItemList[i]->Move();
            }
        }

    iObserver.StateChanged( ECarouselSceneUpdated );
    }

// ----------------------------------------------------------------------------
// CCarouselScene::DoAccelerate
// ----------------------------------------------------------------------------
//
void CCarouselScene::DoAccelerate()
    {
    if ( --iAccelerateFactor == KDefaultAccelerateFactor )
        {
        iAccelerateTimer->Cancel();
        delete iAccelerateTimer;
        iAccelerateTimer = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Cos
// ----------------------------------------------------------------------------
//
TReal CCarouselScene::Cos( TReal aSrc ) const
    {
    TReal trg = 0.0;
    Math::Cos( trg, aSrc );
    return trg;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Sin
// ----------------------------------------------------------------------------
//
TReal CCarouselScene::Sin( TReal aSrc ) const
    {
    TReal trg = 0.0;;
    Math::Sin( trg, aSrc );
    return trg;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Mod
// ----------------------------------------------------------------------------
//
TReal CCarouselScene::Mod( TReal aSrc, const TReal &aModulus ) const
    {
    TReal trg = 0.0;;
    Math::Mod( trg, aSrc, aModulus );
    return trg;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::InitializeOrbit
// ----------------------------------------------------------------------------
//
void CCarouselScene::InitializeOrbit()
    {
    // Remove all orbit points from the list first.
    iOrbitPointList.Reset();

    TReal a = iOrbitRect.Width() / 2;
    TReal b = iOrbitRect.Height() / 2;

    // Angle is given by degree value
    TReal beta = -KAngle * ( KPI / 180 ); // Converts degree value into radians
    TReal sinbeta = Sin( beta );
    TReal cosbeta = Cos( beta );
    
    for ( TInt i = 0; i < 360; i += 360 / KSetps )
        {
        TReal alpha = i * ( KPI / 180 );
        TReal sinalpha = Sin( alpha );
        TReal cosalpha = Cos( alpha );
        
        TOrbitPoint orbitPoint;
        orbitPoint.iPosition.iX
            = iOrbitRect.Center().iX + ( a * cosalpha * cosbeta - b * sinalpha * sinbeta );
        orbitPoint.iPosition.iY
            = iOrbitRect.Center().iY + ( a * cosalpha * sinbeta + b * sinalpha * cosbeta );

        TReal gap = orbitPoint.iPosition.iY - iOrbitRect.iTl.iY;
        orbitPoint.iScaleFactor = gap / iOrbitRect.Height();

        iOrbitPointList.Insert( orbitPoint, 0 );
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::InitializeCarouselItemL
// ----------------------------------------------------------------------------
//
void CCarouselScene::InitializeCarouselItemL()
    {
    for ( TInt i = 0; i < KMaxItemNumber; i++ )
        {
        CCarouselItem* item = CCarouselItem::NewL( iBmpContext, *this );
        TInt index = iOrbitPointList.Count() / KMaxItemNumber * i;
        item->SetOrbitIndex( index );
        TRgb color;
        color.SetRed( Rand( KMaxPigment ) );
        color.SetGreen( Rand( KMaxPigment ) );
        color.SetBlue( Rand( KMaxPigment ) );
        item->SetColor( color );
        iCarouselItemList.AppendL( item );
        }
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Rand
// ----------------------------------------------------------------------------
//
TInt CCarouselScene::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CCarouselScene::Sort
// ----------------------------------------------------------------------------
//
void CCarouselScene::Sort()
    {
    TLinearOrder<CCarouselItem> order( CCarouselItem::Compare );
    iCarouselItemList.Sort( order );
    }
