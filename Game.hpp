#pragma once
#include "Team.hpp"
namespace daniel
{
class Game
{
public:
    Game(Team& a, Team& b) : m_HomeTeam{a}, m_GuestTeam{b} , m_Winner{nullptr}, hasCompleted{false} {};
    ~Game() = default;

    void play();
    Team & winner() const;
private:
    Team& m_HomeTeam;
    Team& m_GuestTeam;

    Team* m_Winner;
    int hScore;
    int gScore;

    bool hasCompleted;
};
}