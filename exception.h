#ifndef EXPECTIONS_H
#define EXPECTIONS_H

#include <string>

//define expections

struct RoundOver
{
    std::string message; // details of the problem
    RoundOver(std::string message);
};

#endif
