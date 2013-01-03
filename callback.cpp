#include <iostream>
#include <SDL/SDL.h>
#include "control.h"
#include "window.h"
#include "paper.h"

bool	mouse_down(SDL_Event* event)
{
	return (event->button.type == SDL_MOUSEBUTTONDOWN &&
		(event->button.button == SDL_BUTTON_LEFT || event->button.button == SDL_BUTTON_RIGHT));
}

void	carre(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void) cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->carre_brush();

}

void	rond(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void) cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->rond_brush();
}

void	fct_button(SDL_Event* event, Control* cont, void* data)
{
	(void)data;
	(void)event;
	(void)cont;
}

void	brush(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(BRUSH);
}

void	eraser(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(ERASER);
}

void	load_file(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Load_file("cat.bmp");
}

void	pipette(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(EYEDROPPER);
}


void	fill(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(FILL);
}

void	get_color(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;
	pos	tmp;

	drawing_area = (Paper*)data;
	tmp.x = event->button.x;
	tmp.y = event->button.y;
	cont->Get_pos(&tmp);
	if (mouse_down(event) && cont->is_pos_valid(tmp.x, tmp.y))
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			drawing_area->Set_color(cont->Get_pixel(tmp.x, tmp.y), LEFT);
		else if (event->button.button == SDL_BUTTON_RIGHT)
			drawing_area->Set_color(cont->Get_pixel(tmp.x, tmp.y), RIGHT);
	}
}

void	save(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	drawing_area = (Paper*)data;
	if (event->button.button == SDL_BUTTON_LEFT)
		cont->Save(drawing_area);
}

void	square(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(SQUARE);
}

void	line(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(LINE);
}


void	circle(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Change_tool(CIRCLE);
}

void	rotate(SDL_Event* event, Control* cont, void* data)
{
	Paper*	drawing_area;

	(void)cont;
	drawing_area = (Paper*)data;
	if (mouse_down(event))
		drawing_area->Rotate();
}


void	taille(SDL_Event* event, Control* cont, void* data)
{
	Window*	screen;
	Paper*	drawing_area;

	drawing_area = (Paper*)data;
	(void)drawing_area;
	if (mouse_down(event))
	{
		screen = (Window*)cont->Get_root();
		screen->Show_taille();
	}
}

void	open_file(SDL_Event* event, Control* cont, void* data)
{
	Window*	screen;
	Paper*	drawing_area;

	drawing_area = (Paper*)data;
	(void)drawing_area;
	if (mouse_down(event))
	{
		screen = (Window*)cont->Get_root();
		screen->Show_open();
	}
}

void	save_file(SDL_Event* event, Control* cont, void* data)
{
	Window*	screen;
	Paper*	drawing_area;

	drawing_area = (Paper*)data;
	(void)drawing_area;
	if (mouse_down(event))
	{
		screen = (Window*)cont->Get_root();
		screen->Show_save();
	}
}
