//============================================================================
// Name        : SmallestKElements.cpp
// Author      : Yael Cohen
// Version     : 0
// Description : Solution to question 17.14 Smallest K   in O(N) time, O(1) additional space
//				 Design an algorithm to find the smallest K numbers in an array
//============================================================================

#include <iostream>
#include <vector>
#include <stdlib.h>

#include <algorithm>    // std::sort required for test case #8

using namespace std;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test6b();
void test7();
void test8();
void test9();



void printVec(vector<int>& vec)
{
	for (unsigned int i =0; i < vec.size(); i++)
		cout <<vec[i]<<" ";
	cout <<endl;
}

/*
 * method swp
 * swaps between integers a and b using bit manipulation
 */
void swp(int &a, int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}

/*
 * method partition
 * same as quicksort partioning, K is used here as a 'random' pivot, any other pivot (eg. random, median ) can work instead
 */
int partition(vector<int>& A, int lo, int hi,  int k)
{
    int pivot = A[k];
    int i = lo;
    int j = hi;
    while(i <j)
    {
    	while( A[i] < pivot )
    		i++;
    	while( A[j] > pivot )
            j--;

        if ( A[i] == A[j] )	// added to support duplicate values
                i++;
        else if ( i < j )
        {
        	swp(A[i], A[j]);
        }
    }
        return j;
}

/*
 * method quicksortKPartitioned (Recursive)
 * @input:
 * A - array of integers
 * lo - the lowest index to begin with
 * hi - the highest index to end with
 * k - integer
 * @the method runs quicksort algorithm until the Kth element is in place (hence the k smallest elements are in the left) and quiit
 */
void quicksortKPartitioned(vector<int>& A, int lo, int hi,  int k)
    {
		if (lo < hi)
		{
			int p = partition(A, lo, hi, k);
			if (p == k)
				return;
			if (p < k)
				quicksortKPartitioned(A, p + 1, hi, k);
			else if (p > k)
				quicksortKPartitioned(A, lo, p-1, k);
		}
    }

/*
 *  @Input:
 *  	numVec:			 array of integers
 * 		k:				 an integer where k <= size of the array
 *  	o_smallestKVec:  output vector of reserved size k
 *  @Output:
 *  	for success: returns true and o_smallestKVec populated with the smallest k elements of array numVec
 *  	for failure: returns false
 *  @Runtime:
 *  	on each recursive call it process only half of the remaining array, on average: n+ 1/2n + 1/4n +... = until the k'th element is in place = O(n).
 *  @Additional space:
 *  	O(1)
 *  @General description: based on quicksort partitioning
 */
bool findSmallestKElements(vector<int>& numVec,  int k, vector<int>& o_smallestKVec)
{
	 int len = numVec.size();
	if (k > len || k <= 0)
	{
		cerr <<"input is not valid. k: " <<k << ". The input array length is: "<<len <<endl;
		return false;
	}
	quicksortKPartitioned(numVec, 0, len-1, k);

	for ( int i = 0; i < k ; i++)
	{
		o_smallestKVec.push_back(numVec[i]);
	}
	return true;

}

int main() {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6b();
	test7();
	test8();
	test8();

	//	test9();
	return 0;
}



//   ----------------   TEST CASES
void test1()
{
	cout <<"Running test1, expected result is true, output array contains all the numbers in set {15,10,5,13}" <<endl;
	int myints[] = {30,15,10,5,13,25};
	int k = 4;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test1" <<endl;
	cout <<" ------------ " <<endl;

}
void test1b()
{
	cout <<"Running test1, expected result is true, output array contains all the numbers in set {15,10,5,13}" <<endl;
	int myints[] = {30,15,10,5,13,25};
	int k = 4;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test1" <<endl;
	cout <<" ------------ " <<endl;

}
// normal flow k = length of array
void test2()
{
	cout <<"Running test2, expected result is true, output array contains all the numbers in set {30,15,10,5,13,25}" <<endl;
	int myints[] = {30,15,10,5,13,25};
	int k = 6;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test2" <<endl;
	cout <<" ------------ " <<endl;

}

//basic test - normal flow k = 1
void test3()
{
	cout <<"Running test3, expected result is true, output array contains the smallest number: 5" <<endl;
	int myints[] = {30,15,10,5,13,25};
	int k = 1;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test3" <<endl;
	cout <<" ------------ " <<endl;

}

