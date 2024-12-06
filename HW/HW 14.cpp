/*
    Substituion De-Cipher

    Dan Ross
    Original Nov 2023

    When complete, this program will decipher an encrypted file named
    "eText.txt" which was originally encypted using a "hard coded"
    random substitution cipher named map[].

    You must complete the inverse mapping table imap[], which is
    initialized to simply pass thru encrypted text thru unchanged.
    imap[] must be manually edited so that it contains the inverse
    of the (unkown) map[] table.

    Since we know that the input file was an English text file created
    with a random substitution cypher, we can use a frequency analysis
    of the eText to help us determine the imap table.

    Several manual revisions of imap[] will likely be required - such
    is the nature of frequency analysis cracking.

    This program first performs a frequency analysis of the eText.txt

    ****************************************************************
    *  THE ONLY THING YOU NEED TO CHANGE IN THIS PROGRAM IS IMAP[] *
    * **************************************************************

*/
#include <iostream>
#include <fstream>
using namespace std;


// a lil struct to calculate character frequencies
struct cf {
    int count;
    float freq;
} charfreqs[27];	// 'a' thru 'z' plus ' '
int totalchars = 0;


// THE INVERSE MAPPING (DECRYPTION) TABLE
// 
// Start with regular alphabet order, except mark spaces with @.  
// In effect we are just "passing thru" the eText, initially.
// 
// Then, while consulting the frequency analysis, change each letter to capitals one-by-one.  
// This way we can keep track of what we have changed.  Also see "Char Freq Analysis.xls"
// 
//                 0                                       1                                       2
//                 0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6
//                 a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z  ' '
char imap[27] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','@' };

/*
******************************************************************
                            MAIN
******************************************************************
*/
void main()
{
    char ch;

    // open the input file
    ifstream in("eText.txt");
    if (!in) {
        cout << "Cannot open input file.\n";
    }

    // read file
    while (in) { 	// in will be false when eof is reached
        in.get(ch);

        // process each letter read from file
        if (in) {

            // COUNT ENCRYPTED LETTERS
            totalchars++;
            if (ch == ' ')
                charfreqs[26].count++;
            else
                charfreqs[ch - 'a'].count++;

            // DO THE ACTUAL DECRYPTION HERE
            // this works fine....if your imap[] is correct!
            // that's all there is to it.
            if (ch == ' ')
                ch = imap[26];
            else
                ch = imap[ch - 'a'];
            cout << ch;
        }
    }

    // finish up the freq calcs
    // print chars, counts, and freqs
    cout << "\n\n\char\tcount\tfreq\n";
    for (int i = 0; i < 26; i++)
    {
        charfreqs[i].freq = charfreqs[i].count / (float)totalchars;
        cout << (char)(i + 'a') << "\t" << charfreqs[i].count << "\t" << charfreqs[i].freq << endl;
    }
    // special treatment for the space
    charfreqs[26].freq = charfreqs[26].count / (float)totalchars;
    cout << "space\t" << charfreqs[26].count << "\t" << charfreqs[26].freq << endl;

    in.close();

}