#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <chrono>
#include <deque>

#include "constants.h"
#include "level.h"

#include "rectangle.h"
#include "texture.h"
#include "sky.h"
#include "ground.h"
#include "crate.h"
#include "released-crates.h"
#include "cat.h"
#include "text.h"
#include "score.h"


using namespace std;
using fsec = std::chrono::duration<float>;
using timeStamp = chrono::steady_clock::time_point;

Position positions[4] = {STILL, LEFT_FRONT, STILL, RIGHT_FRONT};

bool setUp(SDL_Window*& window, SDL_Renderer*& pRenderer) {
    bool isSetUp = false;
    window = SDL_CreateWindow( "Cantering Cat: An Endless Runner Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    pRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << SDL_GetError() << endl;

    } else if (!window) {
        cout << "failed creating window" << endl;

    } else if (!pRenderer) {
        cout << "failed creating renderer" << endl;

    } else if (!IMG_Init(IMG_INIT_PNG)) {
        cout << SDL_GetError() << endl;
    } else if (TTF_Init() == -1) {
        cout << "couldn't initialize ttf" << endl;
    } else {
        isSetUp = true;
    }

    return isSetUp;

}

int main() {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    
    if (!setUp(window, renderer)) {
        cout << "couldn't initialize & set-up SDL" << endl;
    } else {
        Ground ground(renderer);

        Cat gilbert(20, SCREEN_HEIGHT - CAT_HEIGHT - GROUND_HEIGHT, renderer);
        Sky sky(renderer);
        RelCrates currentCrates(renderer);
        Text text(renderer);
        Score score(renderer);
        Level level = LEVEL1;

        SDL_Event e;

        bool gameRunning = true;

        // main timer
        chrono::steady_clock timer;
        std::__1::chrono::steady_clock::time_point timeZero;


        // exits loop when there are no more pending events
        while (gameRunning) {
            while(SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    gameRunning = false;
                }
                auto timeNow = timer.now();
                gilbert.processInput(e, timeNow, timeZero);
            }       

            auto curTime = timer.now();

            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		    SDL_RenderClear( renderer );

            if (!gilbert.startedRun) {

                sky.render(curTime, false);
                ground.render(curTime, false);
                gilbert.render(STILL);
                text.render(START);

            } else if (gilbert.collision) {

                sky.render(curTime, false);
                ground.render(curTime, false);
                gilbert.render(positions[gilbert.numPosition]);
                //text.render(PLAYAGAIN);
                text.render(HIT);
                score.renderResults();

            } else {

                // update level if neccesarry
                fsec curRoundTimeElap = curTime - timeZero;
                if (curRoundTimeElap.count() > 20) { 
                    level = LEVEL3;
                } else if (curRoundTimeElap.count() > 10) {
                    level = LEVEL2;
                }

                gilbert.move(curTime); 
                gilbert.prevTime = curTime; // update prev time

                sky.render(curTime, true);
                ground.render(curTime, true);

                gilbert.render(positions[gilbert.numPosition]);

                // release crates if is right time
                if (currentCrates.releaseCrate(level, curTime)) {
                    currentCrates.chooseNextRelTime(level);
                }

                // render crates
                currentCrates.render(curTime);
                currentCrates.update();

                // run collision detection
                deque<Crate*>::iterator it = currentCrates.begin();
                while (it != currentCrates.end()) {
                    if (gilbert.checkCollision(*it)) {
                        //Collision = true;
                        
                        // reset
                        gilbert.reset();
                        currentCrates.reset();
                        score.reset();
                        level = LEVEL1;
                        break;
                    }
                    it++;  
                }
                if (gilbert.clearedCrate) {
                    score.update();
                    gilbert.clearedCrate = false;
                }
                
                score.render();
            }

            //Update screen
		    SDL_RenderPresent( renderer );
        }

    }
    
    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	IMG_Quit();
	SDL_Quit();

}

