#include "card.h"

Card::Card(int rank, char suit) : rank{rank}, suit{suit} {}
int Card::getRank() const { return rank; }
char Card::getSuit() const { return suit; }
