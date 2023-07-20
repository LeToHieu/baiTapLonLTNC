#include "MyText.h"

MyText::MyText(SDL_Renderer* ren,std::string text,int x, int y, SDL_Color textColor, TTF_Font* font)
{
    renderer = ren;
	myTextTexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == NULL) {
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else {
		myTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (myTextTexture == NULL) {
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else {
            destRect.x = x;
			destRect.y = y;
			destRect.w = textSurface->w;
			destRect.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

MyText::~MyText()
{
    free();
}

void MyText::Render(){
    SDL_RenderCopy(renderer, myTextTexture, NULL, &destRect);
}

void MyText::free(){
    if( myTextTexture != NULL || myTextTexture != nullptr)
	{
		SDL_DestroyTexture( myTextTexture );
		myTextTexture = NULL;
	}
}
