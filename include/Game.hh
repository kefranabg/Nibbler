//
// Game.hh for Game.hh in /home/abgral_f/dev/nibler3/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 19:17:38 2014 abgral_f
// Last update Thu Apr  3 16:40:31 2014 abgral_f
//

#ifndef                         GAME_HH
# define                        GAME_HH

#include                        <string>
#include                        <iostream>
#include			<sstream>
#include			<fstream>
#include			<SDL/SDL.h>
#include			<SDL/SDL_mixer.h>
#include			"IGraphic.hh"
#include			"Map.hh"
#include			"Snake.hh"

/* ERRORS */

# define ERROR_DLSYM		"Error on dlsym: "
# define ERROR_DLOPEN		"Error on dlopen: "
# define USAGE			"Usage: ./nibbler map_width map_height ./libXXX.so"
# define WIDTH_MAP_ERROR	"Nibbler : Width must be included between 10 and 60"
# define HEIGHT_MAP_ERROR	"Nibbler : Height must be included between 10 and 35"
# define CANT_WRITE_HIGHSCORE	"Error: can't write highscore to file"

/* DEFINES */

# define CREATOR_NAME		"create_graphic"
# define S_FOOD                 "Food"
# define S_WALL		        "Wall"
# define S_SNAKE                "Snake"
# define S_SNAKE_HEAD           "Snake Head"
# define S_EMPTY         	"Black"
# define S_SUPERFOOD         	"SuperFood"

# define ENTER_NAME		"Enter your name : "

# define NB_OBJECTS		6

# define SDL_AUDIO_FREQ		44100

# define AUDIO_THEME		"sound/theme.wav"

# define HIGHSCORE_FILE		"Highscore.txt"
# define HIGHSCORE_HEADER	4
# define HIGHSCORE_MAX_LINE	5

class				Snake;

class				Game
{
public:

  typedef struct                s_object
  {
    std::string                 name;
    Map::square	                type;
  }                             t_object;

public:
  Game();
  ~Game();
  Game(const Game &);
  Game                          &operator=(const Game &);
  void                          setLoose(bool const);
  bool                          getLoose() const;
  int                           getScore() const;
  void                          setScore(int const);
  void				launchGame(bool const);
  void				setGraphicPoint(IGraphic *);
  void				setMapPoint(Map *);
  void				setSnakePoint(Snake *);
  Snake				*getSnakePoint() const;
  IGraphic                      *getGraphicPoint() const;
  void                          initObjects();
  void				initAudio();
  void				writeScore() const;
  unsigned int			toNum(std::string const &) const;
  std::string			toString(unsigned int const &) const;
  std::string			epurString(std::string &) const;
  void				readScoreFile(std::vector<std::string> &, unsigned int &, std::string &) const;
  void				writeScoreFile(std::vector<std::string> const &, std::vector<std::string> const &) const;
  void				sortScoreFile(std::vector<std::string> &, std::vector<std::string> &) const;

private:
  Snake				*SnakePoint;
  unsigned int			score;
  bool				loose;
  bool				sound;
  IGraphic			*GraphicPoint;
  Map				*MapPoint;
  std::vector<t_object>		types;
  Mix_Music			*music;
};

#endif
