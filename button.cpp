#include "button.h"
#include <iostream>

Button::Button(void)
{
	this->__image = 0;
}

Button::~Button(void)
{
	SDL_FreeSurface(this->__image);
}

SDL_Surface*	Button::Init(int x, int y, int w, int h, const char* image)
{
	this->Init_rect(x, y, w, h);
	this->__image = SDL_LoadBMP(image);
	if (this->__image == NULL)
		return 0;
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	if (this->_surface == 0)
		return 0;
	if (SDL_BlitSurface(this->__image, &this->_srcrect, this->_surface, 0) == -1)
		return 0;
	return this->_surface;
}


bool		Button::Click_button(SDL_Event* event)
{
	if (event->button.button == SDL_BUTTON_LEFT && event->button.state == SDL_PRESSED)
	{
		if (SDL_BlitSurface(this->__image, &this->__srcrect, this->_surface, 0) == -1)
			return 1;
		if (this->Update())
			return 1;
	}
	this->_fct(event, this, this->_data);
	return 0;
}

bool	Button::Focus(SDL_Event*)
{
	return 0;
}


bool	Button::On_key_up(SDL_Event*)
{
	return 0;
}
