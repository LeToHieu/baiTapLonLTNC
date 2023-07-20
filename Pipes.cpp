#include "Pipes.h"
#include "Pipe.h"
#include <time.h>
#include <iostream>

Pipes::Pipes(SDL_Renderer* ren)
{
    srand(time(0));
    int lb = -(SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2, ub = (SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2;
    int randPosition = (rand() % (ub - lb + 1)) + lb;

    renderer = ren;

    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition));
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true));
    coins.push_back(new Coin(renderer, SCREEN_WIDTH+(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2, (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2));

    randPosition = (rand() % (ub - lb + 1)) + lb;
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+WIDTH_BET_PIPES, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition));
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+WIDTH_BET_PIPES, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true));
    coins.push_back(new Coin(renderer, SCREEN_WIDTH+ WIDTH_BET_PIPES +(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2, (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2));

    randPosition = (rand() % (ub - lb + 1)) + lb;
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+2*WIDTH_BET_PIPES, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition));
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+2*WIDTH_BET_PIPES, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true));
    coins.push_back(new Coin(renderer, SCREEN_WIDTH+ WIDTH_BET_PIPES*2 +(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2, (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2));

    /*
    pipe1 = new Pipe("res/pipe.png", renderer, SCREEN_WIDTH, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition);
    pipe2 = new Pipe("res/pipe.png", renderer, SCREEN_WIDTH, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true);
    */
}

Pipes::~Pipes()
{
    free();
}

void Pipes::Update(){

    int lb = -(SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2, ub = (SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2;
    int randPosition = (rand() % (ub - lb + 1)) + lb;

    for(int i = 0; i < pipes.size(); i+=2){
        Pipe* childPipe1 = pipes[i];
        Pipe* childPipe2 = pipes[i+1];
        if(childPipe1->destRect.x < -100){
            childPipe1->destRect.x = SCREEN_WIDTH;
            childPipe2->destRect.x = SCREEN_WIDTH;
            childPipe1->destRect.y = (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition;
            childPipe2->destRect.y = -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition;
        }
        childPipe1->Update();
        childPipe2->Update();
    }
    for(Coin* childCoin: coins){
        if(childCoin->destRect.x < -100+(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2){
            childCoin->destRect.x = SCREEN_WIDTH+(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2;
            childCoin->destRect.y = (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2;
            childCoin->isClaim = false;
        }
        childCoin->Update();
    }
}

void Pipes::Render(){
    /*
    pipe1->Render();
    pipe2->Render();
    */
    for(Pipe* childPipe: pipes){
        childPipe->Render();
    }

    for(Coin* childCoin: coins){
        childCoin->Render();
    }
}

/*
SDL_Rect Pipes::getDestRect1(){
    return pipe1->destRect;
}
*/
/*
SDL_Rect Pipes::getDestRect2(){
    return pipe2->destRect;
}
*/

void Pipes::free(){
    /*
    pipe1->free();
    pipe2->free();
    delete pipe1;
    delete pipe2;
    */
    for(Pipe* childPipe: pipes){
        childPipe->free();
        delete childPipe;
    }

    for(Coin* childCoin: coins){
        childCoin->free();
        delete childCoin;
    }
    pipes.clear();
}

void Pipes::pause(){
    for(Pipe* childPipe: pipes){
        childPipe->pause();
    }

    for(Coin* childCoin: coins){
        childCoin->pause();
    }
}
void Pipes::notPause(){
    for(Pipe* childPipe: pipes){
        childPipe->notPause();
    }

    for(Coin* childCoin: coins){
        childCoin->notPause();
    }
}
void Pipes::reset(){
    for(Pipe* childPipe: pipes){
        childPipe->reset();
    }

    for(Coin* childCoin: coins){
        childCoin->reset();
    }
}

