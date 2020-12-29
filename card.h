#ifndef CARD_H
#define CARD_H

class Card
{
public:
    Card(int rank, char suit);
    int getRank() const;
    char getSuit() const;

private:
    int rank;
    char suit;
};

#endif
