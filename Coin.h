#ifndef COIN_H
#define COIN_H
#include "TextureManager.h"

class Coin
{
    public:
        Coin(SDL_Renderer* ren,int x, int y);
        virtual ~Coin();
        int COIN_VEL = 3;
        static const int COIN_HEIGHT = 70;
        static const int COIN_WIDTH = 70;
        void Update();
        void Render();
        void free();
        bool isClaim;
        SDL_Rect destRect;
        void pause();
        void notPause();
        void reset();

    private:
        int TEMP_X, TEMP_Y, TEMP_VEL;
        SDL_Texture* coinTexture;
        SDL_Renderer* renderer;
};

#endif // COIN_H
