#pragma once
#include "SDL.h"
#include "gme/player/Music_Player.h"
#include "shared/My_Nfd.h"
#include "shared/Experience.h"
#include "shared/Voice_Control.h"

extern bool quitting;
extern My_Nfd nfd;
extern Experience *cur_exp;
extern Voice_Control voice_control;
extern uint8_t *IAPURAM;
extern track_info_t tag;

void handle_error( const char* );

// 5 minutes default
#define DEFAULT_SONGTIME  (60*5) 

#define PROG_NAME_VERSION_STRING "SNES Tracker Debugger v%s"
#define CREDITS "APU emulation code from Blargg's GME and Snes_Spc 0.9.0"
