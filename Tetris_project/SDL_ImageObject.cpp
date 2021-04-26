#include "SDL_ImageObject.h"

ImageObject::ImageObject() {
    renderer = nullptr;
    surface = nullptr;
    texture = nullptr;
    rect = new SDL_Rect();
    path = "";
}

ImageObject::ImageObject(SDL_Renderer* _renderer){
    renderer = _renderer;
    surface = nullptr;
    texture = nullptr;
    rect = new SDL_Rect();
    path = "";
}

void ImageObject::setRenderer(SDL_Renderer* _renderer) {
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    renderer = _renderer;
}

SDL_Texture* ImageObject::loadImage(std::string _path) {
    if (_path == "") return nullptr;
    else path = _path;
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    surface = IMG_Load(path.c_str());
    if (surface == nullptr) {std::cout << SDL_GetError() << std::endl; return nullptr;}
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &(rect->w), &(rect->h));
    return texture;
}

std::string ImageObject::getPath() const { return path; }
const SDL_Rect* ImageObject::getRect() const { return rect; }
SDL_Surface* ImageObject::getSurface() const { return surface; }
SDL_Texture* ImageObject::getTexture() const { return texture; }

bool ImageObject::operator=(const ImageObject &imageObject) {
    if (this->renderer == nullptr) {
        if (imageObject.renderer == nullptr) return false;
        else this->setRenderer(imageObject.renderer);
    }
    this->loadImage(imageObject.getPath());
    return true;
}

ImageObject::~ImageObject() {
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (rect != nullptr) {
        delete rect;
        rect = nullptr;
    }
}
