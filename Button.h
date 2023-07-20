#ifndef BUTTON_H
#define BUTTON_H
#include "TextureManager.h"

enum ButtonState {
	BUTTON_STATE_MOUSE_OUTSIDE = 0,
	BUTTON_STATE_MOUSE_OVER_MOTION = 1,
	BUTTON_STATE_MOUSE_CLICK = 2,
	BUTTON_STATE_MOUSE_REALEASE = 3,
	BUTTON_STATE_TOTAL = 4
};

class Button
{
    public:
        Button(const char*fileName, SDL_Renderer* ren,int x, int y, int w, int h);
        virtual ~Button();
        void Render();
        bool handleEvent(SDL_Event& ev);
        bool handleEvent2(SDL_Event& ev);
        void free();
        bool isInside(int x, int y);
        SDL_Rect destRect;

    private:
        SDL_Texture* btnTexture;
        ButtonState CurrentState;
        SDL_Rect Shape[BUTTON_STATE_TOTAL];
        SDL_Renderer* renderer;

};

#endif // BUTTON_H
