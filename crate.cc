#include "crate.h"

Crate::Crate(CrateType crateType, SDL_Renderer* pRenderer) :
    collisionBox {}, cleared{false}, singleCrateTexture{pRenderer}, doubleCrateTexture{pRenderer} {

    SDL_Rect colBox;

    if (!singleCrateTexture.loadImage("images/crate.png")) {
        cout << "couldn't load single crate" << endl;
    } else if (!doubleCrateTexture.loadImage("images/double_crate.png")) {
        cout << "couldn't load double crate" << endl;
    } else {
        switch (crateType) {
            case REGULAR:
                type = REGULAR;
                yPos = SCREEN_HEIGHT - GROUND_HEIGHT - singleCrateTexture.getHeight();

                width = singleCrateTexture.getWidth();
                height = singleCrateTexture.getHeight();
               
                colBox.w = singleCrateTexture.getWidth();
                colBox.h = singleCrateTexture.getHeight();
                break;
            case DOUBLE:
                type = DOUBLE;
                yPos = SCREEN_HEIGHT - GROUND_HEIGHT - doubleCrateTexture.getHeight();
                
                width = doubleCrateTexture.getWidth();
                height = doubleCrateTexture.getHeight();
                
                colBox.w = doubleCrateTexture.getWidth();
                colBox.h = doubleCrateTexture.getHeight();
                break;
        }
        xPos = SCREEN_WIDTH; // starts outside screen
        
        colBox.x = xPos;
        colBox.y = yPos;
        collisionBox = Rectangle{colBox};

        prevTime = {};
    }
	
}

void Crate::move(float x) {
	xPos += x;
	collisionBox.x = xPos;
    collisionBox.left = xPos;
    collisionBox.right = xPos + collisionBox.w;
}

void Crate::render(timeStamp curTime) {
    fsec elapTime = curTime - prevTime;

    // DON'T NEED TO 
    if (elapTime.count() > 0.01) {
        move(-4);
        prevTime = curTime;
    }

	switch (type) {
		case REGULAR:
			singleCrateTexture.render( (int)xPos, (int)yPos);
			break;
		case DOUBLE:
			doubleCrateTexture.render( (int)xPos, (int)yPos);
			break;
	}
}

void Crate::reset() {
	xPos = SCREEN_WIDTH; // starts outside screen

	switch (type) {
		case REGULAR:
			xPos = SCREEN_HEIGHT - GROUND_HEIGHT - singleCrateTexture.getHeight();
			collisionBox.w = singleCrateTexture.getWidth();
			collisionBox.h = singleCrateTexture.getHeight();
			break;
		case DOUBLE:
			xPos = SCREEN_HEIGHT - GROUND_HEIGHT - doubleCrateTexture.getHeight();
			collisionBox.w = doubleCrateTexture.getWidth();
			collisionBox.h = doubleCrateTexture.getHeight();
			break;
	}

	collisionBox.x = xPos;
	collisionBox.y = yPos;
	
}