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
    apple = new Fruit(renderer, "res/Apple.png", SCREEN_WIDTH + WIDTH_BET_PIPES/2+(Fruit::FRUIT_WIDTH)/2,  (SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);

    randPosition = (rand() % (ub - lb + 1)) + lb;
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+WIDTH_BET_PIPES, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition));
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+WIDTH_BET_PIPES, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true));
    coins.push_back(new Coin(renderer, SCREEN_WIDTH+ WIDTH_BET_PIPES +(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2, (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2));
    randPosition = (rand() % (ub - lb + 1)) + lb;
    banana = new Fruit(renderer, "res/Banana.png", SCREEN_WIDTH + WIDTH_BET_PIPES + WIDTH_BET_PIPES/2 +(Fruit::FRUIT_WIDTH)/2,(SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);


    randPosition = (rand() % (ub - lb + 1)) + lb;
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+2*WIDTH_BET_PIPES, (SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition));
    pipes.push_back(new Pipe("res/pipe.png", renderer, SCREEN_WIDTH+2*WIDTH_BET_PIPES, -(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 + randPosition, true));
    coins.push_back(new Coin(renderer, SCREEN_WIDTH+ WIDTH_BET_PIPES*2 +(Pipe::PIPE_WIDTH/2)-(Coin::COIN_WIDTH)/2, (SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2));
    randPosition = (rand() % (ub - lb + 1)) + lb;
    mushroom = new Fruit(renderer, "res/Mushroom.png", SCREEN_WIDTH + WIDTH_BET_PIPES + WIDTH_BET_PIPES + WIDTH_BET_PIPES/2 +(Fruit::FRUIT_WIDTH)/2,(SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);
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

    if(apple->destRect.x < -100+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2){
        apple->destRect.x = SCREEN_WIDTH+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2;
        apple->destRect.y = (SCREEN_HEIGHT/2) +  randPosition -(Fruit::FRUIT_HEIGHT)/2;
        randPosition = (rand() % (5 - 1 + 1)) + 1;

        if(randPosition == 5){
            apple->isClaim = false;
        }
    }

    if(banana->destRect.x < -100+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2){
        banana->destRect.x = SCREEN_WIDTH+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2;
        banana->destRect.y = (SCREEN_HEIGHT/2) +  randPosition -(Fruit::FRUIT_HEIGHT)/2;
        randPosition = (rand() % (5 - 1 + 1)) + 1;
        if(randPosition == 5){
            banana->isClaim = false;
        }
    }

    if(mushroom->destRect.x < -100+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2){
        mushroom->destRect.x = SCREEN_WIDTH+(Pipe::PIPE_WIDTH/2)-(Fruit::FRUIT_WIDTH)/2;
        mushroom->destRect.y = (SCREEN_HEIGHT/2) +  randPosition -(Fruit::FRUIT_HEIGHT)/2;
        randPosition = (rand() % (5 - 1 + 1)) + 1;
        if(randPosition == 5){
            mushroom->isClaim = false;
        }
    }

    apple->Update();
    banana->Update();
    mushroom->Update();
}

void Pipes::Render(){
    /*
    pipe1->Render();
    pipe2->Render();
    */
    apple->Render();
    banana->Render();
    mushroom->Render();

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
    apple->free();
    banana->free();
    mushroom->free();

    delete apple;
    delete banana;
    delete mushroom;

    pipes.clear();
    coins.clear();
}

void Pipes::pause(){
    apple->pause();
    banana->pause();
    mushroom->pause();
    for(Pipe* childPipe: pipes){
        childPipe->pause();
    }

    for(Coin* childCoin: coins){
        childCoin->pause();
    }
}
void Pipes::notPause(){
    apple->notPause();
    banana->notPause();
    mushroom->notPause();
    for(Pipe* childPipe: pipes){
        childPipe->notPause();
    }

    for(Coin* childCoin: coins){
        childCoin->notPause();
    }
}
void Pipes::reset(){
    int lb = -(SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2, ub = (SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2;
    int randPosition = (rand() % (ub - lb + 1)) + lb;
    apple->reset((SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);

    randPosition = (rand() % (ub - lb + 1)) + lb;
    banana->reset((SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);

    randPosition = (rand() % (ub - lb + 1)) + lb;
    mushroom->reset((SCREEN_HEIGHT/2)+randPosition-(Fruit::FRUIT_HEIGHT)/2);

    randPosition = (rand() % (ub - lb + 1)) + lb;

    int j = 0;
    for(int i = 0; i < pipes.size(); i+=2){
        Coin* childCoin = coins[j];
        Pipe* childPipe1 = pipes[i];
        Pipe* childPipe2 = pipes[i+1];
        childPipe1->reset((SCREEN_HEIGHT/2)+SPACE_BET_PIPES/2 +  randPosition);
        childPipe2->reset(-(SCREEN_HEIGHT/2)-SPACE_BET_PIPES/2 +  randPosition);
        childCoin->reset((SCREEN_HEIGHT/2) +  randPosition -(Coin::COIN_HEIGHT)/2);
        j++;
    }
    /*

    for(Pipe* childPipe: pipes){
        childPipe->reset();
    }

    for(Coin* childCoin: coins){
        childCoin->reset();
    }
    */
}

void Pipes::PlusVelo(){
    for(Pipe* childPipe: pipes){
        childPipe->PIPE_VEL+=1;
    }

    for(Coin* childCoin: coins){
        childCoin->COIN_VEL+=1;
    }
    apple->FRUIT_VEL+=1;
    banana->FRUIT_VEL+=1;
    mushroom->FRUIT_VEL+=1;
}

