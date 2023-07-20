#include "MenuScreen.h"

MenuScreen::MenuScreen(SDL_Renderer* ren)
{
    //ctor

    renderer = ren;

    Title = new MyText(renderer, "Flappy Bird", (SCREEN_WIDTH - 70*5)/2, SCREEN_HEIGHT/4,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 70));
    PlayBtn = new Button("res/DoCanBtn.png", renderer, (SCREEN_WIDTH - 200)/2, Title->destRect.y + Title->destRect.h + 20, 200, 100);
    ExitBtn = new Button("res/DoCanBtn2.png", renderer, (SCREEN_WIDTH - 200)/2, PlayBtn->destRect.y + PlayBtn->destRect.h + 20, 200, 100);
}

MenuScreen::~MenuScreen()
{
    //dtor
    free();
}

void MenuScreen::Render(){
    Title->Render();
    PlayBtn->Render();
    ExitBtn->Render();
}
/*
bool MenuScreen::handleEvent(SDL_Event& ev){
    PlayBtn->handleEvent(ev);
    ExitBtn->handleEvent(ev);
}
*/

void MenuScreen::free(){
    Title->free();
    PlayBtn->free();
    ExitBtn->free();
    delete Title; delete PlayBtn; delete ExitBtn;
}
