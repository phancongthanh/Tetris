#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <fstream>
#include "SDL_lib.h"
#include "SDL_ImageObject.h"
#include "SDL_TextObject.h"

namespace Input_Data {

struct Tetris_Input_Data
{
    int squareEdge = 35;
    int rowNumber = 20;     // y
    int columnNumber = 10;  // x
    bool checkMenu = true;
    bool checkSound = false;
    int level = 5;
};

bool getInputData(Tetris_Input_Data &inputData);
void paintData(const Tetris_Input_Data &inputData, SDL_Renderer* renderer, ImageObject &menuImage, TextObject &menuText);

}
#endif // INPUT_DATA_H
