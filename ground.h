#include <SDL.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"

using namespace std;
using fsec = std::chrono::duration<float>;
using timeStamp = chrono::steady_clock::time_point;

class Ground {
    public:
        Ground(SDL_Renderer* rendererPtr);

        void render(timeStamp curTime, bool scroll);
        
        int getHeight();

        int offset; // so that crates can access
    private:
        Texture groundTexture;
        timeStamp prevTime;
        
        float xFrontGround;
        float xBackGround;
        float yPos;

};