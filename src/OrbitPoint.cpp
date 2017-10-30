/*
 ============================================================================
 Name       : OrbitPoint.cpp
 Author   : Sun Jinbo
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : CCCarouselScene declaration
 ============================================================================
 */


#include "OrbitPoint.h"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TMenuItem::Compare
// ----------------------------------------------------------------------------
//
TInt TOrbitPoint::Compare( const TOrbitPoint& aFirst, const TOrbitPoint& aSecond )
    {
     if ( aFirst.iPosition.iY > aSecond.iPosition.iY )
      return 1; 
     if ( aFirst.iPosition.iY < aSecond.iPosition.iY )
      return -1;
    return 0;
    }
