#include "color.h"
#include "paper.h"
#include <iostream>

Color::Color(void)
{
	this->__color = 0;
}

Color::~Color(void)
{

}

SDL_Surface*	Color::Init(int x, int y, int w, int h, Uint32 color)
{
	this->Init_rect(x, y, w, h);
	this->__color = color;
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	if (this->_surface == 0)
		return 0;
	if (this->Color_surface(color))
		return 0;
	return this->_surface;
}

bool		Color::Click_button(SDL_Event* event)
{
	Paper*	drawing_area;

	drawing_area = (Paper*)this->_data;

	if (event->button.button == SDL_BUTTON_LEFT)
		drawing_area->Set_color(this->__color, LEFT);
	else if (event->button.button == SDL_BUTTON_RIGHT)
		drawing_area->Set_color(this->__color, RIGHT);
	return 0;
}

Uint32		Color::Get_color(void) const
{
	return this->__color;
}
