#include "paint.h"
#include "control.h"
#include "callback.h"
#include "button.h"
#include "menu.h"
#include "menu_item.h"
#include "paper.h"
#include "scrollbar.h"
#include "text_area.h"
#include <iostream>
#include <SDL/SDL_ttf.h>
#include <exception>

Paint::Paint(void)
{
	this->__police = NULL;
	this->__drawing_area = 0;
	this->__menu_size = 42;
	this->__tool_size = 82;
	this->__whidth = 800;
	this->__height = 600;
	this->__focus = 0;
}

Paint::~Paint(void)
{
	TTF_CloseFont(this->__police);
	TTF_Quit();
}

bool	Paint::Load_ttf(void)
{
	if (TTF_Init() == -1)
	{
		std::cout << "Can't init ttf" << std::endl;
		return 1;
	}
	this->__police = TTF_OpenFont("PIXEARG_.TTF", 15);
	if (this->__police == NULL)
	{
		std::cout << "Can't load ttf" << std::endl;
		return 1;
	}
	return 0;
}

bool	Paint::Load_paper(int argc, char** argv)
{
	Paper*		surface;
	Scrollbar*	scroll;

	scroll = new (std::nothrow) Scrollbar();
	if (scroll == 0 || scroll->Init(this->__tool_size, this->__menu_size, 500, 500) == 0)
	{
		delete scroll;
		return 1;
	}
	surface = new (std::nothrow) Paper();
	if (surface == 0)
	{
		delete scroll;
		return 1;
	}
	if (argc == 2 && surface->Init(0, 0, argv[1]) == 0)
	{
		delete scroll;
		delete surface;
		return 1;
	}
	else if (argc != 2 && surface->Init(0, 0, 500, 500) == 0)
	{
		delete scroll;
		delete surface;
		return 1;
	}
	if (scroll->Add_child(surface))
	{
		delete scroll;
		delete surface;
		return 1;
	}
	if ( this->__root.Add_child(scroll))
	{
		delete scroll;
		return 1;
	}
	this->__drawing_area = surface;
	return 0;
}

Menu_item*	Paint::Menu_file(void)
{
	Menu_item*	menu;

	menu = new (std::nothrow) Menu_item();
	if (menu == 0 || menu->Init(this->__tool_size, 10, 50, this->__menu_size, "  file  ", this->__police, this->__drawing_area))
	{
		delete menu;
		return 0;
	}
	if (menu->Add_items(0, 0, 50, 20, taille, this->__drawing_area, "picture/menu/new.bmp") ||
	    menu->Add_items(0, 20, 50, 20, open_file, this->__drawing_area, "picture/menu/open.bmp") ||
	    menu->Add_items(0, 40, 50, 20, save_file, this->__drawing_area, "picture/menu/save.bmp"))
	{
		delete menu;
		return 0;
	}
	return menu;
}

bool	Paint::Init_menu(Control* screen)
{
	Menu*		menu;
	Menu_item*	file;

	menu = new (std::nothrow) Menu();
	if (menu == 0 || menu->Init(0, 0, this->__whidth - 300, this->__menu_size) == 0)
	{
		delete menu;
		return 1;
	}
	file = this->Menu_file();
	if (file == 0 || menu->Add_items(file))
	{
		delete file;
		delete menu;
		return 1;
	}
	if (screen->Add_child(menu) || this->__root.Add_child(screen))
	{
		delete menu;
		return 1;
	}
	if (file->Add_surface())
		return 1;
	return this->__drawing_area->Update();
}

bool	Paint::Init_top(void)
{
	Control*	screen;
	Text_area*	px;

	screen = new (std::nothrow) Control();
	if (screen == 0 || screen->Init(0, 0, this->__whidth, this->__menu_size) == 0 || screen->Top())
	{
		delete screen;
		return 1;
	}
	px = new (std::nothrow) Text_area();
	if (px == 0 || px->Init(this->__whidth - 300, 10, 100, 20, "PX : ", this->__police, this->__drawing_area, 0) == 0 ||
	    screen->Add_child(px))
	{
		delete px;
		delete screen;
		return 1;
	}
	if (this->Init_menu(screen))
	{
		delete screen;
		return 1;
	}
	return 0;
}

