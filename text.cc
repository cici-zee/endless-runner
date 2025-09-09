#include "text.h"

Text::Text(SDL_Renderer* rendererPtr) 
    : hitTexture{rendererPtr}, startTexture{rendererPtr} {
    if (!hitTexture.loadImage("images/hit.png")) {
        cout << "couldn't load hit picture" << endl;
    }
    if (!startTexture.loadImage("images/start.png")) {
        cout << "couldn't load cat start" << endl;
    }
}

void Text::render(TextType textType) {
    switch(textType) {
        case START:
            startTexture.render((SCREEN_WIDTH - startTexture.getWidth()) / 2, (SCREEN_HEIGHT - GROUND_HEIGHT - startTexture.getHeight()) / 2);
            break;
        case HIT:
            hitTexture.render((SCREEN_WIDTH - hitTexture.getWidth()) / 2, (SCREEN_HEIGHT - GROUND_HEIGHT - hitTexture.getHeight()) / 2);
            break;
        case PLAYAGAIN:
            startTexture.render((SCREEN_WIDTH - startTexture.getWidth()) / 2, 50);
    }
}