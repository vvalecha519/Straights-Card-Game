#ifndef CARDS_H
#define CARDS_H

#include <map>
#include <vector>
#include <string>
#include "card.h"
#include <memory>
#include <algorithm>
#include <random>

class Cards
{
public:
    //Construct Cards with the following seed number and create 52 cards
    Cards(int);
    //shuffle the deck
    void shuffle();
    //return all the cards that have been played
    const std::map<char, std::vector<Card *>> &getplayedcards() const;
    //add to the cards that have been played
    void addplayedcard(Card *card);
    //empty playedCards map
    void reset();
    //get the deck of cards
    const std::vector<std::unique_ptr<Card>> &getCard();

private:
    std::map<char, std::vector<Card *>> playedcards;
    std::vector<std::unique_ptr<Card>> deck;
    int seed;
    std::default_random_engine rng;
};

#endif
