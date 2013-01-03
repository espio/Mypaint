#include "scrollbar.h"
#include "paper.h"
#include <iostream>


Scrollbar::Scrollbar(void)
{
}

SDL_Surface*	Scrollbar::Init(int x, int y, int w, int h)
{
	this->__screen = 0;
	this->Init_rect(x, y, w, h);
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	return this->_surface;
}

bool		Scrollbar::Click_button(SDL_Event* event)
{
	pos	tmp;
	Uint8*	keys;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	keys = SDL_GetKeyState(NULL);
	if (this->is_pos_valid(tmp.x, tmp.y) == 0)
		return 0;
	if (keys[SDLK_LSHIFT])
	{
		if (event->button.button == SDL_BUTTON_WHEELUP)
		{
			this->__screen->Change_src(-10, 0);
			this->__screen->Update();
		}
		if (event->button.button == SDL_BUTTON_WHEELDOWN)
		{
			this->__screen->Change_src(10, 0);
			this->__screen->Update();
		}
	}
	else
	{
		if (event->button.button == SDL_BUTTON_WHEELUP)
		{
			this->__screen->Change_src(0, -10);
			this->__screen->Update();
		}
		if (event->button.button == SDL_BUTTON_WHEELDOWN)
		{
			this->__screen->Change_src(0, 10);
			this->__screen->Update();
		}
	}
	if (this->__screen != 0)
		this->__screen->Click_button(event);
	return 0;
}

bool		Scrollbar::Add_child(Control* child)
{
	if (Control::Add_child(child, 1))
		return 1;
	this->__screen = child;
	return 0;
}

void		Scrollbar::Horizontal(void)
{


}

void		Scrollbar::Vertical(void)
{


}

bool		Scrollbar::Resize(int w, int h)
{
	if (this->Color_surface(50, 50, 50))
		return 1;
	if (w > 500)
		w = 500;
	if (h > 500)
		h = 500;
	return Control::Resize(w, h);
}

void		Scrollbar::Rotate(void)
{

}
