#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
    public:
        static SDL_Texture *LoadTexture(const char*fileName, SDL_Renderer *renderer);
        // static SDL_Texture *loadFromRenderedText(SDL_Renderer* Renderer, string textureText, SDL_Color textColor, TTF_Font* font);

};

#endif // TEXTUREMANAGER_H
