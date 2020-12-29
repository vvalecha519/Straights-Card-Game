#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "cards.h"
#include "player.h"
#include "subject.h"
#include <vector>
#include <string>
#include <memory>

class Card;

class Straight : public Subject
{
public:
  //Straight constructor, intitalize seed in Cards and create
  //4 human players
  Straight(int);

  //play the card the player wants to play
  //then add card to map which has all the played cards
  //finally update all the players legal moves
  //make sure it isnt last players last card or last player
  //for the game to end, if so throw exceptions
  void play(int rank, char suit);

  //play the card the player wants to play
  //then add card to map which has all the played cards
  //finally update all the players legal moves
  //make sure it isnt last players last card or last player
  //for the game to end, if so throw exceptions
  void discard(int rank, char suit);

  //gets all cards in deck
  const std::vector<std::unique_ptr<Card>> &viewDeck();

  //find the player in players with index i, call constructor of
  //computer transfer iterator (get them based on player #) get round scores and prevScore
  void replaceHuman(int);

  //new round setup
  //shuffle the cards reset the played cards (in cards class)
  //and reset players with no played card find player with 7S then notify
  void reset();

  //get turn of the player
  int getTurn();

  //get previous card played
  Card *getPrevCard();
  //determine if played or discarded
  bool isPlayed();
  //determine whether human or computer
  bool isCurHuman();
  //get players current hand
  const std::vector<Card *> &curCards() const;
  //get all legal plays
  const std::vector<Card *> &getCurLegalMove() const;
  //get all the cards already played
  const std::map<char, std::vector<Card *>> &getPlayedCards() const;

  //call roundStats and then compare all the players score and add line that says winning player
  std::string getFinalStats() const;
  //get all players previous score, current score, player number and cards discarded
  //and put it in a string
  std::string getRoundStats() const;

  bool gameOver();

private:
  Card *prevCard;
  bool prevPlayed;
  bool over80;
  int turn;
  Cards cards;
  std::vector<std::unique_ptr<Player>> players;
};

#endif
