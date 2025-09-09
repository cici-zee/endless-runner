#ifndef CRATE_H
#define CRATE_H

#include <SDL.h>
#include <iostream>
#include <string>

#include "constants.h"
#include "texture.h"
#include "crate-type.h"
#include "rectangle.h"

using namespace std;
using timeStamp = chrono::steady_clock::time_point;
using fsec = std::chrono::duration<float>;

class Crate
{
	public:
		int width;
		int height;
		Rectangle collisionBox;

		Crate(CrateType crateType, SDL_Renderer* renderer);
		void move(float x);
		void render(timeStamp curTime);
		void reset();
		
        CrateType type;
        bool cleared;
        friend class RelCrates;


	private:
        Texture singleCrateTexture;
        Texture doubleCrateTexture;

		float xPos, yPos;
        timeStamp prevTime;

		
};

#endif
