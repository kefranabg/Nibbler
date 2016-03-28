//
// Game.cpp for Game.cpp in /home/abgral_f/dev/nibler3/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 20:39:46 2014 abgral_f
// Last update Thu Apr  3 20:51:08 2014 Baptiste Acca
//

#include			<cstdio>
#include			<cstdlib>
#include			<ctime>
#include			"Exceptions.hpp"
#include                        "Game.hh"

Game::Game()
{
  this->loose = false;
  this->score = 0;
  this->initObjects();
}

Game::~Game()
{
  Mix_FreeMusic(this->music);
  SDL_Quit();
}

Game::Game(const Game &cpy)
{
  this->loose = cpy.loose;
  this->score = cpy.score;
}

Game                          &Game::operator=(const Game &cpy)
{
  this->loose = cpy.loose;
  this->score = cpy.score;
  return (*this);
}

void                          Game::setLoose(bool const status)
{
  this->loose = status;
}

bool                          Game::getLoose() const
{
  return (this->loose);
}

int                          Game::getScore() const
{
  return (this->score);
}

void                          Game::setScore(int const newScore)
{
  this->score = newScore;
}

void                          Game::setGraphicPoint(IGraphic *point)
{
  this->GraphicPoint = point;
}

void                          Game::setMapPoint(Map *point)
{
  this->MapPoint = point;
}

void                          Game::setSnakePoint(Snake *point)
{
  this->SnakePoint = point;
}

Snake                          *Game::getSnakePoint() const
{
  return (this->SnakePoint);
}

IGraphic                      *Game::getGraphicPoint() const
{
  return (this->GraphicPoint);
}

void                          Game::initObjects()
{
  Game::t_object                   tmp;

  tmp.name = S_FOOD;
  tmp.type = Map::FOOD;
  this->types.push_back(tmp);
  tmp.name = S_WALL;
  tmp.type = Map::WALL;
  this->types.push_back(tmp);
  tmp.name = S_SNAKE;
  tmp.type = Map::SNAKE;
  this->types.push_back(tmp);
  tmp.name = S_SNAKE_HEAD;
  tmp.type = Map::SNAKE_HEAD;
  this->types.push_back(tmp);
  tmp.name = S_EMPTY;
  tmp.type = Map::EMPTY;
  this->types.push_back(tmp);
  tmp.name = S_SUPERFOOD;
  tmp.type = Map::SUPERFOOD;
  this->types.push_back(tmp);
}

