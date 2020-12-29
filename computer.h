#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include "player.h"

class Computer : public Player
{
public:
    Computer(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
             std::vector<std::unique_ptr<Card>>::const_iterator endPos);
    Computer(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
             std::vector<std::unique_ptr<Card>>::const_iterator endPos,
             int roundScore, int prevScore,
             std::vector<Card *> cards,
             std::vector<Card *> discarded,
             std::vector<Card *> legalCards);
    virtual Card *play(int rank, char suit) override;
    virtual Card *discard(int rank, char suit) override;
};
#endif
