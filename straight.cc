#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include "straight.h"
#include "player.h"
#include <vector>
#include "computer.h"
#include "human.h"
#include "cards.h"
#include "exception.h"

Straight::Straight(int seed) : prevCard{}, prevPlayed{}, over80{}, turn{}, cards{Cards{seed}}
{
  //create 4 players
  for (int i = 0; i < 4; i++)
  {
    auto it = cards.getCard().begin() + (i * 13);
    players.emplace_back(std::make_unique<Human>(it, it + 12));
  }
  reset();
}

void Straight::play(int rank, char suit)
{
  Card *add = players.at(turn)->play(rank, suit);
  cards.addplayedcard(add);
  prevCard = add;
  prevPlayed = true;
  for (auto &p : players)
    p->updateLegalMoves(add);
  //determine if next player has no cards to play
  if ((players.at((turn + 1) % 4)->getHand())->size() == 0)
  {
    turn = ((turn + 1) % 4);
    throw RoundOver{""};
  }
  turn = ((turn + 1) % 4);
  notify();
}
void Straight::discard(int rank, char suit)
{
  Card *removed = players.at(turn)->discard(rank, suit);
  int prevScore = players.at(turn)->getPrevScore();
  int roundScore = players.at(turn)->getRoundScore();
  if ((prevScore + roundScore) >= 80)
    over80 = true;
  prevCard = removed;
  prevPlayed = false;
  if ((players.at((turn + 1) % 4)->getHand())->size() == 0)
  {
    turn = ((turn + 1) % 4);
    throw RoundOver{"hi"};
  }
  turn = ((turn + 1) % 4);
  notify();
}

const std::vector<std::unique_ptr<Card>> &Straight::viewDeck()
{
  return cards.getCard();
}

void Straight::replaceHuman(int pos)
{
  auto it = cards.getCard().begin() + (pos * 13);
  //make unique pointer swap current player at pos with new
  auto newPlayer = std::make_unique<Computer>(it, it + 12,
                                              players.at(pos)->getRoundScore(), players.at(pos)->getPrevScore(),
                                              *(players.at(pos)->getHand()),
                                              *(players.at(pos)->getDiscarded()),
                                              *(players.at(pos)->getLegalCards()));
  players.at(pos) = std::move(newPlayer);
}

void Straight::reset()
{
  cards.shuffle();
  cards.reset();
  for (auto &player : players)
  {
    player->reset();
  }
  for (int i = 0; i < 52; i++)
  {
    if (cards.getCard().at(i)->getRank() == 7 && cards.getCard().at(i)->getSuit() == 'S')
    {
      turn = i / 13;
    }
  }
  prevCard = nullptr;
  prevPlayed = 0;
}

int Straight::getTurn()
{
  return turn;
}

Card *Straight::getPrevCard()
{
  return prevCard;
}

bool Straight::isPlayed()
{
  return prevPlayed;
}

const std::vector<Card *> &Straight::curCards() const
{
  return *(players.at(turn)->getHand());
}

const std::vector<Card *> &Straight::getCurLegalMove() const
{
  return *(players.at(turn)->getLegalCards());
}

const std::map<char, std::vector<Card *>> &Straight::getPlayedCards() const
{
  return cards.getplayedcards();
}

std::string Straight::getFinalStats() const
{
  std::string Winners = "";
  std::vector<int> winnerPos;
  int lowestScore = 10000000;
  int counter = 1;
  for (auto &p : players)
  {
    int playerScore = p->getPrevScore() + p->getRoundScore();
    if (playerScore < lowestScore)
    {
      winnerPos.clear();
      winnerPos.push_back(counter);
      lowestScore = playerScore;
    }
    else if (playerScore == lowestScore)
    {
      winnerPos.push_back(counter);
    }
    counter++;
  }

  for (auto &pos : winnerPos)
  {
    Winners = "Player" + std::to_string(pos) + " wins!\n";
  }
  return Winners;
}

std::string Straight::getRoundStats() const
{
  int counter = 1;
  std::string stats = "";

  for (auto &p : players)
  {
    std::string disCards{};
    for (auto &d : (*(p->getDiscarded())))
    {
      if (d->getRank() == 1)
        disCards = disCards + " A" + d->getSuit();
      else if (d->getRank() == 10)
        disCards = disCards + " T" + d->getSuit();
      else if (d->getRank() == 11)
        disCards = disCards + " J" + d->getSuit();
      else if (d->getRank() == 12)
        disCards = disCards + " Q" + d->getSuit();
      else if (d->getRank() == 13)
        disCards = disCards + " K" + d->getSuit();
      else
        disCards = disCards + " " + std::to_string(d->getRank()) + d->getSuit();
    }
    stats = stats + "Player" + std::to_string(counter) + "'s discards:" + disCards + "\n";

    int prevScore = p->getPrevScore();
    int roundScore = p->getRoundScore();

    stats = stats + "Player" + std::to_string(counter) + "'s score: " +
            std::to_string(prevScore) + " + " + std::to_string(roundScore) +
            " = " + std::to_string(prevScore + roundScore) + "\n";
    counter++;
  }
  return stats;
}

bool Straight::isCurHuman()
{
  Player *ptr = players.at(turn).get();
  Human *h = dynamic_cast<Human *>(ptr);
  if (h != nullptr)
    return true;
  else
    return false;
}

bool Straight::gameOver()
{
  return over80;
}
