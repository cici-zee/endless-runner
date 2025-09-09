#include "ground.h"

Ground::Ground(SDL_Renderer* rendererPtr) 
    : xFrontGround{0}, xBackGround{SCREEN_WIDTH}, offset{0}, groundTexture{rendererPtr} {
    if (!groundTexture.loadImage("images/ground.png")) {
        cout << "couldn't load ground" << endl;
    }
    xBackGround = SCREEN_WIDTH - groundTexture.getWidth();
    yPos = SCREEN_HEIGHT - groundTexture.getHeight();
}

void Ground::render(timeStamp curTime, bool scroll) {
    if (scroll) {
        fsec ElapTime = curTime - prevTime;

        if (ElapTime.count() > 0.01) {
                    offset -= 4;
                    prevTime = curTime;
        }
        if( offset < -1*SCREEN_WIDTH) {
            offset = 0;
        }
        xFrontGround = offset;
        xBackGround = offset + SCREEN_WIDTH;
    }

    groundTexture.render(xFrontGround, yPos);
    groundTexture.render(xBackGround, yPos);

    //MAKE A LONGER GROUND TEXTURE!!!
}

int Ground::getHeight() {
    return groundTexture.getHeight();
}