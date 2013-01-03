#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_

#include "control.h"

class	Scrollbar: public Control
{
	SDL_Rect	__srcrect;
	Control*	__screen;

	void		Horizontal(void);
	void		Vertical(void);
	virtual	bool	Click_button(SDL_Event*);
	virtual	bool	Resize(int w, int h);
public:
	Scrollbar(void);
	SDL_Surface*	Init(int x, int y, int w, int h);
	bool		Add_child(Control* child);
	virtual void	Rotate(void);
};

#endif
