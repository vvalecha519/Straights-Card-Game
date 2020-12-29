
#include <vector>
#include <string>
#include "player.h"
#include "computer.h"

Computer::Computer(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
                   std::vector<std::unique_ptr<Card>>::const_iterator endPos) : Player{startPos, endPos} {}

Computer::Computer(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
                   std::vector<std::unique_ptr<Card>>::const_iterator endPos,
                   int roundScore, int prevScore,
                   std::vector<Card *> cards,
                   std::vector<Card *> discarded,
                   std::vector<Card *> legalCards) : Player{startPos, endPos, roundScore, prevScore, cards, discarded, legalCards} {}

Card *Computer::play(int rank, char suit)
{
    int firstCard = 0;
    Card *added = legalCards.at(firstCard);
    legalCards.erase(legalCards.begin() + firstCard);
    for (auto &c : cards)
    {
        if (added == c)
        {
            cards.erase(cards.begin() + firstCard);
            break;
        }
        firstCard++;
    }
    return added;
}

Card *Computer::discard(int rank, char suit)
{
    int firstCard = 0;
    Card *remove = cards.at(firstCard);
    cards.erase(cards.begin() + firstCard);
    discarded.push_back(remove);
    roundScore = roundScore + remove->getRank();
    return remove;
}
