//
// IGraphic.hh for IGraphic.hh in /home/abgral_f/dev/nibler3/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Tue Mar 18 23:32:31 2014 abgral_f
// Last update Thu Apr  3 20:08:47 2014 Baptiste Acca
//

#ifndef                         IGRAPHIC_HH
# define                        IGRAPHIC_HH

#include <iostream>

class				IGraphic
{
public:
  virtual ~IGraphic() {}
  virtual void                          loadImg(int const, int const, std::string const, int const, int const) const = 0;
  virtual void                          event() = 0;
  virtual void                          setEnd(bool const) = 0;
  virtual bool                          getEnd() const;
  virtual int                           getDirection() const = 0;
  virtual void                          putOnScreen(int const) = 0;
  virtual void				init(int,char **, bool, bool, bool) = 0;
  virtual void				setWidth(int const) = 0;
  virtual void				setHeight(int const) = 0;
  virtual void				setScore(int const) = 0;
};

#endif
