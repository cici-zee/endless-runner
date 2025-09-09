#include <SDL.h>
#include <iostream>
#include <string>
#include <chrono>
#include <deque>

#include "constants.h"
#include "crate-type.h"
#include "crate.h"
#include "level.h"

using namespace std;
using timeStamp = chrono::steady_clock::time_point;
using fsec = std::chrono::duration<float>;


class RelCrates {
    public:
        RelCrates(SDL_Renderer* rendererPtr);
        ~RelCrates();
        void addCrate(Crate* crate);
        void render(timeStamp curTime);
        void update();
        void chooseNextRelTime(Level level);
        bool releaseCrate(Level level, timeStamp curTime);
        void reset();

        deque<Crate*>::iterator begin();
        deque<Crate*>::iterator end();

    private:
        timeStamp timeLastRel;
        float timeNextRel;
        deque<Crate*> crates;
        float releaseTimes[11] = {2, 2, 3, 4, 1.8, 1.5, 1.5, 1.2, 1.7, 1.8, 1.2}; 

        SDL_Renderer* pRenderer;
};