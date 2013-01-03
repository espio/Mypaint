#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <SDL/SDL.h>



void	carre(SDL_Event* event, Control* cont, void* data);
void	rond(SDL_Event* event, Control* cont, void* data);
void	fct_menu(SDL_Event* event, Control* cont, void* data);
void	fct_draw(SDL_Event* event, Control* cont, void* data);
void	fct_button(SDL_Event* event, Control* cont, void* data);
void	brush(SDL_Event* event, Control* cont, void* data);
void	eraser(SDL_Event* event, Control* cont, void* data);
void	load_file(SDL_Event* event, Control* cont, void* data);
void	new_menu(SDL_Event* event, Control* cont, void* data);
void	pipette(SDL_Event* event, Control* cont, void* data);
void	fill(SDL_Event* event, Control* cont, void* data);
void	get_color(SDL_Event* event, Control* cont, void* data);
void	save(SDL_Event* event, Control* cont, void* data);
void	square(SDL_Event* event, Control* cont, void* data);
void	line(SDL_Event* event, Control* cont, void* data);
void	circle(SDL_Event* event, Control* cont, void* data);
void	rotate(SDL_Event* event, Control* cont, void* data);
void	taille(SDL_Event* event, Control* cont, void* data);
void	open_file(SDL_Event* event, Control* cont, void* data);
void	open_file(SDL_Event* event, Control* cont, void* data);
void	save_file(SDL_Event* event, Control* cont, void* data);

#endif
