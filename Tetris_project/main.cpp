#include <ctime>
#include "Input_Data.h"
#include "Game_Data.h"

void constructer(const Input_Data::Tetris_Input_Data &inputData, Game_Data &gameData, Square_Data &squareData);
void createNewSquareFall(Square_Data &squareData, bool newGame = false);
void moveSquare(Square_Data &squareData);
bool proccessedKey(const SDL_Event &e, Square_Data &squareData, SDL_Renderer* Renderer, float &speedDelay, Tetris_Sound* sound);
void proccessedGame(Game_Data &gameData, Square_Data &squareData, int level);
bool checkEndGame(const Square_Data &squareData, SDL_Renderer* Renderer, int Score);
void destructer(const Input_Data::Tetris_Input_Data &inputData, Game_Data &gameData, Square_Data &squareData);

int main(int argc, char* argv[]) {
    srand(time(0));
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) std::cout << SDL_GetError() << std::endl;
    if (TTF_Init() == -1) std::cout << TTF_GetError() << std::endl;
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) std::cout << Mix_GetError() << std::endl;

    Input_Data::Tetris_Input_Data inputData;
    while (Input_Data::getInputData(inputData)) {
        Game_Data gameData;
        Square_Data squareData(inputData.columnNumber, inputData.rowNumber);
        bool Exit_Game = false;
        SDL_Event event;
        constructer(inputData, gameData, squareData);
        while (checkEndGame(squareData, gameData.Renderer, gameData.Score) && !Exit_Game) {
            moveSquare(squareData);
            SDL_RenderPresent(gameData.Renderer);
            for (int i=0;i<10;i++) {
                SDL_Delay((int)(gameData.gameDelay * gameData.speedDelay / 10));
                while (SDL_PollEvent(&event) != 0 && !Exit_Game) Exit_Game = proccessedKey(event, squareData,gameData.Renderer, gameData.speedDelay,gameData.sound);
            }
            proccessedGame(gameData, squareData, inputData.level);
            if (gameData.speedDelay == 0.1f && inputData.checkSound && Mix_Playing(-1) == 0) Mix_PlayChannel(-1, gameData.sound->mixKeyDown, 0);
        }
        destructer(inputData, gameData, squareData);
    }
    return 0;
}

