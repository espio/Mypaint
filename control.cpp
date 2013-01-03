#include "control.h"
#include "window.h"
#include "menu.h"
#include "paper.h"
#include <exception>
#include <iostream>

Control::Control(void)
{
	this->_parent = 0;
	this->_surface = 0;
	this->_rect.x = 0;
	this->_rect.y = 0;
	this->_rect.w = 0;
	this->_rect.h = 0;
	this->_fct = 0;
	this->_save = 0;
	this->_etat = true;
	this->_actif = true;
}

Control::~Control(void)
{
	std::list<Control*>::iterator	it;

	it = this->_child.begin();
	while (it != this->_child.end())
	{
		delete *it;
		++it;
	}
	if (this->_parent != 0)
		SDL_FreeSurface(this->_surface);
}

bool		Control::Is_in_area(int x, int y)
{
	if (this->_rect.x < x && x < this->_rect.x + this->_rect.w &&
	    this->_rect.y < y && y < this->_rect.y + this->_rect.h)
		return true;
	return false;
}

Control*	Control::Get_control(SDL_Event* event, int x, int y)
{
	std::list<Control*>::iterator	it;
	Control*			ret;

	if (!this->_actif)
		return 0;
	ret = 0;
	it = this->_child.begin();
	while (it != this->_child.end())
	{
		ret = (*it)->Get_control(event, x - (*it)->_rect.x, y - (*it)->_rect.y);
		if (ret != 0)
			return ret;
		else if ((*it)->Is_in_area(x, y) && (*it)->_actif)
			return *it;
		++it;
	}
	return 0;
}

bool		Control::Add_child(Control* child, bool unique)
{
	if (SDL_BlitSurface(child->_surface, &child->_srcrect, this->_surface, &child->_rect) == -1)
		return 1;
	child->_parent = this;
	if (unique)
		return 0;
	try
	{
		this->_child.push_back(child);
	}
	catch (std::exception ex)
	{
		return 1;
	}
	return 0;
}

void		Control::Init_rect(int x, int y, int w, int h)
{
	this->_rect.x = x;
	this->_rect.y = y;
	this->_rect.w = w;
	this->_rect.h = h;
	this->_srcrect.x = 0;
	this->_srcrect.y = 0;
	this->_srcrect.w = w;
	this->_srcrect.h = h;
}

SDL_Surface*	Control::Init(int x, int y, int w, int h)
{
	this->Init_rect(x, y, w, h);
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	return this->_surface;
}

bool		Control::InputKeyboardEvent(SDL_KeyboardEvent* event)
{
	SDL_keysym*	keysym;
	Uint8*		keys;

	SDL_EnableUNICODE(SDL_ENABLE);
	keysym = &event->keysym;
	keys = SDL_GetKeyState(NULL);
	if (keys[SDLK_LCTRL] && keys[SDLK_z])
	{
		std::cout << "ctrl + z" << std::endl;
//		if (this->Undo())
//			return 1;
	}
	if (keysym->unicode > 32)
		std::cout << "touche " << SDL_GetKeyName(keysym->sym) << std::endl;
	return 0;
}

Control*		Control::Search_control(SDL_Event* event)
{
	Control*	ret;

	ret = this->Get_control(event, event->button.x, event->button.y);
	if (ret != 0 && this->_actif && ret->On_key_up(event))
		return ret;
	return 0;
}

bool		Control::Launch_callback(SDL_Event* event)
{
	Control*	tmp;

	tmp = this->Get_control(event, event->button.x, event->button.y);
	if (tmp != 0 && tmp->_actif)
	{
		tmp->On_key_down(event);
		return tmp->Click_button(event);
	}
	return 0;
}

bool		Control::Click_button(SDL_Event* event)
{
	(void)event;
	return 0;
}

bool		Control::Update(void)
{
	Control*	parent;
	Control*	child;

	child = this;
	parent = child->_parent;
	while (parent != 0)
	{
		if (SDL_BlitSurface(child->_surface, &child->_srcrect, parent->_surface, &child->_rect) == -1)
		{
			std::cout << SDL_GetError() << std::endl;
			return 1;
		}
		SDL_UpdateRect(parent->_surface, 0, 0, parent->_rect.w, parent->_rect.h);
		child = parent;
		parent = child->_parent;
	}
	return 0;
}

void		Control::Get_pos(pos* abs_pos)
{
	Control*	parent;
	Control*	child;

	child = this;
	parent = child->_parent;
	while (parent != 0)
	{
		abs_pos->x -= child->_rect.x;
		abs_pos->y -= child->_rect.y;
		child = parent;
		parent = child->_parent;
	}
}

