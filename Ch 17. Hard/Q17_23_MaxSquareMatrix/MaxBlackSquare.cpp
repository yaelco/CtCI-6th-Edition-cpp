/*
 * MaxBlackSquare.cpp
 *
 *  Created on: July 19 2016
 *      Author: Yael Cohen
 *  Description: Solution in O(N^2) to question 17.23 Max Square Matrix: Imagine you have a square matrix, where each cell (pixel) is either black or white.
 *  Design an algorithm to find the maximum subsquare such that all four borders are filled with black pixels.
 */
#include <iostream>

using namespace std;

#define SIZE 4

struct Result
{
	int SQupperLeftRow;
	int SQupperLeftCol;
	int size;

	Result(int x, int y, int i_size)
	{
		SQupperLeftRow=x;
		SQupperLeftCol=y;
		size =i_size;
	}
};
struct CountBlacks
{
	int down;
	int right;
};

/*
 * Method countDownAndRight
 * @input:
 * 		bwMatrix: a square matrix of char including 'w' for white square or 'b' for black.
 * 		count: a matrix of struct CountBlacks, of the same size of bwMatrix. this will be populated by this method
 *		size: the size of the square side
 * @Description: for each pixel of bwMatrix, the method populates in count the number of adjacent black pixels
 * from current pixel and right (int count[i][j].right) and the number of black pixels from this pixel in down (in count[i][j].down).
 * @Assumption: bwMatrix is populated with 'b' or 'w' only. in case any other character is encountered, the pixel will be treated as white
 * @RunTime: O(N^2)
 * @Additional space: O(1)
 */
void countDownAndRight(char bwMatrix[SIZE][SIZE], CountBlacks count[SIZE][SIZE], int size)
{
	for (int i = size-1; i >= 0; i--)
	{
		for (int j = size-1; j >= 0; j--)
		{
			if ('b' == bwMatrix[i][j])
			{
				count[i][j].down = 1;
				count[i][j].right = 1;
				count[i][j].down +=  (i+1 <size)? count[i+1][j].down : 0;
				count[i][j].right += (j+1< size)? count[i][j+1].right : 0;
			}
			else
			{
				count[i][j].down =0;
				count[i][j].right =0;
				if ('w' != bwMatrix[i][j])
					cerr <<"Invalid pixel ("<<i<<","<<j<<") with value: " << bwMatrix[i][j] <<". Treating as white." <<endl;
			}

		}
	}

}


//returns the top left corner of the maximum square
//use memoization
/*
 * Method maxBlackSquare
 * @Input: bwMatrix: a square matrix of char including 'w' for white square or 'b' for black.
 * 		   size: the size of the square side
 * @Output: struct Result includes the size and the coordinates of the maximum black sub-square of maxBlackSquare
 * @Description: the method finds the maximum subsquare such that all four borders are filled with black pixels
 * @Assumption: the minimum size of the side of the output sub-square is 2
 * @Runtime: O(N^2). additional space: O(N^2)- countMat
 */
Result maxBlackSquare(char bwMatrix[SIZE][SIZE], int size)
{
	Result res(-1,-1,0);
	if (1 >= size)
		return res;
	CountBlacks countMat[SIZE][SIZE];
	countDownAndRight(bwMatrix, countMat, size);
	int maxSize =0;

//	int countLoop =0;
	for (int i =0; i < size-1; i ++)
		for (int j =0; j < size-1; j++)
		{
			if (size -i <= maxSize)
				break;
			if(size -j <= maxSize)
				continue;
		//	countLoop++;
			int potentialSqSize = min(countMat[i][j].right, countMat[i][j].down);
			if ( maxSize < potentialSqSize &&  potentialSqSize > 1 && potentialSqSize <= countMat[i+potentialSqSize-1][j].right && potentialSqSize <= countMat[i][j+potentialSqSize-1].down )
			{
				maxSize =potentialSqSize;
				res.size = potentialSqSize;
				res.SQupperLeftRow = i;
				res.SQupperLeftCol = j;
			}
		}
//	cout <<"countLoop:" <<countLoop<<endl;
	return res;
}

/*
 * Test bestCase_MBS
 * all black
 * expected runtime: O(1) because after the first loop there can't be a bigger sub-square than SIZE  (countLoop:1)
 */
void bestCase_MBS()
{
	char matrix[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				matrix[i][j] ='b';
			}
		}
	Result res = maxBlackSquare(matrix,SIZE);
	if (res.size != 0)
		cout <<"The max sub square is the "<<res.size<<"x"<<res.size<<" square that starts on pixel: (" << res.SQupperLeftRow <<"," <<res.SQupperLeftCol << ")" <<endl;
	else
		cout <<"No black sub square was found of size > 1"<<endl;
}
/*
 * Test worstCase_MBS
 * all white
 * expected runtime: O((n-1)^2) - the whole matrix should be scan (except the last row and column because we assume the minimum subsquare side is 2  (countLoop:(n-1)^2)
 */
void worstCase_MBS()
{
	char matrix[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				matrix[i][j] ='w';
			}
		}
	Result res = maxBlackSquare(matrix,SIZE);
	if (res.size != 0)
		cout <<"The max sub square is the "<<res.size<<"x"<<res.size<<" square that starts on pixel: (" << res.SQupperLeftRow <<"," <<res.SQupperLeftCol << ")" <<endl;
	else
		cout <<"No black sub square was found of size > 1"<<endl;
}
void basicCase_MBS()
{
	char matrix[SIZE][SIZE] = {{'w','b','w','w'}, {'b','b','w','w'}, {'b','b','w','b'}, {'b','b','w','b'} };
		Result res = maxBlackSquare(matrix,SIZE);
		if (res.size != 0)
			cout <<"The max sub square is the "<<res.size<<"x"<<res.size<<" square that starts on pixel: (" << res.SQupperLeftRow <<"," <<res.SQupperLeftCol << ")" <<endl;
		else
			cout <<"No black sub square was found of size > 1"<<endl;}
int main()
{
	basicCase_MBS();
	bestCase_MBS();
	worstCase_MBS();
}
