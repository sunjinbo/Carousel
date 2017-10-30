/*
 ============================================================================
 Name		: CarouselSceneObserver.h
 Author	  : Sun Jinbo
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CCCarouselScene declaration
 ============================================================================
 */

#ifndef MCAROUSELSCENEOBSERVER_H
#define MCAROUSELSCENEOBSERVER_H

// ENUMS
enum TCarouselSceneState
    {
    ECarouselSceneUpdated
    };

// CLASS DECLARATION

/**
* MCarouselSceneObserver class
*
* @since S60 5.0
*/
class MCarouselSceneObserver
    {
public:
    virtual void StateChanged( TInt aNewState ) = 0;
    };

#endif // MCAROUSELSCENEOBSERVER_H
