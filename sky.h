#include <SDL.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"

using namespace std;
using timeStamp = chrono::steady_clock::time_point;
using fsec = std::chrono::duration<float>;

class Sky {
    public:
        Sky();
        Sky(SDL_Renderer* pRenderer);

        void render(timeStamp curTime, bool scroll);

    private:
        Texture skyTexture;
        timeStamp prevTime;

        float xFrontSky;
        float xBackSky;
        int offset;

        const float yPos = 0;
};