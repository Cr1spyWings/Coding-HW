/*
   Generates a state machine to find all occurances of an arbitrary string

   Dan Ross
   Original April 2013
   Improved Nov 2020
   Poked at somemore Oct 2023

*/
#include <iostream>
#include <fstream>
#pragma warning( disable : 4996) 
#pragma warning( disable : 4244) 
using namespace std;

#define STATES 20
char nextState[STATES][2]; /*= {
//     a  b   //inputs
      1, 0,  //state 0
      1, 2,  //state 1
      3, 0,  //state 2
      1, 4,  //state 3
      3, 0,  //state 4
};
*/

char state = 0;
int Count = 0;

// hard code input string
char instr[80] = "abab";   //"abbbbbbaaaaaba";

void process(char ch)
{
    // print current char
    //cout << ch;

    // move to next state
    state = nextState[state][ch - 'a'];

    // output count if we are back to initial state
    if (state == strlen(instr)) cout << Count + 1 << ", ";

    Count++;  //another ch bites the dust!
}


void print_StateTable()
{
    cout << "\nComplete state table for " << instr << "...\n";
    cout << "s\ta\tb\n\n";

    int l = strlen(instr) + 1;
    for (int s = 0; s < l; s++) {
        cout << s << "\t";
        for (int ch = 0; ch < 2; ch++)
            cout << (int)nextState[s][ch] << "\t";
        cout << endl;
    }
}


/*
Compares first n characters of str1,
with last n characters of str2.

Returns 0 (false) if they match

It would look like this if you called it with hard-coded values:
strncmp("abab", "a", 1) match, store this

Copyright (c) 1981 Dan Ross
*/
int strncmp_olap(char* str1, char* str2, int n)
{
    int i, j;
    int l1 = strlen(str1);
    int l2 = strlen(str2);

    for (i = 0, j = l2 - n; i < n; i++, j++)
        if (str1[i] != str2[j])
            return true;

    return false;
}

/*
Create a state table for a sequence detector
*/
void create_StateTable(void)
{
    /////////////////  YOU WRITE THIS FUNCTION PLEASE  ////////////////

    /* you may need these things...
    char got[80];
    got[0] = 0;         // the null terminator
    strncpy(...);       // handy, but it doesn't do this: got[zeroSpot] = 0;
    strcat(...);	    // for sticking on a's and b's
    strlen(...);		// is useful too
    strncmp_olap(..)	// an amazing function!  try it!

    some tricky s**t...
    char ch[2] = "a";
    ch[0]++; // increments the above string to the next character
    */

 }


int main()
{

    /// //////////////  CREATE THE STATE TABLE
    
    create_StateTable();  // you write this function please
    print_StateTable();

    ///////////////////	RUN THE STATE MACHINE

    char ch;
    ifstream in("abab.txt");
    if (!in) {
        cout << "Error opening file";
        return;
    }

    cout << "\nThe string " << instr << " was found at locations: ";

    // read and process characters
    while (in) {
        in.get(ch);
        if (in)
            process(ch);
    }

}