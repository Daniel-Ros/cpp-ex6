/**
 * AUTHOR: Daniel
 */

#include "doctest.h"

#include "Team.hpp"
#include "Game.hpp"
#include "Schedule.hpp"
#include "Leauge.hpp"
#include <algorithm>

using namespace daniel;

TEST_CASE("Team"){
    SUBCASE("Good Team creation"){
        CHECK_NOTHROW(Team("Name", 0.1));
    }

    SUBCASE("Bad Team creation"){
        CHECK_THROWS(Team("Name", 1.5));
        CHECK_THROWS(Team("Name", -1.0));
        CHECK_THROWS(Team("", -1.0));
    }

    SUBCASE("Register game"){
        Team a("a",1.0);
        CHECK_NOTHROW(a.registerGames(70,70));
        CHECK_THROWS(a.registerGames(70,-10));
        CHECK_THROWS(a.registerGames(-10,70));
    }

    SUBCASE("Team stats"){
        SUBCASE("Points ratio"){
            Team a("a",1.0);
            for(int i = 0; i < 5; i++){
                a.registerGames(15,10);
            }
            CHECK_EQ(a.getStats().pointsDiff, 25);
        }

        SUBCASE("wins and losses"){
            Team a("a",1.0);
            for(int i = 0; i < 5; i++){
                a.registerGames(15,10);
                a.registerGames(10,15);
            }
            CHECK_EQ(a.getStats().wins, 5);
            CHECK_EQ(a.getStats().losses, 5);
        }

        SUBCASE("wins and losses streak"){
            Team a("a",1.0);
            for(int i = 0; i < 5; i++){
                a.registerGames(15,10);
                a.registerGames(10,15);
            }
            CHECK_EQ(a.getStats().longestWinStreak, 1);
            CHECK_EQ(a.getStats().longestLossStreak, 1);

            for(int i = 0; i < 5; i++){
                a.registerGames(15,10);
            }
            CHECK_EQ(a.getStats().longestWinStreak, 5);
            CHECK_EQ(a.getStats().longestLossStreak, 1);

            for(int i = 0; i < 5; i++){
                a.registerGames(10,15);
            }
            CHECK_EQ(a.getStats().longestWinStreak, 5);
            CHECK_EQ(a.getStats().longestLossStreak, 5);
        }
    }
}

TEST_CASE("Game"){
    SUBCASE("Good Game creation"){
        Team a("a",1.0);
        Team b("b",0.0);

        CHECK_NOTHROW(Game g(a,b));
    }

    // No need to handle bad parameter in the creation phase as they will be handled in compile time

    SUBCASE("play a game"){
        Team a("a",1.0);
        Team b("b",0.0);

        Game g(a,b);

        CHECK_NOTHROW(g.play());

        CHECK(((g.winner() == a) || (g.winner() == b)));
        if(g.winner() == a)
        {
            CHECK_GE(a.getStats().pointsDiff,b.getStats().pointsDiff);
        }
        else
        {
            CHECK_GE(b.getStats().pointsDiff,a.getStats().pointsDiff);
        }
    }
}

TEST_CASE("Schedule"){
    std::vector<std::shared_ptr<Team>> teams;
    teams.emplace_back(std::make_shared<Team>(Team("Golden State Warriors", 1)));
    teams.emplace_back(std::make_shared<Team>(Team("Boston Celtics", 0.4)));
    teams.emplace_back(std::make_shared<Team>(Team("Brooklyn Nets", 0.5)));
    teams.emplace_back(std::make_shared<Team>(Team("Denver Nuggets", 0.3)));
    teams.emplace_back(std::make_shared<Team>(Team("Philadelphia 76ers", 0.4)));
    teams.emplace_back(std::make_shared<Team>(Team("Minnesota Timberwolves", 0.5)));
    teams.emplace_back(std::make_shared<Team>(Team("Chicago Bulls", 0.3)));
    teams.emplace_back(std::make_shared<Team>(Team("Portland Trail Blazers", 0.2)));
    teams.emplace_back(std::make_shared<Team>(Team("LA Clippers", 0.5)));
    teams.emplace_back(std::make_shared<Team>(Team("Los Angeles Lakers", 1)));
    teams.emplace_back(std::make_shared<Team>(Team("Milwaukee Bucks", 0.7)));
    teams.emplace_back(std::make_shared<Team>(Team("Atlanta Hawks", 0.3)));
    teams.emplace_back(std::make_shared<Team>(Team("Charlotte Hornets", 0.2)));
    teams.emplace_back(std::make_shared<Team>(Team("Miami Heat", 0.6)));
    teams.emplace_back(std::make_shared<Team>(Team("Phoenix Suns", 0.8)));
    teams.emplace_back(std::make_shared<Team>(Team("Dallas Mavericks", 0.6)));
    teams.emplace_back(std::make_shared<Team>(Team("Memphis Grizzlies", 0.5)));
    teams.emplace_back(std::make_shared<Team>(Team("Utah Jazz", 0.3)));
    teams.emplace_back(std::make_shared<Team>(Team("Washington Wizards", 0)));
    teams.emplace_back(std::make_shared<Team>(Team("Oklahoma City Thunder", 0.1)));

    Schedule s;
    CHECK_NOTHROW(s.makeSchedule(teams));
    int cumsum = 0;
    for (const auto &round: s)
    {
        cumsum += round.games.size();
    }
    CHECK_EQ(cumsum,380);
}


