#pragma once
#include <memory>
#include <vector>
#include "Game.hpp"

namespace daniel
{
    


struct Round
{
    std::vector<Game> games;

    std::vector<Game>::iterator begin(){return games.begin();}
    std::vector<Game>::iterator end(){return games.end();}
};

class Schedule
{
public:
    Schedule();
    ~Schedule();

    void makeSchedule(TeamRefGroup);

    std::vector<Round>::iterator begin(){return rounds.begin();}
    std::vector<Round>::iterator end(){return rounds.end();}

private:
    std::vector<Round> rounds;
};
} // namespace daniel