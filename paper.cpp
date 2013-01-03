#include "paper.h"
#include <iostream>
#include <math.h>

Paper::Paper(void)
{
	this->__tool_list[BRUSH].fct = &Paper::Brush;
	this->__tool_list[ERASER].fct = &Paper::Eraser;
	this->__tool_list[MAGNIFIER].fct = &Paper::Magnifier;
	this->__tool_list[EYEDROPPER].fct = &Paper::Eyedropper;
	this->__tool_list[FILL].fct = &Paper::Fill;
	this->__tool_list[SELECTION].fct = &Paper::Selection;
	this->__tool_list[SHAPE].fct = &Paper::Shape;
	this->__tool_list[SQUARE].fct = &Paper::Square;
	this->__tool_list[LINE].fct = &Paper::Line;
	this->__tool_list[CIRCLE].fct = &Paper::Circle;
	this->__pressed = OTHER;
	this->__x = 0;
	this->__y = 0;
	this->__width = 0;
	this->__height = 0;
	this->__type = BRUSH;
	this->__init_tool = false;
	this->__size_brush = 1;
	this->__brush = true;
	this->_save = 0;
}

Paper::~Paper(void)
{
	SDL_FreeSurface(this->__save);
}

SDL_Surface*	Paper::Init(int x, int y, char* file)
{
	SDL_Surface*	surface;

	surface = SDL_LoadBMP(file);
	if (surface == 0)
		return 0;
	this->_surface = SDL_DisplayFormat(surface);
	SDL_FreeSurface(surface);
	if (this->_surface == NULL)
		return 0;
	this->Init_rect(x, y, this->_surface->w, this->_surface->h);
	this->__color_left = SDL_MapRGB(this->_surface->format, 0, 0, 0);
	this->__color_right = SDL_MapRGB(this->_surface->format, 255, 255, 255);
	this->__color = this->__color_left;

	return this->_surface;
}

SDL_Surface*	Paper::Init(int x, int y, int w, int h)
{
	this->_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
	this->Init_rect(x, y, w, h);
	if (this->_surface == 0)
		return 0;
	if (this->Color_surface(255, 255, 255))
		return 0;
	this->__color_left = SDL_MapRGB(this->_surface->format, 0, 0, 0);
	this->__color_right = SDL_MapRGB(this->_surface->format, 255, 255, 255);
	this->__color = this->__color_left;
	return this->_surface;
}

void	Paper::Draw_circle(int r, int center_x, int center_y)
{
	int	x;
	int	y;
	int	m;

	x = 0;
	y = r;
	m = 5 - 4 * r;
	while (x <= y)
	{
		this->Disque(center_x + x, center_y + y);
		this->Disque(center_x + y, center_y + x);
		this->Disque(center_x - x, center_y + y);
		this->Disque(center_x - y, center_y + x);
		this->Disque(center_x + x, center_y - y);
		this->Disque(center_x + y, center_y - x);
		this->Disque(center_x - x, center_y - y);
		this->Disque(center_x - y, center_y - x);
		if (m > 0)
		{
			--y;
			m = m - 8 * y;
		}
		++x;
		m = m + 8 * x + 4;
	}
}

bool		Paper::Click_button(SDL_Event* event)
{
	pos	tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (tmp.x < 0 || tmp.y < 0 || tmp.x > this->_rect.w || tmp.y > this->_rect.h)
	{
		this->__pressed = OTHER;
		return 0;
	}
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			this->__pressed = LEFT;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			this->__pressed = RIGHT;
	}
	if (this->__pressed == OTHER)
		return 0;
	if (event->button.type == SDL_MOUSEBUTTONUP)
		this->__pressed = OTHER;
	if (this->__pressed == LEFT)
		this->__color = this->__color_left;
	else if (this->__pressed == RIGHT)
		this->__color = this->__color_right;
	return ((this->*__tool_list[this->__type].tool::fct)(event));
}

