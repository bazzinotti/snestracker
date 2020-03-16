#pragma once

#include "shared/gui/Text.h"
#include "shared/gui/Button.h"

struct PatLenWidget
{
	PatLenWidget();

	void set_coords(int x, int y);
	int handle_event(const SDL_Event &ev);
	void draw(SDL_Surface *screen=::render->screen);

	void update_patlen();

	char patlen_cbuf[5];
	Text patlen_title, patlen_valtext;
	Button patlen_incbtn, patlen_decbtn;

	static int inc_patlen(void *bsaw);
	static int dec_patlen(void *bsaw);

	SDL_Rect rect;
};
