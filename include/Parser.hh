//
// Parser.hh for Parser.hh in /home/acca_b/rendu/cpp_nibbler
//
// Made by Baptiste Acca
// Login   <acca_b@epitech.net>
//
// Started on  Mon Mar 31 13:42:45 2014 Baptiste Acca
// Last update Thu Apr  3 20:36:43 2014 Baptiste Acca
//

#ifndef PARSER_HH_
#define PARSER_HH_

#include <iostream>
#include <fstream>

#define CONF_FILE "settings.conf"

#define SPEED_OPT "Speed:"
#define SPEED_OPT_SIZE 6
#define CONTROL_OPT "Controls:"
#define CONTROL_OPT_SIZE 9
#define SPEED_ACT "accelerated"
#define SPEED_ACT_SIZE 11
#define SPEED_DACT "normal"
#define SPEED_DACT_SIZE 6
#define CLAS_CONTROL "classic"
#define CLAS_CONTROL_SIZE 7
#define EPI_CONTROL "epitech"
#define EPI_CONTROL_SIZE 7
#define VIEW_OPT "View:"
#define VIEW_OPT_SIZE 5
#define UP_VIEW "up"
#define UP_VIEW_SIZE 2
#define TPS_VIEW "tps"
#define TPS_VIEW_SIZE 3
#define SOUND_OPT "Sound:"
#define SOUND_OPT_SIZE 6
#define SOUND_ON "on"
#define SOUND_ON_SIZE 2
#define SOUND_OFF "off"
#define SOUND_OFF_SIZE 3
#define OBSTACLES_OPT "Obstacles:"
#define OBSTACLES_OPT_SIZE 10
#define OBSTACLES_ON "on"
#define OBSTACLES_ON_SIZE 2
#define OBSTACLES_OFF "off"
#define OBSTACLES_OFF_SIZE 3

#define DOUBLE_SPACE "  "
#define SIMPLE_SPACE " "
#define COMMENT_CHAR "#"
#define DELIMITER_CHAR ":"

class Parser {
  bool controls;
  bool speed;
  bool view;
  bool sound;
  bool obstacles;
  void (Parser::*optionsParser[6])(std::string const &);
  std::string optionsName[6];
  int optionsLen[6];
public:
  Parser();
  ~Parser();
  void readFile();
  std::string epurString(std::string &) const;
  void getOption(std::string const &);
  void getSpeedOpt(std::string const &);
  void getControlsOpt(std::string const &);
  void getViewOpt(std::string const &);
  void getSoundOpt(std::string const &);
  void getObstaclesOpt(std::string const &);
  bool getControls() const;
  bool getSpeed() const;
  bool getView() const;
  bool getSound() const;
  bool getObstacles() const;
};


#endif
