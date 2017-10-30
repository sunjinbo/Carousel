/*
 ============================================================================
 Name		: Carousel.pan
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __CAROUSEL_PAN__
#define __CAROUSEL_PAN__

/** Carousel application panic codes */
enum TCarouselPanics
    {
    ECarouselUi = 1
    // add further panics here
    };

inline void Panic(TCarouselPanics aReason)
    {
    _LIT(applicationName, "Carousel");
    User::Panic(applicationName, aReason);
    }

#endif // __CAROUSEL_PAN__
