#include "Fruit.h"
#include"iostream"

Fruit::Fruit(SDL_Renderer* ren,const char*fileName ,int x, int y)
{
    //free();
    fruitTexture = TextureManager::LoadTexture(fileName, ren);
    renderer = ren;

    destRect.x = x;
    destRect.y = y;
    TEMP_X = x; TEMP_Y = y; TEMP_VEL = FRUIT_VEL;
    destRect.w = FRUIT_HEIGHT;
    destRect.h = FRUIT_WIDTH;
    //isClaim = false;
}

Fruit::~Fruit()
{
    free();
}


void Fruit::Update(){
    destRect.x -= FRUIT_VEL;
    destRect.y = destRect.y;
}


void Fruit::Render(){
    if(!isClaim){
        SDL_RenderCopy(renderer, fruitTexture, NULL , &destRect);
    }
}

void Fruit::free(){
    if( fruitTexture != NULL || fruitTexture != nullptr)
	{
		SDL_DestroyTexture( fruitTexture );
		fruitTexture = NULL;
	}
}

void Fruit::pause(){
    FRUIT_VEL = 0;
}
void Fruit::notPause(){
    FRUIT_VEL = TEMP_VEL;
}
void Fruit::reset(int y){
    //isClaim = false;
    isClaim = true;
    destRect.x = TEMP_X;
    destRect.y = y;
    FRUIT_VEL = TEMP_VEL;
}
