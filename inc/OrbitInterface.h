/*
 ============================================================================
 Name       : OrbitInterface.h
 Author   : Sun Jinbo
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : CCCarouselScene declaration
 ============================================================================
 */


#ifndef MORBITINTERFACE_H
#define MORBITINTERFACE_H

#include "OrbitPoint.h"

// CLASS DECLARATION

/**
* MOrbitInterface class
*
* @since S60 5.0
*/
class MOrbitInterface
    {
public:
    virtual const TOrbitPoint& OrbitPoint( TInt aOrbitIndex ) const = 0;
    virtual TInt OrbitPointCount() const = 0;
    };

#endif // MORBITINTERFACE_H
