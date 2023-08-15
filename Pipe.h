#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>

class Pipe {
public:
    int PIPE_VEL = 3;
    static const int PIPE_WIDTH = 100;
    static const int PIPE_HEIGHT = 600;
    SDL_Rect destRect;

    Pipe(const char* fileName, SDL_Renderer* ren, int x, int y, bool isFlip = false);
    virtual ~Pipe();
    void Update();
    void Render();
    void free();

    void pause();
    void notPause();
    void reset(int y);

private:
    int TEMP_X, TEMP_Y;
    bool pipeFlip;
    int TEMP_VEL;
    SDL_Texture* pipeTexture;
    SDL_Rect srcRect;
    SDL_Renderer* renderer;
};

#endif // PIPE_H
