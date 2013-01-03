#ifndef _MENU_H_
#define _MENU_H_

#include "control.h"
#include "button.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>

class	Menu_item;

class	Menu: public Control
{
public:
	Menu(void);
	~Menu(void);

	SDL_Surface*	Init(int x, int y, int w, int h);
	bool		Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, const char* name);
	bool		Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, int r, int g, int b);
	bool		Add_items(Menu_item* add);
};


#endif
