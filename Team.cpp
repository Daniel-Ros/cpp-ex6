#include "Team.hpp"


namespace daniel
{


void Team::registerGames(int myScore, int opScore)
{
    if(myScore < 0 || opScore <0 ){
        throw "score should be positve";
    }
    if( myScore - opScore > 0)
    {
        m_Stats.wins++;
        m_Stats.currenttWinStreak++;
        m_Stats.currentLossStreak = 0;

        if(m_Stats.currenttWinStreak > m_Stats.longestWinStreak)
        {
            m_Stats.longestWinStreak = m_Stats.currenttWinStreak;
        }
    }
    else
    {
        m_Stats.losses++;
        m_Stats.currentLossStreak++;
        m_Stats.currenttWinStreak = 0;

        if(m_Stats.currentLossStreak > m_Stats.longestLossStreak)
        {
            m_Stats.longestLossStreak = m_Stats.currentLossStreak;
        }
    }
    m_Stats.pointsDiff += myScore - opScore;
    m_Stats.avgPts += (float)myScore / 38;

    if(m_Stats.maxPts < myScore){
        m_Stats.maxPts = myScore;
    }
}

Team::Team(const std::string& name, float skill) : m_Name{name}, m_Skill{skill} {
    if(name.empty())
    {
        throw "name could not be empty";
    }
    if (skill != std::max(std::min(1.0f,m_Skill),0.0f))
    {
        throw "skill should be betwee n 0 and 1 ";
    }
}

    
} // namespace daniel