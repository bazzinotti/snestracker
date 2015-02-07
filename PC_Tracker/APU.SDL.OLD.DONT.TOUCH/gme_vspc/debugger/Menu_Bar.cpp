#include "Menu_Bar.h"

int Menu_Bar::Track_Context::toggle_pause (void *data)
{
  BaseD::toggle_pause();
}         
int Menu_Bar::Track_Context::restart_current_track (void *data)
{
  BaseD::restart_current_track();
}
int Menu_Bar::Track_Context::prev_track (void *data)
{
  BaseD::prev_track();
}        
int Menu_Bar::Track_Context::next_track (void *data)
{
  BaseD::next_track();
}

int Menu_Bar::Window_Context::memory(void *data)
{
  BaseD::switch_mode(BaseD::GrandMode::MAIN);
}
int Menu_Bar::Window_Context::DSP(void *data)
{
  BaseD::switch_mode(BaseD::GrandMode::DSP_MAP);
}
int Menu_Bar::Window_Context::Instrument(void *data)
{
  BaseD::switch_mode(BaseD::GrandMode::INSTRUMENT);
}

void Menu_Bar::draw(SDL_Surface *screen)
{
  if (is_first_run)
  {
    int x = 10, y = 10;
    context_menus.preload(x,y);
    is_first_run = false;
    fprintf(stderr, "menubar DERP");
  }
  //sprintf(tmpbuf, " QUIT - PAUSE - RESTART - PREV - NEXT - WRITE MASK - MM - DM - INSTR");
  //sdlfont_drawString(screen, 0, screen->h-9, tmpbuf, Colors::yellow);
  context_menus.draw(screen);
}

void Menu_Bar::Context_Menus::preload(int x, int y)
{
  file_context.menu.preload(x, y);
  x +=  ( file_context.menu_items[0].clickable_text.str.length() * CHAR_WIDTH ) + CHAR_WIDTH;

  track_context.menu.preload(x, y);
  x +=  ( track_context.menu_items[0].clickable_text.str.length() * CHAR_WIDTH ) + CHAR_WIDTH;

  window_context.menu.preload(x,y);
  x +=  ( window_context.menu_items[0].clickable_text.str.length() * CHAR_WIDTH ) + CHAR_WIDTH;
}

bool Menu_Bar::Context_Menus::check_left_click_activate(int &x, int &y)
{
  if (file_context.menu.check_left_click_activate(x, y))
  {
    track_context.menu.deactivate();
    window_context.menu.deactivate();
    return true;
  }
  if (track_context.menu.check_left_click_activate(x, y))
  {
    file_context.menu.deactivate();
    window_context.menu.deactivate();
    return true;
  }
  if (window_context.menu.check_left_click_activate(x, y))
  {
    file_context.menu.deactivate();
    track_context.menu.deactivate();
    return true;
  }

  return false;
}

int Menu_Bar::Context_Menus::receive_event(SDL_Event &ev)
{
  int r;
  if (ev.type == SDL_MOUSEBUTTONDOWN)
  {
    if (check_left_click_activate(ev.button.x, ev.button.y))
    {
      return EVENT_ACTIVE;
    }
  }

  if ((r=file_context.menu.receive_event(ev)))
  {
    if (r == Expanding_List::EVENT_MENU)
      return EVENT_FILE;
    return EVENT_ACTIVE;
  }
  if ((r=track_context.menu.receive_event(ev)))
  {
    if (r == Expanding_List::EVENT_MENU)
      return EVENT_TRACK;
    return EVENT_ACTIVE;
  }
  if ((r=window_context.menu.receive_event(ev)))
  {
    if (r == Expanding_List::EVENT_MENU)
      return EVENT_WINDOW;
    return EVENT_ACTIVE;
  }

  return EVENT_INACTIVE;
}
void Menu_Bar::Context_Menus::update(Uint8 adsr1, Uint8 adsr2)
{
  // Don't need this because there is no currently selected item, just actions
  /*file_context.menu.update_current_item(Menu_Bar::get_attack_index(adsr1));
  window_context.menu.update_current_item(Menu_Bar::get_sustain_level_index(adsr2));
  track_context.menu.update_current_item(Menu_Bar::get_decay_index(adsr1));*/
  //track_context.update();
}

void Menu_Bar::Context_Menus::draw(SDL_Surface *screen)
{
  file_context.menu.draw(screen);
  track_context.menu.draw(screen);
  window_context.menu.draw(screen);
}