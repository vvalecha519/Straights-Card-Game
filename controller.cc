#include "controller.h"
#include "straight.h"

Controller::Controller(Straight *model) : model{model} {}

void Controller::replaceHuman()
{
    model->replaceHuman(model->getTurn());
}

void Controller::quit()
{
    return;
}

void Controller::play(int rank, char suit)
{
    model->play(rank, suit);
}

void Controller::discard(int rank, char suit)
{
    model->discard(rank, suit);
}

void Controller::newRound()
{
    model->reset();
}
