#pragma once
#include <memory>

#include "Team.hpp"
#include "Schedule.hpp"
namespace daniel
{
    


class Leauge
{
public:
    Leauge(TeamRefGroup);
    ~Leauge();

    void simulateSeason();

    void printTopTeamsByWLR();
    TeamRefGroup getTopTeamsByWLR();
    void printTopTeamsByPR();
    TeamRefGroup getTopTeamsByPR();

    TeamRefGroup getTopTeams(int);
    int getTeamWithLongestWinStreak();
    int getTeamWithLongestLossStreak();
    int getNumOfTeamWithPositiveScoreRatio();
    float getHighestAvgPts();
    int getHighestMaxPts();

    TeamRefGroup getTeams() {return m_Teams;}
    Schedule getSchedule() {return schedule;}
private:
    TeamRefGroup m_Teams;
    Schedule schedule;
};
} // namespace daniel