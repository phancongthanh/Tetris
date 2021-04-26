#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <SDL_mixer.h>
#include <fstream>
#include "SDL_lib.h"
#include "SDL_ImageObject.h"
#include "SDL_TextObject.h"

const int NUMBER_COLOR = 8;
extern SDL_Color Game_Color[];

enum Status{NOTEXIST=0, STANDSTILL=1, FALL=2, MOVE=3};
struct Square
{
    static SDL_Renderer* Renderer;
    static int squareEdge;
    int x,y;
    int movelength = 0;
    int color = 0;
    Status status = NOTEXIST;

    void paintSquare() const;
};

struct Tetris_Display
{
    SDL_Renderer* Renderer;
    SDL_Rect rectMenu;
    SDL_Rect rectScore;
    SDL_Rect rectNext;
    ImageObject imageMenu;
    TextObject textScore;

    Tetris_Display(SDL_Renderer* Renderer, int columns, int rows, int squareEdge);
    void renderMenu(int Score, const Square* squareNext);
};

struct Tetris_Sound
{
    Mix_Chunk * mixKey;
    Mix_Chunk * mixKeyDown;
    Mix_Chunk * mixSquare;
    Mix_Chunk * mixScore;

    Tetris_Sound();
    ~Tetris_Sound();
};

struct Square_Data
{
    const int columns;
    const int rows;

    Square** square;
    Square squareNext[4];
    int FALLx[4];
    int FALLy[4];

    Square_Data(int _columns, int _rows):columns(_columns),rows(_rows) {}
};

struct Game_Data
{
    int SCREEN_HEIGHT;
    int SCREEN_WIDTH;

    SDL_Window* Windows;
    SDL_Renderer* Renderer;

    Tetris_Display* display = nullptr;
    Tetris_Sound* sound = nullptr;

    float gameDelay = 800;
    float speedDelay = 1.0f;
    short int Score = 0;
};

#endif // GAME_DATA_H
