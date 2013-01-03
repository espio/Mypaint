#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <SDL/SDL.h>
#include <list>

class	Window;
class	Paper;

struct	pos
{
	int	x;
	int	y;
};

class	Control
{
	Control*		Get_control(SDL_Event* event, int x, int y);
	void			Refresh(void);
	bool			Is_in_area(int x, int y);
protected:
	Control*		_parent;
	bool			_actif;
	bool			_etat;
	bool			_focus;
	int			_weight;
	SDL_Rect		_srcrect;
	SDL_Rect		_rect;
	SDL_Surface*		_save;
	SDL_Surface*		_surface;
	std::list<Control*>	_child;
	void			(*_fct)(SDL_Event* event, Control* cont, void* data);
	void*			_data;

	virtual void		On_key_down(SDL_Event* event);
	virtual bool		On_key_up(SDL_Event* event);
	bool			InputKeyboardEvent(SDL_KeyboardEvent* event);
	bool			FillRect(int x, int y, int w, int h, Uint32 color);
	virtual void		Put_pixel(int x, int y, Uint32 color);
	void			Init_rect(int x, int y, int w, int h);
public:
	Control(void);
	~Control(void);

	Control*		Get_root(void);
	void			Set_actif(bool actif);
	void			Reverse(void);
	void			Get_pos(pos* abs_pos);
	SDL_Surface*		Init(int x, int y, int w, int h);
	bool			Launch_callback(SDL_Event* event);
	bool			Add_child(Control* child, bool unique = 0);
	bool			Color_surface(Uint32 color);
	bool			Color_surface(int r, int g, int b);
	bool			New_menu(Paper* drawing_area);
	bool			Delete_menu(void);
	void			Set_callback(void (*fct)(SDL_Event*, Control*, void*), void* data);
	bool			Update(void);
	unsigned int		Get_pixel(int x, int y);
	int			Save(Paper* drawing_area);
	virtual	bool		Click_button(SDL_Event*);
	bool			Change_src(int x, int y);
	bool			Top(void);
	bool			Bot(void);
	Control*		Search_control(SDL_Event* event);
	bool			is_pos_valid(int x, int y);
	virtual bool		Focus(SDL_Event*);
	virtual bool		Resize(int w, int h);
	SDL_Surface*		Get_surface(void);
};

#endif
