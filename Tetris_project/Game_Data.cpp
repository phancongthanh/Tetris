#include "Game_Data.h"

SDL_Renderer* Square::Renderer = nullptr;
int Square::squareEdge = 35;
void Square::paintSquare() const {
    SDL_Rect squareRect = {2 + squareEdge * x + 1, 2 + squareEdge * y + 1, squareEdge-2, squareEdge-2};
    SDL_SetRenderDrawColor(Renderer, Game_Color + color);
    SDL_RenderFillRect(Renderer, &squareRect);
}

Tetris_Display::Tetris_Display(SDL_Renderer* Renderer, int columns, int rows, int squareEdge) {
    this->Renderer = Renderer;
    int SCREEN_HEIGHT = 2 + squareEdge*rows + 2;
    imageMenu.setRenderer(Renderer);
    std::ifstream checkExist;
    std::string pathDisplay = "Tetris_Data\\Image\\display.jpg"; checkExist.open(pathDisplay); if (!checkExist.is_open()) pathDisplay = "Tetris_Data/Image/display.jpg"; checkExist.close();
    std::string pathFont = "Tetris_Data\\Font\\arialbd.ttf"; checkExist.open(pathFont); if (!checkExist.is_open()) pathFont = "Tetris_Data/Font/arialbd.ttf"; checkExist.close();
    imageMenu.loadImage(pathDisplay);
    rectMenu = {2 + squareEdge*columns + 2, 0, (int)((300.0f/704.0f)*SCREEN_HEIGHT), SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, imageMenu.getTexture(), NULL, &rectMenu);

    rectMenu = {2 + squareEdge*columns + 2, SCREEN_HEIGHT/2, (int)((300.0f/704.0f)*SCREEN_HEIGHT), SCREEN_HEIGHT/2};

    textScore.setRenderer(Renderer);
    textScore.setFont(pathFont, 40 * SCREEN_HEIGHT / 704);
    textScore.setColor(255,255,255,255);
    rectScore.x = 2 + squareEdge*columns + 2 + SCREEN_HEIGHT/12;
    rectScore.y = SCREEN_HEIGHT * 6 / 12;

    rectNext.w = ((int)(rectMenu.w / 60)) * 40;
    rectNext.h = rectNext.w * 3 / 4;
    rectNext.x = 2 + squareEdge*columns + 2 + (rectMenu.w - rectNext.w)/2;
    rectNext.y = SCREEN_HEIGHT * 8 / 11;
}
void Tetris_Display::renderMenu(int Score, const Square* squareNext) {
    SDL_SetRenderDrawColor(Renderer, 40, 40, 40, 255);
    SDL_RenderFillRect(Renderer, &rectMenu);

    int color = (Score/100) % (NUMBER_COLOR-1) + 1;
    textScore.setColor(Game_Color[color]);
    textScore.loadText("Score:  " + std::to_string(Score));
    rectScore.w = textScore.getRect()->w;
    rectScore.h = textScore.getRect()->h;
    SDL_RenderCopy(Renderer, textScore.getTexture(), NULL, &rectScore);

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Renderer, &rectNext);
    static SDL_Rect rectSquare;
    rectSquare.w = rectNext.w / 5;
    rectSquare.h = rectNext.w / 5;
    SDL_SetRenderDrawColor(Renderer, 225, 225, 225, 225);
    for (int x=0;x<4;x++) {
        for (int y=0;y<3;y++) {
            rectSquare.x = rectNext.x + rectNext.w/40 + rectNext.w/4 * x;
            rectSquare.y = rectNext.y + rectNext.w/40 + rectNext.w/4 * y;
            SDL_RenderFillRect(Renderer, &rectSquare);
        }
    }
    SDL_SetRenderDrawColor(Renderer, Game_Color + squareNext[0].color);
    for (int i=0;i<4;i++) {
        rectSquare.x = rectNext.x + rectNext.w/40 + rectNext.w/4 * (squareNext[i].x+1);
        rectSquare.y = rectNext.y + rectNext.w/40 + rectNext.w/4 * (squareNext[i].y+1);
        SDL_RenderFillRect(Renderer, &rectSquare);
    }
}

Tetris_Sound::Tetris_Sound() {
    std::ifstream checkExist;

    std::string pathMixKey = "Tetris_Data\\Sound\\mixKey.wav";
    checkExist.open(pathMixKey); if(!checkExist.is_open()) pathMixKey = "Tetris_Data/Sound/mixKey.wav"; checkExist.close();
    mixKey = Mix_LoadWAV(pathMixKey.c_str());

    std::string pathMixKeyDown = "Tetris_Data\\Sound\\mixKeyDown.wav";
    checkExist.open(pathMixKeyDown); if(!checkExist.is_open()) pathMixKeyDown = "Tetris_Data/Sound/mixKeyDown.wav"; checkExist.close();
    mixKeyDown = Mix_LoadWAV(pathMixKeyDown.c_str());

    std::string pathMixSquare = "Tetris_Data\\Sound\\mixSquare.wav";
    checkExist.open(pathMixSquare); if(!checkExist.is_open()) pathMixSquare = "Tetris_Data/Sound/mixSquare.wav"; checkExist.close();
    mixSquare = Mix_LoadWAV(pathMixSquare.c_str());

    std::string pathMixScore = "Tetris_Data\\Sound\\mixScore.wav";
    checkExist.open(pathMixScore); if(!checkExist.is_open()) pathMixKey = "Tetris_Data/Sound/mixScore.wav"; checkExist.close();
    mixScore = Mix_LoadWAV(pathMixScore.c_str());
}
Tetris_Sound::~Tetris_Sound() {
    Mix_FreeChunk(mixKey);
    Mix_FreeChunk(mixKeyDown);
    Mix_FreeChunk(mixSquare);
    Mix_FreeChunk(mixScore);
}

SDL_Color Game_Color[] = {
    Game_Color[0] = {40,40,40,255}, // BackGround
    Game_Color[1] = {255,0,0,255}, //RED
    Game_Color[2] = {255,128,0,255}, //ORANGE
    Game_Color[3] = {255,255,0,255}, //YELLOW
    Game_Color[4] = {0,255,0,255}, //GREEN
    Game_Color[5] = {0,0,255,255}, //BLUE
    Game_Color[6] = {255,128,128,255}, //PINK
    Game_Color[7] = {255,0,255,255} //PURPLE
};
