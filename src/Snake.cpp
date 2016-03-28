//
// Snake.cpp for Snake.cpp in /home/abgral_f/dev/nibler/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 20:52:48 2014 abgral_f
// Last update Thu Apr  3 20:51:35 2014 Baptiste Acca
//

#include			"Exceptions.hpp"
#include			"Snake.hh"

Snake::Snake()
{
  for (int count = 0 ; count != SNAKE_SIZE_BEGIN ; count++)
    this->addBody(POS_Y_BEGIN, POS_X_BEGIN + count);
  this->Direction = RIGHT;
  this->loose = false;
}

Snake::Snake(Map *point)
{
  for (int count = 0 ; count != SNAKE_SIZE_BEGIN ; count++)
    this->addBody(POS_Y_BEGIN, POS_X_BEGIN + count);
  this->Direction = RIGHT;
  this->MapPoint = point;
  this->loose = false;
}

Snake::~Snake()
{
  Mix_FreeChunk(this->eatMusic);
}

Snake::Snake(Snake const &cpy)
{
  this->Direction = cpy.Direction;
  this->Body = cpy.Body;
  this->MapPoint = cpy.MapPoint;
  this->loose = cpy.loose;
}

Snake					&Snake::operator=(Snake const &cpy)
{
  this->Direction = cpy.Direction;
  this->Body = cpy.Body;
  this->MapPoint = cpy.MapPoint;
  this->loose = cpy.loose;
  return (*this);
}

std::vector<Snake::t_coord>		&Snake::getBody()
{
  return (this->Body);
}

const Snake::direction			&Snake::getDirection() const
{
  return (this->Direction);
}

void					Snake::setGamePoint(Game *point)
{
  this->GamePoint = point;
}

void					Snake::setMapPoint(Map *point)
{
  this->MapPoint = point;
}

void					Snake::setDirection(direction const _Direction)
{
  this->Direction = _Direction;
}

void					Snake::addBody(int const y, int const x)
{
  t_coord				tmp;

  tmp.x = x;
  tmp.y = y;
  this->Body.push_back(tmp);
}

void					Snake::eat(t_coord &coord, bool const music)
{
  if (this->MapPoint->isType(coord.x, coord.y, Map::FOOD) == true)
    {
      this->MapPoint->addFood(Map::FOOD);
      this->GamePoint->setScore(this->GamePoint->getScore() + 50);
    }
  else
    this->GamePoint->setScore(this->GamePoint->getScore() + 100);
  this->GamePoint->getGraphicPoint()->setScore(this->GamePoint->getScore());
  this->Body.push_back(coord);
  if (music == true)
    Mix_PlayChannel(-1, this->eatMusic, 0);
}

void					Snake::move(bool const music)
{
  t_coord				tmp;
  std::vector<t_coord>::iterator	it = this->Body.begin();

  this->MapPoint->setMap(it->x, it->y, Map::EMPTY);
  while (it != this->Body.end())
    it++;
  it--;
  tmp.x = it->x;
  tmp.y = it->y;
  if (this->Direction == RIGHT)
    tmp.x++;
  if (this->Direction == LEFT)
    tmp.x--;
  if (this->Direction == UP)
    tmp.y--;
  if (this->Direction == DOWN)
    tmp.y++;
  if (this->MapPoint->isType(tmp.x, tmp.y, Map::FOOD) == true
      || this->MapPoint->isType(tmp.x, tmp.y, Map::SUPERFOOD) == true)
    this->eat(tmp, music);
  else
    {
      if (this->MapPoint->isType(tmp.x, tmp.y, Map::EMPTY) == false)
	this->GamePoint->setLoose(true);
      else
	{
	  this->Body.erase(this->Body.begin());
	  this->Body.push_back(tmp);
	}
    }
  this->MapPoint->printSnakeOnMap();
}

Snake::t_coord		Snake::getHead()
{
  t_coord	ret;
  std::vector<t_coord>::iterator it = this->Body.begin();

  while (it != this->Body.end())
    it++;
  it--;
  ret.x = it->x;
  ret.y = it->y;
  return ret;
}

void			Snake::loadAudio()
{
  this->eatMusic = Mix_LoadWAV(AUDIO_EAT);
  if (this->eatMusic == NULL)
    throw std::runtime_error(SDL_GetError());
}
