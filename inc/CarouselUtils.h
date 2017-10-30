/*
 ============================================================================
 Name       : CarouselUtils.h
 Author   : Sun Jinbo
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : CCarouselScene declaration
 ============================================================================
 */

#ifndef CAROUSELUTILS_H_
#define CAROUSELUTILS_H_

// Enums
enum TWise{
    EClockwise,
    EAnticlockwise
    };

enum TDirection
    {
    EToTop,
    EToBottom,
    EToLeft,
    EToRight,
    EToTopLeft,
    EToTopRight,
    EToBottomLeft,
    EToBottomRight,
    EToCenter
    };

static TDirection Direction( const TPoint& aStartPoint, const TPoint& aEndPoint )
    {
    TDirection direction;
    if ( aStartPoint.iX == aEndPoint.iX && aStartPoint.iY > aEndPoint.iY )
        {
        direction = EToTop;
        }
    else if ( aStartPoint.iX == aEndPoint.iX && aStartPoint.iY < aEndPoint.iY )
        {
        direction = EToBottom;
        }
    else if ( aStartPoint.iX < aEndPoint.iX && aStartPoint.iY == aEndPoint.iY )
        {
        direction = EToLeft;
        }
    else if ( aStartPoint.iX > aEndPoint.iX && aStartPoint.iY == aEndPoint.iY )
        {
        direction = EToRight;
        }
    else if ( aStartPoint.iX < aEndPoint.iX && aStartPoint.iY > aEndPoint.iY )
        {
        direction = EToTopLeft;
        }
    else if ( aStartPoint.iX > aEndPoint.iX && aStartPoint.iY > aEndPoint.iY )
        {
        direction = EToTopRight;
        }
    else if ( aStartPoint.iX < aEndPoint.iX && aStartPoint.iY < aEndPoint.iY )
        {
        direction = EToBottomLeft;
        }
    else if ( aStartPoint.iX > aEndPoint.iX && aStartPoint.iY < aEndPoint.iY )
        {
        direction = EToBottomRight;
        }
    else{
        direction = EToCenter;
        }
    return direction;
    }

#endif /* CAROUSELUTILS_H_ */
