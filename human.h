#ifndef HUMAN_H
#define HUMAN_H

#include <vector>
#include <string>
#include "player.h"

class Human: public Player {
public:
Human(std::vector<std::unique_ptr<Card>>::const_iterator startPos, 
std::vector<std::unique_ptr<Card>>::const_iterator endPos);
virtual Card* play(int rank, char suit) override;
virtual Card* discard(int rank, char suit) override;
};
#endif
