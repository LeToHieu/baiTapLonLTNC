#include "Coin.h"

Coin::Coin(SDL_Renderer* ren,int x, int y)
{
    //free();
    coinTexture1 = TextureManager::LoadTexture("res/Coin1.png", ren);
    coinTexture2 = TextureManager::LoadTexture("res/Coin2.png", ren);
    coinTexture3 = TextureManager::LoadTexture("res/Coin3.png", ren);
    coinTexture4 = TextureManager::LoadTexture("res/Coin4.png", ren);
    coinTexture5 = TextureManager::LoadTexture("res/Coin5.png", ren);
    coinTexture6 = TextureManager::LoadTexture("res/Coin6.png", ren);

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
        coinSpin+=5;
        if(coinSpin < 45){
            SDL_RenderCopy(renderer, coinTexture1, NULL , &destRect);
        }else if(coinSpin < 90){
            SDL_RenderCopy(renderer, coinTexture2, NULL , &destRect);
        }else if(coinSpin < 135){
            SDL_RenderCopy(renderer, coinTexture3, NULL , &destRect);
        }else if(coinSpin < 180){
            SDL_RenderCopy(renderer, coinTexture4, NULL , &destRect);
        }else if(coinSpin < 225){
            SDL_RenderCopy(renderer, coinTexture5, NULL , &destRect);
        }else if(coinSpin < 270){
            SDL_RenderCopy(renderer, coinTexture6, NULL , &destRect);
            coinSpin = 0;
        }

    }
}

void Coin::free(){
    if( coinTexture1 != NULL || coinTexture1 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture1 );
		coinTexture1 = NULL;
	}
	if( coinTexture2 != NULL || coinTexture2 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture2 );
		coinTexture2 = NULL;
	}
	if( coinTexture3 != NULL || coinTexture3 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture3 );
		coinTexture3 = NULL;
	}
	if( coinTexture4 != NULL || coinTexture4 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture4 );
		coinTexture4 = NULL;
	}
	if( coinTexture5 != NULL || coinTexture5 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture5 );
		coinTexture5 = NULL;
	}
	if( coinTexture6 != NULL || coinTexture6 != nullptr)
	{
	    SDL_DestroyTexture( coinTexture6 );
		coinTexture6 = NULL;
	}
}

void Coin::pause(){
    COIN_VEL = 0;
}
void Coin::notPause(){
    COIN_VEL = TEMP_VEL;
}
void Coin::reset(int y){
    isClaim = false;
    destRect.x = TEMP_X;
    destRect.y = y;
    COIN_VEL = TEMP_VEL;
}
