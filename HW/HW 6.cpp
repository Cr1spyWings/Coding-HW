/*

Homemade relational database.

Implements Select, Project, Join and Union operations.

Dan Ross
   Original Mar 2013
   Updated Mar 2017
   Updated some more Sep 2020

*/

#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#pragma warning( disable : 4267)
#pragma warning( disable : 4996)

using namespace std;

// ****  THE TABLES  ****
// Use 800kB global tables cuz RAM is cheap and labor is not!
// Seriously, a more efficient memory implementation would 
// use pointers and dynamic memory (using new and/or malloc)
// but that often requires tricky pointer arithmetic
char T1[100][100][80];
char T2[100][100][80];
//Tables for 4 Tasks
char T4[100][100][80];
char T5[100][100][80];
char T6[100][100][80]; 
char T7[100][100][80];


/*
Prints out a table

******* HINTS!! *******
See this function right here?

It has a basic table looping structure that you may find helpful
in building the other functions you need.  Just squeeze in some
logic here and there with maybe strcmp and strcpy.
*/
void printTable(char T[100][100][80])
{
   int i = 0, j = 0;
   while (T[i][j][0]) {		// look for null char at T[i][j][0]
      while (T[i][j][0]) {
         cout << left << setw(20) << T[i][j];// string at T[i][j]
         j++;
      }
      cout << endl;
      i++; j = 0;
   }
   cout << endl;
}


/*
Erases a table
*/
void eraseTable(char T[100][100][80])
{
   // erase the destination array
   for (int i = 0; i < 100; i++)		  // rows
      for (int j = 0; j < 100; j++)	  // cols
         for (int k = 0; k < 80; k++)   // chars
            T[i][j][k] = 0;

}


void eraseArray(int A[], int size)
{
   for (int i = 0; i < size; i++)
      A[i] = 0;
}

/*
Reads a file into a table
*/
void filltable(const char filename[80], char Table[100][100][80])
{
   // open source file
   ifstream fin(filename);
   if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

   char line[80];
   char buf[80];

   // table rows and cols
   int row = 0; int col = 0;

   // Copy file into table
   fin.getline(line, 80);
   while (line[0]) {
      col = 0;   // reset col
      //cout << line << endl << endl;

      // parse this line
      int i = 0; int j = 0;
      int len = strlen(line);
      for (i = 0; i <= len; i++) {
         if ((line[i] == ',') || (line[i] == 0)) { // delimiters
            strncpy(buf, line + j, i - j);
            buf[i - j] = 0;  // null terminator
            j = i + 1;		 // scoot up j	

            // copy buffer to table array
            strcpy(Table[row][col], buf);
            col++;
            //cout << "Hey: " <<  buf << endl;			
         }
      }

      // get another line
      fin.getline(line, 80);
      row++;
   }
}


/*
Performs a select operation on a table.

Receives a table.
Returns a table consisting of only the rows which have
the specified 'value' in the specified 'col'
*/
/*
Performs a select operation on a table.

Receives a table.
Returns a table consisting of only the rows which have
the specified 'value' in the specified 'col'
*/
void select(char Tout[100][100][80], char Tin[100][100][80], int col, const char* value) 
{
   // erase the destination array
   eraseTable(Tout);

   int ToutRows = 0;
    int i = 0;   

    // Determine the number of rows in Tin
    while (Tin[i][0][0] != '\0') {
        if (strcmp(Tin[i][col], value) == 0) {
            strcpy(Tout[ToutRows][0], Tin[i][0]);
            strcpy(Tout[ToutRows][1], Tin[i][1]);
            strcpy(Tout[ToutRows][2], Tin[i][2]);
            ToutRows++; 
        }
        i++; 
    }
}

/*
Performs a project operation on a table.

Receives a table.
Returns a table consisting of the specified cols.
The 'cols' parameter is a set of boolean flags where
true means we want this row in the resulting table
*/
void project(char Tout[100][100][80], char Tin[100][100][80], int cols[100])
{
   // erase the destination array
   eraseTable(Tout);

   int destRow = 0;
   for (int i = 0; i < 100; i++) {
      if (Tin[i][0][0] == '\0') continue;
      int destCol = 0;
      for (int j = 0; j < 100; j++) {
         if (cols[j] == 1) {
            strcpy(Tout[destRow][destCol], Tin[i][j]);
            destCol++;
         }
      }
      destRow++;
   }
}


/*
Performs a join operation on a table.

Receives 2 tables and joins them.
Returns only the rows where the value in table1's T1col
matches the value in table2's T2col
*/
void join(char Tout[100][100][80], char T1[100][100][80], char T2[100][100][80], int T1col, int T2col)
{
   // Erase the destination array
   eraseTable(Tout);

   int destRow = 0;

    for (int i = 0; i < 100; i++) {
        if (strcmp(T1[i][0], "") == 0) break;

        for (int j = 0; j < 100; j++) {
            if (strcmp(T2[j][0], "") == 0) break;

            if (strcmp(T1[i][T1col], T2[j][T2col]) == 0) {
                // Copy the row from T1
                memcpy(Tout[destRow], T1[i], sizeof(T1[i]));
                
                int colCount = 3;
                for (int k = 0; k < 100; k++) {
                    if (k != T2col) { 
                        strcpy(Tout[destRow][colCount++], T2[j][k]);
                    }
                }
                destRow++;
                if (destRow >= 100) break;
            }
        }
    }
}

