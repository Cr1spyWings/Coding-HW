/*
Reads a truth table from a text file into a boolean array
then generates the equivalent Boolean Algebra expression in
Minimal Sum Of Products (SOP) Form, also known as (aka)
Disjunctive Normal Form

Dan Ross
   Original Nov 2023

The input files are text files in "minterm list format."
For example, the file named "g(a,b,c) = SOP(0,1,0,1,0,0,1,1).txt" contains:
0
1
0
1
0
0
1
1

Note:  EVERY line must end in CRLF for Windows.,
LF in Unix, and CR in MacOS, because... of course!
This may mess you up if you are not on Windows.

which represents the following Truth Table:

abc g    minterm

000 0    a'b'c'
001 1    a'b'c
010 0    a'bc'
011 1    a'bc
100 0    ab'c'
101 0    ab'c
110 1    abc'
111 1    abc

SOP expression: g(a,b,c) = a'b'c + a'bc + abc' + abc

*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

// The Truth Table
#define MAXROWS 64
#define MAXCOLS 7
bool TT[MAXROWS][MAXCOLS];  // Truth Table Inputs a thru f (max), and output g
int ROWS, COLS;             // size of current table with input variables only
char minterms[MAXROWS][80]; // minterm for each row
char SOP[80];               // final Sum Of Products expression
#pragma warning (disable : 4996)

/*
This prints a Truth Table
Format: inputs, output column, minterms (if available)
Final SOP expression (if available)
*/
void printTable()
{
    int row, col;

    // print the variable names
    for (col = 0; col < COLS - 1; col++)
        cout << char(col + 'a');
    cout << " g    minterm\n\n";

    // print the actual 1's and 0's
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            cout << TT[row][col];
            if (col == COLS - 2) cout << " ";  // space B4 f
        }
        cout << "    " << minterms[row] << endl;
    }

    cout << endl << "SOP expression: " << SOP << endl;
}

/*
Looks in a Truth Table and creates a Boolean Algebra
expression in Minimal Sum Of Products (SOP) form

First, create each minterm and store it.
Then, concatenate all minterms into one SOP and store it.
*/
void createSOP()
{
     // Clear previous data
    memset(SOP, 0, sizeof(SOP));

    bool isFirstMinterm = true;

    // Loop through each row in the truth table
    for (int row = 0; row < ROWS; row++)
    {
        memset(minterms[row], 0, sizeof(minterms[row]));

        // Generate the minterm for the row (always do this to add variable mappings)
        for (int col = 0; col < COLS - 1; col++)
        {
            char literal[3] = {0}; // For variable (e.g., "a" or "a'")
            literal[0] = 'a' + col; // Variable name: 'a', 'b', 'c', etc.

            if (TT[row][col] == 0)
                strcat(literal, "'");

            strcat(minterms[row], literal);
        }

        // If g is 1, add the minterm to the SOP expression
        if (TT[row][COLS - 1] == 1)
        {
            if (!isFirstMinterm)
                strcat(SOP, " + "); // Add separator for SOP terms
            strcat(SOP, minterms[row]);

            isFirstMinterm = false;
        }
    }
}


/*
Reads a file into a Truth Table
*/
void fillTable(const char filename[80])
{
    cout << "Opening file: " << filename << "... ";

    // open source file
    ifstream fin(filename);
    if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

    // get the file size in bytes
    fin.seekg(0, ios::end);
    int file_size = (int)fin.tellg();

    // rewind back to the start of the file
    fin.seekg(0, ios::beg);

    // calculate ROWS and COLS
    ROWS = file_size / 3;
    COLS = (int)std::log2(ROWS) + 1;

    // report...
    cout << "File size " << file_size << " " << "bytes, " << ROWS << " rows, " << COLS << " columns" << endl << endl;

    char line[MAXCOLS];

    // fill up the output row from the file
    for (int row = 0; row < ROWS; row++)
    {
        fin.getline(line, MAXCOLS);
        TT[row][COLS - 1] = line[0] - '0';
    }

    fin.close();

    // fill up the input part of the table using bitwise magic
    for (int row = 0; row < ROWS; row++)
    {
        int mask = 1 << (COLS - 2);
        for (int col = 0; col < COLS - 1; col++)
        {
            TT[row][col] = row & mask;
            mask = mask >> 1;
        }
    }
}


int main(void)
{
    //char filename[] = "g(a) = SOP(1,0).txt"; 
    //char filename[] = "g(a,b) = SOP(0,0,1,1).txt"; 
    //char filename[] = "g(a,b,c) = SOP(0,1,0,1,0,0,1,1).txt";
    //char filename[] = "g(a,b,c,d) = SOP(0,0,0,0,1,1,1,1,0,1,0,1,0,0,1,1).txt";
    //char filename[] = "g(a,b,c,d,e) = SOP(0,1,1,0,0,1,0,1,0,0,0,0,1,1,1,1,0,1,0,1,1,0,1,0,1,0,1,1,0,0,1,1).txt";
    char filename[] = "g(a,b,c,d,e,f) = SOP(1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,1,1,0,1,0,1,0,0,1,1,0,1,0,1,0,1,1,0,0,1,0,1,0,0,0,0,1,1,1,1,0,1,0,1,1,0,0,1,1,0,1).txt"; 
    fillTable(filename);
    createSOP();
    printTable();

    ////// PLEASE MODIFY AS DESIRED TO PROCESS AND OUTPUT ALL THE INPUT FILES ///////
}