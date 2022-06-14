#include "Game.hpp"
#include <random>

#include <iostream>

namespace daniel
{
void Game::play()
{
    if(!hasCompleted)
    {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<> normalDistributionRand{75,8.0};

        hScore = std::round(normalDistributionRand(gen)) + m_HomeTeam.getSkill() * 10;
        gScore = std::round(normalDistributionRand(gen)) + m_GuestTeam.getSkill() * 10;
        m_HomeTeam.registerGames(hScore,gScore);
        m_GuestTeam.registerGames(gScore,hScore);
        if(hScore > gScore)
        {
            m_Winner = &m_HomeTeam;
        }   
        else
        {
            m_Winner = &m_GuestTeam;
        }
    }
    hasCompleted = true;
}

Team & Game::winner() const {
    if(!hasCompleted)
    {
        throw "Game has not been played yet";
    }
    return *(m_Winner);
}
    
} // namespace daniel