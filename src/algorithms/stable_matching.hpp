#include <bits/stdc++.h>
#define MAX 10007
using namespace std;

class StableMatch
{

public:
    int men_count;
    int women_count;

    vector<vector<int>> men_preference;
    vector<vector<int>> women_preference;

    unordered_map<int, int> women_man_engagement_map;

    stack<int> free_men;
    vector<int> men_next_propose_pointer;

    bitset<MAX> is_women_free;
    vector<vector<int>> women_priority_for_men;

    StableMatch() {}

    StableMatch(int men_count, int women_count, vector<vector<int>> men_preference, vector<vector<int>> women_preference)
    {
        this->men_count = men_count;
        this->women_count = women_count;

        this->men_preference = men_preference;
        this->women_preference = women_preference;

        for (int i = 0; i < men_count; i++)
        {
            this->free_men.push(i);
            men_next_propose_pointer.push_back(0);
        }

        // this->is_women_free = {false};

        for (int woman = 0; woman < this->women_count; woman++)
        {

            vector<int> women_priority_vector{men_count, INT_MAX};

            for (int man = 0; man < this->men_count; man++)
            {
                women_priority_vector[this->women_preference[woman][man]] = man;
            }

            this->women_priority_for_men.push_back(women_priority_vector);
        }
    }

    void run()
    {

        while (!this->free_men.empty())
        {

            int current_man = this->free_men.top();
            this->free_men.pop();

            int next_propose_pointer = this->men_next_propose_pointer[current_man];
            while (next_propose_pointer < this->women_count)
            {

                int current_woman = this->men_preference[current_man][next_propose_pointer];

                if (this->is_women_free[current_woman])
                {
                    this->women_man_engagement_map[current_woman] = current_man;
                    this->is_women_free[current_woman] = false;
                    break;
                }
                else
                {
                    int man_engaged_to_woman = this->women_man_engagement_map[current_woman];
                    if (this->women_priority_for_men[current_woman][current_man] < this->women_priority_for_men[current_woman][man_engaged_to_woman])
                    {
                        this->women_man_engagement_map[current_woman] = current_man;
                        this->free_men.push(man_engaged_to_woman);
                        break;
                    }
                }

                next_propose_pointer++;
            }
        }
    }
};

void simulate_stable_matching()
{
    int men_count = 3;
    int women_count = 3;
    vector<vector<int>> men_priorities = {{0, 1, 2}, {0, 1, 2}, {2, 1, 0}};
    vector<vector<int>> women_priorities = {{0, 1, 2}, {1, 2, 0}, {1, 0, 2}};

    StableMatch sm(men_count, women_count, men_priorities, women_priorities);
    sm.run();

    cout << "Engagement Map: \n";

    for (pair<int, int> p : sm.women_man_engagement_map)
    {
        cout << p.first << " -> " << p.second << '\n';
    }
}