#include "Game.h"
#include "TextureManager.h"
#include "Bird.h"
#include "Pipe.h"
#include "Pipes.h"
#include "BackGround.h"
#include "Button.h"
#include "MyText.h"
#include "MenuScreen.h"
#include "PauseScreen.h"
#include "DeadScreen.h"
#include <fstream>
#include <iostream>
#include <string>
#include<vector>
#include <SDL_mixer.h>

enum Screen {
    MyMenu = 0,
    MyGame = 1,
    MyPause = 2,
    MyDead = 3,
};

Screen Current = MyMenu;

Mix_Chunk* selectMus;
Mix_Chunk* pauseMus;
Mix_Music* bgMus;

Bird *player = nullptr;
Pipes *pipes = nullptr;
BackGround *backGround = nullptr;
Button *musBtn = nullptr;
Button *pauseBtn = nullptr;
MyText *scoreText = nullptr;
MyText *highScoreText = nullptr;
MenuScreen *menuScreen = nullptr;
PauseScreen *pauseScreen = nullptr;
DeadScreen *deadScreen = nullptr;

int score = 0;
int tempScore = 10;
int highScore = 0;

const int SPACE_BET_PIPES = 170;
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 1200;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
    clean();
}

void pause(){
    player->pause();
    pipes->pause();
}
void notPause(){
    player->notPause();
    pipes->notPause();
}
void reset(){
    score = 0;
    player->reset();
    pipes->reset();
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flag = 0;
    if(fullscreen){
        flag = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystem Initiallied" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if(window){
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface* icon = IMG_Load("res/backGround.png");
        SDL_SetWindowIcon(window, icon);

        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            std::cout << "Renderer created!" << std::endl;
        }


        if (TTF_Init() == -1)
        {
            std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            isRunning = false;
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            std::cout <<"SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            isRunning = false;
        }



        isRunning = true;

        player = new Bird("res/bird.png", renderer, 300, 50);

        pipes = new Pipes(renderer);

        backGround = new BackGround(renderer);

        musBtn = new Button("res/speaker.png", renderer, SCREEN_WIDTH-70-20, SCREEN_HEIGHT-62-20, 70,62);
        pauseBtn = new Button("res/pause.png", renderer, SCREEN_WIDTH-70-20, 20, 70,62);

        std::ifstream infile("score.txt");

        if (infile.is_open()){
            infile >> highScore;
            infile.close();
        } else {
            std::cout << "Error opening file.\n";
        }
        highScoreText = new MyText(renderer, "High Score: " + std::to_string(highScore),0 ,30 ,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 30));

        menuScreen = new MenuScreen(renderer);
        pauseScreen = new PauseScreen(renderer, highScore);
        deadScreen = new DeadScreen(renderer, highScore, score);


        selectMus = Mix_LoadWAV( "mus/select.wav" );
        pauseMus = Mix_LoadWAV( "mus/pause.wav" );
        bgMus = Mix_LoadMUS( "mus/bgMus.mp3" );
        Mix_PlayMusic( bgMus, -1 );
    }else{
        isRunning = false;
    }
}

void Game::handleEvents()
{
    //dtor
    SDL_Event event;
    SDL_PollEvent(&event);

    if(Current == MyMenu){
        if(menuScreen->PlayBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            Current = MyGame;
        }
        if(menuScreen->ExitBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            isRunning = false;
        }
    }
    if(Current == MyGame || Current == MyDead){
        player->handleEvent(event);
        if(pauseBtn->handleEvent(event)){
            Mix_PlayChannel( -1, pauseMus, 0 );
            Current = MyPause;
            pause();
        }
        if(player->isAlive == false && Current != MyDead){
            Current = MyDead;
            pipes->pause();
            pauseScreen = new PauseScreen(renderer, highScore);
            deadScreen = new DeadScreen(renderer, highScore, score);
        }
    }

    if(Current == MyPause){
        if(pauseScreen->ContinueBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            Current = MyGame;
            notPause();
        }
        if(pauseScreen->BackBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            Current = MyMenu;
            reset();
        }
    }
    if(Current == MyDead){
        if(deadScreen->ResetBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            Current = MyGame;
            reset();
        }
        if(deadScreen->BackBtn->handleEvent(event)){
            Mix_PlayChannel( -1, selectMus, 0 );
            Current = MyMenu;
            reset();
        }
    }

    if(musBtn->handleEvent2(event)){
        Mix_PlayChannel( -1, selectMus, 0 );
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        } else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }

    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    static bool flagPlusVel = true;
    backGround->Update();
    if(Current == MyGame || Current == MyDead ){
        player->move(pipes->pipes, pipes->coins, pipes->apple, pipes->banana, pipes->mushroom, score);
        pipes->Update();

        if( score % 10 == 0 && score != 0 && flagPlusVel){
            pipes->PlusVelo();
            flagPlusVel = false;
        }else if(score % 10 !=0 ){
            flagPlusVel = true;
        }



        if(score>=highScore && tempScore != score){
            highScore = score;
            highScoreText = new MyText(renderer, "High Score: " + std::to_string(highScore),0 ,30 ,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 30));
            std::ofstream outfile("score.txt");

            if (outfile.is_open()) {
                outfile << highScore;
                outfile.close();
                //std::cout << "File successfully written.\n";
            }else{
                //std::cout << "Error opening file.\n";
            }
        }
        if(tempScore != score){
            scoreText = new MyText(renderer, "Your Score: " + std::to_string(score), 0, 0,{ 255, 255, 255 } ,TTF_OpenFont("font/Roboto-Medium.ttf", 30));
            tempScore = score;
        }
    }
    //dtor
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    //add stuff to render
    backGround->Render();
    if(Current == MyGame || Current == MyPause || Current == MyDead){
        player->Render();
        pipes->Render();
        pauseBtn->Render();
        scoreText->Render();
        highScoreText->Render();
    }
    if(Current == MyPause){
        pauseScreen->Render();
    }
    if(Current == MyDead){
        deadScreen->Render();
    }

    if(Current == MyMenu){
        menuScreen->Render();
    }
    musBtn->Render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    pipes->free();
    backGround->free();
    player->free();
    musBtn->free();
    pauseBtn->free();

    if(Current == MyGame){
        scoreText->free();
        highScoreText->free();
    }

    menuScreen->free();
    pauseScreen->free();
    deadScreen->free();
    Mix_FreeChunk(selectMus);
    Mix_FreeChunk(pauseMus);
    Mix_FreeMusic( bgMus );
    selectMus = NULL;
    pauseMus= NULL;
    bgMus= NULL;

    delete backGround; delete player; delete musBtn; delete pauseBtn; delete scoreText; delete highScoreText;


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Clear!"<<std::endl;
}
