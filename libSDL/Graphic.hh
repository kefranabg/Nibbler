//
// Graphic.hh for Graphic.hh in /home/abgral_f/dev/nibler/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 11:11:03 2014 abgral_f
// Last update Thu Apr  3 20:09:13 2014 Baptiste Acca
//

#ifndef                         GRAPHIC_HH
# define                        GRAPHIC_HH

#include                        <string>
#include                        <iostream>
#include			<vector>
#include			<SDL/SDL.h>
#include			<SDL/SDL_ttf.h>
#include			"IGraphic.hh"

/* EXCEPTIONS */

# define SDL_INIT		"Error on SDL_Init\n"
# define SET_VIDEOMODE		"Error on SDL_SetVideoMode\n"
# define LOADBMP		"Error on SDL_LoadBMP\n"

/* DEFINES */

# define SIZE_SQUARE		30
# define NB_SPRITES		6
# define BUFF			516

# define POLICE			"./police/FEASFBI_.TTF"
# define SCORE			"Score : %d"
# define BMP_FOOD               "img/Food.bmp"
# define BMP_WALL               "img/Wall.bmp"
# define BMP_SNAKE              "img/Snake.bmp"
# define BMP_EMPTY              "img/Empty.bmp"
# define BMP_SUPERFOOD          "img/SuperFood.bmp"
# define BMP_HEAD	        "img/Head.bmp"
# define OBJ_FOOD		"Food"
# define OBJ_WALL		"Wall"
# define OBJ_SNAKE		"Snake"
# define OBJ_EMPTY		"Black"
# define OBJ_SUPERFOOD		"SuperFood"
# define OBJ_HEAD		"Snake Head"
# define GAME_NAME		"Nibbler"

class				Graphic : public IGraphic
{
public:
  Graphic();
  virtual ~Graphic();
  virtual void			loadImg(int const, int const,  std::string const) const;
  virtual void			event();
  virtual void			setEnd(bool const);
  virtual bool			getEnd() const;
  virtual int			getDirection() const;
  virtual void			putOnScreen(int const);
  virtual void			init(int, char **, bool, bool);
  virtual void			setWidth(int const);
  virtual void			setHeight(int const);
  virtual void			setScore(int const);
  void				initSprites();
  void                          displayScore();
public:
  typedef enum
  {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
  }             e_direction;

private:
  typedef struct		s_sprites
  {
    SDL_Surface                 *img;
    std::string			name;
  }				t_sprites;
private:
  t_sprites			sprites[NB_SPRITES];
  int				sdlkDirection;
  bool				end;
  SDL_Surface			*window;
  int				width;
  int				height;
  unsigned int			score;
  bool				speed;
  bool				controls;
  TTF_Font                      *police;
};

#endif
