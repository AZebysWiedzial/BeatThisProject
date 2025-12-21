#include "Renderable.h"
#include<stdio.h>
#include<string.h>

Renderable::Renderable(){}
Renderable::Renderable(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight)
{
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->objectWidth = objectWidth;
    this->objectHeight = objectHeight;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = spriteWidth;
    srcRect.h = spriteHeight;

    destRect.x = x;
    destRect.y = y;
    destRect.w = objectWidth;
    destRect.h = objectHeight;

    sprite = nullptr;
    texture = nullptr;
    // renderer = nullptr;

    anchor = TOP_RIGHT;
}



void Renderable::render()
{
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

int Renderable::setSprite(const char* filePath)
{
    sprite = SDL_LoadBMP(filePath);
    if(sprite == NULL) return 1;
    setTextureFromSprite();

    return 0;
}

int Renderable::setSprite(SDL_Surface* sprite)
{
    this->sprite = sprite;
    setTextureFromSprite();

    return 0;
}
int Renderable::setRectangleAsSprite(uint8_t red, uint8_t green, uint8_t blue)
{
    sprite = SDL_CreateRGBSurface(0, 10, 10, 32,
                                0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_FillRect(sprite, NULL, SDL_MapRGB(sprite->format, red, green, blue));
    setTextureFromSprite();
    return 0;
}
void Renderable::setTextureFromSprite()
{
    if(texture != nullptr) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, sprite);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    if(texture == nullptr) printf("Texture Creation Error: %s\n", SDL_GetError());
}
void Renderable::DrawText(const char *text, SDL_Surface *charset, double scale) 
{
	int px, py, c;
    int tempX = 0, tempY = 0;

    int textWidth = strlen(text) * CHAR_BITMAP_SIZE;

    srcRect.w = textWidth;
    srcRect.h = CHAR_BITMAP_SIZE;
    srcRect.x = 0;
    srcRect.y = 0;

	SDL_Rect s, d;
    s.w = CHAR_BITMAP_SIZE;
	s.h = CHAR_BITMAP_SIZE;
	d.w = CHAR_BITMAP_SIZE;
	d.h = CHAR_BITMAP_SIZE;    
    if(sprite != nullptr) SDL_FreeSurface(sprite);
    sprite = SDL_CreateRGBSurface(0, textWidth, CHAR_BITMAP_SIZE, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    
	while(*text) 
    {
		c = *text & 255;
		px = (c % 16) * CHAR_BITMAP_SIZE;
		py = (c / 16) * CHAR_BITMAP_SIZE;
		s.x = px;
		s.y = py;
        // printf("Position on the charset: %d; %d\n", s.x/8, s.y/8);
		d.x = tempX;
		d.y = tempY;
        // printf("Position on the sprite: %d; %d\n\n", d.x/8, d.y/8);

		SDL_BlitSurface(charset, &s, sprite, &d);
        // SDL_RenderCopy(renderer, tex)
		tempX += CHAR_BITMAP_SIZE; 
		text++;
	}
    destRect.w = textWidth * scale;
    destRect.h = CHAR_BITMAP_SIZE * scale;
    

    objectWidth = textWidth * scale;
    objectHeight = CHAR_BITMAP_SIZE * scale;
    destRect.x = x;
    destRect.y = y;
    // SDL_SaveBMP(sprite, "debug_text.bmp");
    setTextureFromSprite();
    // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
    SDL_SetTextureAlphaMod(texture, 255);

}
void Renderable::setX(double newX)
{
    x = newX;
}

void Renderable::setY(double newY)
{
    y = newY;
}
void Renderable::setPosition(double newX, double newY)
{
    x = newX;
    y = newY;
}
int Renderable::getX()
{
    return x;
}
int Renderable::getY()
{
    return y;
}