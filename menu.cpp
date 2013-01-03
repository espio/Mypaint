#include "menu.h"
#include "menu_item.h"
#include "callback.h"
#include "color.h"
#include <exception>
#include <iostream>

Menu::Menu(void)
{
	this->_surface = 0;
}

Menu::~Menu(void)
{
	SDL_FreeSurface(this->_surface);
}


SDL_Surface*	Menu::Init(int x, int y, int w, int h)
{
	this->Init_rect(x, y, w, h);
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	if (this->_surface == 0)
		return 0;
	if (this->FillRect(0, 0, this->_rect.w, this->_rect.h - 2, SDL_MapRGB(this->_surface->format, 30, 30, 30)))
		return 0;
	return this->_surface;
}

bool		Menu::Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, const char* name)
{
	Button*		menu_item;

	menu_item = new (std::nothrow) Button();
	if (menu_item == 0 || menu_item->Init(x, y, w, h, name) == 0 ||
	    this->Add_child(menu_item))
	{
		delete menu_item;
		return 1;
	}
	menu_item->Set_callback(fct, data);
	return 0;
}

bool		Menu::Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, int r, int g, int b)
{
	Color*		color;

	color = new (std::nothrow) Color();
	if (color == 0 || color->Init(x, y, w, h, SDL_MapRGB(this->_surface->format, r, g, b)) == 0 ||
	    this->Add_child(color))
	{
		delete color;
		return 1;
	}
	color->Set_callback(fct, data);
	return 0;
}

bool		Menu::Add_items(Menu_item* add)
{
	if (this->Add_child(add))
		return 1;
	return 0;
}


