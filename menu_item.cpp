#include "menu_item.h"
#include "callback.h"
#include "paper.h"
#include <list>
#include <iostream>

Menu_item::Menu_item(void)
{
	this->__etat = false;
	this->__click = false;
	this->__size_child = 0;
}

Menu_item::~Menu_item(void)
{
	std::list<Control*>::iterator	it;

	it = this->__tmp_child.begin();
	while (this->__size_child > 0)
	{
		delete *it;
		++it;
		--this->__size_child;
	}
}

bool	Menu_item::Init(int x, int y, int w, int h, const char* name, TTF_Font* font, Paper* draw)
{
	SDL_Color	color;
	SDL_Surface*	text;

	this->__drawing_area = draw;
	if (Control::Init(x, y, w, h) == 0)
		return 1;
	this->_rect.h -=12;
	if (this->Color_surface(30, 30, 30))
		return 1;
	this->_rect.h +=12;
	color.r = 250;
	color.g = 0;
	color.b = 0;
	text = TTF_RenderText_Solid(font, name, color);
	if (text == 0)
		return 1;
	if (SDL_BlitSurface(text, 0, this->_surface, 0))
	{
		SDL_FreeSurface(text);
		return 1;
	}
	return 0;
}

void	Menu_item::Show_menu(void)
{
	std::list<Control*>::iterator	it;

	it = this->__tmp_child.begin();
	while (this->__tmp_child.end() != it)
	{
		(*it)->Update();
		++it;
	}
}

bool	Menu_item::Click_button(SDL_Event* event)
{
	pos		tmp;

	if (event == 0)
		return 0;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (((tmp.x < 0 || tmp.x >= this->_surface->w ||
	    tmp.y < 0 || tmp.y >= this->_surface->h + 60) &&
	    this->__etat == true))
	{
		this->__drawing_area->Set_actif(!this->__click);
		this->__click = false;
		this->__etat = false;
	}
	if (((tmp.x > 0 && tmp.x < this->_surface->w &&
	    tmp.y > this->_rect.h && tmp.y < this->_rect.h + 60) &&
	    this->__etat == true) && event->button.button == SDL_BUTTON_LEFT && event->button.type == SDL_MOUSEBUTTONDOWN)
		this->__click = true;
	return 0;
}

bool	Menu_item::Add_items(int x, int y, int w, int h, void (*fct)(SDL_Event*, Control*, void*), void* data, const char* name)
{
	Button*		menu_item;

	menu_item = new (std::nothrow) Button();
	if (menu_item == 0 || menu_item->Init(this->_rect.x + x , this->_surface->h + y, w, h, name) == 0)
	{
		delete menu_item;
		return 1;
	}
	try
	{
		this->__tmp_child.push_back(menu_item);
		++this->__size_child;
	}
	catch (std::exception ex)
	{
		return 1;
	}
	menu_item->Set_callback(fct, data);
	return 0;
}

bool	Menu_item::Add_surface(void)
{
	std::list<Control*>::iterator	it;
	Control*			root;

	root = this->Get_root();
	it = this->__tmp_child.end();
	while (it != this->__tmp_child.begin())
	{
		--it;
		if (root->Add_child(*it))
			return 1;
		--this->__size_child;
	}
	return 0;
}

void	Menu_item::On_key_down(SDL_Event* event)
{
	if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED)
	{
		if (this->__etat == false)
			this->Show_menu();
		else
		{
			this->__click = false;
			this->__drawing_area->Update();
		}
		this->__drawing_area->Set_actif(this->__etat);
		this->__etat = !this->__etat;
	}
}

bool	Menu_item::On_key_up(SDL_Event*)
{
	return 1;
}
