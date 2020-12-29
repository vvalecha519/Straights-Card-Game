
#include <vector>
#include <string>
#include "player.h"
#include <cmath>
#include <algorithm>

//create player, with iterator create vector of 13 cards (doesnt change)
//inside of human/computer in constructor if 7 exist then add it to legal Cards
//new game constructor
Player::Player(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
               std::vector<std::unique_ptr<Card>>::const_iterator endPos) : roundScore{0}, prevScore{0}, startPos{startPos}, endPos{endPos}
{
    reset();
}

//replace human constructor
Player::Player(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
               std::vector<std::unique_ptr<Card>>::const_iterator endPos,
               int roundScore, int prevScore,
               std::vector<Card *> cards,
               std::vector<Card *> discarded,
               std::vector<Card *> legalCards) : cards{cards}, discarded{discarded},
                                                 legalCards{legalCards}, roundScore{roundScore}, prevScore{prevScore}, startPos{startPos},
                                                 endPos{endPos}
{
}

int Player::getRoundScore() const
{
    return roundScore;
}
int Player::getPrevScore() const
{
    return prevScore;
}
const std::vector<Card *> *Player::getHand()
{
    return &cards;
}
const std::vector<Card *> *Player::getDiscarded()
{
    return &discarded;
}
const std::vector<Card *> *Player::getLegalCards()
{
    return &legalCards;
}

//not done
void Player::updateLegalMoves(Card *added)
{
    for (auto &c : cards)
    {
        //if it has a 7 and not in curLegal add it
        if (c->getRank() == 7)
        {
            if (find(legalCards.begin(), legalCards.end(), c) == legalCards.end())
                addToLegal(c);
            continue;
        }
        if (c->getSuit() == added->getSuit())
        {
            if (abs(c->getRank() - added->getRank()) == 1)
            {
                addToLegal(c);
            }
        }
    }
}

void Player::addToLegal(Card *add)
{
    int index = find(cards.begin(), cards.end(), add) - cards.begin();
    for (auto &c : legalCards)
    {
        auto it = find(cards.begin(), cards.end(), c);
        int cIndex = it - cards.begin();
        if (index < cIndex)
        {
            auto put = find(legalCards.begin(), legalCards.end(), c);
            legalCards.insert(put, add);
            return;
        }
    }
    legalCards.push_back(add);
}

void Player::reset()
{
    prevScore = prevScore + roundScore;
    roundScore = 0;
    cards.clear();
    discarded.clear();
    legalCards.clear();

    for (auto i = startPos; i <= endPos; i++)
    {
        cards.push_back(i->get());
    }

    for (auto &c : cards)
    {
        if (c->getRank() == 7 && c->getSuit() == 'S')
            legalCards.push_back(c);
    }
}
