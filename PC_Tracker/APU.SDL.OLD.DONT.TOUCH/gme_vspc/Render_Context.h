#pragma once
#include "SDL.h"
struct Render_Context
{
public:
  //Render_Context()

  void sdl_draw();
  void clear_screen();

  static SDL_Window *sdlWindow;//      =NULL;
  static SDL_Renderer *sdlRenderer;//  =NULL;
  static SDL_Texture *sdlTexture;//    =NULL;
  static SDL_Surface *screen;//        = NULL;
  static char tmpbuf[500];
};
