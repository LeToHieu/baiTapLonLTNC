#include "Coin.h"

Coin::Coin(SDL_Renderer* ren,int x, int y)
{
    //free();
    coinTexture = TextureManager::LoadTexture("res/Coin.png", ren);
    renderer = ren;

    destRect.x = x;
    destRect.y = y;
    TEMP_X = x; TEMP_Y = y; TEMP_VEL = COIN_VEL;
    destRect.w = COIN_HEIGHT;
    destRect.h = COIN_WIDTH;
    isClaim = false;
}

Coin::~Coin()
{
    free();
}

void Coin::Update(){
    destRect.x -= COIN_VEL;
    destRect.y = destRect.y;
}


void Coin::Render(){
    if(!isClaim){
        SDL_RenderCopy(renderer, coinTexture, NULL , &destRect);
    }
}

void Coin::free(){
    if( coinTexture != NULL || coinTexture != nullptr)
	{
		SDL_DestroyTexture( coinTexture );
		coinTexture = NULL;
	}
}

void Coin::pause(){
    COIN_VEL = 0;
}
void Coin::notPause(){
    COIN_VEL = TEMP_VEL;
}
void Coin::reset(){
    isClaim = false;
    destRect.x = TEMP_X;
    destRect.y = TEMP_Y;
    COIN_VEL = TEMP_VEL;
}
