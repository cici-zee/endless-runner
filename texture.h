#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

class Texture {
    public:
        Texture(SDL_Renderer* rendererPtr);

        ~Texture();

        bool loadImage(string file);
        bool loadText(string text, TTF_Font* font);

        void render(int x, int y);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* oTexture;
        SDL_Renderer* pRenderer;

        int imgWidth;
        int imgHeight;
};

#endif
