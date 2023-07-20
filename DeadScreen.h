#ifndef DEADSCREEN_H
#define DEADSCREEN_H
#include "TextureManager.h"
#include "MyText.h"
#include "Button.h"
class DeadScreen
{
    public:
        static const int SCREEN_HEIGHT = 600;
        static const int SCREEN_WIDTH = 1200;

        DeadScreen(SDL_Renderer* ren, int &highScore, int &yourScore);
        virtual ~DeadScreen();
        void Render();
        void free();

        SDL_Rect bgRect;
        SDL_Rect outLineRect;
        MyText *BestScoreText = nullptr;
        MyText *YourScoreText = nullptr;
        Button *BackBtn = nullptr;
        Button *ResetBtn = nullptr;


    private:
        SDL_Renderer* renderer;
};

#endif // DEADSCREEN_H
