/*
 ============================================================================
 Name       : OrbitPoint.h
 Author   : Sun Jinbo
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : CCCarouselScene declaration
 ============================================================================
 */

#ifndef MORBITPOINT_H
#define MORBITPOINT_H

#include <e32def.h>
#include <e32cmn.h>

// CLASS DECLARATION

/**
* TOrbitPoint class
*
* @since S60 5.0
*/
class TOrbitPoint
    {
public: 
    // New method
    static TInt Compare( const TOrbitPoint& aFirst, const TOrbitPoint& aSecond );
public:
    TPoint iPosition;
    TReal iScaleFactor; // 0.0 ~ 1.0
    };

#endif // MORBITPOINT_H
