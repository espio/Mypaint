#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "control.h"
#include "text_area.h"

class	Paper;

class	Window: public Control
{
	TTF_Font*	__font;
	Control*	__taille;
	Text_area*	__save;
	Text_area*	__open;
public:
	Window(void);
	~Window(void);

	bool		surface_open(Paper* draw);
	bool		Show_open(void);
	bool		surface_save(Paper* draw);
	bool		Show_save(void);
	bool		Show_taille(void);
	SDL_Surface*	Init(int w, int h, TTF_Font* font);
	bool		surface_taille(Paper* draw);

};

#endif