void		Paper::Disque(int cx, int cy)
{
	int	d;
	int	x;
	double	y;
	if (this->__brush == true)
	{
		d = 3 - (2 * this->__size_brush);
		x = 0;
		y = this->__size_brush;
		while (y >= x)
		{
			this->FillRect(cx - x, cy - y, 2 * x + 1, 1, this->__color);
			this->FillRect(cx - x, cy + y, 2 * x + 1, 1, this->__color);
			this->FillRect(cx - y, cy - x, 2 * y + 1, 1, this->__color);
			this->FillRect(cx - y, cy + x, 2 * y + 1, 1, this->__color);
			if (d < 0)
				d = d + (4 * x) + 6;
			else
			{
				d = d + 4 * (x - y) + 10;
				--y;
			}
			++x;
		}
	}
	else if (this->__type == BRUSH || this->__type == ERASER || this->__type == SQUARE)
		this->FillRect(cx - this->__size_brush / 2, cy - this->__size_brush / 2,
			       this->__size_brush, this->__size_brush, this->__color);
}

void		Paper::Set_color(Uint32 color, state_mouse side)
{
	if (side == LEFT)
		this->__color_left = color;
	else if (side == RIGHT)
		this->__color_right = color;
}

void		Paper::Set_color(int r, int g, int b)
{
	this->__color = SDL_MapRGB(this->_surface->format, r, g, b);
}

int		Paper::Load_file(const char* file)
{
	SDL_Surface*	surface;

	surface = SDL_LoadBMP(file);
	if (surface == 0)
		return 1;
	SDL_FreeSurface(this->_surface);
	this->Set_actif(true);
	this->Init_rect(0, 0, surface->w, surface->h);
	this->_surface = SDL_DisplayFormat(surface);
	SDL_FreeSurface(surface);
	if (this->_surface == NULL)
		return 1;
	return this->Update();
}

int		Paper::Save_file(const char* file)
{
	this->Set_actif(true);
	return SDL_SaveBMP(this->_surface, file);
}



bool		Paper::Clear(void)
{
	SDL_FreeSurface(this->_surface);
	this->_surface = 0;
	return this->Color_surface(255, 255, 255);
}

int		Paper::Abs(int val)
{
	if (val < 0)
		return -val;
	return val;
}

void		Paper::Line(int x1, int y1, int x2, int y2)
{
	int	Dx;
	int	Dy;
	int	xincr;
	int	yincr;
	int	i;
	int	error;

	Dx = this->Abs(x1 - x2);
	Dy = this->Abs(y1 - y2);
	if (x2 < x1)
		xincr = 1;
	else
		xincr = -1;
	if (y2 < y1)
		yincr = 1;
	else
		yincr = -1;
	if (Dx > Dy)
	{
		error = Dx / 2;
		for (i = 0; i < Dx; ++i)
		{
			x2 += xincr;
			error += Dy;
			if (error > Dx)
			{
				error -= Dx;
				y2 += yincr;
			}
			this->Disque(x2, y2);
		}
	}
	else
	{
		error = Dy / 2;
		for (i = 0; i < Dy; ++i)
		{
			y2 += yincr;
			error += Dx;
			if (error > Dy)
			{
				error -= Dy;
				x2 += xincr;
			}
			this->Disque(x2, y2);
		}
	}
}

void		Paper::Put_pixel(int x, int y, Uint32 color)
{
	int		bpp;
	unsigned char*	p;

	bpp = this->_surface->format->BytesPerPixel;
	p = (unsigned char*)this->_surface->pixels + (y + this->_srcrect.y) * this->_surface->pitch + (x + this->_srcrect.x) * bpp;
	if (x >= 0 && y >= 0 && x < this->_surface->w && y < this->_surface->h)
		*(unsigned*)p = color;
}

void	Paper::carre_brush()
{
	this->__brush = false;
}

void	Paper::rond_brush()
{
	this->__brush = true;
}

