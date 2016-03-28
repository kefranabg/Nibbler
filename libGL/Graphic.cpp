//
// Graphic.cpp for  in /home/acca_b/rendu/cpp_nibbler/libGL
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.eu>
//
// Started on  Tue Mar  25 13:58:24 2014 Baptiste Acca
// Last update Thu Apr  3 20:53:51 2014 Baptiste Acca
//

#include			<stdexcept>
#include			"Graphic.hh"

Graphic::Graphic()
{
  this->end = false;
  this->sdlkDirection = Graphic::RIGHT;
  this->loaders[0] = &Graphic::loadSnakeHead;
  this->loaders[1] = &Graphic::loadSnake;
  this->loaders[2] = &Graphic::loadFood;
  this->loaders[3] = &Graphic::loadWall;
  this->loaders[4] = &Graphic::loadSuperfood;
  this->loaders[5] = &Graphic::loadEmpty;
  this->loadersName[0] = OBJ_SNAKE_HEAD;
  this->loadersName[1] = OBJ_SNAKE;
  this->loadersName[2] = OBJ_FOOD;
  this->loadersName[3] = OBJ_WALL;
  this->loadersName[4] = OBJ_SUPERFOOD;
  this->loadersName[5] = OBJ_EMPTY;
  this->score = 0;
}

Graphic::~Graphic()
{
  TTF_Quit();
  SDL_Quit();
}

void                          Graphic::event()
{
  SDL_Event		      event;

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

void                          Graphic::init(int argc,
					    char **argv,
					    bool speed, bool controls, bool view)
{
  this->speed = speed;
  this->controls = controls;
  this->view = view;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error(SDL_GetError());
  glutInit(&argc, argv);
  if ((this->window = SDL_SetVideoMode(this->width * SIZE_SQUARE, this->height * SIZE_SQUARE,
				       32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
    throw std::runtime_error(SDL_GetError());
  SDL_WM_SetCaption(GAME_NAME, NULL);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->view == false)
    gluPerspective(70, static_cast<double>((MAP_X * SIZE_SQUARE) / (MAP_Y * SIZE_SQUARE)), 1, 1000);
  else
    gluPerspective(90, static_cast<double>((MAP_X * SIZE_SQUARE) / (MAP_Y * SIZE_SQUARE)), 1, 1000);
  glEnable(GL_DEPTH_TEST);
}

void			      Graphic::drawCube(SDL_Color const color[], SDL_Rect const &pos,
						int const z[]) const
{
  glBegin(GL_QUADS);
  glColor3ub(color[0].r, color[0].g, color[0].b);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[1]);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[1]);
  glColor3ub(color[0].r, color[0].g, color[0].b);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[1]);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[0]);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[1]);
  glColor3ub(color[0].r, color[0].g, color[0].b);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[1]);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[1]);
  glColor3ub(color[0].r, color[0].g, color[0].b);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[1]);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[1]);
  glColor3ub(color[0].r, color[0].g, color[0].b);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[0]);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[0]);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[0]);
  glColor3ub(color[1].r, color[1].g, color[1].b);
  glVertex3d(pos.x + 0.5, pos.y - 0.5, z[1]);
  glVertex3d(pos.x + 0.5, pos.y + 0.5, z[1]);
  glVertex3d(pos.x - 0.5, pos.y + 0.5, z[1]);
  glVertex3d(pos.x - 0.5, pos.y - 0.5, z[1]);
  glEnd();
}

void			      Graphic::loadSnakeHead(SDL_Color color[], int z[]) const
{
  color[0].r = 58;
  color[0].g = 127;
  color[0].b = 43;
  color[1].r = 87;
  color[1].g = 191;
  color[1].b = 65;
  z[0] = -1;
  z[1] = 1;
}

void			      Graphic::loadSnake(SDL_Color color[], int z[]) const
{
  color[0].r = 87;
  color[0].g = 191;
  color[0].b = 65;
  color[1].r = 58;
  color[1].g = 127;
  color[1].b = 43;
  z[0] = -1;
  z[1] = 1;
}

void			      Graphic::loadFood(SDL_Color color[], int z[]) const
{
  color[0].r = 191;
  color[0].g = 52;
  color[0].b = 39;
  color[1].r = 127;
  color[1].g = 35;
  color[1].b = 26;
  z[0] = -1;
  z[1] = 1;
}

void			      Graphic::loadWall(SDL_Color color[], int z[]) const
{
  color[0].r = 109;
  color[0].g = 141;
  color[0].b = 191;
  color[1].r = 73;
  color[1].g = 94;
  color[1].b = 127;
  z[0] = -1;
  z[1] = 1;
}

void			      Graphic::loadSuperfood(SDL_Color color[], int z[]) const
{
  color[0].r = 255;
  color[0].g = 190;
  color[0].b = 36;
  color[1].r = 229;
  color[1].g = 171;
  color[1].b = 32;
  z[0] = -1;
  z[1] = 1;
}

void			      Graphic::loadEmpty(SDL_Color color[], int z[]) const
{
  color[0].r = 64;
  color[0].g = 56;
  color[0].b = 64;
  color[1].r = 64;
  color[1].g = 56;
  color[1].b = 64;
  z[0] = 0;
  z[1] = 0;
}

void                          Graphic::loadImg(int const y, int const x, std::string const name, int const xhead, int const yhead) const
{
  SDL_Rect			pos;
  SDL_Color			color[2];
  int				z[2];
  unsigned int			i;

  pos.x = -x;
  pos.y = y;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (this->view == true)
    {
      if (this->sdlkDirection == Graphic::UP)
	gluLookAt(-xhead, yhead + 5, 3, -xhead, yhead - 1, 0, 0, 0, 1);
      else if (this->sdlkDirection == Graphic::DOWN)
	gluLookAt(-xhead, yhead - 5, 3, -xhead, yhead + 1, 0, 0, 0, 1);
      else if (this->sdlkDirection == Graphic::LEFT)
	gluLookAt(-xhead - 5, yhead, 3, -xhead + 1, yhead, 0, 0, 0, 1);
      else if (this->sdlkDirection == Graphic::RIGHT)
	gluLookAt(-xhead + 5, yhead, 3, -xhead - 1, yhead, 0, 0, 0, 1);
    }
  else if (this->view == false)
    gluLookAt(-this->width / 2 - (xhead / 10), this->height + (this->height - 5) + (yhead / 10),
	      this->width - this->height + 10, -this->width / 2 - (xhead / 10), 0, 0, 0, 0, 1);
  for (i = 0; i < 6 && this->loadersName[i] != name ; ++i);
  if (i != 6 && this->loadersName[i] == name)
    {
      (this->*loaders[i])(color, z);
      this->drawCube(color, pos, z);
    }
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
  glClear(GL_DEPTH_BUFFER_BIT);
  glFlush();
  SDL_GL_SwapBuffers();
  SDL_Delay(delay);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void                          Graphic::displayScore()
{
  char				tmp[BUFF];
  unsigned int			i;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, this->width * SIZE_SQUARE, 0.0, this->height * SIZE_SQUARE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glColor3f(255, 255, 255);
  glRasterPos2i(10, (this->height * SIZE_SQUARE) - 20);
  sprintf(tmp, SCORE, this->score);
  for (i = 0; i < strlen(tmp) ; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tmp[i]);
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

void				Graphic::setScore(int const score)
{
  this->score = score;
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

extern "C"
{
  IGraphic			*create_graphic()
  {
    return (new Graphic());
  }
}