bool	Paint::Init_tool(void)
{
	Menu*		tool;

	tool = new (std::nothrow) Menu();
	if (tool == 0 || tool->Init(0, this->__menu_size, this->__tool_size, this->__height - this->__menu_size) == 0 ||
	    tool->Bot())
	{
		delete tool;
		return 1;
	}
	if (tool->Add_items(7.5, 280, 15, 15, 0, this->__drawing_area, 255, 0, 0) ||
	    tool->Add_items(32.5, 280, 15, 15, 0, this->__drawing_area, 0, 0, 255) ||
	    tool->Add_items(57.5, 280, 15, 15, 0, this->__drawing_area, 0, 255, 0) ||
	    tool->Add_items(21, 261, 15, 15, 0, this->__drawing_area, 0, 0, 0) ||
	    tool->Add_items(45, 261, 15, 15, 0, this->__drawing_area, 255, 255, 255) ||
	    tool->Add_items(7.5, 28, 25, 25, brush, this->__drawing_area, "picture/pinceau.bmp") ||
	    tool->Add_items(47.5, 66.5, 25, 25, pipette, this->__drawing_area, "picture/pipette.bmp") ||
	    tool->Add_items(47.5, 181, 25, 25, square, this->__drawing_area, "picture/carre.bmp") ||
	    tool->Add_items(47.5, 219, 25, 25, carre, this->__drawing_area, "picture/carre-Brush.bmp") ||
	    tool->Add_items(7.5, 219, 25, 25, rond, this->__drawing_area, "picture/rond_brush.bmp") ||
	    tool->Add_items(7.5, 143, 25, 25, line, this->__drawing_area, "picture/trait.bmp") ||
	    tool->Add_items(47.5, 143, 25, 25, circle, this->__drawing_area, "picture/circle.bmp") ||
	    tool->Add_items(7.5, 181, 25, 25, pipette, this->__drawing_area, "picture/resize.bmp") ||
	    tool->Add_items(47.5, 105, 25, 25, rotate, this->__drawing_area, "picture/rotate.bmp") ||
	    tool->Add_items(47.5, 28, 25, 25, eraser, this->__drawing_area, "picture/Eraser.bmp") ||
	    tool->Add_items(7.5, 66.5, 25, 25, fct_button, 0, "picture/loupe.bmp") ||
	    tool->Add_items(7.5, 105, 25, 25, fill, this->__drawing_area, "picture/fill.bmp") ||
	    tool->Add_items(10, 305, 60, 60, get_color, this->__drawing_area, "picture/palette1.bmp") ||
	    tool->Add_items(10, 365, 60, 60, get_color, this->__drawing_area, "picture/palette4.bmp") ||
	    tool->Add_items(10, 425, 60, 60, get_color, this->__drawing_area, "picture/palette2.bmp") ||
	    tool->Add_items(10, 486, 60, 60, get_color, this->__drawing_area, "picture/palette3.bmp") ||
	    this->__root.Add_child(tool))
	{
		delete tool;
		return 1;
	}
	return 0;
}

bool	Paint::Init_window(int argc, char** argv)
{
	if (this->Load_paper(argc, argv))
		return 1;
	if (this->__root.surface_taille(this->__drawing_area) ||
	    this->__root.surface_open(this->__drawing_area)||
	    this->__root.surface_save(this->__drawing_area))
		return 1;
	if (this->Init_top())
		return 1;
	if (this->Init_tool())
		return 1;
	return 0;
}

bool	Paint::Create_window(void)
{
	if (this->__root.Init(this->__whidth, this->__height, this->__police) == 0 ||
	    this->__root.Color_surface(50, 50, 50))
		return 1;
	return 0;
}

bool	Paint::Init(int argc, char** argv)
{
	if (this->Load_ttf())
		return 1;
	if (this->Create_window())
		return 1;
	if (this->Init_window(argc, argv))
		return 1;
	return 0;
}

bool	Paint::Run(void)
{
	bool		quit;
	SDL_Event	event;
	Control*	focus;

	quit = false;
	while (quit == false)
	{
		SDL_WaitEvent(&event);
		focus = this->__root.Search_control(&event);
		if (focus != 0)
			this->__focus = focus;
		if (this->__focus != 0 && this->__focus->Click_button(&event))
			quit = true;
		if (this->__root.Launch_callback(&event))
			quit = true;
		else
			quit = (event.type == SDL_QUIT);
	}
	return 0;
}
