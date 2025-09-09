#include "cat.h"

bool basicCheckCollision(Rectangle a, Rectangle b, bool &clear) {
    bool collision = true;
    
    if (a.left >= b.right) {
        clear = true;
        collision = false;
    } else if (a.bottom <= b.top) {
        collision = false;
    } else if ( a.top >= a.bottom) {
        collision = false;
    } else if (a.right <= b.left) {
        collision = false;
    } 
    return collision;
}

// when create cat --> have to specify where u want it to start on the screen
Cat::Cat(int x, int y, SDL_Renderer* pRenderer) 
    : numPosition{0}, clearedCrate{false}, onGround{false}, startedRun{false}, collision{false},
      catLeftTexture{pRenderer}, catRightTexture{pRenderer}, catStillTexture{pRenderer}, catSittingTexture{pRenderer} {
    //catLeftTexture = Texture(pRenderer);

    // load all images of cat position to their textures
    if (!catLeftTexture.loadImage("images/cat-left-front.png")) {
        cout << "couldn't load cat left :(" << endl;
    }
    if (!catRightTexture.loadImage("images/cat-right-front.png")) {
        cout << "couldn't load cat right front :(" << endl;
    }
    if (!catStillTexture.loadImage("images/cat-still.png")) {
        cout << "couldn't load cat still :(" << endl;
    } 
    if (!catSittingTexture.loadImage("images/cat-sitting.png")) {
        cout << "couldn't load cat still :(" << endl;
    }

    // initialize height and width
    height = catStillTexture.getHeight();
    width = catStillTexture.getWidth();
    
    xPos = x;
    yPos = y;

    SDL_Rect colBox;
    colBox.x = xPos;
    colBox.y = yPos;
    colBox.h = height;
    colBox.w = width;
    collisionBox = Rectangle(colBox);

    prevTime = {};
    prevWalkTime = {};

}

bool Cat::checkCollision(Crate* crate) {
    bool clear = false;
    collision = basicCheckCollision(collisionBox, crate->collisionBox, clear);
    if (clear && !(crate->cleared)) {
        clearedCrate = true;
        crate->cleared = true;
    }
    return collision;
}

void Cat::changeVel(int vel, Axis direction) {
    switch(direction) {
        case X:
            xVel = vel;
            break;
        case Y:
            yVel = vel;
            break;
    }
}

// only want to process space bar & up key
void Cat::processInput(SDL_Event& e, timeStamp curTime, timeStamp &timeZero) {

    // only want to process pressing key down
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {

        switch(e.key.keysym.sym) {
            
            // jumping
            case SDLK_UP:
                if (onGround) {
                    // can only jump if on the ground
                    changeVel(-CAT_VEL, Y); 
                    onGround = false;
                }
                break;
            
            // to start the game
            case SDLK_SPACE:
                collision = false;
                startedRun = true;
                timeZero = curTime;
        }
    // key is released --> velocity 
    /*} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        if (e.key.keysym.sym == SDLK_DOWN) {
            changeVel(-CAT_VEL, Y);
        }*/
    }
}


void Cat::move(timeStamp curTime) {
    
    walk(curTime);
    
    std::chrono::duration<float> timeElapsed = (curTime - prevTime);
    //SDL_Log("%f", timeElapsed.count());
    //timeElapsed /= 10000000;

    yPos += yVel * (timeElapsed.count());

    if (yPos > SCREEN_HEIGHT - height - GROUND_HEIGHT) {
        yPos = SCREEN_HEIGHT - height - GROUND_HEIGHT;
        yVel = G;
        onGround = true;
        
    } else {
        yPos += 0.5*G*(timeElapsed.count())*(timeElapsed.count());
        yVel += G*(timeElapsed.count());
    }
    // update collision box
    collisionBox.y = yPos;
    collisionBox.top = collisionBox.y;
    collisionBox.bottom = collisionBox.y + collisionBox.h;

}

void Cat::walk(timeStamp curTime) {
    if (onGround) {
        fsec timeSinceStep = curTime - prevWalkTime;
        if (timeSinceStep.count() > 0.18) {
            numPosition++;
            if (numPosition > 3) {
                numPosition = 0;
            }
            prevWalkTime = curTime;
        }
    } else {
        numPosition = 0;
        prevWalkTime = curTime;
    }
}


void Cat::render(Position position) {
    switch(position) {
        case LEFT_FRONT:
            catLeftTexture.render( (int)xPos, (int)yPos );
            break;
        case RIGHT_FRONT:
            catRightTexture.render( (int)xPos, (int)yPos );
            break;
        case STILL:
            catStillTexture.render( (int)xPos, (int)yPos );
            break;
		case SITTING:
			catSittingTexture.render( (int)xPos, (int)yPos );
			break;
    }
}

void Cat::reset() {
    xPos = 20;
    yPos = SCREEN_HEIGHT - GROUND_HEIGHT - height;

    SDL_Rect collRect = {20, yPos, width, height};
    collisionBox = Rectangle(collRect);

    numPosition = STILL;

    xVel = 0;
    yVel = 0;
}

int Cat::getHeight() {
    return height;
}

int Cat::getWidth() {
    return width;
}