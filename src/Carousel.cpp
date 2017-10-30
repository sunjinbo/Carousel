/*
 ============================================================================
 Name		: Carousel.cpp
 Author	  : Sun Jinbo
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "CarouselApplication.h"

LOCAL_C CApaApplication* NewApplication()
    {
    return new CCarouselApplication;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

