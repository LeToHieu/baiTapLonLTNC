#include "PauseScreen.h"

PauseScreen::PauseScreen(SDL_Renderer* ren, int &highScore)
{
    renderer = ren;
    bgRect = {(SCREEN_WIDTH-PAUSE_SCREEN_WIDTH)/2, (SCREEN_HEIGHT-PAUSE_SCREEN_HEIGHT)/2,PAUSE_SCREEN_WIDTH, PAUSE_SCREEN_HEIGHT};
    outLineRect = {(SCREEN_WIDTH-PAUSE_SCREEN_WIDTH-20)/2, (SCREEN_HEIGHT-PAUSE_SCREEN_HEIGHT-20)/2,PAUSE_SCREEN_WIDTH+20, PAUSE_SCREEN_HEIGHT+20};


    PauseText = new MyText(renderer, "PAUSING", (SCREEN_WIDTH - 30*4)/2, bgRect.y + 10,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 30));
    BestScoreText = new MyText(renderer, "Best Score: " + std::to_string(highScore), (SCREEN_WIDTH - 70*5.5)/2, PauseText->destRect.y + PauseText->destRect.h +20,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 60));

    ContinueBtn = new Button("res/ContinueBtn.png", renderer, (SCREEN_WIDTH - 200)/2, BestScoreText->destRect.y + BestScoreText->destRect.h +100 , 200, 100);
    BackBtn = new Button("res/MenuBtn.png", renderer, (SCREEN_WIDTH - 200)/2, ContinueBtn->destRect.y + ContinueBtn->destRect.h + 20, 200, 100);

}

void PauseScreen::Render(){
    SDL_SetRenderDrawColor( renderer, 166, 255, 190, 0xFF );
    SDL_RenderFillRect( renderer, &outLineRect);
    SDL_SetRenderDrawColor( renderer, 155, 155, 155, 0xFF );
    SDL_RenderFillRect( renderer, &bgRect);

    PauseText->Render();
    BestScoreText->Render();
    BackBtn->Render();
    ContinueBtn->Render();
}

void PauseScreen::free(){
    PauseText->free();
    BestScoreText->free();
    BackBtn->free();
    ContinueBtn->free();
    delete PauseText;
    delete BestScoreText;
    delete BackBtn;
    delete ContinueBtn;
}

PauseScreen::~PauseScreen()
{
    free();
}
