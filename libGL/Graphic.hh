//
// Graphic.hh for  in /home/acca_b/rendu/cpp_nibbler/libGL
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.eu>
//
// Started on  Tue Mar  25 13:58:26 2014 Baptiste Acca
// Last update Thu Apr  3 20:25:55 2014 Baptiste Acca
//

#ifndef GRAPHIC_HH
#define GRAPHIC_HH

#include			<string>
#include			<iostream>
#include			<vector>
#include			<SDL/SDL.h>
#include			<SDL/SDL_ttf.h>
#include			<GL/gl.h>
#include			<GL/glu.h>
#include			<GL/glut.h>
#include			"IGraphic.hh"

/* EXCEPTIONS */

# define SDL_GL_INIT		"Error on SDL_GL_Init\n"
# define SET_VIDEOMODE		"Error on SDL_SetVideoMode\n"

/* DEFINES */

# define MAP_Y			20
# define MAP_X			30
# define SIZE_SQUARE		30
# define NB_SPITES		4
# define BUFF			516

# define POLICE			"./police/FEASFBI_.TTF"
# define SCORE			"Score : %d"
# define BMP_FOOD		"img/Food.bmp"
# define BMP_WALL		"img/Wall.bmp"
# define BMP_SNAKE		"img/Snake.bmp"
# define BMP_EMPTY		"img/Empty.bmp"
# define OBJ_FOOD		"Food"
# define OBJ_WALL		"Wall"
# define OBJ_SUPERFOOD		"SuperFood"
# define OBJ_SNAKE		"Snake"
# define OBJ_EMPTY		"Black"
# define OBJ_SNAKE_HEAD		"Snake Head"
# define GAME_NAME		"Nibbler"

# define NB_SPRITES		4

class			Graphic : public IGraphic
{
public:
  typedef enum		e_direction
  {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
  }			t_direction;
private:
public:
  Graphic();
  virtual ~Graphic();
  virtual void         loadImg(int const, int const, std::string const, int const, int const) const;
  virtual void         event();
  virtual void         setEnd(bool const);
  virtual bool         getEnd() const;
  virtual int          getDirection() const;
  virtual void         putOnScreen(int const);
  virtual void	       init(int, char **, bool, bool, bool);
  virtual void         setWidth(int const);
  virtual void         setHeight(int const);
  virtual void         setScore(int const);
  void		       drawCube(SDL_Color const [], SDL_Rect const &, int const []) const;
  void                 displayScore();
  void		       loadSnakeHead(SDL_Color color[], int y[]) const;
  void		       loadSnake(SDL_Color color[], int y[]) const;
  void		       loadFood(SDL_Color color[], int y[]) const;
  void		       loadWall(SDL_Color color[], int y[]) const;
  void		       loadSuperfood(SDL_Color color[], int y[]) const;
  void		       loadEmpty(SDL_Color color[], int y[]) const;
private:
  int		       sdlkDirection;
  bool		       end;
  SDL_Surface	       *window;
  int		       width;
  int		       height;
  bool		       controls;
  bool		       speed;
  bool		       view;
  unsigned int	       score;
  TTF_Font             *police;
  void (Graphic::*loaders[6])(SDL_Color color[], int y[]) const;
  std::string	      loadersName[6];
};

#endif // GRAPHIC_HH
