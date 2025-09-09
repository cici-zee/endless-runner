#include <SDL.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"
#include "rectangle.h"
#include "crate.h"

using namespace std;
using timeStamp = chrono::steady_clock::time_point;
using fsec = std::chrono::duration<float>;

enum Axis {
    X,
    Y,
};

enum Position {
    STILL,
    LEFT_FRONT,
    RIGHT_FRONT,
	SITTING,
};

class Cat {
    public:
        Cat(int x, int y, SDL_Renderer* renderer);

        const int CAT_VEL = 800;
        
        bool checkCollision(Crate* crate);
        void changeVel(int vel, Axis direction);
        void processInput(SDL_Event& e, timeStamp curTime, timeStamp &timeZero);
        void move(timeStamp timeStep);
        void walk(timeStamp timeStep);
        void render(Position position);
        
        void reset();

        int getHeight();
        int getWidth();

        timeStamp prevTime;
        timeStamp prevWalkTime;
        int numPosition;
        bool clearedCrate;
        bool onGround;
        bool startedRun;
        bool collision;

        Rectangle collisionBox;
    
    private:
        int height;
        int width;

        int xPos;
        int yPos;

        float xVel;
        float yVel;


        Texture catLeftTexture;
        Texture catRightTexture;
        Texture catStillTexture;
        Texture catSittingTexture;

};