

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
bool isValid(int row, int col, DailySchedule& sched, const size_t dailyNeed, const size_t maxShifts);
bool scheduleHelper(unsigned int row, unsigned int col, DailySchedule& sched, const AvailabilityMatrix& avail,const size_t dailyNeed, const size_t maxShifts);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    //avail is a vector<vector<bool>>
    //sched is a vector<vector<int>>
    //dailyNeed is 2 and maxshifts is 2
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
    //Intialize the uninitalized sched array 
    unsigned int numRows = avail.size();
    unsigned int numCols = dailyNeed;
    std::vector<Worker_T> schedVect;
    for(unsigned int i = 0; i < numRows; i++)
    {
        for(unsigned int j = 0; j < numCols; j++)
        {
            //place -1 as a placeholder for now 
            schedVect.push_back( INVALID_ID);
        }
        sched.push_back(schedVect);
    }
    //By the end of this, the sched vector<vector<int>> should look like this

    /*  {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
    */
   //now pass the sched, avail and other necessary elements into the helper function 
   unsigned int row = 0;
   unsigned int col = 0;
   bool result = scheduleHelper(row, col, sched, avail, dailyNeed, maxShifts);

  if(result)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool scheduleHelper(unsigned int row, unsigned int col, DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts)
{
//iterate through the entire schedule vector of vectors
//(the days are individual vectors that store nurses on schedule) 
//and check to see if whether or not that nurse can be stored 
//in that particular index or not, similar to that of the Sudoku Lab
//int n = avail.size();
unsigned int k = dailyNeed;
Worker_T workers = avail[0].size();
//Worker_T worker;
for(unsigned int i = 0; i < workers; i++)
 {
		if(isValid(row,col, sched, dailyNeed, maxShifts))
		{
			sched[row][col] = i;
			if(col > k-1)
				{
					col = 0;
					//goes to the next row 
					if(scheduleHelper(row+1, col, sched, avail, dailyNeed, maxShifts))
					{
						return true;
					}
					else
					{
						sched[row][col]=INVALID_ID;
					}
				}
				else 
				{
					//goes to the next column 
					if(scheduleHelper(row, col + 1, sched, avail, dailyNeed, maxShifts))
					{
						return true;
					}
					else
					{
						sched[row][col]=INVALID_ID;
					}
				}
		}
 }
return false;
}
bool isValid(int row, int col, DailySchedule& sched, const size_t dailyNeed, const size_t maxShifts)
{
    int daysNeed = dailyNeed;
    int week = sched.size();
    //Grab the worker ID and see if whether or not
    //the position is valid as well if the nurse has
    //been scheduled already and if the amount of days 
    // necessary are already filled 
    Worker_T worker = sched[row][col];

    size_t shifts = 0;

    for(int i = 0; i < week; i++)
    {
        for(int j = 0; j < daysNeed; j++)
        {
            if(sched[i][j] == worker)
            {
                shifts++;
            }
        }
    }
    if(shifts > maxShifts)
    {
        return false;
    }
    else
    {
        return true;
    }
}


