/*
 ============================================================================
 Name		: CarouselAppView.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include <fbs.h>
#include <bitdev.h>
#include <bitstd.h>
#include <w32std.h>
#include <akndef.h>

#include "CarouselAppView.h"
#include "CarouselScene.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;
const TInt KOrbitRectWidth = 250;
const TInt KOrbitRectHeight = 100;
const TInt KDefaultDragCount = 0;
const TInt KMaxDragCount = 3;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CCarouselAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCarouselAppView* CCarouselAppView::NewL(const TRect& aRect)
    {
    CCarouselAppView* self = CCarouselAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCarouselAppView* CCarouselAppView::NewLC(const TRect& aRect)
    {
    CCarouselAppView* self = new (ELeave) CCarouselAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCarouselAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    CreateBmpBufferL();
    
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                    KDoDelayTimeout,
                    KDoFrameUpdateTimeout,
                    TCallBack( TimerCallback, this ) );

    CalcOrbitRect( iOrbitRect );
    iScene = CCarouselScene::NewL( *this, iBitmapGc, iOrbitRect );

    // Enable Drag Events.
    EnableDragEvents();
 
    // OR can also be done with
    Window().PointerFilter( EPointerFilterDrag, 0 );
    
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::CCarouselAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCarouselAppView::CCarouselAppView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::~CCarouselAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CCarouselAppView::~CCarouselAppView()
    {
    Stop();
    ReleaseBmpBuffer();
    delete iScene;
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CCarouselAppView::SizeChanged()
    {
    if ( iScene )
        {
        TRAP_IGNORE( CreateBmpBufferL() );
        }
    }

// -----------------------------------------------------------------------------
// CCarouselAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CCarouselAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( iOrbitRect.Contains( aPointerEvent.iPosition ) )
        {
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                iKeyLongPressed = EFalse;
                iDragCount = KDefaultDragCount;
                iStartPoint = aPointerEvent.iPosition;
                }
                break;

            case TPointerEvent::EButton1Up:
                {
                if ( iKeyLongPressed )
                    {
                    TDirection d = Direction( iStartPoint, aPointerEvent.iPosition );
                    HandleDirectionEventL( d );
                    }
                }
                break;

            case TPointerEvent::EDrag:
                {
                ++iDragCount;
                if ( iDragCount > KMaxDragCount )
                    {
                    iKeyLongPressed = ETrue;
                    }
                }
                break;

            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CCarouselAppView::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        CalcOrbitRect( iOrbitRect );
        iScene->SetOrbitRect( iOrbitRect );
        }
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CCarouselAppView::StateChanged( TInt /*aNewState*/ )
    {
    DoDraw();
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CCarouselAppView::CreateBmpBufferL()
    {
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBitmap->Create( Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CCarouselAppView::ReleaseBmpBuffer()
    {
    if ( iBitmapGc )
        {
        delete iBitmapGc;
        iBitmapGc = NULL;
        }
    if ( iBitmapDevice )
        {
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        }
    if ( iBitmap )
        {
        delete iBitmap;
        iBitmap = NULL;
        }
    }
    
// ----------------------------------------------------------------------------
// CCarouselAppView::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CCarouselAppView::TimerCallback( TAny* aPtr )
    {
    CCarouselAppView* self = static_cast<CCarouselAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::Stop
// ----------------------------------------------------------------------------
//
void CCarouselAppView::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::DoFrame
// ----------------------------------------------------------------------------
//
void CCarouselAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBitmap );
    Window().EndRedraw();
    DeactivateGc();
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::DoDraw
// ----------------------------------------------------------------------------
//
void CCarouselAppView::DoDraw()
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetBrushColor( KRgbBlack );
    iBitmapGc->DrawRect( Rect() );

    if ( iScene )
        {
        iScene->Draw();
        }
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::CalcOrbitRect
// ----------------------------------------------------------------------------
//
void CCarouselAppView::CalcOrbitRect( TRect& aOrbitRect )
    {
    aOrbitRect.iTl.iX = Rect().Center().iX - KOrbitRectWidth / 2;
    aOrbitRect.iTl.iY = Rect().Center().iY - KOrbitRectHeight / 2;
    aOrbitRect.iBr.iX = Rect().Center().iX + KOrbitRectWidth / 2;
    aOrbitRect.iBr.iY = Rect().Center().iY + KOrbitRectHeight / 2;
    }

// ----------------------------------------------------------------------------
// CCarouselAppView::HandleDirectionEventL
// ----------------------------------------------------------------------------
//
void CCarouselAppView::HandleDirectionEventL( TDirection aDirection )
    {
    switch ( aDirection )
        {
        case EToLeft:
        case EToTopLeft:
        case EToBottomLeft:
            iScene->AccelerateL( EAnticlockwise );
            break;

        case EToRight:
        case EToTopRight:
        case EToBottomRight:
            iScene->AccelerateL( EClockwise );
            break;

        case EToTop:
        case EToBottom:
        case EToCenter:
        default:
            break;
        }
    }

// End of File
