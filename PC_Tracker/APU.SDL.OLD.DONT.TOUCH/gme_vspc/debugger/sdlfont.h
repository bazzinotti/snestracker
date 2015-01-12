#pragma once
#include "SDL.h"
#include "Colors.h"

#define CHAR_HEIGHT 9
#define CHAR_WIDTH 8
#define TILE_WIDTH CHAR_WIDTH
#define TILE_HEIGHT CHAR_HEIGHT

void sdlfont_drawString(SDL_Surface *dst, int x, int y, const char *string, Uint32 color, bool prefill=true, bool flipV=false, bool flipH=false);
void sdlfont_drawString2c(SDL_Surface *dst, int x, int y, const char *string, Uint32 color1, Uint32 Color2);
void put4pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void put44pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);