void constructer(const Input_Data::Tetris_Input_Data &inputData, Game_Data &gameData, Square_Data &squareData) {
    gameData.SCREEN_HEIGHT = 2 + inputData.squareEdge*inputData.rowNumber + 2;
    if (inputData.checkMenu) gameData.SCREEN_WIDTH = 2 + inputData.squareEdge*inputData.columnNumber + 2 + (300.0f/704.0f)*gameData.SCREEN_HEIGHT;
    else gameData.SCREEN_WIDTH = 2 + inputData.squareEdge*inputData.columnNumber + 2;
    initSDL(gameData.Windows, gameData.Renderer, gameData.SCREEN_WIDTH, gameData.SCREEN_HEIGHT, std::string("Game Tetris"));

    Square::Renderer = gameData.Renderer;
    Square::squareEdge = inputData.squareEdge;
    std::cout << "SCREEN WIDTH: " << gameData.SCREEN_WIDTH << std::endl;
    std::cout << "SCREEN HEIGHT: " << gameData.SCREEN_HEIGHT << std::endl;
    std::cout << "Square Edge: " << Square::squareEdge << std::endl;
    std::cout << "Level: " << inputData.level << std::endl;
    squareData.square = new Square*[inputData.columnNumber];
    for (int x=0;x<inputData.columnNumber;x++) {
        squareData.square[x] = new Square[inputData.rowNumber];
        for (int y=0;y<inputData.rowNumber;y++) {
            squareData.square[x][y].x = x;
            squareData.square[x][y].y = y;
        }
    }

    squareData.squareNext[0].x = 0;squareData.squareNext[0].y = 0;
    squareData.squareNext[1].x = 1;squareData.squareNext[1].y = 0;
    squareData.squareNext[2].x = 1;squareData.squareNext[2].y = 1;
    squareData.squareNext[3].x = 0;squareData.squareNext[3].y = 1;
    for (int i=0;i<4;i++) squareData.squareNext[i].color = 1;
    createNewSquareFall(squareData, true);

    for (int x=0;x<inputData.columnNumber;x++) for (int y=0;y<inputData.rowNumber;y++) squareData.square[x][y].paintSquare();
    if (inputData.checkMenu) {
        gameData.display = new Tetris_Display(gameData.Renderer, inputData.columnNumber, inputData.rowNumber, inputData.squareEdge);
        gameData.display->renderMenu(0, squareData.squareNext);
    }
    if (inputData.checkSound) gameData.sound = new Tetris_Sound();
    SDL_RenderPresent(gameData.Renderer);
}
void createNewSquareFall(Square_Data &squareData, bool newGame) {
    int columnNumber = squareData.columns;
    Square** square = squareData.square;
    Square* squareNext = squareData.squareNext;
    int center = ((int)columnNumber/2) - 1;
    for (int i=0;i<4;i++) if (square[center + squareNext[i].x][1 + squareNext[i].y].status != NOTEXIST) return;
    for (int i=0;i<4;i++) {
        int x = center + squareNext[i].x;
        int y = 1 + squareNext[i].y;
        square[x][y].status = FALL;
        square[x][y].movelength = 0;
        square[x][y].color = squareNext[i].color;
        squareData.FALLx[i] = x;
        squareData.FALLy[i] = y;
        square[x][y].paintSquare();
    }
    static int Count[7] = {50,50,50,50,50,50,50};
    if (newGame) for (int i=0;i<7;i++) Count[i] = 50;
    int ran = rand() % 350;
    if (ran < Count[0]) {
        Count[0]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 0;squareNext[1].y = -1;
        squareNext[2].x = 1;squareNext[2].y = 0;
        squareNext[3].x = 0;squareNext[3].y = 1;
    } else if (ran < Count[0] + Count[1]) {
        Count[1]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 1;squareNext[1].y = 0;
        squareNext[2].x = 1;squareNext[2].y = 1;
        squareNext[3].x = 0;squareNext[3].y = 1;
    } else if (ran < Count[0] + Count[1] + Count[2]) {
        Count[2]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 1;squareNext[1].y = -1;
        squareNext[2].x = 0;squareNext[2].y = -1;
        squareNext[3].x = 0;squareNext[3].y = 1;
    } else if (ran < Count[0] + Count[1] + Count[2] + Count[3]) {
        Count[3]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 0;squareNext[1].y = -1;
        squareNext[2].x = 0;squareNext[2].y = 1;
        squareNext[3].x = 1;squareNext[3].y = 1;
    } else if (ran < Count[0] + Count[1] + Count[2] + Count[3] + Count[4]) {
        Count[4]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 1;squareNext[1].y = -1;
        squareNext[2].x = 1;squareNext[2].y = 0;
        squareNext[3].x = 0;squareNext[3].y = 1;
    } else if (ran < Count[0] + Count[1] + Count[2] + Count[3] + Count[4] + Count[5]) {
        Count[5]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = 0;squareNext[1].y = -1;
        squareNext[2].x = 1;squareNext[2].y = 0;
        squareNext[3].x = 1;squareNext[3].y = 1;
    } else {
        Count[6]-=7; for (int i=0;i<7;i++) Count[i]++;
        squareNext[1].x = -1;squareNext[1].y = 0;
        squareNext[2].x = 1;squareNext[2].y = 0;
        squareNext[3].x = 2;squareNext[3].y = 0;
    }
    static int ranColor;
    ranColor = (ranColor+1)%(NUMBER_COLOR-1) + 1;
    for (int i=0;i<4;i++) squareNext[i].color = ranColor;
}
void moveSquare(Square_Data &squareData) {
    Square** square = squareData.square;
    int* FALLx = squareData.FALLx;
    int* FALLy = squareData.FALLy;
    int colorFALL = square[FALLx[0]][FALLy[0]].color;
    for (int i=0;i<4;i++) {
        square[FALLx[i]][FALLy[i]].status = NOTEXIST;
        square[FALLx[i]][FALLy[i]].color = 0;
        square[FALLx[i]][FALLy[i]].paintSquare();
    }
    for (int i=0;i<4;i++) {
        FALLy[i]++;
        square[FALLx[i]][FALLy[i]].status = FALL;
        square[FALLx[i]][FALLy[i]].color = colorFALL;
        square[FALLx[i]][FALLy[i]].paintSquare();
    }

    for (int x=0;x<squareData.columns;x++) {
        for (int y=squareData.rows-1;y>0;y--) {
            if (square[x][y-1].status == MOVE) {
                square[x][y].status = MOVE;
                square[x][y-1].status = NOTEXIST;
                square[x][y].color = square[x][y-1].color;
                square[x][y-1].color = 0;
                square[x][y].movelength = square[x][y-1].movelength - 1;
                square[x][y-1].movelength = 0;

                square[x][y].paintSquare();
                square[x][y-1].paintSquare();
            }
        }
    }
}
bool proccessedKey(const SDL_Event &e, Square_Data &squareData, SDL_Renderer* Renderer, float &speedDelay, Tetris_Sound* sound) {
    Square** square = squareData.square;
    int* FALLx = squareData.FALLx;
    int* FALLy = squareData.FALLy;
    if (e.type == SDL_QUIT) return true;
    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_DOWN) speedDelay = 1.0f;
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:   {bool moveup = true;
                            int x[4];
                            int y[4];
                            x[0] = FALLx[0];
                            y[0] = FALLy[0];
                            for (int i=1;i<4;i++) {
                                x[i] = FALLx[0] - (FALLy[i]-FALLy[0]);
                                y[i] = FALLy[0] + (FALLx[i]-FALLx[0]);
                                if (x[i]<0 || x[i]>=squareData.columns) { moveup=false; break; }
                                if (y[i]>= squareData.rows) { moveup=false; break; }
                                else if (square[x[i]][y[i]].status == STANDSTILL || square[x[i]][y[i]].status == MOVE) { moveup=false; break; }
                            }
                            if (moveup) {
                                int squareColor = square[FALLx[0]][FALLy[0]].color;
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = NOTEXIST;
                                    square[FALLx[i]][FALLy[i]].color = 0;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                    FALLx[i] = x[i];
                                    FALLy[i] = y[i];
                                }
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = FALL;
                                    square[FALLx[i]][FALLy[i]].color = squareColor;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                }
                                if (sound != nullptr) Mix_PlayChannel(-1, sound->mixKey, 0);
                                SDL_RenderPresent(Renderer);
                            }}
                            break;
            case SDLK_DOWN: speedDelay = 0.1f;
                            break;
            case SDLK_LEFT: {bool moveleft = true;
                            for (int i=0;i<4;i++) {
                                if (FALLx[i] == 0) {moveleft = false; break;}
                                else if (square[FALLx[i]-1][FALLy[i]].status == STANDSTILL || square[FALLx[i]-1][FALLy[i]].status == MOVE) {moveleft = false; break;}
                            }
                            if (moveleft) {
                                int squareColor = square[FALLx[0]][FALLy[0]].color;
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = NOTEXIST;
                                    square[FALLx[i]][FALLy[i]].color = 0;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                    FALLx[i]--;
                                }
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = FALL;
                                    square[FALLx[i]][FALLy[i]].color = squareColor;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                }
                                if (sound != nullptr) Mix_PlayChannel(-1, sound->mixKey, 0);
                                SDL_RenderPresent(Renderer);
                            }}
                            break;
            case SDLK_RIGHT:{bool moveright = true;
                            for (int i=0;i<4;i++) {
                                if (FALLx[i] == squareData.columns-1) {moveright = false; break;}
                                else if (square[FALLx[i]+1][FALLy[i]].status == STANDSTILL || square[FALLx[i]+1][FALLy[i]].status == MOVE) {moveright = false; break;}
                            }
                            if (moveright) {
                                int squareColor = square[FALLx[0]][FALLy[0]].color;
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = NOTEXIST;
                                    square[FALLx[i]][FALLy[i]].color = 0;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                    FALLx[i]++;
                                }
                                for (int i=0;i<4;i++) {
                                    square[FALLx[i]][FALLy[i]].status = FALL;
                                    square[FALLx[i]][FALLy[i]].color = squareColor;
                                    square[FALLx[i]][FALLy[i]].paintSquare();
                                }
                                if (sound != nullptr) Mix_PlayChannel(-1, sound->mixKey, 0);
                                SDL_RenderPresent(Renderer);
                            }}
                            break;
            case SDLK_F2:   SDL_Event _e;
                            while (SDL_WaitEvent(&_e) >= 0) {
                                if (_e.type == SDL_QUIT) {return true; }
                                if (_e.type == SDL_KEYDOWN && _e.key.keysym.sym == SDLK_F2) break;
                            }
                            break;
        }
    }
    return false;
}
void proccessedGame(Game_Data &gameData, Square_Data &squareData, int level) {
    Square** square = squareData.square;
    int* FALLx = squareData.FALLx;
    int* FALLy = squareData.FALLy;
    bool createSquare = false;
    for (int i=0;i<4;i++) {
        if (FALLy[i] == squareData.rows-1) square[FALLx[i]][FALLy[i]].status = STANDSTILL;
        else if (square[FALLx[i]][FALLy[i]+1].status == STANDSTILL) square[FALLx[i]][FALLy[i]].status = STANDSTILL;
    }
    for (int i=0;i<4;i++) createSquare = createSquare || (square[FALLx[i]][FALLy[i]].status == STANDSTILL);
    if (createSquare) {
        for (int i=0;i<4;i++) square[FALLx[i]][FALLy[i]].status = STANDSTILL;
        createNewSquareFall(squareData);
        gameData.Score += 4;
        if (gameData.sound != nullptr) Mix_PlayChannel(-1, gameData.sound->mixSquare, 0);
        if (gameData.display != nullptr) gameData.display->renderMenu(gameData.Score, squareData.squareNext);
    }

    for (int x=0;x<squareData.columns;x++) {
        for (int y=squareData.rows-1;y>=0;y--) {
            if (square[x][y].status == MOVE) {
                if (square[x][y].movelength <= 0) square[x][y].status = STANDSTILL;
                if (y == squareData.rows-1) square[x][y].status = STANDSTILL;
                else if (square[x][y+1].status == STANDSTILL) square[x][y].status = STANDSTILL;
            }
        }
    }

    int combo = 0;
    for (int y=squareData.rows-1;y>=0;y--) {
        for (int x=0;x<=squareData.columns;x++) {
            if (x==squareData.columns) {
                for (int _x=0;_x<squareData.columns;_x++) {
                    square[_x][y].status = NOTEXIST;
                    square[_x][y].color = 0;
                    square[_x][y].paintSquare();
                }
                gameData.speedDelay = 1;
                gameData.Score += squareData.columns*level/5*(++combo);
                if (gameData.sound != nullptr) Mix_PlayChannel(-1, gameData.sound->mixScore, 0);
                if (gameData.display != nullptr) gameData.display->renderMenu(gameData.Score, squareData.squareNext);
                gameData.gameDelay = gameData.gameDelay * (100 - level) / 100;
                SDL_RenderPresent(gameData.Renderer);
                for (int _y=0;_y<y;_y++) {
                    for (int _x=0;_x<squareData.columns;_x++) {
                        if (square[_x][_y].status == STANDSTILL || square[_x][_y].status == MOVE) {
                            if (square[_x][_y].status == STANDSTILL) square[_x][_y].movelength = 0;
                            square[_x][_y].status = MOVE;
                            square[_x][_y].movelength++;
                        }
                    }
                }
            }
            else if (square[x][y].status == FALL || square[x][y].status == NOTEXIST) break;
        }
    }
}
bool checkEndGame(const Square_Data &squareData, SDL_Renderer* Renderer, int Score) {
    bool continueGame = true;
    int center = (int)squareData.columns/2 - 1;
    for (int i=0;i<4;i++) if (squareData.square[center+squareData.squareNext[i].x][2+squareData.squareNext[i].y].status == STANDSTILL) continueGame = false;
    if (continueGame) return true;
        SDL_Rect rectEnd = {2,2,squareData.columns*Square::squareEdge,squareData.rows*Square::squareEdge};
        SDL_SetRenderDrawColor(Renderer, 125, 125, 125, 128);
        SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(Renderer, &rectEnd);

        rectEnd = {2+Square::squareEdge*(squareData.columns/2-3), 2+Square::squareEdge*(squareData.rows/2-1), 6*Square::squareEdge, 4*Square::squareEdge};
        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(Renderer, &rectEnd);

        TextObject textEnd(Renderer);
        textEnd.setFont("Tetris_Data\\Font\\arialbd.ttf",32);
        textEnd.setColor(0,0,0,255);
        rectEnd.x = 2+Square::squareEdge*(squareData.columns/2-2.25f);
        rectEnd.y = 2+Square::squareEdge*(squareData.rows/2-0.75f);
        rectEnd.w = 4.5f*Square::squareEdge;    rectEnd.h = 2.5f*Square::squareEdge;
        textEnd.loadText("You lose!");
        SDL_RenderCopy(Renderer, textEnd.getTexture(), NULL, &rectEnd);

        textEnd.setColor(Game_Color[rand()%NUMBER_COLOR]);
        rectEnd.x = 2+Square::squareEdge*(squareData.columns/2-2.25f);
        rectEnd.y = 2+Square::squareEdge*(squareData.rows/2+1.75f);
        rectEnd.w = 4.5f*Square::squareEdge;    rectEnd.h = 1.0f*Square::squareEdge;
        textEnd.loadText("Your Score: " + std::to_string(Score));
        SDL_RenderCopy(Renderer, textEnd.getTexture(), NULL, &rectEnd);

        SDL_RenderPresent(Renderer);
        SDL_Event e;
        while (SDL_WaitEvent(&e)) {
            if ((e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)) || e.type == SDL_QUIT) return false;
        }
        return false;
}
void destructer(const Input_Data::Tetris_Input_Data &inputData, Game_Data &gameData, Square_Data &squareData) {
    for (int i=0;i<inputData.columnNumber;i++) delete[] squareData.square[i];
    delete[] squareData.square;

    if (inputData.checkMenu) delete gameData.display;
    if (inputData.checkSound) delete gameData.sound;
    quitSDL(gameData.Windows, gameData.Renderer);
}
