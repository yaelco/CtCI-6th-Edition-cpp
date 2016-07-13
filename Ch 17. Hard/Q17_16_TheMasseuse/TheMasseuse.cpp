/*
 * TheMasseuse.cpp
 *
 *  Created on: July 13  2016
 *  Author: Yael Cohen
 *  Description:
 *  A popular masseuse receives a sequence of back-to-back appointment requests and is debating which ones to accept.
 *  she needs a 15-minute break between appointments and therefore she can't accept any adjacent requests.
 *  Given a sequence of appointments (all multiples of 15 minutes, none overlap and none can be moved)
 *  find the optimal (highest total booked minutes) set the masseuse can honor.
 *  Return the number of minutes.
 */

#include <vector>
#include <iostream>
using namespace std;
typedef unsigned int uint;

/*
 * O(N) time, O(1) additional space
 */
uint maxAppointmentsDuration(vector<uint> & b2bApts)
{
	uint maxDuration =0;
	uint preStepMaxDuration = 0;
	uint PrePreStepMaxDuration =0;
	for (int i =b2bApts.size()-1; i >= 0; i--)
	{
		maxDuration = max (PrePreStepMaxDuration+b2bApts[i], preStepMaxDuration) ;
		PrePreStepMaxDuration = preStepMaxDuration;
		preStepMaxDuration = maxDuration;
	}
	return maxDuration;
}


void test1 ()
{
	uint array[] = {30, 15, 60, 75, 45, 15,15,45};
		vector<uint> b2bApts(array, array+ sizeof(array)/sizeof(uint));
		cout <<" max duration is: " << maxAppointmentsDuration(b2bApts) << endl;
}

void test2()
{
	uint array[] = {75, 105, 120, 75, 90, 135};
		vector<uint> b2bApts(array, array+ sizeof(array)/sizeof(uint));
		cout <<" max duration is: " << maxAppointmentsDuration(b2bApts) << endl;
}
int main()
{
	test1();
	test2();
	return 0;
}



