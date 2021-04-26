#ifndef SDL_LIB_H_INCLUDED
#define SDL_LIB_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>

// xuất thông báo lỗi
extern void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
// Mở cửa sổ
extern bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer,const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const std::string &WINDOW_TITLE, bool virtualMachine = false);
// đóng của sổ
extern void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
// Lấy ảnh
extern SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);
// Đặt màu vẽ
extern int SDL_SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color* color);

#endif // SDL_LIB_H_INCLUDED
