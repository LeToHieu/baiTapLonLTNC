#include "Bird.h"
#include"TextureManager.h"
#include<iostream>
#include<vector>

Bird::Bird(const char*fileName, SDL_Renderer* ren,int x, int y)
{
    birdTexture = TextureManager::LoadTexture(fileName, ren);
    renderer = ren;
    birdPosX = x;
    birdPosY = y;
    birdVelX = 0;
    birdVelY = 10;

    //
    srcRect.h = 600;
    srcRect.w = 600;
    srcRect.x = 0;
    srcRect.y = 0;


    destRect.x = birdPosX;
    destRect.y = birdPosY;
    destRect.w = BIRD_WIDTH;
    destRect.h = BIRD_HEIGHT;
    angle=0;
    isPause = false;
    TEMP_X = x; TEMP_Y = y; TEMP_VEL = BIRD_VEL;
}

Bird::~Bird()
{
    free();
}
/*
void Bird::Update(){
    srcRect.h = 600;
    srcRect.w = 600;
    srcRect.x = 0;
    srcRect.y = 0;


    destRect.x = birdPosX;
    destRect.y = birdPosY;
    destRect.w = BIRD_WIDTH;
    destRect.h = BIRD_HEIGHT;
}
*/

void Bird::handleEvent(SDL_Event& e){

    if(!isPause){
        angle+=3;
    }
    if(angle >= 90){
        angle = 90;
    }

    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && !isPause)
    {

        //Adjust the velocity
        switch( e.key.keysym.sym)
        {
            case SDLK_UP: birdVelY -= BIRD_VEL; break;
            case SDLK_DOWN: birdVelY += BIRD_VEL; break;
            case SDLK_LEFT: birdVelX -= BIRD_VEL; break;
            case SDLK_RIGHT: birdVelX += BIRD_VEL; break;
            case SDLK_SPACE:
                birdVelY -= BIRD_VEL;
                angle = -45;
            break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: birdVelY += BIRD_VEL; break;
            case SDLK_DOWN: birdVelY -= BIRD_VEL; break;
            case SDLK_LEFT: birdVelX += BIRD_VEL; break;
            case SDLK_RIGHT: birdVelX -= BIRD_VEL; break;
            case SDLK_SPACE: birdVelY += BIRD_VEL;  break;
        }
    }
}

void Bird::move(std::vector<Pipe*> pipes, std::vector<Coin*> coins, int &score){

    SDL_Rect& coin1 = coins[0]->destRect;
    SDL_Rect& coin2 = coins[1]->destRect;
    SDL_Rect& coin3 = coins[2]->destRect;

    if(checkCollision( destRect, coin1)&& coins[0]->isClaim ==false){
        coins[0]->isClaim = true;
        score++;
    }
    if(checkCollision( destRect, coin2) && coins[1]->isClaim ==false){
        coins[1]->isClaim = true;
        score++;
    }
    if(checkCollision( destRect, coin3) && coins[2]->isClaim ==false){
        coins[2]->isClaim = true;
        score++;

    }

    SDL_Rect& pipe1 = pipes[0]->destRect;
    SDL_Rect& pipe2 = pipes[1]->destRect;
    SDL_Rect& pipe3 = pipes[2]->destRect;
    SDL_Rect& pipe4 = pipes[3]->destRect;
    SDL_Rect& pipe5 = pipes[4]->destRect;
    SDL_Rect& pipe6 = pipes[5]->destRect;

        //Move the dot left or right

        birdPosX += birdVelX;
            destRect.x = birdPosX;

        //If the dot went too far to the left or right
        if( ( birdPosX < 0 ) || ( birdPosX + BIRD_WIDTH > 800 )
           || checkCollision( destRect, pipe1)
           || checkCollision( destRect, pipe2)
           || checkCollision( destRect, pipe3 )
           || checkCollision( destRect, pipe4 )
           || checkCollision( destRect, pipe5 )
           || checkCollision( destRect, pipe6 )
        ){
            //Move back
            birdPosX -= birdVelX;
            destRect.x = birdPosX;
        }

        if(checkCollision( destRect, pipe1)
           || checkCollision( destRect, pipe2)
           || checkCollision( destRect, pipe3 )
           || checkCollision( destRect, pipe4 )
           || checkCollision( destRect, pipe5 )
           || checkCollision( destRect, pipe6 )){
            birdPosX -= 3;
            destRect.x = birdPosX;
        }


        birdPosY += birdVelY;
        destRect.y = birdPosY;


        //Move the dot up or down
        //If the dot went too far up or down
        if( ( birdPosY < 0 ) || ( birdPosY + BIRD_HEIGHT > 600 )
                ||checkCollision( destRect, pipe1)
               || checkCollision( destRect, pipe2)
               || checkCollision( destRect, pipe3)
               || checkCollision( destRect, pipe4)
               || checkCollision( destRect, pipe5)
               || checkCollision( destRect, pipe6)
           ){
            //Move back
            birdPosY -= birdVelY;
            destRect.y = birdPosY;
        }
}

void Bird::Render(){
    //SDL_RenderCopy(renderer, birdTexture, &srcRect , &destRect);
    SDL_RenderCopyEx( renderer, birdTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void Bird::free(){
    if( birdTexture != NULL || birdTexture != nullptr)
	{
		SDL_DestroyTexture( birdTexture );
		birdTexture = NULL;
	}
}

void Bird::pause(){
    BIRD_VEL = 0;
    birdVelY = 0;
    isPause = true;
}
void Bird::notPause(){
    BIRD_VEL = 40;
    birdVelY = 10;
    isPause = false;
}
void Bird::reset(){
    if(isPause){
        notPause();
    }
    destRect.x = TEMP_X;
    destRect.y = TEMP_Y;
    birdPosX = TEMP_X;
    birdPosY = TEMP_Y;
    BIRD_VEL = TEMP_VEL;
    angle = 0;
}

bool Bird::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;


    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
