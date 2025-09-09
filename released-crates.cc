#include "released-crates.h"

RelCrates::RelCrates(SDL_Renderer* rendererPtr)
    : timeNextRel{3}, pRenderer{rendererPtr} {
    addCrate(new Crate(REGULAR, pRenderer));
    timeLastRel = {};
}

RelCrates::~RelCrates() {
    for (Crate* crate : crates) {
        delete crate;
    }
}

deque<Crate*>::iterator RelCrates::begin() {
    return crates.begin();
}

deque<Crate*>::iterator RelCrates::end() {
    return crates.end();
}

bool RelCrates::releaseCrate(Level level, timeStamp curTime) {
    bool crateReleased = false;
    CrateType possCrates[4] = {REGULAR, DOUBLE, REGULAR, DOUBLE};
    int i = 0;

    fsec timeElap = curTime - timeLastRel;
    
    if (timeElap.count() >= timeNextRel) {
        switch (level) {
            case LEVEL1:
                break;
            case LEVEL2:
                i = rand() % 3; // 2/3 chance regular
                break;
            case LEVEL3:
                i = rand() % 4; // 50/50 chance regular
                break;
        }
        addCrate(new Crate(possCrates[i], pRenderer));
        timeLastRel = curTime; // update time of last released crate to now
        crateReleased = true;
    }
    return crateReleased;
}

void RelCrates::addCrate(Crate* crate) {
    crates.push_back(crate);
}

void RelCrates::render(timeStamp curTime) {
    for (Crate* crate : crates) {
        crate->render(curTime);
    }
}


void RelCrates::update() {
    // should really only need to check the first one
    if (crates.size() != 0) {
        // not empty
        if (crates[0]->xPos < (0 - crates[0]->width)) {
            delete crates[0];
            crates.pop_front();
        }
    }
}

void RelCrates::chooseNextRelTime(Level level) {
    int i = 0;
    switch (level) {
        case LEVEL1:
            i = rand() % 5;
            break;
        case LEVEL2:
            i = rand() % 5;
            break;
        case LEVEL3:
            i = rand() % 11; // now includes 1 sec too
            break;
    }
    timeNextRel = releaseTimes[i];
}

void RelCrates::reset() {
    for (Crate* crate : crates) {
        delete crate;
        crates.pop_back();
    }
    addCrate(new Crate(REGULAR, pRenderer));
    timeLastRel = {};
    timeNextRel = 3;
}
