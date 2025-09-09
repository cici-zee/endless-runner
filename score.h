#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"

using namespace std;

class Score {
    public:
        Score(SDL_Renderer* rendererPtr);
        void render();
        void reset();
        void update();
        void renderResults();
        int currentScore;
        int hiScore;
        int prevScore;
    private:
        TTF_Font* font;
        SDL_Renderer* pRenderer;
};
