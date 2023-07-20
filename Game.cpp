#include "Game.h"
#include "TextureManager.h"
#include "Bird.h"
#include "Pipe.h"
#include "Pipes.h"
#include "BackGround.h"
#include "Button.h"
#include "MyText.h"
#include "MenuScreen.h"
#include <fstream>
#include <iostream>
#include <string>
#include<vector>

enum Screen {
    MyMenu = 0,
    MyGame = 1,
    MyPause = 2,
    MyDead = 3,
};

Screen Current = MyMenu;


Bird *player = nullptr;
Pipes *pipes = nullptr;
BackGround *backGround = nullptr;
Button *musBtn = nullptr;
Button *pauseBtn = nullptr;
MyText *scoreText = nullptr;
MyText *highScoreText = nullptr;
MenuScreen *menuScreen = nullptr;

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
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            std::cout << "Renderer created!" << std::endl;
        }


        if (TTF_Init() == -1)
        {
            std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
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
            Current = MyGame;
        }
        if(menuScreen->ExitBtn->handleEvent(event)){
            isRunning = false;
        }
    }
    if(Current == MyGame){
        player->handleEvent(event);
        if(pauseBtn->handleEvent(event)){
            pause();
        }
    }
    if(musBtn->handleEvent2(event)){
        reset();
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
    backGround->Update();
    if(Current == MyGame){
        player->move(pipes->pipes, pipes->coins, score);
        pipes->Update();


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
    musBtn->Render();

    if(Current == MyGame){
        player->Render();
        pipes->Render();
        pauseBtn->Render();
        scoreText->Render();
        highScoreText->Render();
    }

    if(Current == MyMenu){
        menuScreen->Render();
    }

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
    delete backGround; delete player; delete musBtn; delete pauseBtn; delete scoreText; delete highScoreText;


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Clear!"<<std::endl;
}
