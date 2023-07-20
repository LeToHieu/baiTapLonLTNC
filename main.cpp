#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"

Game *game = nullptr;


int main(int argv, char** args){
    /*
        Idea of the game loop
        while(gameIsRunning){
         handle any user input
         update all object
         render change to the display
        }
    */
    const int FPS = 60;
    const int frameDelay = 1000/60;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("PlippyFlap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600,false);

    while(game->running()){
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        //std::cout << frameTime << std::endl;

        if(frameDelay>frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}
