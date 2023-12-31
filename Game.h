#ifndef GAME_H
#define GAME_H
#include<SDL.h>
#include <SDL_image.h>
#include<iostream>

class Game
{
    public:
        Game();
        virtual ~Game();
        void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void clean();
        bool running(){
            return isRunning;
        };
    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;

};

#endif // GAME_H
