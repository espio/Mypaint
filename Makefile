NAME		=	id_paint

SRC		=	atoi.cpp	\
			atof.cpp	\
			button.cpp	\
			callback.cpp	\
			color.cpp	\
			control.cpp	\
			main.cpp	\
			menu.cpp	\
			menu_item.cpp	\
			paint.cpp	\
			paper.cpp	\
			scrollbar.cpp	\
			text_area.cpp	\
			window.cpp

CFLAGS		+=	-W -Wall -Werror -g3

LDFLAGS		=	-lSDL -lSDL_ttf


%.o: %.cpp
			g++ $(CFLAGS) -o $@ -c $<

OBJ		=	$(SRC:.cpp=.o)

$(NAME)		:	$(OBJ)
			g++ -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
clean		:
			rm -rf $(OBJ)

distclean	:	clean
			rm -rf $(NAME)

rebuild		:	distclean all

all		:	$(NAME)
