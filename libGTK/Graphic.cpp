//
// Graphic.cpp for Graphic.cpp in /home/abgral_f/dev/nibler/src
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 11:14:37 2014 abgral_f
// Last update Thu Apr  3 20:54:48 2014 Baptiste Acca
//

#include			<stdexcept>
#include			"Graphic.hh"

Graphic::Graphic()
{
  this->end = false;
  this->gtkDirection = Graphic::RIGHT;
  this->data = NULL;
  this->score = 0;
}

Graphic::~Graphic()
{
  gtk_exit(EXIT_SUCCESS);
}

void                          Graphic::event()
{

}

void                          Graphic::setDirection(e_direction const direction)
{
  this->gtkDirection = direction;
}

void                          Graphic::init(int argc, char **argv, bool speed, bool controls)
{
  this->speed = speed;
  this->controls = controls;
  this->data = (guchar *)malloc(sizeof(guchar) * this->width * SIZE_SQUARE * this->height * SIZE_SQUARE * 3);
  gtk_init (&argc, &argv);
  this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  this->darea = gtk_drawing_area_new ();
  gtk_widget_set_size_request (this->darea, this->width * SIZE_SQUARE, this->height * SIZE_SQUARE);
  gtk_container_add(GTK_CONTAINER(this->window), this->darea);
  gtk_signal_connect (GTK_OBJECT(this->darea), EXPOSE,
                      G_CALLBACK(on_darea_expose), this);
  g_signal_connect(G_OBJECT(this->window), KEY_PRESS, G_CALLBACK(on_key_press), this);
  g_signal_connect(G_OBJECT(this->window), DELETE, G_CALLBACK(quit_gtk), this);
  this->initColor();
  gtk_widget_show_all(this->window);
  g_timeout_add(SPEED, timeout, NULL);
}

void				Graphic::initColor()
{
  this->color = *new std::vector<t_color>(NB_OBJ);
  this->color[0].color = COLOR_FOOD;
  this->color[0].name = OBJ_FOOD;
  this->color[1].color = COLOR_WALL;
  this->color[1].name = OBJ_WALL;
  this->color[2].color = COLOR_SNAKE;
  this->color[2].name = OBJ_SNAKE;
  this->color[3].color = COLOR_EMPTY;
  this->color[3].name = OBJ_EMPTY;
  this->color[4].color = COLOR_SUPERFOOD;
  this->color[4].name = OBJ_SUPERFOOD;
  this->color[5].color = COLOR_HEAD;
  this->color[5].name = OBJ_HEAD;
}

void				Graphic::printColor(int y, int x, int const color)
{
  int y_ref = y * SIZE_SQUARE;
  int x_ref = x * SIZE_SQUARE;

  for (y = y_ref ; y < y_ref + SIZE_SQUARE; y++)
    {
        for (x = x_ref ; x < x_ref + SIZE_SQUARE ; x++)
	  {
	  if (x * 3 + y * this->width * SIZE_SQUARE * 3 + 2
	      < this->width * SIZE_SQUARE * this->height * SIZE_SQUARE * 3)
	    {
	      this->data[x * 3 + y * this->width * SIZE_SQUARE * 3] = (color & 0xFF0000) >> 16;
	      this->data[x * 3 + y * this->width * SIZE_SQUARE * 3 + 1] = (color & 0x00FF00) >> 8;
	      this->data[x * 3 + y * this->width * SIZE_SQUARE * 3 + 2] = (color & 0x0000FF);
	    }
	}
    }
}

void                          Graphic::loadImg(int y, int x, std::string const name)
{
  for (int count = 0 ; count != NB_OBJ ; count++)
    if (this->color[count].name == name)
      printColor(y, x, this->color[count].color);
}

void				Graphic::putOnScreen(int const __attribute__((unused))score)
{
  on_darea_expose(this->darea, NULL, this);
  gtk_main();
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
  return (this->gtkDirection);
}

void                          Graphic::setWidth(int const width)
{
  this->width = width;
}

void                          Graphic::setHeight(int const height)
{
  this->height = height;
}

int                           Graphic::getWidth() const
{
  return (this->width);
}

int                           Graphic::getHeight() const
{
  return (this->height);
}

guchar                           *Graphic::getData() const
{
  return (this->data);
}

bool				Graphic::getControls() const
{
  return this->controls;
}

void                            Graphic::setScore(int const score)
{
  this->score = score;
}

void				quit_gtk(GtkWidget __attribute__((__unused__))*widget,
					 GdkEventKey __attribute__((__unused__))*event, gpointer user_data)
{
  Graphic			*tmp;

  tmp = (Graphic *)user_data;
  tmp->setEnd(TRUE);
}


gboolean			on_darea_expose(GtkWidget *widget,
						GdkEventKey __attribute__((__unused__))*event, gpointer user_data)
{
  Graphic			*tmp;

  tmp = (Graphic *)user_data;
  if (widget->window != NULL && tmp->getData() != NULL)
    gdk_draw_rgb_image(widget->window, widget->style->fg_gc[GTK_STATE_NORMAL],
		       0, 0, tmp->getWidth() * SIZE_SQUARE, tmp->getHeight() * SIZE_SQUARE,
		       GDK_RGB_DITHER_MAX, tmp->getData(), tmp->getWidth() * SIZE_SQUARE * 3);
  return TRUE;
}

void				on_key_press(GtkWidget __attribute__((__unused__))*widget,
					     GdkEventKey *event, gpointer user_data)
{
  Graphic			*tmp;

  tmp = (Graphic *)user_data;
  if (event->keyval == GDK_Up && tmp->getDirection() != Graphic::DOWN)
    tmp->setDirection(Graphic::UP);
  if (event->keyval == GDK_Down && tmp->getDirection() != Graphic::UP)
    tmp->setDirection(Graphic::DOWN);
  if (event->keyval == GDK_Right)
    {
      if (tmp->getControls() == false)
	tmp->setDirection((Graphic::e_direction)((tmp->getDirection() + 1) % 4));
      else if (tmp->getDirection() != Graphic::LEFT)
	tmp->setDirection(Graphic::RIGHT);
    }
  if (event->keyval == GDK_Left)
    {
      if (tmp->getControls() == false)
	tmp->setDirection((Graphic::e_direction)(tmp->getDirection() - 1));
      else if (tmp->getDirection() != Graphic::RIGHT)
	tmp->setDirection(Graphic::LEFT);
    }
  if (event->keyval == GDK_Escape)
    tmp->setEnd(TRUE);
  if (tmp->getDirection() == -1)
    tmp->setDirection(Graphic::LEFT);
}

gboolean			timeout(gpointer __attribute__((__unused__))data)
{
  gtk_main_quit();
  return TRUE;
}

extern "C"
{
  IGraphic			*create_graphic()
  {
    return (new Graphic());
  }
}