TEST_CASE("League"){
    SUBCASE("too much teams"){
        TeamRefGroup teams;
        teams.emplace_back(std::make_shared<Team>(Team("Golden State Warriors", 1)));
        teams.emplace_back(std::make_shared<Team>(Team("Boston Celtics", 0.4)));
        teams.emplace_back(std::make_shared<Team>(Team("Brooklyn Nets", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Denver Nuggets", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Philadelphia 76ers", 0.4)));
        teams.emplace_back(std::make_shared<Team>(Team("Minnesota Timberwolves", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Chicago Bulls", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Portland Trail Blazers", 0.2)));
        teams.emplace_back(std::make_shared<Team>(Team("LA Clippers", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Los Angeles Lakers", 1)));
        teams.emplace_back(std::make_shared<Team>(Team("Milwaukee Bucks", 0.7)));
        teams.emplace_back(std::make_shared<Team>(Team("Atlanta Hawks", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Charlotte Hornets", 0.2)));
        teams.emplace_back(std::make_shared<Team>(Team("Miami Heat", 0.6)));
        teams.emplace_back(std::make_shared<Team>(Team("Phoenix Suns", 0.8)));
        teams.emplace_back(std::make_shared<Team>(Team("Dallas Mavericks", 0.6)));
        teams.emplace_back(std::make_shared<Team>(Team("Memphis Grizzlies", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Utah Jazz", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Washington Wizards", 0)));
        teams.emplace_back(std::make_shared<Team>(Team("Oklahoma City Thunder", 0.1)));
        teams.emplace_back(std::make_shared<Team>(Team("Bad team", 0.1)));

        CHECK_THROWS(Leauge(teams));
    }

    SUBCASE("Teams generated"){
        TeamRefGroup teams;
        Leauge l(teams);
        int i = 0;
        for(const auto& team : l.getTeams())
        {
            CHECK_EQ(team->getName(),"Team" + std::to_string(i++));
        }
    }

    SUBCASE("Luague Played"){
        TeamRefGroup teams;
        teams.emplace_back(std::make_shared<Team>(Team("Golden State Warriors", 1)));
        teams.emplace_back(std::make_shared<Team>(Team("Boston Celtics", 0.4)));
        teams.emplace_back(std::make_shared<Team>(Team("Brooklyn Nets", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Denver Nuggets", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Philadelphia 76ers", 0.4)));
        teams.emplace_back(std::make_shared<Team>(Team("Minnesota Timberwolves", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Chicago Bulls", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Portland Trail Blazers", 0.2)));
        teams.emplace_back(std::make_shared<Team>(Team("LA Clippers", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Los Angeles Lakers", 1)));
        teams.emplace_back(std::make_shared<Team>(Team("Milwaukee Bucks", 0.7)));
        teams.emplace_back(std::make_shared<Team>(Team("Atlanta Hawks", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Charlotte Hornets", 0.2)));
        teams.emplace_back(std::make_shared<Team>(Team("Miami Heat", 0.6)));
        teams.emplace_back(std::make_shared<Team>(Team("Phoenix Suns", 0.8)));
        teams.emplace_back(std::make_shared<Team>(Team("Dallas Mavericks", 0.6)));
        teams.emplace_back(std::make_shared<Team>(Team("Memphis Grizzlies", 0.5)));
        teams.emplace_back(std::make_shared<Team>(Team("Utah Jazz", 0.3)));
        teams.emplace_back(std::make_shared<Team>(Team("Washington Wizards", 0)));
        teams.emplace_back(std::make_shared<Team>(Team("Oklahoma City Thunder", 0.1)));

        Leauge l(teams);
        l.simulateSeason();

        for(const auto& round: l.getSchedule())
        {
            for(const auto& game:round.games){
                CHECK_NOTHROW(game.winner());
            }
        }
    }
}
