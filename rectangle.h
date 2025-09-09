#ifndef RECTANGLE
#define RECTANGLE

struct Rectangle {
    Rectangle(SDL_Rect rectangle);
    Rectangle();

    // sides
    int x;
    int y;
    int h;
    int w;

    int top;
    int bottom;
    int left;
    int right;

    SDL_Rect rect;
};

#endif
