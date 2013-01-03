#ifndef _PAPER_H_
#define _PAPER_H_

#include "control.h"
#include "menu_item.h"
#include <list>

class	Menu_item;

enum	state_mouse
{
	LEFT,
	RIGHT,
	OTHER
};

enum	tool_type
{
	BRUSH,
	ERASER,
	MAGNIFIER,
	EYEDROPPER,
	FILL,
	SELECTION,
	SHAPE,
	SQUARE,
	LINE,
	CIRCLE,
	CURVE
};

struct	tool
{
	bool		(Paper::*fct)(SDL_Event*);
};

class	Paper: public Control
{
	int		__width;
	int		__height;
	bool		__brush;
	double		__size_brush;
	bool		__init_tool;
	tool		__tool_list[11];
	tool_type	__type;
	state_mouse	__pressed;
	unsigned int	__color_left;
	unsigned int	__color_right;
	unsigned int	__color;
	int		__x;
	int		__y;
	SDL_Surface*	__save;

	bool		Save_surface(void);
	bool		Get_surface(void);
	bool		Init_pixel(void);
	int		Re_to_EcrX(double r);
	int		Re_to_EcrY(double r);
	double		Ecr_to_ReX(int i);
	double		Ecr_to_ReY(int i);
	void		Showposs();
	void		Casteljau(double t,pos* tab,int nbpoints,double* rx,double* ry);
	void		ShowBezier(double tstep);
	void		CheckMouseDeplace(SDL_Event* event);
	void		clear_list(std::list<pos>* list_fill);
	bool		add_list(std::list<pos>* list_fill, int x, int y);
	void		Add_event(SDL_Event*);
	void		Draw_circle(int r, int center_x, int center_y);
	void		Disque(int cx, int cy);
	void		Line(int x1, int y1, int x2, int y2);
	void		Flood(int x, int y, Uint32 cb);
	bool		Flood_fill(pos* px, Uint32 cr, Uint32 cb);
	bool		Fill_color(Uint32 cr, Uint32 cb);
	bool		Draw(SDL_Event*);
	virtual void	Put_pixel(int x, int y, Uint32 color);
	int		Abs(int val);
	void		Clear_pixel(void);

	bool		Line(SDL_Event*);
	bool		Brush(SDL_Event*);
	bool		Eraser(SDL_Event*);
	bool		Magnifier(SDL_Event*);
	bool		Eyedropper(SDL_Event*);
	bool		Fill(SDL_Event*);
	bool		Selection(SDL_Event*);
	bool		Shape(SDL_Event*);
	bool		Square(SDL_Event*);
	bool		Circle(SDL_Event*);
	bool		Curve(SDL_Event*);
public:
	Paper(void);
	~Paper(void);

	void		carre_brush();
	void		rond_brush();
	int		Load_file(const char* file);
	int		Save_file(const char* file);
	void		Set_actif(bool actif);
	void		InitCpoints(void);
	SDL_Surface*	Init(int x, int y, int w, int h);
	SDL_Surface*	Init(int x, int y, char* file);
	void		Set_color(Uint32 color, state_mouse);
	void		Set_color(int r, int g, int b);
	bool		Clear(void);
	void		Get_color(SDL_Event* event, state_mouse side);
	virtual	bool	Click_button(SDL_Event* event);
	void		Change_tool(tool_type type);
	int		Change_size_brush(double size);
	int		New_width(int width);
	int		New_height(int height);
	bool		Rotate(void);
};

#endif
