//
// snake.hh for snake.hh in /home/abgral_f/dev/nibler/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 17:53:12 2014 abgral_f
// Last update Thu Apr  3 16:44:36 2014 abgral_f
//

#ifndef                         SNAKE_HH
# define                        SNAKE_HH

#include                        <string>
#include                        <iostream>
#include			<vector>
#include			"Map.hh"
#include			"Game.hh"

/* DEFINES */

# define SNAKE_SIZE_BEGIN	4
# define POS_X_BEGIN		2
# define POS_Y_BEGIN		2

# define AUDIO_EAT		"sound/eat.wav"

class				Map;
class				Game;

class                           Snake
{
public:
  typedef enum
    {
      UP = 0,
      RIGHT = 1,
      DOWN = 2,
      LEFT = 3
   }	direction;
public:
  typedef struct		s_coord
  {
    int				x;
    int				y;
  }				t_coord;
public:
  Snake();
  Snake(Map *);
  ~Snake();
  Snake(Snake const &);
  Snake				&operator=(Snake const &);
  void				setDirection(direction const);
  const direction		&getDirection() const;
  std::vector<t_coord>		&getBody();
  void				addBody(int const, int const);
  void				move(bool const);
  void                          eat(t_coord &, bool const);
  void				setGamePoint(Game *);
  void				setMapPoint(Map *);
  t_coord			getHead();
  void				loadAudio();
private:
  direction			Direction;
  std::vector<t_coord>		Body;
  Map				*MapPoint;
  bool				loose;
  Game				*GamePoint;
  Mix_Chunk			*eatMusic;
};

#endif
