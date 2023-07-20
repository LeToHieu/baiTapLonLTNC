#ifndef MYTEXT_H
#define MYTEXT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "string"
#include <iostream>

class MyText
{
    public:
        MyText(SDL_Renderer* ren,std::string text,int x, int y, SDL_Color textColor, TTF_Font* font);
        virtual ~MyText();
        void Render();
        void free();
        SDL_Rect destRect;
    private:
        SDL_Texture* myTextTexture;
        SDL_Renderer* renderer;
};

#endif // MYTEXT_H
