##
## Makefile for Makefile in /home/abgral_f/dev/avm
## 
## Made by abgral_f
## Login   <abgral_f@epitech.net>
## 
## Started on  Wed Feb 12 14:31:08 2014 abgral_f
## Last update Sun Apr  6 19:55:20 2014 Baptiste Acca
##

RM		= rm -f

CC		= g++

PATH1		= include/

PATH2		= src/

NAME_LIB_SDL	= lib_nibbler_sdl.so
SRC_LIB_SDL	= libSDL/Graphic.cpp

NAME_LIB_GL	= lib_nibbler_opengl.so
SRC_LIB_GL	= libGL/Graphic.cpp

NAME_LIB_GTK	= lib_nibbler_gtk.so
SRC_LIB_GTK	= libGTK/Graphic.cpp

NAME		= nibbler

SRC	 	= $(PATH2)main.cpp				\
	  	  $(PATH2)Map.cpp				\
	  	  $(PATH2)Snake.cpp				\
	  	  $(PATH2)Parser.cpp				\
	  	  $(PATH2)Game.cpp				\

OBJ		= $(SRC:.cpp=.o)

CPPFLAGS	= -W -Wall -Werror -Wextra -I $(PATH1)
CPPFLAGS	+= -fPIC
LDFLAGS		= -ldl

all: $(NAME)
	tar -xsvf Misc.tar.gz
	tar -xsvf Img.tar.gz
	tar -xsvf Font.tar.gz
	tar -xsvf Sound.tar.gz

$(NAME): $(OBJ)
	$(CC) -rdynamic $(LDFLAGS) -o $(NAME) $(OBJ) -lSDL -lSDL_mixer
	$(CC) -shared $(CPPFLAGS) $(SRC_LIB_SDL) -o $(NAME_LIB_SDL) -lSDLmain -lSDL -lSDL_ttf 
	$(CC) -shared $(CPPFLAGS) $(SRC_LIB_GL) -o $(NAME_LIB_GL) -lSDL -lGL -lGLU -lSDL_ttf -lglut
	$(CC) -shared $(CPPFLAGS) `pkg-config --cflags --libs gtk+-2.0` $(SRC_LIB_GTK) -o $(NAME_LIB_GTK)

clean:
	$(RM) $(OBJ)
	$(RM) -r Img.tar.gz
	$(RM) -r Font.tar.gz
	$(RM) -r Sound.tar.gz

fclean: clean
	$(RM) $(NAME) $(NAME_LIB_SDL) $(NAME_LIB_GL) $(NAME_LIB_GTK)
	$(RM) -r img/
	$(RM) -r police/
	$(RM) -r sound/

re: fclean all
