#include "window.h"
#include "control.h"
#include "text_area.h"
#include <iostream>

Window::Window(void)
{
	this->__save = 0;
	this->__taille = 0;
}

Window::~Window(void)
{
	SDL_Quit();
}

SDL_Surface*	Window::Init(int w, int h, TTF_Font* font)
{

	this->__font = font;
	this->Init_rect(0, 0, w, h);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return 0;
	}
	this->_surface = SDL_SetVideoMode(w, h, 0, SDL_HWSURFACE | SDL_RESIZABLE);
	if (this->_surface == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return 0;
	}
	SDL_WM_SetCaption("Id_Paint", NULL);
	return this->_surface;
}

bool		Window::surface_taille(Paper* draw)
{
	Text_area*	width;
	Text_area*	height;

	this->__taille = new (std::nothrow) Control();
	if (this->__taille == 0 ||
	    this->__taille->Init(this->_surface->w / 2 - 100, this->_surface->h / 2 - 10, 200, 60) == 0 || 
	    this->__taille->Color_surface(30, 30, 30))
	{
		delete this->__taille;
		return 1;
	}
	width = new (std::nothrow) Text_area();
	if (width == 0 ||
	    width->Init(0, 10, 180, 20, "Width : ", this->__font, draw, 0) == 0 || this->__taille->Add_child(width))
	{
		delete this->__taille;
		delete width;
		return 1;
	}
	width->Set_id(NEW_WIDTH);
	height = new (std::nothrow) Text_area();
	if (height == 0 ||
	    height->Init(0, 30, 180, 20, "Height : ", this->__font, draw, 0) == 0 || this->__taille->Add_child(height))
	{
		delete this->__taille;
		delete height;
		return 1;
	}
	height->Set_id(NEW_HEIGHT);
	if (this->Add_child(this->__taille))
	{
		delete this->__taille;
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	this->__taille->Set_actif(false);
	return 0;
}

bool	Window::Show_taille(void)
{
	this->__taille->Set_actif(true);
	this->__open->Set_actif(false);
	this->__save->Set_actif(false);
	return this->__taille->Update();
}

bool		Window::surface_open(Paper* draw)
{
	this->__open = new (std::nothrow) Text_area();
	if (this->__open == 0 ||
	    this->__open->Init(this->_surface->w / 2 - 100, this->_surface->h / 2 - 10, 200, 20, "open : ", this->__font, draw, 0) == 0 ||
	    this->Add_child(__open))
	{
		delete this->__open;
		return 1;
	}
	this->__open->Set_actif(false);
	this->__open->Set_id(FILE_OPEN);
	return 0;
}

bool	Window::Show_open(void)
{
	this->__taille->Set_actif(false);
	this->__open->Set_actif(true);
	this->__save->Set_actif(false);
	return this->__open->Update();
}


bool		Window::surface_save(Paper* draw)
{
	this->__save = new (std::nothrow) Text_area();
	if (this->__save == 0 ||
	    this->__save->Init(this->_surface->w / 2 - 100, this->_surface->h / 2 - 10, 200, 20, "save : ", this->__font, draw, 0) == 0 ||
	    this->Add_child(this->__save))
	{
		delete this->__save;
		return 1;
	}
	this->__save->Set_actif(false);
	this->__save->Set_id(FILE_SAVE);
	return 0;
}

bool	Window::Show_save(void)
{
	this->__taille->Set_actif(false);
	this->__open->Set_actif(false);
	this->__save->Set_actif(true);
	return this->__save->Update();
}
