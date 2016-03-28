//
// Map.cpp for Map.cpp in /home/abgral_f/dev/nibler/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 19:45:45 2014 abgral_f
// Last update Mon Mar 31 18:23:11 2014 abgral_f
//

#include			<cstdio>
#include			<cstdlib>
#include			<ctime>
#include			"Exceptions.hpp"
#include			"Map.hh"
#include			"Snake.hh"

Map::Map(int const width, int const height)
{
  std::vector<square> tmp;

  this->width = width;
  this->height = height;
  this->superFoodPop = 0;
  for (int j = 0; j < width; j++)
    tmp.push_back(Map::WALL);
  for (int i = 0; i < height ; i++)
    this->MapSnake.push_back(tmp);
}

Map::~Map()
{

}

Map::Map(Map const &cpy)
{
  this->MapSnake = cpy.MapSnake;
  this->SnakePoint = cpy.SnakePoint;
}

Map                           &Map::operator=(Map const &cpy)
{
  this->MapSnake = cpy.MapSnake;
  this->SnakePoint = cpy.SnakePoint;
  return (*this);
}

void                          Map::setMap(int const x, int const y, square const square)
{
  if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    throw mapError(INVALID_COORD);
  this->MapSnake[y][x] = square;
}

void                          Map::addFood(square const type)
{
  int			      rand_x;
  int			      rand_y;
  bool			      pop = false;

  if (type == SUPERFOOD)
    this->superFoodPop = time(NULL);
  while (pop == false && this->isMapFull() == false)
    {
      rand_x = rand() % this->width;
      rand_y = rand() % this->height;
      if (this->MapSnake[rand_y][rand_x] == EMPTY
	  && rand_x > 0 && rand_y > 0
	  && rand_x < this->width - 2 && rand_y < this->height - 2)
	{
	  pop = true;
	  setMap(rand_x, rand_y, type);
	}
    }
}

void                          Map::printSnakeOnMap()
{
  std::vector<Snake::t_coord>::iterator it;

  for(it = this->SnakePoint->getBody().begin();
      it != this->SnakePoint->getBody().end() - 1; it++)
    this->MapSnake[it->y][it->x] = SNAKE;
  this->MapSnake[it->y][it->x] = SNAKE_HEAD;
}

bool                          Map::isType(int const x, int const y, square const type) const
{
  if (this->MapSnake[y][x] != type)
    return (false);
  return (true);
}

Map::square                        Map::getSquare(int const y, int const x) const
{
  return (this->MapSnake[y][x]);
}

Snake	                       *Map::getSnakePoint() const
{
  return (this->SnakePoint);
}

void					Map::setSnakePoint(Snake *point)
{
  this->SnakePoint = point;
}

int                           Map::getWidth() const
{
  return (this->width);
}

int                           Map::getHeight() const
{
  return (this->height);
}

int                           Map::getSuperFoodPop() const
{
  return (this->superFoodPop);
}

void                          Map::depopSuperFood()
{
  for (int y = 0 ; y != height ; y++)
    for (int x = 0 ; x != width ; x++)
      if (MapSnake[y][x] == SUPERFOOD)
	MapSnake[y][x] = EMPTY;
}

bool				Map::isMapFull() const
{
  for(int y = 0 ; y != this->height ; y++)
    {
      for(int x = 0 ; x != this->width ; x++)
        {
	  if (this->MapSnake[y][x] == EMPTY)
	    return (false);
	}
    }
  return (true);
}

void                          Map::initMap(bool const obstacles)
{
  int                         count = 0;
  int                         rand_x;
  int                         rand_y;

  this->obstacles = obstacles;
  for(int y = 0 ; y != this->height ; y++)
    {
      for(int x = 0 ; x != this->width ; x++)
        {
          if (y == 0 || y == (this->height - 1) || x == 0 || x == this->width -1)
            this->MapSnake[y][x] = WALL;
          else
            this->MapSnake[y][x] = EMPTY;
	}
    }
  this->printSnakeOnMap();
  this->addFood(FOOD);
  if (this->obstacles == true)
    {
      while (count != NB_WALL)
	{
	  rand_x = rand() % this->width;
	  rand_y = rand() % this->height;
	  if (this->MapSnake[rand_y][rand_x] == EMPTY && rand_x > 0 && rand_y > 0)
	    {
	      setMap(rand_x, rand_y, WALL);
	      count++;
	    }
	}
    }
}
