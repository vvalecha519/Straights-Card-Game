
#include <iostream>
#include <string>
#include <sstream>
#include "text_view.h"
#include "straight.h"
#include "controller.h"
#include "card.h"
#include "exception.h"
#include <algorithm>

TextView::TextView(Controller *c, Straight *m) : controller{c}, model{m}, ragequit{0}
{
    model->subscribe(this);

    for (int i = 0; i < 4; i++)
    {
        std::string type;
        std::cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << std::endl;
        std::getline(std::cin, type);
        if (type[0] == 'c')
        {
            model->replaceHuman(i);
        }
        else if (type[0] == 'h')
        {
            continue;
        }
        else
        {
        }
    }
    std::cout << "A new round begins. It's Player" << model->getTurn() + 1 << "'s turn to play." << std::endl;
    //start game
    update();
}

void TextView::update()
{
    try
    {
        //display previous card
        if (!(model->getPrevCard() == nullptr) && !ragequit)
        {
            int turn = model->getTurn();
            std::string move{"discards"};
            std::string rank = rankValue(model->getPrevCard()->getRank());
            char suit = model->getPrevCard()->getSuit();
            if (model->isPlayed())
                move = "plays";
            if (model->getTurn() == 0)
                turn = 4;

            std::cout << "Player" << turn << " " << move << " " << rank << suit << "." << std::endl;
        }
        ragequit = false;
        //determine if human or computer
        if (model->isCurHuman())
        {
            //display cards on table
            std::cout << "Cards on the table:" << std::endl;
            for (auto &s : model->getPlayedCards())
            {
                std::vector<int> temp;
                if (s.first == 'C')
                    std::cout << "Club: ";
                if (s.first == 'D')
                    std::cout << "Diamonds: ";
                if (s.first == 'H')
                    std::cout << "Hearts: ";
                if (s.first == 'S')
                    std::cout << "Spades: ";
                for (auto &num : s.second)
                    temp.push_back(num->getRank()); //put in order
                std::sort(temp.begin(), temp.end());
                for (auto &num : temp)
                    std::cout << rankValue(num) << " ";
                std::cout << std::endl;
            }
            std::cout << "Your hand: ";
            for (auto &c : model->curCards())
            {
                std::cout << rankValue(c->getRank()) << c->getSuit() << " ";
            }
            std::cout << std::endl;
            std::cout << "Legal plays: ";
            for (auto &c : model->getCurLegalMove())
            {
                std::cout << rankValue(c->getRank()) << c->getSuit() << " ";
            }
            std::cout << std::endl;
            getHumanInput(); //get players input
        }
        else
        {
            if (model->getCurLegalMove().size() > 0)
            {
                controller->play(1, 1); //dummy value for now cause computer makes own choice
            }
            else
            {
                controller->discard(1, 1);
            }
        }
    }
    catch (RoundOver &i)
    {
        int turn = model->getTurn();
        std::string move{"discards"};

        std::string rank = rankValue(model->getPrevCard()->getRank());
        char suit = model->getPrevCard()->getSuit();
        if (model->isPlayed())
            move = "plays";
        if (model->getTurn() == 0)
            turn = 4;
        std::cout << "Player" << turn << " " << move << " " << rank << suit << "." << std::endl;
        std::cout << model->getRoundStats();

        if (model->gameOver()) //80+ points
            std::cout << model->getFinalStats();
        else
        {
            controller->newRound();
            std::cout << "A new round begins. It's Player" << model->getTurn() + 1 << "'s turn to play." << std::endl;
            update();
        }
    }
}

std::string TextView::rankValue(int c)
{
    std::string rank = std::to_string(c);

    if (rank == "1")
    {
        rank = "A";
    }
    else if (rank == "10")
    {
        rank = "T";
    }
    else if (rank == "11")
    {
        rank = "J";
    }
    else if (rank == "12")
    {
        rank = "Q";
    }
    else if (rank == "13")
    {
        rank = "K";
    }
    return rank;
}

void TextView::getHumanInput()
{
    while (true)
    {
        int counter = 0; //count word number
        std::string input = "";
        std::string move = "";
        std::string c = "";
        std::getline(std::cin, input);
        std::istringstream iss(input);

if(std::cin.eof()){ //stop at certain state
    break;
}

        while (iss >> input) //get first and second words
        {
            if (counter == 0)
                move = input;
            if (counter == 1)
            {
                c = input;
                break;
            }
            counter++;
        }

        if (c == "" && (move == "play" || move == "discard"))
        { //card not given
            std::cout << "Rank not given" << std::endl;
            continue;
        }
        if (move == "play")
        {
            bool exitLoop = 0;
            if (c.length() != 2) //invalid input
            {
                std::cout << "Bad Input" << std::endl;
                continue;
            }
            std::string r = "";
            r = r + c[0];
            for (auto &valid : model->getCurLegalMove())
            {
                if (rankValue(valid->getRank()) == r && c[1] == valid->getSuit())
                { //valid card
                    controller->play(valid->getRank(), valid->getSuit());
                    exitLoop = true;
                    break;
                }
            }
            if (exitLoop)
                break;
            std::cout << "Not valid" << std::endl;
        }
        else if (move == "discard")
        {
            bool exitLoop = 0;
            if (model->getCurLegalMove().size() > 0)
            {
                std::cout << "Move doesnt exist" << std::endl;
                continue;
            }
            if (c.length() != 2) //input is not valid card
            {
                std::cout << "Bad Input" << std::endl;
                continue;
            }
            std::string r = "";
            r = r + c[0];
            for (auto &valid : model->curCards())
            {
                if (rankValue(valid->getRank()) == r && c[1] == valid->getSuit())
                { //valid card
                    controller->discard(valid->getRank(), valid->getSuit());
                    exitLoop = true;
                    break;
                }
            }
            if (exitLoop)
                break;
            std::cout << "not valid" << std::endl;
        }
        else if (move == "deck")
        {
            int i = 1;
            for (auto &c : model->viewDeck())
            {
                std::cout << rankValue(c.get()->getRank()) << c->getSuit() << " ";
                if (i % 13 == 0)
                    std::cout << std::endl;
                i++;
            }
        }
        else if (move == "ragequit")
        {
            model->replaceHuman(model->getTurn());
            ragequit = true;
            update();
            break;
        }
        else if (move == "quit")
        {
            break;
        }
    }
}
