#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H
#include "TextureManager.h"
#include "MyText.h"
#include "Button.h"

class PauseScreen
{
    public:
        static const int SCREEN_HEIGHT = 600;
        static const int SCREEN_WIDTH = 1200;

        static const int PAUSE_SCREEN_HEIGHT = 500;
        static const int PAUSE_SCREEN_WIDTH = 550;

        PauseScreen(SDL_Renderer* ren, int &highScore);
        virtual ~PauseScreen();
        void Render();
        void free();

        SDL_Rect bgRect;
        SDL_Rect outLineRect;
        MyText *BestScoreText = nullptr;
        MyText *PauseText = nullptr;
        Button *BackBtn = nullptr;
        Button *ContinueBtn = nullptr;


    private:
        SDL_Renderer* renderer;
};

#endif // PAUSESCREEN_H
