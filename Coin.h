#ifndef COIN_H
#define COIN_H
#include "TextureManager.h"

class Coin
{
    public:
        Coin(SDL_Renderer* ren,int x, int y);
        virtual ~Coin();
        int COIN_VEL = 3;
        static const int COIN_HEIGHT = 50;
        static const int COIN_WIDTH = 50;
        void Update();
        void Render();
        void free();
        bool isClaim;
        SDL_Rect destRect;
        void pause();
        void notPause();
        void reset(int y);

    private:
        int coinSpin = 0;
        int TEMP_X, TEMP_Y, TEMP_VEL;
        SDL_Texture* coinTexture1;
        SDL_Texture* coinTexture2;
        SDL_Texture* coinTexture3;
        SDL_Texture* coinTexture4;
        SDL_Texture* coinTexture5;
        SDL_Texture* coinTexture6;
        SDL_Renderer* renderer;
};

#endif // COIN_H
