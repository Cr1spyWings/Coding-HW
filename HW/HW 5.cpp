/*
Reads in a matrix from a binary file and determines RST and EC's.

Dan Ross
   Original Sep 2014
   Fixes Sep 2020

The input files are binary files with the following format:
the first byte is the SIZE of the relation,
followed by a byte for each element of the matrix,
filling rows from left to right.

For example, a file with the following byte sequence:

   4, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1

represents the following matrix, R:

   1, 1, 0, 1,
   1, 1, 0, 1,
   0, 0, 1, 0,
   1, 1, 0, 1

Given a set A = {0, 1, 2, 3} we can label R as follows:

       0  1  2  3
   0   1, 1, 0, 1,
   1   1, 1, 0, 1,
   2   0, 0, 1, 0,
   3   1, 1, 0, 1

So, the above matrix represents the a relation R on set A where,

R = {(0,0) (0,1) (0,3) (1,0) (1,1) (1,3) (2,2) (3,0) (3,1) (3,3)}

Which is reflexive, symmetric and transitive.  This makes it an
equivalence relation with the following equivalence classes:

[0] = {0 1 3}
[2] = {2}

*/

#include <iostream>
#include <string.h>
#include <fstream>
#pragma warning( disable : 4267)
#define MAX 40

using namespace std;

// The Matrix.  No-one can be told what the Matrix is, you must be shown.
#define BLUEPILL
#define REDPILL
int R[MAX][MAX];   // a boolean array indicating members of a relation
int EC[MAX];       // a boolean array indicating representatives of equivalence classes
int SIZE;

/*
This prints a matrix
*/
void printMatrix(int R[MAX][MAX])
{
   int i, j;

   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++)
         cout << R[i][j];
      cout << endl;
   }
}

/*
Checks if a matrix is reflexive.

Checks the diagonals of a matrix.  All elements on the diagonal
must be 1.
*/
int IsRefx(int R[MAX][MAX])
{
   return 42;  // return a dummy value for now
}


/*
Checks is a matrix is symmetric

i,j == j,i for every cell of the matrix
*/
int IsSymt(int R[MAX][MAX])
{
   return 42;  // return a dummy value for now
}


/*
Squares a matrix

R2 = R x R
R2 i,j = sum of R i,k * R k,j
*/
void SquareMatrix(int R[MAX][MAX], int R2[MAX][MAX])
{

}


/*
Checks if a matrix is transitive.

First calculate the matrix squared
Every non-zero element of Rsquared must also be non zero in R
*/
int IsTrans(int R[MAX][MAX], int R2[MAX][MAX])
{
   return 42;  // return a dummy value for now
}

/*
Finds equivalence classes and elects representatives of each class.

EC will contain a list of class representatives aka "captians" represented
as an array of boolean flags.

Each row in a matrix represents an equivalence class.  But there may be
several duplicate rows.  Our task is to find the captian of each class,
which will be the first member of the class.

ALGORITHM:
0 is always a captian

For elements 1 thru N, assign each as a captian
then, go to that elements row and look backwards for members less than this.
If found, demote the captian.
This works because captains are the first members of their class.  Think about it.
*/
void FindECs(int R[MAX][MAX], int EC[MAX])
{

}


/*
Iterate thru the captains array.  For each captian, go to that row of
the matrix and print the members of the class.
*/
void printECs(int R[MAX][MAX], int EC[MAX])
{

}


int main(void)
{
   char c;

   // open source file
   // By default Visual Studio 2019 looks in same folder as cpp file
   ifstream fin("R1.bin", ios_base::binary);
   if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

   // get the matrix SIZE
   fin.read(&c, 1); SIZE = c;

   // fill the matrix from the file
   int i, j;
   for (i = 0; i < SIZE; i++)
      for (j = 0; j < SIZE; j++)
      {
         fin.read(&c, 1);
         R[i][j] = c;
      }

   // close file
   fin.close();

   printMatrix(R);

   // more code....






}