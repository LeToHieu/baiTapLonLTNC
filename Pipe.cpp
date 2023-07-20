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

    pipeVelX = PIPE_VEL;
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

    destRect.x -= pipeVelX;

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
    pipeVelX = 0;
}
void Pipe::notPause(){
    pipeVelX = PIPE_VEL;
}
void Pipe::reset(){
    destRect.x = TEMP_X;
    destRect.y = TEMP_Y;
    pipeVelX = PIPE_VEL;
}
