#pragma once
#include "SDL.h"

struct Texture
{
  //Texture();
  ~Texture();
  static void load_bmp(Texture *t, const char *filename, SDL_Renderer *r);
  // you may optionally query the width and height from SDL
  static void queryXY(Texture *t);

  const char *filename; // no extension, e.g "filename"
  union {
    Uint32 rgb;
    struct {
      Uint8 r;
      Uint8 g;
      Uint8 b;
    } __attribute__((packed));
  } colorkey;
  int w,h;
  SDL_Surface *surface; // keep the surface just in case
  SDL_Texture *sdltexture;
};

struct TextureFrame
{
  Texture *texture;
  SDL_Point coord; //relative coordinate from mouse
};

struct TextureAni
{
  ~TextureAni();
  //bool loaded;
  int num_frames;
  int num_sprites;
  int num_textures;
  int frametime; // in ms
  Texture *texture; // this will be pluralized
  TextureFrame *frames;
};
