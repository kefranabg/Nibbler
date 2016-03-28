//
// Graphic.hh for Graphic.hh in /home/abgral_f/dev/nibler/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 11:11:03 2014 abgral_f
// Last update Thu Apr  3 20:09:38 2014 Baptiste Acca
//

#ifndef                         GRAPHIC_HH
# define                        GRAPHIC_HH

#include                        <string>
#include			<unistd.h>
#include			<stdio.h>
#include			<stdlib.h>
#include                        <iostream>
#include			<vector>
#include			<gtk/gtk.h>
#include			<gdk/gdkkeysyms.h>
#include			"IGraphic.hh"

/* DEFINES */

# define SIZE_SQUARE		30
# define NB_OBJ			6
# define SPEED			150

# define COLOR_SNAKE            0x006707
# define COLOR_FOOD             0x8C0000
# define COLOR_EMPTY            0x000000
# define COLOR_WALL             0xCC9933
# define COLOR_SUPERFOOD        0xFFFF00
# define COLOR_HEAD	        0x123456
# define OBJ_FOOD		"Food"
# define OBJ_WALL		"Wall"
# define OBJ_SNAKE		"Snake"
# define OBJ_EMPTY		"Black"
# define OBJ_SUPERFOOD		"SuperFood"
# define OBJ_HEAD		"Snake Head"
# define GAME_NAME		"Nibbler"

# define EXPOSE			"expose-event"
# define KEY_PRESS		"key_press_event"
# define DELETE			"delete-event"

class				Graphic : public IGraphic
{
public:
  typedef enum
  {
   UP = 0,
   RIGHT = 1,
   DOWN = 2,
   LEFT = 3
  }             e_direction;

private:
  typedef struct		s_color
  {
    int				color;
    std::string			name;
  }				t_color;
public:
  Graphic();
  virtual ~Graphic();
  virtual void                  loadImg(int, int, std::string const);
  virtual void                  event();
  virtual void                  setEnd(bool const);
  virtual bool                  getEnd() const;
  virtual int                   getDirection() const;
  virtual void                  putOnScreen(int const);
  virtual void                  init(int, char **, bool, bool);
  virtual void                  setWidth(int const);
  virtual void                  setHeight(int const);
  virtual void                  setScore(int const);
  void				setDirection(e_direction const);
  void                          printColor(int, int, int const);
  void				initColor();
  int				getWidth() const;
  int				getHeight() const;
  guchar			*getData() const;
  void				displayScore(unsigned int const);
  bool				getControls() const;
private:
  std::vector<t_color>		color;
  int				gtkDirection;
  bool				end;
  GtkWidget			*window;
  GtkWidget			*darea;
  int				width;
  int				height;
  guchar			*data;
  bool				controls;
  bool				speed;
  unsigned int			score;
};

void				on_key_press(GtkWidget *, GdkEventKey *, gpointer);
gboolean                        on_darea_expose(GtkWidget *, GdkEventKey *, gpointer);
gboolean                        timeout(gpointer);
void                            quit_gtk(GtkWidget *, GdkEventKey *, gpointer);

#endif
