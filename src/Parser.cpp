//
// Parser.cpp<2> for Parser.cpp<2> in /home/acca_b/rendu/cpp_nibbler
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.net>
//
// Started on  Mon Mar 31 13:42:33 2014 Baptiste Acca
// Last update Thu Apr  3 20:41:13 2014 Baptiste Acca
//

#include "Parser.hh"

Parser::Parser()
{
  this->controls = true;
  this->speed = true;
  this->sound = true;
  this->view = true;
  this->obstacles = true;
  this->optionsName[0] = SPEED_OPT;
  this->optionsLen[0] = SPEED_OPT_SIZE;
  this->optionsParser[0] = &Parser::getSpeedOpt;
  this->optionsName[1] = CONTROL_OPT;
  this->optionsLen[1] = CONTROL_OPT_SIZE;
  this->optionsParser[1] = &Parser::getControlsOpt;
  this->optionsName[2] = VIEW_OPT;
  this->optionsLen[2] = VIEW_OPT_SIZE;
  this->optionsParser[2] = &Parser::getViewOpt;
  this->optionsName[3] = SOUND_OPT;
  this->optionsLen[3] = SOUND_OPT_SIZE;
  this->optionsParser[3] = &Parser::getSoundOpt;
  this->optionsName[4] = OBSTACLES_OPT;
  this->optionsLen[4] = OBSTACLES_OPT_SIZE;
  this->optionsParser[4] = &Parser::getObstaclesOpt;
}

Parser::~Parser()
{

}

std::string Parser::epurString(std::string &s) const
{
  size_t occur;

  while ((occur = s.find(DOUBLE_SPACE, 0)) && occur != std::string::npos)
    s.replace(occur, 2, SIMPLE_SPACE);
  if ((occur = s.find(COMMENT_CHAR)) != std::string::npos)
    s = s.substr(0, occur);
  return s;
}

void	Parser::getSpeedOpt(std::string const &s)
{
  size_t start;

  start = s.find(DELIMITER_CHAR);
  start++;
  if (s.compare(start, SPEED_ACT_SIZE, SPEED_ACT) == 0)
    this->speed = true;
  else if (s.compare(start, SPEED_DACT_SIZE, SPEED_DACT) == 0)
    this->speed = false;
}

void	Parser::getControlsOpt(std::string const &s)
{
  size_t start;

  start = s.find(DELIMITER_CHAR);
  start++;
  if (s.compare(start, CLAS_CONTROL_SIZE, CLAS_CONTROL) == 0)
    this->controls = true;
  else if (s.compare(start, EPI_CONTROL_SIZE, EPI_CONTROL) == 0)
    this->controls = false;
}

void	Parser::getViewOpt(std::string const &s)
{
  size_t start;

  start = s.find(DELIMITER_CHAR);
  start++;
  if (s.compare(start, UP_VIEW_SIZE, UP_VIEW) == 0)
    this->view = false;
  else if (s.compare(start, TPS_VIEW_SIZE, TPS_VIEW) == 0)
    this->view = true;
}

void	Parser::getSoundOpt(std::string const &s)
{
  size_t start;

  start = s.find(DELIMITER_CHAR);
  start++;
  if (s.compare(start, SOUND_ON_SIZE, SOUND_ON) == 0)
    this->sound = true;
  else if (s.compare(start, SOUND_OFF_SIZE, SOUND_OFF) == 0)
    this->sound = false;
}

void	Parser::getObstaclesOpt(std::string const &s)
{
  size_t start;

  start = s.find(DELIMITER_CHAR);
  start++;
  if (s.compare(start, OBSTACLES_ON_SIZE, OBSTACLES_ON) == 0)
    this->obstacles = true;
  else if (s.compare(start, OBSTACLES_OFF_SIZE, OBSTACLES_OFF) == 0)
    this->obstacles = false;
}

void	Parser::getOption(std::string const &s)
{
  unsigned int i;

  for (i = 0; i < 5 && s.compare(0, this->optionsLen[i], this->optionsName[i]) != 0; ++i);
  if (i != 5 && s.compare(0, this->optionsLen[i], this->optionsName[i]) == 0)
    (this->*optionsParser[i])(s);
}

void Parser::readFile()
{
  std::ifstream stream;
  std::string s;

  stream.open(CONF_FILE, std::ifstream::in);
  if (stream.fail() == true)
    return;
  while (std::getline(stream, s, '\n'))
    {
      s = this->epurString(s);
      if (s.empty() == false)
	this->getOption(s);
    }
}

bool Parser::getSpeed() const
{
  return this->speed;
}

bool Parser::getControls() const
{
  return this->controls;
}

bool Parser::getView() const
{
  return this->view;
}

bool Parser::getSound() const
{
  return this->sound;
}

bool Parser::getObstacles() const
{
  return this->obstacles;
}
