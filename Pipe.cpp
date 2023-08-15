#include "Pipe.h"
#include "TextureManager.h"
#include <iostream>


void Pipe::free(){
    if( pipeTexture != NULL || pipeTexture != nullptr)
	{
		SDL_DestroyTexture( pipeTexture );
		int pipePosX = 0, pipePosY = 0;
		int pipeVelX = 0, pipeVelY = 0;
		pipeTexture = NULL;
	}
}

Pipe::Pipe(const char*fileName, SDL_Renderer* ren,int x, int y, bool isFlip)
{
    //???
    //pipeTexture = TextureManager::LoadTexture(fileName, ren);
    //free();
    pipeTexture = TextureManager::LoadTexture(fileName, ren);

    renderer = ren;

    TEMP_VEL = PIPE_VEL;
    pipeFlip = isFlip;

    //
    srcRect.h = 1489;
    srcRect.w = 244;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x= x;
    destRect.y = y;
    destRect.w = PIPE_WIDTH;
    destRect.h = PIPE_HEIGHT;

    TEMP_X = x; TEMP_Y = y;
}


Pipe::~Pipe()
{
    free();
}

void Pipe::Update(){

    destRect.x -= PIPE_VEL;

    destRect.y = destRect.y;
}

void Pipe::Render(){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(pipeFlip){
        flip = SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx( renderer, pipeTexture, &srcRect, &destRect, 0.0, NULL, flip);
}

void Pipe::pause(){
    PIPE_VEL = 0;
}
void Pipe::notPause(){
    PIPE_VEL = TEMP_VEL;
}
void Pipe::reset(int y){
    destRect.x = TEMP_X;
    destRect.y = y;

    PIPE_VEL = TEMP_VEL;
}
