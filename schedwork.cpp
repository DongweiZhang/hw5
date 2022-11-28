

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool dfs(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int ith_day, int jth_people, vector<int>&numDays, int people_st) {
    int n = (int)avail.size();
    int k = (int)avail[0].size();
    if(ith_day >= n) {
        return true;
    }
    if(jth_people >= dailyNeed) {
        return dfs(avail, dailyNeed, maxShifts, sched, ith_day + 1, 0, numDays, 0);
    }
    if(people_st >= k) {
        return false;
    }
    int i = people_st;
    if(avail[ith_day][i] && numDays[i] < maxShifts) {
        numDays[i] += 1;
        sched[ith_day][jth_people] = i;
        // cout << ith_day << " " << jth_people << " " << i << endl;
        // if(ith_day == 0 && jth_people == 1 && i == 3) {
        //     for(auto o : numDays) {
        //         cout << o << " " ;
        //     }
        //     cout << endl;
        // }
        if(dfs(avail, dailyNeed, maxShifts, sched, ith_day, jth_people + 1, numDays, people_st + 1)) {
            return true;
        }
        numDays[i] -= 1;
        sched[ith_day][jth_people] = -1;
    }
    if(dfs(avail, dailyNeed, maxShifts, sched, ith_day, jth_people, numDays, people_st + 1)) {
        return true;
    }
    return false;
}

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int n = (int)avail.size();
    int k = (int)avail[0].size();
    sched = vector<vector<Worker_T>>(n, vector<Worker_T>(dailyNeed, 0));
    vector<int>numDays = vector<int>(k, 0);
    return dfs(avail, dailyNeed, maxShifts, sched, -1, k + 1, numDays, 0);
}

