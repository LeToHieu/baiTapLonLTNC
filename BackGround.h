#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "TextureManager.h"

class BackGround
{
    public:
        BackGround(SDL_Renderer* ren);
        virtual ~BackGround();
        void Update(); void Render();
        void free();

    protected:

    private:
        int scrollingOffset = 0;
        SDL_Renderer* renderer;
        SDL_Texture* backGround;
        SDL_Rect srcRect, destRect;
};

#endif // BACKGROUND_H
