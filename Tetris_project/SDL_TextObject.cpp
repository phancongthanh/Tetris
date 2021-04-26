#include "SDL_TextObject.h"

TextObject::TextObject() {
    renderer = nullptr;
    nameFont = "";
    color = {255, 255, 255, 255};
    fontSize = 14;
    font = nullptr;
    text = "";
    surface = nullptr;
    texture = nullptr;
    rect = new SDL_Rect();
}
TextObject::TextObject(SDL_Renderer* _renderer) {
    renderer = _renderer;
    nameFont = "";
    color = {255, 255, 255, 255};
    fontSize = 14;
    font = nullptr;
    text = "";
    surface = nullptr;
    texture = nullptr;
    rect = new SDL_Rect();
}

void TextObject::setRenderer(SDL_Renderer* _renderer) {
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

void TextObject::setFont(std::string _namefont, int _fontSize) {
    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    nameFont = _namefont;
    fontSize = _fontSize;
    font = TTF_OpenFont(nameFont.c_str(), fontSize);
}
void TextObject::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color = { r, g, b, a};
}
void TextObject::setColor(const SDL_Color &_color) {
    color.r = _color.r;
    color.g = _color.g;
    color.b = _color.b;
    color.a = _color.a;
}

std::string TextObject::getNameFont() const { return nameFont;}
const SDL_Color* TextObject::getColor() const { return &color;}
int TextObject::getSize() const { return fontSize;}
const TTF_Font* TextObject::getFont() const { return font;}
const SDL_Rect* TextObject::getRect() const {return rect;}

std::string TextObject::getText() const { return text;}
SDL_Surface* TextObject::getSurface() const { return surface;}
SDL_Texture* TextObject::getTexture() const { return texture;}

SDL_Texture* TextObject::loadText(std::string _text) {
    if (_text == "") return nullptr;
    else text = _text;
    if (font == nullptr) return nullptr;
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) { std::cout << SDL_GetError() << std::endl; return nullptr;}
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &(rect->w), &(rect->h));
    return texture;
}

bool TextObject::operator=(const TextObject &textObject) {
    if (this->renderer == nullptr) {
        if (textObject.renderer == nullptr) return false;
        else this->renderer = textObject.renderer;
    }
    if (textObject.getNameFont() != "") this->setFont(textObject.getNameFont(), textObject.getSize());
    this->setColor(*textObject.getColor());
    return true;
}

TextObject::~TextObject() {
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (rect != nullptr) {
        delete rect;
        rect = nullptr;
    }
}
