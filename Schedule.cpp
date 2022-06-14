#include "Schedule.hpp"

#include <array>
#include <algorithm>
#include <cmath>

namespace daniel
{


Schedule::Schedule()
{

}

Schedule::~Schedule()
{

}

void Schedule::makeSchedule(TeamRefGroup teams) {
    std::vector<int> permutation(teams.size());
    int i = 0;
    std::for_each(permutation.begin(),permutation.end(),[&](int& x){ x = i++;});

    int halfPoint = std::floor(teams.size() / 2);

    for(i = 0; i < teams.size() - 1; i++)
    {
        Round round;
        for(int j = 0; j < halfPoint; j++)
        {
            // place both configurations in the round (T1 as home vs T2 as guest and T1 as guest and T2 as home)
            round.games.emplace_back(*(teams.at(permutation.at(j))),*(teams.at(permutation.at(teams.size() - 1- j))));
            round.games.emplace_back(*(teams.at(permutation.at(teams.size() - 1- j))),*(teams.at(permutation.at(j))));
        }

        rounds.push_back(round);

        int last = permutation.at(permutation.size() - 1);
        for(int j = permutation.size() - 1; j >= 2 ; j--)
        {
            permutation.at(j) = permutation.at(j-1);
        }
        permutation.at(1) = last;
    }
}
    
} // namespace daniel