/*
Makes a 3rd table containing all the stuff in 2 other tables.
The 2 input tables must have the same schema.
*/
void Union(char Tout[100][100][80], char T1[100][100][80], char T2[100][100][80])
{
   // erase the destination array
   eraseTable(Tout);

   int destRow = 0;
   for (int i = 0; i < 100; i++) {
      if (T1[i][0][0] != '\0') {
         for (int j = 0; j < 100; j++) {
            strcpy(Tout[destRow][j], T1[i][j]);
         }
         destRow++;
      }
   }
   for (int i = 0; i < 100; i++) {
      if (T2[i][0][0] != '\0') {
         for (int j = 0; j < 100; j++) {
            strcpy(Tout[destRow][j], T2[i][j]);
         }
         destRow++;
      }
   }
}

// Function to count the number of valid rows in a given 2D array
int numRows(char array[][100][80]) {
    int count = 0;
    
    for (int i = 0; i < 100; i++) {
        if (strcmp(array[i][0], "") == 0) {
            break;
        }
        count++; 
    }
    return count;
}


/*
Reads in some tables and does operations on them
*/
int main(void) {
   filltable("Professors.txt", T1);
   filltable("Students.txt", T2);

   cout << "Original Professors table:\n";
   printTable(T1);

   cout << "Original Students table:\n";
   printTable(T2);

   // SELECT TEST: Extracting students with address '555 Riley'
   static char Temp1[100][100][80];
   select(Temp1, T2, 1, "555 Riley");
   cout << "\nSELECT TEST: Temp1 = Students[Address = 555 Riley]\n";
   printTable(Temp1);

   // PROJECT TEST: Extracting Names and Phone Numbers
   cout << "\nPROJECT TEST: Temp2 = Students[Name, Phone]\n";
   static char Temp2[100][100][80];
   int* cols = new int[100]; 
   eraseArray(cols, 100); // Ensure cols array is cleared
   cols[0] = cols[2] = 1; // Projecting Name and Phone
   project(Temp2, T2, cols);
   printTable(Temp2);

   // JOIN TEST: Joining Students and Professors on Address
   cout << "\nJOIN TEST: Temp3 = Students[address = address]Professors\n";
   static char Temp3[100][100][80];
   join(Temp3, T1, T2, 1, 1);
   printTable(Temp3);

   // UNION TEST: Combining Students with MoreStudents
   cout << "\nUNION TEST: Temp4 = Students UNION MoreStudents\n";
   static char T3[100][100][80];
   filltable("MoreStudents.txt", T3);
   static char Temp4[100][100][80];
   Union(Temp4, T2, T3);
   printTable(Temp4);

   filltable("buyer.txt", T4);
   filltable("department.txt", T5);
   filltable("employee.txt", T6);
   filltable("supplier.txt", T7);

   // TASK A: Find all employees who work in departments that supply parts for JCN Electronics
   cout << "\nTASK A: Finding employees in departments supplying parts for JCN Electronics\n";
   static char Temp5[100][100][80];
   static char Temp6[100][100][80];
   static char Temp7[100][100][80];
   static char Temp8[100][100][80];
   static char Temp9[100][100][80];

   select(Temp5, T4, 0, "JCN Electronics");
   for (int i = 0; i < numRows(Temp5); i++) {
    select(Temp6, T7, 1, Temp5[i][1]);
   }
   for (int i = 0; i < numRows(Temp6); i++) {
    select(Temp7, T5, 0, Temp6[i][0]); 
   }
   for (int i = 0; i < numRows(Temp7); i++) {
    select(Temp8, T6, 2, Temp7[i][1]); 
   }
   int cols1[100] = {0};
   cols1[1] = 1;
   project(Temp9, Temp8, cols1);
   printTable(Temp9); 

   // TASK B: Find all buyers who buy parts in the department managed by Jones
   cout << "\nTASK B: Finding buyers for the department managed by Jones\n";
   static char Temp0[100][100][80];
   static char Temp10[100][100][80];
   static char Temp11[100][100][80];
   static char Temp12[100][100][80];

   select(Temp0, T5, 1, "Jones");
   join(Temp10, T7, Temp0, 0, 0);
   for (int i = 0; i < numRows(Temp10); i++) {
    select(Temp11, T4, 1, Temp10[i][1]); 
   }
   int cols2[100] = {0};
   cols2[0] = 1;
   project(Temp12, Temp11, cols2);
   printTable(Temp12);

   // TASK C: Find all buyers who buy parts that are produced by the department for which Suzuki works
   cout << "\nTASK C: Finding buyers for the department where Suzuki works\n";
   static char Temp13[100][100][80];
   static char Temp14[100][100][80];
   static char Temp15[100][100][80];
   static char Temp16[100][100][80];
   static char Temp17[100][100][80];

   select(Temp13, T6, 1, "Suzuki");
   join(Temp14, Temp13, T5, 2, 1);
   for (int i = 0; i < numRows(Temp14); i++) {
    select(Temp15, T7, 0, Temp14[i][3]); 
   }
   int destRow = numRows(Temp16);
   for (int i = 0; i < numRows(Temp15); i++) {
      static char TempTemp[100][100][80];
      select(TempTemp, T4, 1, Temp15[i][1]);

      for (int j = 0; j < numRows(TempTemp); j++) {
         for (int k = 0; k < 100; k++) {
            strcpy(Temp16[destRow][k], TempTemp[j][k]);
         }
         destRow++;
      }
   }
   project(Temp17, Temp16, cols2);
   printTable(Temp17);

   // TASK D: Union of Buyers and MoreBuyers tables
   cout << "\nTASK D: Union of Buyers and MoreBuyers tables\n";
   filltable("MoreBuyers.txt", Temp16);
   Union(Temp17, T4, Temp16);
   printTable(Temp17);
}
