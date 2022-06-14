#include "Leauge.hpp"
#include <algorithm>
#include <iostream>

namespace daniel{
Leauge::Leauge(TeamRefGroup teams) : m_Teams{teams}, schedule{} {
    if(teams.size() > 20)
    {
        throw "to many teams";
    }
    while (m_Teams.size() < 20) {
        int i = m_Teams.size();
        bool available = false;
        while (!available) {
            available = true;
            std::for_each(m_Teams.begin(), m_Teams.end(),
                          [&](const TeamRef t) {
                              if (t->getName() == "Team" + std::to_string(i)) { available = false; }
                          });
        }
        float skill = std::rand() / double(RAND_MAX);
        m_Teams.push_back(std::make_shared<Team>("Team" + std::to_string(i),skill));
    }

    schedule.makeSchedule(m_Teams);
}

Leauge::~Leauge() {

}

void Leauge::simulateSeason() {
    for (auto &round: schedule) {
        for (auto &game: round) {
            game.play();
        }
    }
}

void Leauge::printTopTeamsByWLR() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().wins > b->getStats().wins;
    });
    for (auto &t: m_Teams) {
        float precent = t->getStats().losses == 0 ? m_Teams.size() - 1 : ((float) t->getStats().wins /
                                                                          (float) t->getStats().losses);
        std::cout << t->getName() << " " << precent << "\n";
    }
    std::cout << std::endl;
}

void Leauge::printTopTeamsByPR() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().pointsDiff > b->getStats().pointsDiff;
    });
    for (auto &t: m_Teams) {
        std::cout << t->getName() << " " << t->getStats().pointsDiff << "\n";
    }
    std::cout << std::endl;
}

TeamRefGroup Leauge::getTopTeamsByWLR() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().wins > b->getStats().wins;
    });
    std::cout << std::endl;

    return m_Teams;
}

TeamRefGroup Leauge::getTopTeamsByPR() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().pointsDiff > b->getStats().pointsDiff;
    });
    std::cout << std::endl;

    return m_Teams;
}

TeamRefGroup Leauge::getTopTeams(int numOfTeams) {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().pointsDiff > b->getStats().pointsDiff;
    });

    std::vector<std::shared_ptr<Team>> ret(m_Teams.begin(), m_Teams.begin() + numOfTeams);
    return ret;
}

int Leauge::getTeamWithLongestWinStreak() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().longestWinStreak > b->getStats().longestWinStreak;
    });
    return m_Teams.at(0)->getStats().longestWinStreak;
}

int Leauge::getTeamWithLongestLossStreak() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().longestLossStreak > b->getStats().longestLossStreak;
    });
    return m_Teams.at(0)->getStats().longestLossStreak;;
}

int Leauge::getNumOfTeamWithPositiveScoreRatio() {
    int ret = 0;
    for (auto &t: m_Teams) {
        if (t->getStats().pointsDiff > 0) {
            ret++;
        }
    }
    return ret;
}

float Leauge::getHighestAvgPts() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().avgPts > b->getStats().avgPts;
    });
    return m_Teams.at(0)->getStats().avgPts;;
}

int Leauge::getHighestMaxPts() {
    std::stable_sort(m_Teams.begin(), m_Teams.end(), [](const std::shared_ptr<Team> &a, const std::shared_ptr<Team> &b) {
        return a->getStats().maxPts > b->getStats().maxPts;
    });
    return m_Teams.at(0)->getStats().maxPts;;
}
}