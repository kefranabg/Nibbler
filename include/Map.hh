//
// map.hh for map.hh in /home/abgral_f/dev/nibler/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 17:51:05 2014 abgral_f
// Last update Mon Mar 31 18:23:22 2014 abgral_f
//

#ifndef				MAP_HH
# define			MAP_HH

#include			<string>
#include			<iostream>
#include			<vector>

/* ERRORS */

# define INVALID_COORD		"[SNAKE] : Try to set invalid coordonates on the map\n"

/* DEFINES */

# define NB_WALL		5

/* CLASSES */

class				Snake;

class				Map
{

public:

  typedef       enum
    {
      WALL,
      FOOD,
      SUPERFOOD,
      SNAKE,
      SNAKE_HEAD,
      EMPTY
    }           square;

public:

  Map(int const, int const);
  ~Map();
  Map(Map const &);
  Map				&operator=(Map const &);
  void			        setMap(int const, int const, square const);
  void				addFood(square const);
  void				printSnakeOnMap();
  void				initMap(bool const);
  bool                          isType(int const, int const, square const) const;
  square			getSquare(int const, int const) const;
  Snake				*getSnakePoint() const;
  void				setSnakePoint(Snake *);
  int				getWidth() const;
  int				getHeight() const;
  int				getSuperFoodPop() const;
  void				depopSuperFood();
  bool                          isMapFull() const;
private:
  Snake					*SnakePoint;
  std::vector<std::vector<square> >	MapSnake;
  int					width;
  int					height;
  int					superFoodPop;
  bool					obstacles;
};

#endif
