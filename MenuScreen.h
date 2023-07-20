#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "TextureManager.h"
#include "MyText.h"
#include "Button.h"

class MenuScreen
{
    public:
        static const int SCREEN_HEIGHT = 600;
        static const int SCREEN_WIDTH = 1200;

        MenuScreen(SDL_Renderer* ren);
        virtual ~MenuScreen();

        void Render();
        //bool handleEvent(SDL_Event& ev);
        void free();

        MyText *Title = nullptr;
        Button *PlayBtn = nullptr;
        Button *ExitBtn = nullptr;


    private:
        SDL_Renderer* renderer;
};

#endif // MENUSCREEN_H
