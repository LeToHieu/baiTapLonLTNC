#include "TextureManager.h"


SDL_Texture *TextureManager::LoadTexture(const char*fileName, SDL_Renderer *renderer){
    SDL_Surface*tmpSurface = IMG_Load(fileName);
    SDL_Texture* Tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return Tex;
}
