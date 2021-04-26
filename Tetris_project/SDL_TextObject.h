#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TextObject
{
private:
    SDL_Renderer* renderer;

    std::string nameFont;
    SDL_Color color;
    int fontSize;
    TTF_Font* font;

    std::string text;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect* rect;
public:
    TextObject();
    TextObject(SDL_Renderer* _renderer);

    void setRenderer(SDL_Renderer* _renderer);
    void setFont(std::string _namefont, int _fontSize);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setColor(const SDL_Color &_color);

    std::string getNameFont() const;
    const SDL_Color* getColor() const;
    int getSize() const;
    const TTF_Font* getFont() const;
    const SDL_Rect* getRect() const;

    std::string getText() const;
    SDL_Surface* getSurface() const;
    SDL_Texture* getTexture() const;

    SDL_Texture* loadText(std::string text);

    bool operator=(const TextObject &textObject);

    ~TextObject();
};

#endif // TEXTOBJECT_H