bool		Control::FillRect(int x, int y, int w, int h, Uint32 color)
{
	int		i;
	int		j;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			this->Put_pixel(x + i, y + j, color);
			++i;
		}
		++j;
	}
	return (0);
}

bool		Control::Color_surface(Uint32 color)
{
	if (this->FillRect(0, 0, this->_surface->w, this->_surface->h, color) == -1)
		return (1);
	return (0);
}

bool		Control::Color_surface(int r, int g, int b)
{
	if (this->Color_surface(SDL_MapRGB(this->_surface->format, r, g, b)))
		return (1);
	return (0);
}

Control*	Control::Get_root(void)
{
	Control*	parent;

	parent = this->_parent;
	while (parent->_parent != 0)
		parent = parent->_parent;
	return parent;
}

void		Control::Refresh(void)
{
	std::list<Control*>::iterator	it;

	it = this->_child.begin();
	while (it != this->_child.end())
	{
		(*it)->Refresh();
		++it;
	}
	SDL_Flip(this->_surface);
}

void		Control::Set_callback(void (*fct)(SDL_Event*, Control*, void*), void* data)
{
	this->_fct = fct;
	this->_data = data;
}

void		Control::Put_pixel(int x, int y, Uint32 color)
{
	int		bpp;
	unsigned char*	p;

	bpp = this->_surface->format->BytesPerPixel;
	p = (unsigned char*)this->_surface->pixels + y * this->_surface->pitch + x * bpp;
	*(unsigned long*)p = color;
}

unsigned int	Control::Get_pixel(int x, int y)
{
	int		bpp;
	unsigned char*	p;

	bpp = this->_surface->format->BytesPerPixel;
	p = (unsigned char*)this->_surface->pixels + y * this->_surface->pitch + x * bpp;
	if (bpp == 4)
		return *(unsigned int*)p;
	return (0);
}

int		Control::Save(Paper* drawing_area)
{
	return SDL_SaveBMP(drawing_area->_surface, "bob.bmp");
}

bool		Control::Change_src(int x, int y)
{
	if (y != 0 && this->_srcrect.y + y + this->_parent->_surface->h <= this->_surface->h &&
	    this->_srcrect.y + y >= 0)
		this->_srcrect.y += y;
	if (x != 0 && this->_srcrect.x + x + this->_parent->_surface->w <= this->_surface->w &&
	    this->_srcrect.x + x >= 0)
		this->_srcrect.x += x;
	else
		return 1;
	return 0;
}

bool		Control::Top(void)
{
	if (this->FillRect(0, 0, this->_rect.w, this->_rect.h, SDL_MapRGB(this->_surface->format, 0, 0, 0)))
		return (1);
	if (this->FillRect(0, 0, this->_rect.w, this->_rect.h - 2, SDL_MapRGB(this->_surface->format, 30, 30, 30)))
		return (1);
	return (0);
}

bool		Control::Bot(void)
{
	if (this->FillRect(0, 0, this->_rect.w, this->_rect.h, SDL_MapRGB(this->_surface->format, 0, 0, 0)))
		return (1);
	if (this->FillRect(0, 0, this->_rect.w - 2, this->_rect.h, SDL_MapRGB(this->_surface->format, 30, 30, 30)))
		return (1);
	return (0);
}

void		Control::On_key_down(SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		this->_focus = true;
}

bool		Control::On_key_up(SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONUP && this->_focus)
	{
		this->_focus = false;
		return 1;
	}
	return 0;
}

bool		Control::is_pos_valid(int x, int y)
{
	return (x >= 0 && x < this->_rect.w &&
		y >= 0 && y < this->_rect.h);
}

bool		Control::Focus(SDL_Event*)
{
	return 0;
}

bool		Control::Resize(int w, int h)
{
	if (this->Color_surface(50, 50, 50))
		return 1;
	if (this->Update())
		return 1;
	this->_srcrect.x = 0;
	this->_srcrect.y = 0;
	this->_srcrect.w = w;
	this->_srcrect.h = h;
	this->_rect.w = w;
	this->_rect.h = h;
	SDL_FreeSurface(this->_surface);
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	if (this->_surface == 0)
		return 1;
	if (this->Update())
		return 1;
	return 0;
}


void		Control::Reverse(void)
{
	this->_child.reverse();
}

void		Control::Set_actif(bool actif)
{
	this->_actif = actif;
}


