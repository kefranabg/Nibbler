//
// Exceptions.hpp for Exceptions.hpp in /home/abgral_f/dev/nibler/include
//
// Made by abgral_f
// Login   <abgral_f@epitech.net>
//
// Started on  Mon Mar 17 20:06:28 2014 abgral_f
// Last update Mon Mar 24 16:30:23 2014 abgral_f
//

#ifndef         EXCEPTIONS_HPP_
# define        EXCEPTIONS_HPP_

#include        <stdexcept>
#include        <string>

class           mapError : public std::runtime_error
{
public:
  mapError(std::string const msg) : std::runtime_error(msg) {}
};

#endif
