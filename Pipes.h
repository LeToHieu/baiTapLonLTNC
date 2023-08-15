#ifndef PIPES_H
#define PIPES_H
#include "Pipe.h"
#include "Coin.h"
#include "Fruit.h"
#include<vector>
class Pipes
{
    public:
        Pipes(SDL_Renderer* ren);
        virtual ~Pipes();
        void Render();
        void Update();
        void PlusVelo();
        //SDL_Rect getDestRect1();
        //SDL_Rect getDestRect2();
        static const int SPACE_BET_PIPES = 230;
        static const int WIDTH_BET_PIPES = 440;
        std::vector<Pipe*> pipes;
        std::vector<Coin*> coins;
        Fruit* apple;
        Fruit* banana;
        Fruit* mushroom;

        static const int SCREEN_HEIGHT = 600;
        static const int SCREEN_WIDTH = 1200;
        void free();

        void pause();
        void notPause();
        void reset();

    private:
        SDL_Renderer* renderer;
};

#endif // PIPES_H
