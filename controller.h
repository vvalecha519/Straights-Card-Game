#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "straight.h"

class Controller : public Subject
{
public:
  Controller(Straight *);

  //call replaceHuman in straight
  void replaceHuman();
  //return
  void quit();
  //call play in straight with the following card
  void play(int, char);
  //call discard in straight with the following card
  void discard(int, char);
  //call reset in straight
  void newRound();

private:
  Straight *model;
};

#endif
