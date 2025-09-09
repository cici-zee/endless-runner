#include <SDL.h>

#include "rectangle.h"


Rectangle::Rectangle() {
    SDL_Rect rectangle;
    rect = rectangle;
}

Rectangle::Rectangle(SDL_Rect rectangle) {
    rect = rectangle;

    top = rect.y;
    bottom = rect.y + rect.h;
    left = rect.x;
    right = rect.x + rect.w;
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

