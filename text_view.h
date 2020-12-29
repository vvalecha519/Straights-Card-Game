#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "observer.h"
#include "card.h"
#include <string>

class Controller;
class Straight;

class TextView : Observer
{
public:
    TextView(Controller *, Straight *);

    //display the cards, score, and call appropriate
    //control based on type of player
    virtual void update() override;

    //convert the rank to string
    std::string rankValue(int);

    //get Input from Human
    void getHumanInput();

private:
    Controller *controller;
    Straight *model;
    bool ragequit;
};

#endif
