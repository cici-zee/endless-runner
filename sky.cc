#include "sky.h"


Sky::Sky(SDL_Renderer* pRenderer) 
    : xFrontSky{0}, xBackSky{SCREEN_WIDTH}, offset{0}, skyTexture{pRenderer} {
    if (!skyTexture.loadImage("images/sky.png")) {
        cout << "couldn't load sky" << endl;
    }
    prevTime = {};
}


void Sky::render(timeStamp curTime, bool scroll) {
    if (scroll) {
        fsec ElapTime = curTime - prevTime;

        if (ElapTime.count() > 0.1) {
                    offset -= 1;
                    prevTime = curTime;
        }
        if( offset < -1*SCREEN_WIDTH ) {
            offset = 0;
        }
        xFrontSky = offset;
        xBackSky = offset + SCREEN_WIDTH;
    }

    skyTexture.render(xFrontSky, yPos);
    skyTexture.render(xBackSky, yPos);
}
