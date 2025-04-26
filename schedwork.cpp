#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helperfunct(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsworked,
    size_t day,
    size_t numworker
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    // save the number of workers and days
    size_t workers = avail[0].size();
    size_t days = avail.size();

    // initialize schedule
    sched = DailySchedule(days, vector<Worker_T>());

    // initialize shiftsworked to 0
    vector<size_t>shiftsworked(workers, 0);

    // return the helper functions boolean
    return helperfunct(avail, dailyNeed, maxShifts, sched, shiftsworked, 0, 0);
}

bool helperfunct(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsworked,
    size_t day,
    size_t numworker
)
{
    // base case for if all the days are scheduled
    if(day == avail.size()){
        return true;
    }

    // recursive call for next day if the day is full
    if(dailyNeed == numworker){
        return helperfunct(avail, dailyNeed, maxShifts, sched, shiftsworked, day+1, 0);
    }

    // loop through all of the workers
    for(size_t w = 0; w < avail[0].size(); ++w){
        // check if the worker is still available for the day
        if(avail[day][w] == true){
            bool scheduled = false;
        
            // now workers assigned for the day in schedule
            for(size_t a = 0; a < sched[day].size(); ++a){
                // see if the worker is on schedule
                if(sched[day][a] == w){
                    // update this if so and break
                    scheduled = true;
                    break;
                }
            }

            // now check further things if the worker still isnt assigned
            if(scheduled == false){
                // make sure the worker hasn't worked all of his shifts
                if(maxShifts > shiftsworked[w]){
                    // assign the worker to today
                    sched[day].push_back(w);
                    // increment shiftsworked
                    shiftsworked[w]++;
                

                    // recursive call
                    if(helperfunct(avail, dailyNeed, maxShifts, sched, shiftsworked, day, numworker+1)){
                        return true;
                    }

                    // backtrack by decrementing shifts worked
                    shiftsworked[w]--;
                    // backtrack by removing the worker from schedule for the day
                    sched[day].pop_back(); 
                } 
            }
        }   
    }
    // no worker works
    return false;
}

