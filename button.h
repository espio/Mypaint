#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "control.h"
#include <SDL/SDL_ttf.h>

class	Button: public Control
{
	SDL_Surface*	__image;
	SDL_Rect	__srcrect;
	virtual	bool	Click_button(SDL_Event*);
	bool		Delete_menu(void);
	bool		New_menu(void);
	virtual bool	Focus(SDL_Event*);
	virtual bool	On_key_up(SDL_Event*);
public:
	Button(void);
	~Button(void);

	SDL_Surface*	Init(int x, int y, int w, int h, const char* image);
};

#endif