void				Game::initAudio()
{
  if (SDL_Init(SDL_INIT_AUDIO) == -1)
    throw std::runtime_error(SDL_GetError());
  if (Mix_OpenAudio(SDL_AUDIO_FREQ, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    throw std::runtime_error(SDL_GetError());
  this->getSnakePoint()->loadAudio();
  this->music = Mix_LoadMUS(AUDIO_THEME);
  if (this->music == NULL)
    throw std::runtime_error(SDL_GetError());
}

std::string			Game::epurString(std::string &s) const
{
  size_t occur;

  while ((occur = s.find("  ", 0)) && occur != std::string::npos)
    s.replace(occur, 2, " ");
  return s;
}

unsigned int			Game::toNum(std::string const &s) const
{
  std::istringstream		ss(s);
  unsigned int			ret;

  ss >> ret;
  return ret;
}

std::string			Game::toString(unsigned int const &nb) const
{
  std::ostringstream		ss;

  ss << nb;
  return ss.str();
}

void				Game::readScoreFile(std::vector<std::string> &fileContent,
						    unsigned int &nbScore, std::string &goodStr) const
{
  std::ifstream			rdStream;
  int				tmp;
  size_t			occur;
  std::string			s;

  rdStream.open(HIGHSCORE_FILE, std::ifstream::in);
  if (rdStream.fail() == true)
    return;
  nbScore = 10;
  tmp = 0;
  while (std::getline(rdStream, s, '\n') && tmp < 3)
    {
      tmp++;
      fileContent.push_back(s);
    }
  tmp++;
  fileContent.push_back(s);
  while (std::getline(rdStream, s, '\n'))
    {
      if (s.empty() == false)
	{
	  occur = s.find("~ ", 0);
	  if (occur != std::string::npos && this->toNum(s.substr(occur)) < this->score)
	    {
	      goodStr.assign(s);
	      nbScore = tmp;
	    }
	}
      tmp++;
      fileContent.push_back(s);
    }
  rdStream.close();
}

void				Game::writeScoreFile(std::vector<std::string> const &fileContent,
						     std::vector<std::string> const &toWrite) const
{
  unsigned int i;
  std::ofstream		stream(HIGHSCORE_FILE, std::ios::out);

  if (stream.fail() == true)
    return;
  for (i = 0; i < HIGHSCORE_HEADER ; i++)
    {
      stream.write(fileContent[i].c_str(), fileContent[i].size());
      stream.write("\n", 1);
    }
  for (i = 0; i < HIGHSCORE_MAX_LINE ; i++)
    {
      if (toWrite.empty() == false)
	{
	  stream.write(this->toString(i + 1).c_str(), 1);
	  stream.write(toWrite[i].c_str() + 1, toWrite[i].size() - 1);
	}
      if (i != 5)
	stream.write("\n", 1);
    }
  stream.close();
}

void				Game::sortScoreFile(std::vector<std::string> &fileContent,
						    std::vector<std::string> &toWrite) const
{
  std::string			max;
  unsigned int			nb;
  unsigned int			j;
  int				tmp;

  while (toWrite.size() != HIGHSCORE_MAX_LINE)
    {
      nb = 0;
      j = 4;
      max = "";
      while (j < fileContent.size())
	{
	  if (fileContent[j].empty() == false && fileContent[j] != "used" &&
	      this->toNum(fileContent[j].substr(fileContent[j].find("~ ") + 2)) >= nb)
	    {
	      nb = this->toNum(fileContent[j].substr(fileContent[j].find("~ ") + 2));
	      max.assign(fileContent[j]);
	      tmp = j;
	    }
	  j++;
	}
      fileContent[tmp].assign("used");
      toWrite.push_back(max);
    }
}

void				Game::writeScore() const
{
  std::string			nameScore;
  unsigned int			scoreFile;
  std::ostringstream		finalLine;
  unsigned int			nbScore;
  std::vector<std::string>	fileContent;
  std::string			goodStr;
  std::vector<std::string>	toWrite;
  size_t			occur;

  this->readScoreFile(fileContent, nbScore, goodStr);
  if (goodStr.empty() == true)
    return;
  occur = goodStr.find("~ ", 0);
  if (occur == std::string::npos)
    return;
  if (goodStr.substr(occur).empty() == true)
    return;
  scoreFile = this->toNum(goodStr.substr(occur));
  if (this->score > scoreFile)
    {
      std::cout << ENTER_NAME;
      std::cin >> nameScore;
      occur = goodStr.find(" -", 0);
      if (occur == std::string::npos)
	return;
      nbScore = this->toNum(goodStr.substr(0, occur));
      finalLine << "  - " << nameScore << " ~ " << this->toString(this->score);
      std::vector<std::string>::iterator it = fileContent.begin() + 3 + nbScore;
      fileContent.insert(it, finalLine.str());
      this->sortScoreFile(fileContent, toWrite);
      this->writeScoreFile(fileContent, toWrite);
    }
}

void				Game::launchGame(bool const sound)
{
  int				sec = 1;
  Snake::t_coord		headCoord;

  this->sound = sound;
  if (this->sound == true)
    {
      this->initAudio();
      Mix_PlayMusic(this->music, -1);
    }
  srand(clock());
  while (this->GraphicPoint->getEnd() == false && this->loose == false)
    {
      if (sec % 100 == 0)
	{
	  this->MapPoint->addFood(Map::SUPERFOOD);
	  sec = 1;
	}
      if ((time(NULL) - this->MapPoint->getSuperFoodPop()) > 5)
	this->MapPoint->depopSuperFood();
      this->GraphicPoint->event();
      this->getSnakePoint()->setDirection(static_cast<Snake::direction>(this->GraphicPoint->getDirection()));
      this->getSnakePoint()->move(sound);
      headCoord = this->getSnakePoint()->getHead();
      for (int y = 0 ; y != this->MapPoint->getHeight() ; y++)
	for (int x = 0 ; x != this->MapPoint->getWidth() ; x++)
	  for (int count = 0 ; count != NB_OBJECTS ; count++)
	    if (this->MapPoint->getSquare(y, x) == this->types[count].type)
	      this->GraphicPoint->loadImg(y, x, this->types[count].name, headCoord.x, headCoord.y);
      this->GraphicPoint->putOnScreen(this->getScore());
      sec++;
    }
  delete this->GraphicPoint;
  if (this->loose == true)
    this->writeScore();
}
