#ifndef _Color_H_
#define _Color_H_

#include "control.h"

class	Color: public Control
{
	Uint32		__color;
	virtual bool	Click_button(SDL_Event* event);
public:
	Color(void);
	~Color(void);

	SDL_Surface*	Init(int x, int y, int w, int h, Uint32 Color);
	Uint32		Get_color(void) const;
};

#endif
