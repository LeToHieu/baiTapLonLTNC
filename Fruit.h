#ifndef FRUIT_H
#define FRUIT_H
#include "TextureManager.h"

class Fruit
{
    public:
        Fruit(SDL_Renderer* ren,const char*fileName ,int x, int y);
        virtual ~Fruit();
        int FRUIT_VEL = 3;
        static const int FRUIT_HEIGHT = 50;
        static const int FRUIT_WIDTH = 50;
        void Update();
        void Render();
        void free();
        bool isClaim = true;
        SDL_Rect destRect;
        void pause();
        void notPause();
        void reset(int y);

    private:
        int TEMP_X, TEMP_Y, TEMP_VEL;
        SDL_Texture* fruitTexture;
        SDL_Renderer* renderer;
};

#endif // FRUIT_H
