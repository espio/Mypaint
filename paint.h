#ifndef _PAINT_H_
#define _PAINT_H_

#include "control.h"
#include "window.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class	Paper;
class	Menu_item;

class	Paint
{
	int		__whidth;
	int		__height;
	int		__menu_size;
	int		__tool_size;
	TTF_Font*	__police;
	Window		__root;
	Paper*		__drawing_area;
	Control*	__focus;

	bool		Create_window(void);
	bool		Init_window(int argc, char** argv);
	bool		Init_menu(Control*);
	bool		Init_top(void);
	bool		Init_tool(void);
	bool		Load_file(char* file_name);
	bool		Load_paper(int argc, char** argv);
	bool		Load_ttf(void);
	Menu_item*	Menu_file(void);
public:
	Paint(void);
	~Paint(void);

	bool	Init(int argc, char** argv);
	bool	Run(void);
};

#endif