void		Paper::Get_color(SDL_Event* event, state_mouse side)
{
	pos	tmp;

	int		bpp;
	unsigned char*	p;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	bpp = this->_surface->format->BytesPerPixel;
	p = (unsigned char*)this->_surface->pixels + tmp.y * this->_surface->pitch + tmp.x * bpp;
	if (side == LEFT)
		this->__color_left = (Uint32)*p;
	else if (side == RIGHT)
		this->__color_right = (Uint32)*p;
}

bool		Paper::Brush(SDL_Event* event)
{
	this->Draw(event);
	return 0;
}

bool		Paper::Eraser(SDL_Event* event)
{
	this->__color = SDL_MapRGB(this->_surface->format, 255, 255, 255);
	this->Draw(event);
	return 0;
}

bool		Paper::Magnifier(SDL_Event*)
{


	return 0;
}

bool		Paper::Eyedropper(SDL_Event* event)
{
	pos		tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			this->__color_left = this->Get_pixel(tmp.x, tmp.y);
		else if (event->button.button == SDL_BUTTON_RIGHT)
			this->__color_right = this->Get_pixel(tmp.x, tmp.y);
	}
	return 0;
}

bool		Paper::Fill(SDL_Event* event)
{
	pos	tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			this->Flood_fill(&tmp, this->__color, this->Get_pixel(tmp.x, tmp.y));
		else if (event->button.button == SDL_BUTTON_RIGHT)
			this->Fill_color(this->__color, this->Get_pixel(tmp.x, tmp.y));
		this->Update();
	}
	return 0;
}

bool		Paper::Fill_color(Uint32 cr, Uint32 cb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < this->_surface->h)
	{
		while (i < this->_surface->w)
		{
			if (this->Get_pixel(i, j) == cb && cr != cb)
				this->Put_pixel(i, j, cr);
			++i;
		}
		i = 0;
		++j;
	}
	return 0;
}

void	add(std::list<pos>* list, pos* add)
{
	std::list<pos>::iterator	it;

	it = list->begin();
	while (it != list->end() && !(it->x == add->x && it->y == add->y))
		++it;
	if (it == list->end())
		list->push_back(*add);
}


bool		Paper::Flood_fill(pos* px, Uint32 cr, Uint32 cb)
{
	std::list<pos>	list;
	pos		tmp;

	try
	{
		list.push_back(*px);
		while (list.empty() == 0)
		{
			tmp = list.front();
			if (tmp.x >= 0 && tmp.x < this->_surface->w &&
			    tmp.y >= 0 && tmp.y < this->_surface->h &&
			    this->Get_pixel(tmp.x, tmp.y) == cb && cr != cb)
			{
				this->Put_pixel(tmp.x, tmp.y, cr);
				++tmp.y;
				list.push_back(tmp);
				tmp.y -= 2;
				list.push_back(tmp);
				++tmp.x;
				++tmp.y;
				list.push_back(tmp);
				tmp.x -= 2;
				list.push_back(tmp);
				++tmp.x;
			}
			list.pop_front();
		}
	}
	catch (std::exception ex)
	{
		return 1;
	}
	return 0;
}

bool		Paper::Selection(SDL_Event*)
{


	return 0;
}

bool		Paper::Shape(SDL_Event*)
{


	return 0;
}

bool		Paper::Circle(SDL_Event* event)
{
	pos	tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		this->__x = tmp.x;
		this->__y = tmp.y;
	}
	if (this->__x != tmp.x && this->__y != tmp.y)
	{
		this->Save_surface();
		this->Draw_circle(sqrt((this->__x - tmp.x) * (this->__x - tmp.x) + (this->__y - tmp.y) * (this->__y - tmp.y)),
			  this->__x, this->__y);
		this->Update();
		if (event->button.type != SDL_MOUSEBUTTONUP)
			this->Get_surface();
	}
	return 0;
}

bool		Paper::Square(SDL_Event* event)
{
	pos	tmp;

	this->__brush = false;
	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		this->__x = tmp.x;
		this->__y = tmp.y;
	}
	if (this->__x != tmp.x && this->__y != tmp.y)
	{
		this->Save_surface();
		this->Line(this->__x, this->__y, tmp.x, this->__y);
		this->Line(this->__x, this->__y, this->__x, tmp.y);
		this->Line(tmp.x, this->__y, tmp.x, tmp.y);
		this->Line(this->__x, tmp.y, tmp.x, tmp.y);
		this->Update();
		if (event->button.type != SDL_MOUSEBUTTONUP)
			this->Get_surface();
	}
	return 0;
}

