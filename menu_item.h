#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include "menu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class	Paper;

class	Menu_item: public Menu
{
	bool			__etat;
	bool			__click;
	std::list<Control*>	__tmp_child;
	int			__size_child;
	Control*		__surface_menu;
	void			Show_menu(void);
	Paper*			__drawing_area;
	virtual bool		On_key_up(SDL_Event* event);
	virtual void		On_key_down(SDL_Event* event);
public:
	Menu_item(void);
	~Menu_item(void);

	bool		Add_surface(void);
	bool		Init(int x, int y, int w, int h, const char* name, TTF_Font* font, Paper* draw);
	virtual bool	Click_button(SDL_Event* event);
	bool		Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, const char* name);
};

#endif
