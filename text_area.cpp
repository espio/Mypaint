#include "text_area.h"
#include "atoi.h"
#include "paper.h"
#include <iostream>

Text_area::Text_area(void)
{
	this->__size_text = 0;
	this->__message = 0;
	this->__color.r = 255;
	this->__color.g = 0;
	this->__color.b = 0;
	this->__id = SIZE_BRUSH;
}

Text_area::~Text_area(void)
{
	this->__size_text = 0;
	SDL_FreeSurface(this->__message);
}

SDL_Surface*	Text_area::Init(int x, int y, int w, int h, const char* image, TTF_Font* font, Paper* draw, void (*fct)(SDL_Event*, Control*, void*))
{
	SDL_Surface*	text;

	this->Init_rect(x, y, w, h);
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	if (this->_surface == 0)
		return 0;
	text = TTF_RenderText_Solid(font, image, this->__color);
	if (text == 0)
		return 0;
	if (SDL_BlitSurface(text, 0, this->_surface, 0) == -1)
	{
		SDL_FreeSurface(text);
		std::cout << SDL_GetError() << std::endl;
		return 0;
	}
	this->_fct = fct;
	SDL_FreeSurface(text);
	this->__drawing_area = draw;
	this->__font = font;
	this->__rect_message.x = text->w;
	this->__rect_message.y = 0;
	this->__rect_message.w = w - text->w;
	this->__rect_message.h = h;
	if (this->FillRect(this->__rect_message.x, this->__rect_message.y,
	    this->__rect_message.w, this->__rect_message.h, SDL_MapRGB(this->_surface->format, 255, 255, 255)))
		return (0);
	return this->_surface;
}

bool		Text_area::is_text_valid(char c)
{
		return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');

}

bool		Text_area::clear_message(void)
{
	SDL_FreeSurface(this->__message);
	this->__message = 0;
	if (this->FillRect(this->__rect_message.x, this->__rect_message.y,
	    this->__rect_message.w, this->__rect_message.h, SDL_MapRGB(this->_surface->format, 255, 255, 255)))
		return 1;
	return 0;
}

bool		Text_area::add_message(void)
{
	char*	text;

	if (this->__size_text == 0)
		return this->Update();
	text = this->__text;
	if (this->__size_text > 5)
		text += this->__size_text - 5;
	this->__message = TTF_RenderText_Solid(this->__font, text, this->__color);
	if (SDL_BlitSurface(this->__message, 0, this->_surface, &this->__rect_message) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	return this->Update();
}

bool		Text_area::write(char c)
{
	if (this->clear_message())
		return 1;
	this->__text[this->__size_text] = c;
	++this->__size_text;
	this->__text[this->__size_text] = 0;
	return this->add_message();
}

bool		Text_area::Focus(SDL_Event*)
{
	return 0;
}

char		Text_area::get_key(SDL_keysym* key)
{
	if (key->sym >= SDLK_KP0 && key->sym <= SDLK_KP9)
		return key->sym - SDLK_KP0 + '0';
	return *SDL_GetKeyName(key->sym);
}

bool		Text_area::Click_button(SDL_Event* event)
{
	SDL_keysym*	keysym;

	if (event->type != SDL_KEYDOWN)
		return 0;
	SDL_EnableUNICODE(SDL_ENABLE);
	keysym = &event->key.keysym;
	if (keysym->unicode == SDLK_BACKSPACE && this->__size_text > 0)
	{
		--this->__size_text;
		this->__text[this->__size_text] = 0;
		if (this->clear_message())
			return 1;
		if (this->add_message())
			return 1;
	}
	if (keysym->unicode == SDLK_SPACE)
		this->write(' ');
	if ((keysym->unicode == SDLK_FIRST || keysym->unicode > 32) && this->__size_text < 99)
		this->write(this->get_key(keysym));
	if (keysym->unicode == SDLK_RETURN)
		return this->Valid_message();
	return 0;
}

bool		Text_area::Valid_message(void)
{
	int	ret;

	ret = -1;
	if (this->clear_message())
		return 1;
	if (this->__id == SIZE_BRUSH)
		ret = this->__drawing_area->Change_size_brush(id_atoi(this->__text));
	else if (this->__id == NEW_WIDTH)
		ret = this->__drawing_area->New_width(id_atoi(this->__text));
	else if (this->__id == NEW_HEIGHT)
		ret = this->__drawing_area->New_height(id_atoi(this->__text));
	else if (this->__id == FILE_OPEN)
		ret = this->__drawing_area->Load_file(this->__text);
	else if (this->__id == FILE_SAVE)
		ret = this->__drawing_area->Save_file(this->__text);
	this->__size_text = 0;
	this->__text[this->__size_text] = 0;
	if (this->add_message())
		return 1;
	if (ret != -1)
	{
		this->__drawing_area->Set_actif(true);
		return this->__drawing_area->Update();
	}
	return 0;
}

void		Text_area::Set_id(area_id id)
{
	this->__id = id;
}
