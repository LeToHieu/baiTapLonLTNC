#include "DeadScreen.h"

DeadScreen::DeadScreen(SDL_Renderer* ren, int &highScore, int &yourScore)
{
    renderer = ren;
    bgRect = {(SCREEN_WIDTH-PAUSE_SCREEN_WIDTH)/2, (SCREEN_HEIGHT-PAUSE_SCREEN_HEIGHT)/2,PAUSE_SCREEN_WIDTH, PAUSE_SCREEN_HEIGHT};
    outLineRect = {(SCREEN_WIDTH-PAUSE_SCREEN_WIDTH-20)/2, (SCREEN_HEIGHT-PAUSE_SCREEN_HEIGHT-20)/2,PAUSE_SCREEN_WIDTH+20, PAUSE_SCREEN_HEIGHT+20};

    DeadText = new MyText(renderer, "NICE TRY :)", (SCREEN_WIDTH - 30*5)/2, bgRect.y + 10,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 30));
    BestScoreText = new MyText(renderer, "Best Score: " + std::to_string(highScore), (SCREEN_WIDTH - 65*6)/2, DeadText->destRect.y + DeadText->destRect.h +20,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 60));
    YourScoreText = new MyText(renderer, "Your Score: " + std::to_string(yourScore), (SCREEN_WIDTH - 50*6)/2, BestScoreText->destRect.y + BestScoreText->destRect.h +5,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 50));

    ResetBtn = new Button("res/TryAgainBtn.png", renderer, (SCREEN_WIDTH - 200)/2, YourScoreText->destRect.y + YourScoreText->destRect.h +50, 200, 100);
    BackBtn = new Button("res/MenuBtn.png", renderer, (SCREEN_WIDTH - 200)/2, ResetBtn->destRect.y + ResetBtn->destRect.h + 20, 200, 100);
}

void DeadScreen::Render(){
    SDL_SetRenderDrawColor( renderer, 166, 255, 190, 0xFF );
    SDL_RenderFillRect( renderer, &outLineRect);
    SDL_SetRenderDrawColor( renderer, 155, 155, 155, 0xFF );
    SDL_RenderFillRect( renderer, &bgRect);

    DeadText->Render();
    BestScoreText->Render();
    YourScoreText->Render();

    ResetBtn->Render();
    BackBtn->Render();
}

void DeadScreen::free(){
    DeadText->free();
    BestScoreText->free();
    YourScoreText->free();
    ResetBtn->free();
    BackBtn->free();
    delete DeadText;
    delete BestScoreText;
    delete YourScoreText;
    delete ResetBtn;
    delete BackBtn;
}

DeadScreen::~DeadScreen()
{
    free();
}


