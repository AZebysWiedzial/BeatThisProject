#include "UIText.h"
#include <stdio.h>
#include <string.h>

UIText::UIText(SDL_Renderer* renderer, double x, double y, int width, int height, const char* text) : UIElement(renderer, x, y, width, height)
{
    charset = SDL_LoadBMP("../assets/cs8x8.bmp");
    if(charset == nullptr)
    {
        printf("Failed to load charset bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(charset, true, SDL_MapRGB(charset->format, 0, 0, 0));
    }
    setText(text);
}

void UIText::setText(const char* newText)
{
    text = newText;
    DrawText();
}

void UIText::DrawText() 
{
	int px, py, c;
    int tempX = 0, tempY = 0;

    int textWidth = strlen(text) * CHAR_BITMAP_SIZE;

    // double scale = (double)destRect.w / (double)textWidth;

    // srcRect.w = textWidth;
    // srcRect.h = CHAR_BITMAP_SIZE;
    // srcRect.x = 0;
    // srcRect.y = 0;

	SDL_Rect s, d;
    s.w = CHAR_BITMAP_SIZE;
	s.h = CHAR_BITMAP_SIZE;
	d.w = CHAR_BITMAP_SIZE;
	d.h = CHAR_BITMAP_SIZE;    
    if(sprite != nullptr) SDL_FreeSurface(sprite);
    sprite = SDL_CreateRGBSurface(0, textWidth, CHAR_BITMAP_SIZE, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    
    const char* textPtr = text;
	while(*textPtr) 
    {
		c = *textPtr & 255;
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
		textPtr++;
	}

    spriteWidth = textWidth;
    spriteHeight = CHAR_BITMAP_SIZE;

    
    setWidth(textWidth);
    setHeight(CHAR_BITMAP_SIZE);
    
    // SDL_SaveBMP(sprite, "debug_text.bmp");
    setTextureFromSprite();
    // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
    SDL_SetTextureAlphaMod(texture, 255);
    

}