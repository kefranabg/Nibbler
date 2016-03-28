//
// main.cpp for main.cpp in /home/abgral_f/dev/nibler/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 17:15:07 2014 abgral_f
// Last update Fri Apr  4 17:54:54 2014 Baptiste Acca
//

#include		<dlfcn.h>
#include		<stdexcept>
#include		<sstream>
#include		"Exceptions.hpp"
#include		"IGraphic.hh"
#include		"Snake.hh"
#include		"Map.hh"
#include		"Game.hh"
#include		"Parser.hh"

static void		launch_snake(IGraphic *lib, int argc, char **argv)
{
  Map			mapgame(atoi(argv[1]), atoi(argv[2]));
  Game			game;
  Snake			snake;
  Parser		parser;

 try
   {
     parser.readFile();
     lib->setWidth(atoi(argv[1]));
     lib->setHeight(atoi(argv[2]));
     lib->init(argc, argv, parser.getSpeed(), parser.getControls(), parser.getView());
     snake.setMapPoint(&mapgame);
     mapgame.setSnakePoint(&snake);
     mapgame.initMap(parser.getObstacles());
     game.setSnakePoint(&snake);
     game.setGraphicPoint(lib);
     game.setMapPoint(&mapgame);
     mapgame.getSnakePoint()->setGamePoint(&game);
     game.launchGame(parser.getSound());
    }
 catch (const mapError& e)
   {
     std::cerr << e.what() << std::endl;
   }
 catch (const std::runtime_error& e)
   {
     std::cerr << e.what() << std::endl;
   }
}

int			getNb(std::string const &nb)
{
  int			ret;
  std::stringstream	ss(nb);

  ss >> ret;
  return ret;
}

int			isNum(std::string const &nb)
{
  unsigned int		i;

  for (i = 0; i < nb.size() ; ++i)
    if (nb[i] < '0' || nb[i] > '9')
      return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
  void			*handle;
  IGraphic*		(*external_creator)();
  IGraphic		*lib;
  int			x;
  int			y;


  if (argc != 4)
    {
      std::cerr << USAGE << std::endl;
      return (EXIT_FAILURE);
    }
  if (isNum(argv[1]) == EXIT_FAILURE || isNum(argv[2]) == EXIT_FAILURE)
    {
      std::cerr << USAGE << std::endl;
      return (EXIT_FAILURE);
    }
  x = getNb(argv[1]);
  y = getNb(argv[2]);
  if ((handle = dlopen(argv[3], RTLD_LAZY)) == NULL)
    {
      std::cerr << ERROR_DLOPEN << dlerror() << std::endl;
      return (EXIT_FAILURE);
    }
  external_creator = reinterpret_cast<IGraphic* (*)()>(dlsym(handle, CREATOR_NAME));
  if (external_creator == NULL)
    {
      std::cerr << ERROR_DLSYM << dlerror() << std::endl;
      return (EXIT_FAILURE);
    }
  if (x < 10 || x > 60)
    {
      std::cerr << WIDTH_MAP_ERROR << std::endl;
      return (EXIT_FAILURE);
    }
  if (y < 4 || y > 35)
    {
      std::cerr << HEIGHT_MAP_ERROR << std::endl;
      return (EXIT_FAILURE);
    }
  lib = external_creator();
  launch_snake(lib, argc, argv);
  dlclose(handle);
  return (EXIT_SUCCESS);
}
