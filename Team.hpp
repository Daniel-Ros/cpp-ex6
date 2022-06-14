#pragma once

#include <string>
#include <utility>
#include <memory>
#include <vector>

namespace daniel
{
struct Stats {
    int wins;
    int losses;
    int pointsDiff;
    int longestWinStreak;
    int longestLossStreak;
    int currenttWinStreak;
    int currentLossStreak;

    float avgPts;
    int maxPts;
    Stats()
            : wins{0}, losses{0}, pointsDiff{0}, longestLossStreak{0}, longestWinStreak{0},
              currenttWinStreak{0} , currentLossStreak{0}, avgPts{0},maxPts{0}
                      {

                      }
};

class Team {
public:
    Team(const std::string& name, float skill);

    ~Team() = default;

    bool operator==(const Team &other) const { return m_Name == other.m_Name && m_Skill == other.m_Skill; }

    void registerGames(int, int);

    float getSkill() const { return m_Skill; }

    const std::string &getName() const { return m_Name; }

    Stats getStats() const { return m_Stats; }

private:
    const std::string m_Name;
    float m_Skill;
    Stats m_Stats;
};


using TeamRef = std::shared_ptr<Team>;
using TeamRefGroup = std::vector<TeamRef>;

}