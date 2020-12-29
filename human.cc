
#include <vector>
#include <string>
#include "player.h"
#include "human.h"

Human::Human(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
             std::vector<std::unique_ptr<Card>>::const_iterator endPos) : Player{startPos, endPos} {}

Card *Human::play(int rank, char suit)
{
    int counter = 0;
    Card *added = nullptr;
    for (auto &c : cards)
    {
        if (c->getRank() == rank && c->getSuit() == suit)
        {
            added = c;
            cards.erase(cards.begin() + counter);
            break;
        }
        counter++;
    }
    counter = 0;
    for (auto &c : legalCards)
    {
        if (added == c)
        {
            legalCards.erase(legalCards.begin() + counter);
            break;
        }
        counter++;
    }
    return added;
}

Card *Human::discard(int rank, char suit)
{
    int counter = 0;
    Card *remove = nullptr;
    for (auto &c : cards)
    {
        if (c->getRank() == rank && c->getSuit() == suit)
        {
            remove = c;
            cards.erase(cards.begin() + counter);
            break;
        }
        counter++;
    }
    discarded.push_back(remove);
    roundScore = roundScore + remove->getRank();
    return remove;
}
