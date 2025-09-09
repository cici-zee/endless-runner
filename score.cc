#include "score.h"

Score::Score(SDL_Renderer* rendererPtr) 
    : currentScore{0}, hiScore{0}, prevScore{0}, pRenderer{rendererPtr} {
    font = TTF_OpenFont("fonts/fff-forward.regular.ttf", 20);
    if (!font) { 
        cout << "couldn't open font" << endl;
    }
}

void Score::render() {
    Texture score(pRenderer);
    score.loadText("SCORE: " + to_string(currentScore), font);
    score.render(10, 10);
}

void Score::reset() {
    prevScore = currentScore;
    currentScore = 0;
}

void Score::update() {
    currentScore += 1;
}

void Score::renderResults() {
    if (prevScore > hiScore) {
        hiScore = prevScore;
    }
    // render score
    Texture score(pRenderer);
    score.loadText("SCORE: " + to_string(prevScore), font);
    score.render((SCREEN_WIDTH - score.getWidth())/2, 250);
    
    // render high score
    Texture highScore(pRenderer);
    highScore.loadText("HIGH SCORE: " + to_string(hiScore), font);
    highScore.render((SCREEN_WIDTH - highScore.getWidth())/2, 300);
}