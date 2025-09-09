#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"

using namespace std;

enum TextType {
    START,
    HIT,
    PLAYAGAIN
};

class Text {
    public:
        Text(SDL_Renderer* rendererPtr);
        void render(TextType textType);

    private:
        Texture hitTexture;
        Texture startTexture;
};

#endif