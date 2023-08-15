#include "Bird.h"
#include"TextureManager.h"
#include<iostream>
#include<vector>

Bird::Bird(const char*fileName, SDL_Renderer* ren,int x, int y)
{
    birdTexture = TextureManager::LoadTexture(fileName, ren);
    birdTexture1 = TextureManager::LoadTexture("res/bird2.png", ren);
    birdTexture2 = TextureManager::LoadTexture("res/bird3.png", ren);

    ghostBirdTexture = TextureManager::LoadTexture("res/ghostBird1.png", ren);
    ghostBirdTexture1 = TextureManager::LoadTexture("res/ghostBird2.png", ren);
    ghostBirdTexture2 = TextureManager::LoadTexture("res/ghostBird3.png", ren);

    renderer = ren;
    birdPosX = x;
    birdPosY = y;
    birdVelX = 0;
    birdVelY = 0;

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
    isAlive = true;
    TEMP_X = x; TEMP_Y = y;

    pointMus = Mix_LoadWAV( "mus/sfx_point.wav" );
    hitMus = Mix_LoadWAV( "mus/sfx_hit.wav" );
    dieMus = Mix_LoadWAV( "mus/sfx_die.wav" );
    wingMus = Mix_LoadWAV( "mus/sfx_wing.wav" );
    powerGhostMus= Mix_LoadWAV( "mus/sfx_powerGhost.wav" );
	powerSmallMus= Mix_LoadWAV( "mus/sfx_powerSmall.wav" );
	powerBigMus = Mix_LoadWAV("mus/sfx_powerBig.wav");


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
    if(isAlive){
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && !isPause  /*&& !isJumping*/)
        {

            //Adjust the velocity
            switch( e.key.keysym.sym)
            {
                /*
                case SDLK_UP: birdVelY -= BIRD_VEL;angle = -45; break;
                case SDLK_DOWN: birdVelY += BIRD_VEL; break;
                case SDLK_LEFT: birdVelX -= BIRD_VEL; break;
                case SDLK_RIGHT: birdVelX += BIRD_VEL; break;
                */
                case SDLK_SPACE:
                    Mix_PlayChannel( -1, wingMus, 0 );
                    isJumping = true;
                    birdVelY -= BIRD_VEL;
                    angle = -45;
                break;
            }
        }

        //If a key was released
        /*
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 && !isPause)
        {

            //Adjust the velocity
            switch( e.key.keysym.sym )
            {

                case SDLK_UP: birdVelY += BIRD_VEL; break;
                case SDLK_DOWN: birdVelY -= BIRD_VEL; break;
                case SDLK_LEFT: birdVelX += BIRD_VEL; break;
                case SDLK_RIGHT: birdVelX -= BIRD_VEL; break;

                case SDLK_SPACE:
                    birdVelY += BIRD_VEL;
                    BirdCountVelo = 0;
                    break;
            }

        }
        */
    }

}

