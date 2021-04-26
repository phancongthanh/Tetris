#include "Input_Data.h"

bool Input_Data::getInputData(Tetris_Input_Data &inputData) {
    std::ifstream checkExist;
    std::string pathMenu = "Tetris_Data\\Image\\menu.jpg"; checkExist.open(pathMenu); if (!checkExist.is_open()) pathMenu = "Tetris_Data/Image/menu.jpg"; checkExist.close();
    std::string pathFont = "Tetris_Data\\Font\\arialbd.ttf"; checkExist.open(pathFont); if (!checkExist.is_open()) pathFont = "Tetris_Data/Font/arialbd.ttf"; checkExist.close();
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, 600, 450, "Game Tetris");
    ImageObject menuImage(renderer);    menuImage.loadImage(pathMenu);
    TextObject menuText(renderer);  menuText.setFont(pathFont, 32); menuText.setColor(255, 0, 0, 255);
    paintData(inputData, renderer, menuImage, menuText);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quitSDL(window, renderer);
            return false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x,y;    SDL_GetMouseState(&x, &y);
            if (x >= 430 && x <= 443) {
                if (y > 117 && y < 130 && inputData.columnNumber < 99) inputData.columnNumber++;
                else if (y > 132 && y < 145 && inputData.columnNumber > 10) inputData.columnNumber--;
                else if (y > 153 && y < 166 && inputData.rowNumber < 49) inputData.rowNumber++;
                else if (y > 168 && y < 181 && inputData.rowNumber > 10) inputData.rowNumber--;
                else if (y > 188 && y < 201 && inputData.squareEdge < 99) inputData.squareEdge++;
                else if (y > 203 && y < 216 && inputData.squareEdge > 15) inputData.squareEdge--;
                else if (y > 300 && y < 313 && inputData.level < 49) inputData.level++;
                else if (y > 315 && y < 328 && inputData.level > 1) inputData.level--;
            }
            if (x >= 424 && x <= 450) {
                if (y > 229 && y < 252) inputData.checkMenu = !inputData.checkMenu;
                else if (y > 264 && y < 288) inputData.checkSound = !inputData.checkSound;
            }
            if (x > 217 && x < 360 && y > 366 && y < 412) {
                quitSDL(window, renderer);
                return true;
            }
            paintData(inputData, renderer, menuImage, menuText);
            SDL_RenderPresent(renderer);
        }
        else if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)) {
            quitSDL(window, renderer);
            return true;
        }
        SDL_Delay(25);
    }
    return true;
}
void Input_Data::paintData(const Tetris_Input_Data &inputData, SDL_Renderer* renderer, ImageObject &menuImage, TextObject &menuText) {
    SDL_Rect bufferRect = {0, 0, 0, 0};
    SDL_RenderCopy(renderer, menuImage.getTexture(), NULL, NULL);

    menuText.loadText(std::to_string(inputData.columnNumber));
    bufferRect = {370, 113, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);

    menuText.loadText(std::to_string(inputData.rowNumber));
    bufferRect = {370, 150, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);

    menuText.loadText(std::to_string(inputData.squareEdge));
    bufferRect = {370, 188, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);

    menuText.loadText((inputData.checkMenu?"On":"Off"));
    bufferRect = {365, 223, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);

    menuText.loadText((inputData.checkSound?"On":"Off"));
    bufferRect = {365, 260, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);

    menuText.loadText(std::to_string(inputData.level));
    bufferRect = {375, 295, menuText.getRect()->w, menuText.getRect()->h};
    SDL_RenderCopy(renderer, menuText.getTexture(), NULL, &bufferRect);
}
