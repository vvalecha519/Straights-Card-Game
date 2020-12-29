#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>
#include "card.h"
#include <memory>

class Player
{
public:
    //create player, with iterator create vector of 13 cards (doesnt change)
    //inside of human/computer in constructor if 7 exist then add it to legal Cards
    Player(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
           std::vector<std::unique_ptr<Card>>::const_iterator endPos);

    //mid game player added
    Player(std::vector<std::unique_ptr<Card>>::const_iterator startPos,
           std::vector<std::unique_ptr<Card>>::const_iterator endPos,
           int roundScore, int prevScore,
           std::vector<Card *> cards,
           std::vector<Card *> discarded,
           std::vector<Card *> legalCards);
    //remove from cards
    virtual Card *play(int rank, char suit) = 0;
    //increase score and add to discard
    virtual Card *discard(int rank, char suit) = 0;
    //return round score
    int getRoundScore() const;
    //return previous round score
    int getPrevScore() const;
    //return cards I currently have available
    const std::vector<Card *> *getHand();
    //return cards that player has discarded
    const std::vector<Card *> *getDiscarded();
    //return all the cards that can be played
    const std::vector<Card *> *getLegalCards();
    //using the parameter finds if any cards are above or below
    //the following card
    void updateLegalMoves(Card *);
    //reset current round score and add to previous
    //reset my current cards, empty discarded, legal and find 7s
    //round score is 0 and prev score = prevScore + round
    void reset();

protected:
    std::vector<Card *> cards;
    std::vector<Card *> discarded;
    std::vector<Card *> legalCards;
    int roundScore;
    int prevScore;

private:
    void addToLegal(Card *added);
    std::vector<std::unique_ptr<Card>>::const_iterator startPos;
    std::vector<std::unique_ptr<Card>>::const_iterator endPos;
};

#endif
