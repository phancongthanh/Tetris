#include "SDL_lib.h"

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const std::string& WINDOW_TITLE, bool virtualMachine) {
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << "CreateWindow: " << SDL_GetError() << std::endl;
            return false;
        }
    if (virtualMachine) renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    else renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "CreateSoftRenderer: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    return true;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path) {
    //SDL_Surface* image = IMG_Load(path.c_str());
    SDL_Surface* image = SDL_LoadBMP(path.c_str());
    if (image == nullptr) std::cout << "IMG_Load: " << SDL_GetError() << std::endl;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == nullptr) std::cout << "CreateTextureFromSurface: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(image);
    return texture;
}

int SDL_SetRenderDrawColor(SDL_Renderer* renderer,const SDL_Color* color) {
    return SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}
