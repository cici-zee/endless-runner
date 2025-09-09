#include "texture.h"


Texture::Texture(SDL_Renderer* rendererPtr) {
    pRenderer = rendererPtr;
    oTexture = NULL;
    imgWidth = 0;
    imgHeight = 0;
}


Texture::~Texture() {
    if (oTexture != NULL) {
        SDL_DestroyTexture(oTexture);
        oTexture = NULL;
    }
}

bool Texture::loadImage(string file) {

    SDL_Texture* texture = IMG_LoadTexture(pRenderer, file.c_str());

    if (!texture) {
        cout << "unable to load inmage into texture " << SDL_GetError() << endl;

    } else {
        SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    }
    oTexture = texture;
    return oTexture != NULL;
}

bool Texture::loadText(string text, TTF_Font* font) {
    SDL_Colour black = {0, 0, 0};
    SDL_Colour teal = {13, 95, 97};

    SDL_Surface* surfaceText = TTF_RenderText_Solid(font, text.c_str(), teal);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(pRenderer, surfaceText);
    imgWidth = surfaceText->w;
    imgHeight = surfaceText->h;

    oTexture = textTexture;
    return oTexture != NULL;

}

void Texture::render(int x, int y) {
    SDL_Rect destination;
    
    destination.x = x;
    destination.y = y;
    destination.w = imgWidth;
    destination.h = imgHeight;

    SDL_RenderCopy(pRenderer, oTexture, NULL, &destination);
}

int Texture::getWidth() {
    return imgWidth;
}

int Texture::getHeight() {
    return imgHeight;
}