#ifndef BIRD_H
#define BIRD_H
#include<SDL.h>
#include<vector>
#include "Pipes.h"
#include <SDL_mixer.h>

class Bird
{
    public:
        int BIRD_VEL = 10;
        int Gravity = 10;
        static const int BIRD_WIDTH = 50;
		static const int BIRD_HEIGHT = 40;

        Bird(const char*fileName, SDL_Renderer* ren,int x, int y);
        virtual ~Bird();
        void Update();
        void Render();
        void handleEvent(SDL_Event& e);
		void move(std::vector<Pipe*> pipes,std::vector<Coin*> coins,Fruit* apple,Fruit* banana,int &score);
		bool checkCollision( SDL_Rect a, SDL_Rect b );
		void free();
		void pause();
		void notPause();
		void reset();
		bool isAlive;

    private:
        bool isPause;
        bool isInvisible = false;
        bool isSmall = false;
        float angle;
        int BirdFlap = 0;
        int BirdCountVelo = 0;
        int birdPosX, birdPosY;
        //The velocity of the dot
		int birdVelX, birdVelY;

        int TEMP_X, TEMP_Y;

        int powerTime = 0, powerTime2 = 0, MAX_POWERTIME = 3000;

        SDL_Texture* birdTexture;
        SDL_Texture* birdTexture1;
        SDL_Texture* birdTexture2;

        SDL_Texture* ghostBirdTexture;
        SDL_Texture* ghostBirdTexture1;
        SDL_Texture* ghostBirdTexture2;

        Mix_Chunk* pointMus;
        Mix_Chunk* hitMus;
        Mix_Chunk* dieMus;
        Mix_Chunk* wingMus;
        Mix_Chunk* powerGhostMus;
        Mix_Chunk* powerSmallMus;

        SDL_Rect srcRect, destRect;
        SDL_Renderer* renderer;
};

#endif // BIRD_H