void Bird::move(std::vector<Pipe*> pipes, std::vector<Coin*> coins,Fruit* apple,Fruit* banana,Fruit* mushroom, int &score){


    if(checkCollision( destRect, apple->destRect) && apple->isClaim ==false){
        Mix_PlayChannel( -1, powerGhostMus, 0 );
        apple->isClaim = true;
        powerTime = SDL_GetTicks()+MAX_POWERTIME;
    }

    if(powerTime>SDL_GetTicks()){
        isInvisible = true;
    }else{
        isInvisible = false;
    }

    if(checkCollision( destRect, banana->destRect) && banana->isClaim ==false){
        Mix_PlayChannel( -1, powerSmallMus, 0 );
        banana->isClaim = true;
        powerTime2 = SDL_GetTicks()+MAX_POWERTIME;
    }

    if(powerTime2>SDL_GetTicks()){
        isSmall = true;
    }else{
        isSmall = false;
    }
    if(isSmall && powerTime2 > powerTime3){
        destRect.w = 30;
        destRect.h = 20;
    }

    if(checkCollision( destRect, mushroom->destRect) && mushroom->isClaim ==false){
        Mix_PlayChannel( -1, powerBigMus, 0 );
        mushroom->isClaim = true;
        powerTime3 = SDL_GetTicks()+MAX_POWERTIME;
    }

    if(powerTime3>SDL_GetTicks()){
        isBig = true;
    }else{
        isBig = false;
    }
    if(isBig && powerTime3 > powerTime2){
        destRect.w = 65;
        destRect.h = 55;
    }

    if(!isBig && !isSmall){
        destRect.w = BIRD_WIDTH;
        destRect.h = BIRD_HEIGHT;
    }


    SDL_Rect& coin1 = coins[0]->destRect;
    SDL_Rect& coin2 = coins[1]->destRect;
    SDL_Rect& coin3 = coins[2]->destRect;

    if(checkCollision( destRect, coin1)&& coins[0]->isClaim ==false){
        Mix_PlayChannel( -1, pointMus, 0 );
        coins[0]->isClaim = true;
        score++;
    }
    if(checkCollision( destRect, coin2) && coins[1]->isClaim ==false){
        Mix_PlayChannel( -1, pointMus, 0 );
        coins[1]->isClaim = true;
        score++;
    }
    if(checkCollision( destRect, coin3) && coins[2]->isClaim ==false){
        Mix_PlayChannel( -1, pointMus, 0 );
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

        if(isAlive){
            birdPosX += birdVelX;
        }
        destRect.x = birdPosX;

        //If the dot went too far to the left or right
        if( ( birdPosX < 0 ) || ( birdPosX + BIRD_WIDTH > 800 )){
            //Move back
            if(isAlive){
                Mix_PlayChannel( -1, hitMus, 0 );
                Mix_PlayChannel( -1, dieMus, 0 );
            }

            birdPosX -= birdVelX;
            destRect.x = birdPosX;
            isAlive = false;
        }

        if((checkCollision( destRect, pipe1)
           || checkCollision( destRect, pipe2)
           || checkCollision( destRect, pipe3 )
           || checkCollision( destRect, pipe4 )
           || checkCollision( destRect, pipe5 )
           || checkCollision( destRect, pipe6 )) && !isInvisible){
            if(isAlive){
                Mix_PlayChannel( -1, hitMus, 0 );
                Mix_PlayChannel( -1, dieMus, 0 );
            }
            birdPosX -= 3;
            destRect.x = birdPosX;
            isAlive = false;
        }

        BirdCountVelo +=birdVelY;
        //birdPosY += Gravity;
        if(isAlive){
            //birdVelY+=Gravity;
            if(BirdCountVelo>=-150){
                birdPosY += birdVelY/*+Gravity*/;
            }else{
                birdPosY += Gravity;
            }
            if(BirdCountVelo <= -150){
                BirdCountVelo = 0;
                birdVelY += BIRD_VEL;
                //isJumping = false;
            }

            if(BirdCountVelo==0){
                birdPosY += Gravity;
            }


        }else{
            birdVelY = 0;
            birdPosY += Gravity;
        }

        destRect.y = birdPosY;



        //Move the dot up or down
        //If the dot went too far up or down
        if( ( birdPosY < 0 ) || ( birdPosY + BIRD_HEIGHT > 600 )){
            //Move back
            if(isAlive){
                Mix_PlayChannel( -1, hitMus, 0 );
                Mix_PlayChannel( -1, dieMus, 0 );
            }
            birdPosY -= birdVelY+Gravity;
            destRect.y = birdPosY;
            isAlive = false;
        }

        if((checkCollision( destRect, pipe1)
               || checkCollision( destRect, pipe2)
               || checkCollision( destRect, pipe3)
               || checkCollision( destRect, pipe4)
               || checkCollision( destRect, pipe5)
               || checkCollision( destRect, pipe6)) && !isInvisible
           ){
            //Move back
            if(isAlive){
                Mix_PlayChannel( -1, hitMus, 0 );
                Mix_PlayChannel( -1, dieMus, 0 );
            }
            birdPosY -= birdVelY+Gravity;
            destRect.y = birdPosY;
            isAlive = false;
        }
}

void Bird::Render(){
    //SDL_RenderCopy(renderer, birdTexture, &srcRect , &destRect);
    BirdFlap+=5;

    if(!isInvisible){
        if(BirdFlap < 45){
            SDL_RenderCopyEx( renderer, birdTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
        }else if(BirdFlap < 90){
            SDL_RenderCopyEx( renderer, birdTexture1, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
        }else if(BirdFlap < 135){
            SDL_RenderCopyEx( renderer, birdTexture2, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
            BirdFlap = 0;
        }
    }

    if(isInvisible){
        if(BirdFlap < 45 && isInvisible){
            SDL_RenderCopyEx( renderer, ghostBirdTexture, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
        }else if(BirdFlap < 90){
            SDL_RenderCopyEx( renderer, ghostBirdTexture1, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
        }else if(BirdFlap < 135){
            SDL_RenderCopyEx( renderer, ghostBirdTexture2, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
            BirdFlap = 0;
        }
    }




}

void Bird::free(){
    if( birdTexture != NULL || birdTexture != nullptr)
	{
		SDL_DestroyTexture( birdTexture );
		birdTexture = NULL;
	}
	if( birdTexture1 != NULL || birdTexture1 != nullptr)
	{
		SDL_DestroyTexture( birdTexture1 );
		birdTexture1 = NULL;
	}
	if( birdTexture2 != NULL || birdTexture2 != nullptr)
	{
		SDL_DestroyTexture( birdTexture2 );
		birdTexture2 = NULL;
	}

	//
	if( ghostBirdTexture != NULL || ghostBirdTexture != nullptr)
	{
		SDL_DestroyTexture( ghostBirdTexture );
		ghostBirdTexture = NULL;
	}
	if( ghostBirdTexture1 != NULL || ghostBirdTexture1 != nullptr)
	{
		SDL_DestroyTexture( ghostBirdTexture1 );
		ghostBirdTexture1 = NULL;
	}
	if( ghostBirdTexture2 != NULL || ghostBirdTexture2 != nullptr)
	{
		SDL_DestroyTexture( ghostBirdTexture2 );
		ghostBirdTexture2 = NULL;
	}
	Mix_FreeChunk(pointMus);
	Mix_FreeChunk(hitMus);
	Mix_FreeChunk(dieMus);
	Mix_FreeChunk(wingMus);
	Mix_FreeChunk(powerGhostMus);
	Mix_FreeChunk(powerSmallMus);
	Mix_FreeChunk(powerBigMus);
	pointMus = NULL;
	hitMus= NULL;
	dieMus= NULL;
	wingMus= NULL;
	powerGhostMus= NULL;
	powerSmallMus= NULL;
	powerBigMus = NULL;
}

void Bird::pause(){

    isPause = true;
}
void Bird::notPause(){
    isPause = false;
}
void Bird::reset(){
    if(isPause){
        notPause();
    }
    BirdCountVelo = 0;
    isAlive = true;
    isJumping = false;
    destRect.x = TEMP_X;
    destRect.y = TEMP_Y;
    birdPosX = TEMP_X;
    birdPosY = TEMP_Y;
    birdVelY = 0;
    birdVelX = 0;
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