// invalid input k > length
void test4()
{
	cout <<"Running test4, (Error scenario k > array length) expected result is 0" <<endl;

	int myints[] = {30,15,10,5,13,25};
	int k = 7;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test4" <<endl;
	cout <<" ------------ " <<endl;

}

// invalid input k <=0
void test5()
{
	cout <<"Running test5, (Error scenario k =0) expected result is 0" <<endl;

	int myints[] = {30,15,10,5,13,25};
	int k = 0;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test5" <<endl;
	cout <<" ------------ " <<endl;

}

// special scenario - duplicate elements
void test6()
{
	cout <<"Running test6, expected result is true, output array contains all the numbers in set {30,15,10,5,13,25,30}" <<endl;

	int myints[] = {30,15,10,5,13,25, 30,30};
	int k = 7;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test6" <<endl;
	cout <<" ------------ " <<endl;

}
void test6b()
{
	cout <<"Running test6b, expected result is true, output array contains all the numbers in set {15,10,5,13,25}" <<endl;

	int myints[] = {30,15,10,5,13,25, 30,30};
	int k = 5;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test6b" <<endl;
	cout <<" ------------ " <<endl;

}

//includes 0 and negative values
void test7()
{
	cout <<"Running test7, expected result is true, output array contains all the numbers in set {-3, -2, -1, 0, 1 }" <<endl;
	int myints[] = {-3, -2, -1, 0, 1, 2, 3};
	int k = 5;
	vector<int> vec (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test7" <<endl;
	cout <<" ------------ " <<endl;

}

template <typename T>  // T comparable
bool vectorsEqual(vector<T> &vec1, vector<T> &vec2)
{
	if (vec1.size() != vec2.size())
		return false;
	for(int i =0; i < vec1.size(); i++)
	{
		if (vec1[i] != vec2[i])
		{
	//		cout <<" element "<< i <<" is different: " << vec1[i] <<" != " <<vec2[i]<<endl;
			return false;
		}
	}
	return true;
}

//O(N(LOGN)
bool smallestKLessEfficient(vector<int> &vec, int k, vector<int> &o_smallestK)
{
	sort(vec.begin(), vec.end());
	for (int i =0; i < k; i ++)
		o_smallestK.push_back(vec[i]);
	return true;

}

//test big array
void test8()
{
	vector<int>* vec = new vector<int>();
	vec->reserve(1000000);
	for (int i =0 ; i < 1000000; i++)
	{
		vec->push_back( rand());  //will generate same set each run but it's good enough for this test purpose, [tradeoff: srand(time(0)) is too slow for massive generation]
	}
	int k =553;
	vector<int> smallestK;
	smallestK.reserve(k);
	 findSmallestKElements(*vec, k, smallestK);
//	cout <<"Result of findSmallestKElements: " << findSmallestKElements(*vec, k, smallestK) <<endl;
	sort(smallestK.begin(), smallestK.end());
	vector<int> smallestK2;
	smallestK2.reserve(k);
	smallestKLessEfficient(*vec, k, smallestK2);
	if( vectorsEqual(smallestK, smallestK2))
		cout<<"Test8 Passed Successfully!" <<endl;
	else
		cout <<"Test8 Failed!" <<endl;
	printVec(smallestK);
	delete vec;
	cout <<"End of test8" <<endl;
	cout <<" ------------ " <<endl;

}


//manual test
void test9()
{
	vector<int> vec;
	cout <<"Please enter numbers to the array:  (To finish type 9999)" <<endl;
	int n, k;
	cin >> n;
	while (n != 9999 )
	{
		vec.push_back(n);
		cin >> n;
	}
	cout <<"\nPlease enter k:"<<endl;
	cin >>k;
	vector<int> smallestK;
	smallestK.reserve(k);
	cout <<"Result of findSmallestKElements: " << findSmallestKElements(vec, k, smallestK) <<endl;
	for (unsigned int i =0; i < smallestK.size(); i++)
	{
		cout <<smallestK[i] <<" ";
	}
	cout <<endl;
	cout <<"End of test9" <<endl;
	cout <<" ------------ " <<endl;
}

