//
// Graphic.cpp for Graphic.cpp in /home/abgral_f/dev/nibler/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 11:14:37 2014 abgral_f
// Last update Fri Apr  4 14:30:33 2014 abgral_f
//

#include			<stdexcept>
#include			"Graphic.hh"

Graphic::Graphic()
{
  this->end = false;
  this->sdlkDirection = Graphic::RIGHT;
  this->score = 0;
}

Graphic::~Graphic()
{
  for (int count = 0 ; count != NB_SPRITES ; count++)
    SDL_FreeSurface(this->sprites[count].img);
  SDL_Quit();
  TTF_Quit();
}

void                          Graphic::event()
{
  SDL_Event                   event;

  if (SDL_PollEvent(&event))
  {
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_UP && this->sdlkDirection != Graphic::DOWN)
        this->sdlkDirection = Graphic::UP;
      if (event.key.keysym.sym == SDLK_DOWN && this->sdlkDirection != Graphic::UP)
        this->sdlkDirection = Graphic::DOWN;
	  if (event.key.keysym.sym == SDLK_RIGHT)
	    {
	      if (this->controls == false)
		this->sdlkDirection = (this->sdlkDirection + 1) % 4;
	      else if (this->sdlkDirection != Graphic::LEFT)
		this->sdlkDirection = Graphic::RIGHT;
	    }
	  if (event.key.keysym.sym == SDLK_LEFT)
	    {
	      if (this->controls == false)
		this->sdlkDirection = this->sdlkDirection - 1;
	      else if (this->sdlkDirection != Graphic::RIGHT)
		this->sdlkDirection = Graphic::LEFT;
	    }
	  if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
	    this->end = true;
    }
    if (this->sdlkDirection == -1)
      this->sdlkDirection = Graphic::LEFT;
  }
}

void                          Graphic::init(int __attribute__((unused))argc,
					    char __attribute__((unused))**argv,
					    bool speed, bool controls)
{
  this->speed = speed;
  this->controls = controls;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error(SDL_GetError());
  if (TTF_Init() == -1)
    throw std::runtime_error(SDL_GetError());
  if ((this->window = SDL_SetVideoMode(this->width * SIZE_SQUARE, this->height * SIZE_SQUARE,
				       32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::runtime_error(SDL_GetError());
  SDL_WM_SetCaption(GAME_NAME, NULL);
  this->initSprites();
}

void				Graphic::initSprites()
{
  this->sprites[0].img = SDL_LoadBMP(BMP_FOOD);
  this->sprites[0].name = OBJ_FOOD;
  this->sprites[1].img = SDL_LoadBMP(BMP_WALL);
  this->sprites[1].name = OBJ_WALL;
  this->sprites[2].img = SDL_LoadBMP(BMP_SNAKE);
  this->sprites[2].name = OBJ_SNAKE;
  this->sprites[3].img = SDL_CreateRGBSurface(SDL_HWSURFACE,
					      SIZE_SQUARE, SIZE_SQUARE, 32, 0, 0, 0, 0);
  this->sprites[3].name = OBJ_EMPTY;
  this->sprites[4].img = SDL_LoadBMP(BMP_SUPERFOOD);
  this->sprites[4].name = OBJ_SUPERFOOD;
  this->sprites[5].img = SDL_LoadBMP(BMP_HEAD);
  this->sprites[5].name = OBJ_HEAD;
  if (SDL_FillRect(this->sprites[3].img, NULL, SDL_MapRGB(this->window->format, 0, 0, 0)) == -1)
    throw std::runtime_error(SDL_GetError());
  for (int count = 0 ; count != NB_SPRITES ; count++)
    if (this->sprites[count].img == NULL)
      throw std::runtime_error(SDL_GetError());
  if ((this->police = TTF_OpenFont(POLICE, 25)) == NULL)
    throw std::runtime_error(TTF_GetError());
}

void                          Graphic::loadImg(int const y, int const x, std::string const name) const
{
  SDL_Rect			pos;

  pos.x = x * SIZE_SQUARE;
  pos.y = y * SIZE_SQUARE;
  for (int count = 0 ; count != NB_SPRITES ; count++)
    if (this->sprites[count].name == name)
      if (SDL_BlitSurface(this->sprites[count].img, NULL, this->window, &pos) == -1)
	throw std::runtime_error(SDL_GetError());
}

void				Graphic::putOnScreen(int const score)
{
  int				delay;

  this->displayScore();
  if (this->speed == true)
    {
      delay = 130 - ((score / 10) - 1);
      if (delay <= 80)
	delay = 80;
    }
  else
    delay = 130;
  if (SDL_Flip(this->window) == -1)
    throw std::runtime_error(SDL_GetError());
  SDL_Delay(delay);
}

void                          Graphic::setWidth(int const width)
{
  this->width = width;
}

void                          Graphic::setHeight(int const height)
{
  this->height = height;
}

void                          Graphic::setEnd(bool const status)
{
  this->end = status;
}

bool                          Graphic::getEnd() const
{
  return (this->end);
}

int                          Graphic::getDirection() const
{
  return (this->sdlkDirection);
}

void				Graphic::setScore(int const score)
{
  this->score = score;
}

void                          Graphic::displayScore()
{
  SDL_Color			color;
  SDL_Rect			pos;
  SDL_Surface			*text = NULL;
  char				tmp[BUFF];

  sprintf(tmp, SCORE, this->score);
  color.r = 0;
  color.g = 0;
  color.b = 0;
  if ((text = TTF_RenderText_Blended(this->police, tmp, color)) == NULL)
    throw std::runtime_error(TTF_GetError());
  pos.x = 0;
  pos.y = 0;
  SDL_BlitSurface(text, NULL, this->window, &pos);
}

extern "C"
{
  IGraphic			*create_graphic()
  {
    return (new Graphic());
  }
}
