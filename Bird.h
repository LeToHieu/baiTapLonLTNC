#ifndef BIRD_H
#define BIRD_H
#include<SDL.h>
#include<vector>
#include "Pipes.h"

class Bird
{
    public:
        int BIRD_VEL = 40;
        static const int BIRD_WIDTH = 50;
		static const int BIRD_HEIGHT = 40;

        Bird(const char*fileName, SDL_Renderer* ren,int x, int y);
        virtual ~Bird();
        void Update();
        void Render();
        void handleEvent(SDL_Event& e);
		void move(std::vector<Pipe*> pipes,std::vector<Coin*> coins,int &score);
		bool checkCollision( SDL_Rect a, SDL_Rect b );
		void free();
		void pause();
		void notPause();
		void reset();

    private:
        bool isPause;
        float angle;
        int birdPosX, birdPosY;
        //The velocity of the dot
		int birdVelX, birdVelY;

        int TEMP_X, TEMP_Y, TEMP_VEL;

        SDL_Texture* birdTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};

#endif // BIRD_H
