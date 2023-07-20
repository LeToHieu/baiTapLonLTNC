#include "BackGround.h"
#include "iostream"

BackGround::BackGround(SDL_Renderer* ren)
{
    renderer = ren;
    backGround = TextureManager::LoadTexture("res/backGround.png", ren);
    srcRect.x = 0; srcRect.y = 0; srcRect.w = 900; srcRect.h = 500;
    destRect.x = 0; destRect.y = 0; destRect.w = 900; destRect.h = 600;
    //ctor
}

BackGround::~BackGround()
{
    //dtor
}

void BackGround::Update(){
    --scrollingOffset;
    if( scrollingOffset < -900 )
    {
        scrollingOffset = 0;
    }
}

void BackGround::Render(){

     destRect.x = scrollingOffset;
     SDL_RenderCopy(renderer, backGround, NULL , &destRect);
     destRect.x = scrollingOffset+900;
     SDL_RenderCopy(renderer, backGround, NULL , &destRect);
     destRect.x = scrollingOffset+900*2;
     SDL_RenderCopy(renderer, backGround, NULL , &destRect);
}


void BackGround::free(){
    backGround = NULL;
    scrollingOffset = 0;
}

