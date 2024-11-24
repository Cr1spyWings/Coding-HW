/*
    Implements the following CFG:

    Nonterminals:   N = {A, B, C}
    Terminals:      T = {a, b, c}

    Productions
    A -> Bc
    B -> Cb | l
    C -> Ba | l

    Where the terminals a, b, and c expand into the substrings:  
    a = “he said”,  b = “she said”,  c = “you lied”

    Example Series of Productions:
    w = A
      A->Bc
    w = Bc
      B->Cb
    w = Cbc
      C->Ba
    w = Babc
      B->Cb
    w = Cbabc
      C->l
    w = lbabc
    w = she said he said she said you lie.

    Dan Ross
    Oct 2014

*/

#include <iostream>
#include <string.h>
#include <time.h>
#pragma warning( disable : 4996)
using namespace std;

// Strings
#define SIZE 10000
char w[SIZE] = "A";     // our initial string of N's and T's
char buf[SIZE] = "";    // a buffer for string processing

// Productions
char P [][5][20] = {
	"Bc", "", "", "", "",	// A -> Bc
	"Cb", "l", "", "", "",	// B -> Cb|l
	"Ba", "l", "",  "", "",		// C -> Ba|l
};

// Terminal Expansions
char tTable[][20] = {
    "he said ",			
	"she said ",	
    "you lie ",
};

// Gets the cardinality for a row of the Productions table
int Cardinality(int row)
{
    int col = 0;

    // look for an empty string
    while(P[row][col][0])
        col++;

    return col;
}

// Returns true if there are Nonterminals in w
bool gotNs()
{
    for(int i =0; w[i]; i++)
        if(w[i] >= 'A' && w[i] <= 'Z')
            return true;
    return false;
}

/*
Introduces verbosity
Replaces terminals with big strings for humans to read and ponder
*/
void expand()
{
    int i = 0;  buf[0] = 0; 
    while(w[i])
    {
        int index = w[i] - 'a';
        if (index >= 0 && index < 26) { // Ensure valid index range
            strcat(buf, tTable[index]);
        } else { // If not a valid terminal, copy as-is
            char lilbuf[2] = {w[i], '\0'};
            strcat(buf, lilbuf);
        }
        i++;
    }
    
    // copy back to w
    strcpy(w, buf);
}

/* 
Implements an iterative CFG processor driven by global tables.
Can process any CFG that can be put in these global tables.

This is our "Phonological Loop" for all you psychology fans.

Some lines in the inner loop in main have been hobbled, 
to force you to think about what is going on - you have to fix them.
Once you get it working, you should not have to modify this processor,
you only need to modify the global tables to process other grammars.
*/
int main() {
    // Seed random number generator
    srand((unsigned) time(0)); 

    // Print initial string
    cout << "w = " << w << endl;

    // Process until there are no more non-terminals
    while (gotNs()) {
        int i = 0; int j = 0; buf[0] = 0; // Clear the buffer

        while (w[i]) { // Process each character in w
            if (w[i] >= 'A' && w[i] <= 'Z') { // Non-terminal
                int row = w[i] - 'A';            // Map non-terminal to row in P
                int C = Cardinality(row);  // Number of productions
                int col = rand() % C;           // Randomly select a production

                cout << w[i] << " -> " << P[row][col] << endl;
                strcat(buf, P[row][col]);
            } else { // Terminal
                char lilbuf[10] = {w[i], 0};
                strcat(buf, lilbuf);
            }
            i++;
        }

        // Copy buffer back to w
        strcpy(w, buf);
        cout << "w = " << w << endl;
    }

    // Perform final terminal expansion
    expand();
    cout << "w = " << w << endl;

    return 0;
}