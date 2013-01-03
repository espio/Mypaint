#ifndef __TEXT_AREA_H_
#define __TEXT_AREA_H_


#include "button.h"
#include <SDL/SDL_ttf.h>
class	Paper;

enum	area_id
{
	SIZE_BRUSH,
	NEW_WIDTH,
	NEW_HEIGHT,
	FILE_OPEN,
	FILE_SAVE
};

class	Text_area: public Control
{
	TTF_Font*	__font;
	SDL_Rect	__rect_message;
	SDL_Surface*	__message;
	unsigned int	__size_text;
	char		__text[100];
	SDL_Color	__color;
	virtual bool	Click_button(SDL_Event*);
	bool		is_text_valid(char);
	bool		clear_message(void);
	bool		write(char c);
	bool		add_message(void);
	Paper*		__drawing_area;
	bool		Valid_message(void);
	virtual bool	Focus(SDL_Event*);
	char		get_key(SDL_keysym*);
	area_id		__id;
public:
	Text_area(void);
	~Text_area(void);
	SDL_Surface*	Init(int x, int y, int w, int h, const char* image, TTF_Font* font, Paper* draw, void (*fct)(SDL_Event*, Control*, void*));
	void		Set_id(area_id id);
};

#endif