bool		Paper::Line(SDL_Event* event)
{
	pos	tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		this->__x = tmp.x;
		this->__y = tmp.y;
	}
	if (this->__x != tmp.x && this->__y != tmp.y)
	{
		this->Save_surface();
		this->Line(this->__x, this->__y, tmp.x, tmp.y);
		this->Update();
		if (event->button.type != SDL_MOUSEBUTTONUP)
			this->Get_surface();
	}
	return 0;
}

void		Paper::Change_tool(tool_type type)
{
	this->__pressed = OTHER;
	this->__init_tool = false;
	this->__type = type;
	this->__brush = true;
}

bool		Paper::Draw(SDL_Event* event)
{
	pos	tmp;

	tmp.x = event->button.x;
	tmp.y = event->button.y;
	this->Get_pos(&tmp);
	if (event->button.type == SDL_MOUSEBUTTONDOWN)
	{
		this->__x = tmp.x;
		this->__y = tmp.y;
	}
	this->Disque(this->__x, this->__y);
	this->Line(this->__x, this->__y, tmp.x, tmp.y);
	this->__x = tmp.x;
	this->__y = tmp.y;
	return this->Update();
}

int		Paper::Change_size_brush(double size)
{
	if (size > 0 && size < 20)
		this->__size_brush = size;
	return -1;
}

int		Paper::New_width(int width)
{
	if (width > 0)
	{
		this->__width = width;
		if (this->__width != 0 && this->__height != 0)
		{
			if (this->Resize(this->__width, this->__height) || this->Color_surface(255, 255, 255))
				return 1;
			this->__width = 0;
			this->__height = 0;
			this->Set_actif(true);
			if (this->Update())
				return 1;
			return 0;
		}
	}
	return -1;
}

int		Paper::New_height(int height)
{
	if (height > 0)
	{
		this->__height = height;
		if (this->__width != 0 && this->__height != 0)
		{
			if (this->Resize(this->__width, this->__height) || this->Color_surface(255, 255, 255))
				return 1;
			this->__width = 0;
			this->__height = 0;
			this->Set_actif(true);
			if (this->Update())
				return 1;
			return 0;
		}
	}
	return -1;
}

bool		Paper::Rotate(void)
{
	SDL_Surface*	screen;
	int		bpp;
	unsigned char*	q;
	int		x;
	int		y;

	y = 0;
	screen = SDL_DisplayFormat(this->_surface);
	if (this->Resize(this->_surface->h, this->_surface->w))
	{
		SDL_FreeSurface(screen);
		return 1;
	}
	bpp = screen->format->BytesPerPixel;
	while (y < this->_surface->w)
	{
		x = 0;
		while (x < this->_surface->h)
		{
			q = (unsigned char*)this->_surface->pixels +
			     (x) * this->_surface->pitch +
			     (this->_surface->w - y - 1) * bpp;
			*(unsigned int*)q = *(unsigned int*)((unsigned char*)screen->pixels + y * screen->pitch + x * bpp);
			++x;
		}
		++y;
	}
	SDL_FreeSurface(screen);
	return this->Update();
}

void	Paper::Set_actif(bool actif)
{
	this->_parent->Set_actif(actif);
}

bool	Paper::Save_surface(void)
{
	if (this->__save != 0)
		SDL_FreeSurface(this->__save);
	this->__save = SDL_DisplayFormat(this->_surface);
	if (this->__save == 0)
		return 1;
	return 0;
}

bool	Paper::Get_surface(void)
{
	if (this->_surface != 0)
		SDL_FreeSurface(this->_surface);
	this->_surface = SDL_DisplayFormat(this->__save);
	if (this->_surface == 0)
		return 1;
	return 0;
}
