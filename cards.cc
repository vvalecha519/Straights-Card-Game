#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include "cards.h"

Cards::Cards(int seed) : seed{seed}, rng{seed}
{
    std::vector<char> suits = {'C', 'D', 'H', 'S'};

    for (char &s : suits)
    {
        for (int r = 1; r < 14; r++)
        {

            deck.emplace_back(std::make_unique<Card>(r, s));
        }
    }
    //intiatize empty map with 4 keys
    reset();
}

void Cards::shuffle()
{
    std::shuffle(deck.begin(), deck.end(), rng);
}
const std::map<char, std::vector<Card *>> &Cards::getplayedcards() const
{
    return playedcards;
}

void Cards::addplayedcard(Card *card)
{
    playedcards[card->getSuit()].push_back(card);
}

const std::vector<std::unique_ptr<Card>> &Cards::getCard()
{
    return deck;
}

void Cards::reset()
{
    std::vector<Card *> v;
    playedcards.clear();
    playedcards.emplace('C', v);
    playedcards.emplace('D', v);
    playedcards.emplace('H', v);
    playedcards.emplace('S', v);
}
