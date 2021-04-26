#ifndef SDL_IMAGEOBJECT_H
#define SDL_IMAGEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

class ImageObject
{
private:
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect* rect;
	std::string path;
public:
    ImageObject();
	ImageObject(SDL_Renderer* _renderer);

	void setRenderer(SDL_Renderer* _renderer);

	SDL_Texture* loadImage(std::string _path);

	std::string getPath() const;
	const SDL_Rect* getRect() const;
	SDL_Surface* getSurface() const;
	SDL_Texture* getTexture() const;

	bool operator =(const ImageObject &imageObject);

	~ImageObject();
};

#endif // !SDL_IMAGEOBJECT_H
