#include "Button.h"
#include <iostream>
Button::Button(const char*fileName, SDL_Renderer* ren,int x, int y, int w, int h)
{
    //free();
    renderer = ren;
    btnTexture = TextureManager::LoadTexture(fileName, ren);
    for (int i = 0; i < 3; i++) {
		Shape[i].x = 0;
		Shape[i].y = i * h;
		Shape[i].w = w;
		Shape[i].h = h;
	}
    CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;

    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
}

Button::~Button()
{
    free();
}
bool Button::isInside(int x, int y) {
	if (x < destRect.x || x > destRect.x + destRect.w || y < destRect.y || y > destRect.y + destRect.h) {
		return false;
	}
	return true;
}

bool Button::handleEvent(SDL_Event& ev){
    switch(ev.type){
        case SDL_MOUSEMOTION:
            if (isInside(ev.button.x, ev.button.y)) {

                CurrentState = BUTTON_STATE_MOUSE_OVER_MOTION;
            }else {
                CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(isInside(ev.button.x, ev.button.y)) {
                CurrentState = BUTTON_STATE_MOUSE_CLICK;
                return true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(isInside(ev.button.x, ev.button.y)) {
                CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;
            }
            break;
    }
    return false;
}

bool Button::handleEvent2(SDL_Event& ev){
    switch(ev.type){
        case SDL_MOUSEBUTTONDOWN:
            if (isInside(ev.button.x, ev.button.y) == true) {
                if (CurrentState == BUTTON_STATE_MOUSE_OUTSIDE) {
                    CurrentState = BUTTON_STATE_MOUSE_OVER_MOTION;
                }
                else if(CurrentState == BUTTON_STATE_MOUSE_OVER_MOTION) {
                    CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;
                }
                return true;
            }
    }
    return false;
}

void Button::Render() {
	SDL_RenderCopy(renderer, btnTexture, &Shape[CurrentState], &destRect);
}

void Button::free()
{
    if( btnTexture != NULL || btnTexture != nullptr)
	{
		SDL_DestroyTexture( btnTexture );
		btnTexture = NULL;
	}
}
