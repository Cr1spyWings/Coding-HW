/*
Just Another Enigma Emulator (JAEE)

Dan Ross

Version: 1.0 Dec 2022
    it mostly worked!
Version: 2.0 Dec 2023
    fixed bugs, seems to work fine now
    added rotors VI thru VIII
    added reflectors UKW-A and UKW-C
    added more betterer documentation

Comments:  Everybody else has one, now I do too!

Copyright (c) 2022-23 Dan Ross
*/
#include <iostream>
#include <fstream>
using namespace std;

/*  The Encryption Functions for the Stator(ETW), Rotors(I thru VIII), Reflectors(UKW), Plugs

Rotor wiring for Enigma 1 and Enigma M3 courtesy of:
https://www.cryptomuseum.com/crypto/enigma/wiring.htm

            0         1         2
            01234567890123456789012345  Notch	Turnover
    ETW	    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    I	    EKMFLGDQVZNTOWYHXUSPAIBRCJ    Y        Q
    II	    AJDKSIRUXBLHWTMCQGZNPYFVOE    M        E
    III	    BDFHJLCPRTXVZNYEIWGAKMUSQO    D        V
    IV	    ESOVPZJAYQUIRHXLNFTGKDCMWB    R        J
    V	    VZBRGITYUPSDNHLXAWMJQOFECK    H        Z
    VI      JPGVOUMFYQBENHZRDKASXLICTW    HU       ZM
    VII     NZJHGRCXMYSWBOUFAIVLPEKQDT    HU       ZM
    VIII    FKQHTLXOCBJSPDZRAMEWNIUYGV    HU       ZM
    UKW-A	EJMZALYXVBWFCRQUONTSPIKHGD
    UKW-B	YRUHQSLDPXNGOKMIEBFZCWVJAT
    UKW-C	FVPJIAOYEDRZXWGCTKUQSBNMHL
    PLUGS	ABCDEFGHIJKLMNOPQRSTUVWXYZ

The rotor wiring tables below in function notation:
w[0] = { (A,E)(B,K)...(Z,J) }
w[1] = { (A,A)(B,J)...(Z,E) }
etc...
*/
char w[8][26] = {
    //     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25
    //     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z
        {  4, 10, 12,  5, 11,  6,  3, 16, 21, 25, 13, 19, 14, 22, 24,  7, 23, 20, 18, 15,  0,  8,  1, 17,  2,  9 },  // 0  Rotor I
        {  0,  9,  3, 10, 18,  8, 17, 20, 23,  1, 11,  7, 22, 19, 12,  2, 16,  6, 25, 13, 15, 24,  5, 21, 14,  4 },  // 1  Rotor II
        {  1,  3,  5,  7,  9, 11,  2, 15, 17, 19, 23, 21, 25, 13, 24,  4,  8, 22,  6,  0, 10, 12, 20, 18, 16, 14 },  // 2  Rotor III
        {  4, 18, 14, 21, 15, 25,  9,  0, 24, 16, 20,  8, 17,  7, 23, 11, 13,  5, 19,  6, 10,  3,  2, 12, 22,  1 },  // 3  Rotor IV
        { 21, 25,  1, 17,  6,  8, 19, 24, 20, 15, 18,  3, 13,  7, 11, 23,  0, 22, 12,  9, 16, 14,  5,  4,  2, 10 },  // 4  Rotor V
        {  9, 15,  6, 21, 14, 20, 12,  5, 24, 16,  1,  4, 13,  7, 25, 17,  3, 10,  0, 18, 23, 11,  8,  2, 19, 22 },  // 5  Rotor VI
        { 13, 25,  9,  7,  6, 17,  2, 23, 12, 24, 18, 22,  1, 14, 20,  5,  0,  8, 21, 11, 15,  4, 10, 16, 3,  19 },  // 6  Rotor VII
        {  5, 10, 16,  7, 19, 11, 23, 14,  2,  1,  9, 18, 15,  3, 25, 17,  0, 12,  4, 22, 13,  8, 20, 24,  6, 21 }   // 7  Rotor VIII
};

/* The INVERSE Encryption Functions for the 8 ROTORS and the PLUGS only

These wi tables are filled programmatically by fill_wi().
Filling the wi tables once and using them for repeated "reverse-lookups" is
more efficient than searching the w tables for every reverse lookup.

The tables below in function notation:
wi[0] = { (A,U)(B,W)...(Z,J) }
wi[1] = { (A,A)(B,J)...(Z,S) }
etc...
*/
char wi[8][26];

/*
The reflector wiring tables
*/
char u[3][26] = {
    //     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25
    //     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z
        {  4,  9, 12, 25,  0, 11, 24, 23, 21,  1, 22,  5,  2, 17, 16, 20, 14, 13, 19, 18, 15,  8, 10,  7,  6,  3},  // 0  UKW-A
        { 24, 17, 20,  7, 16, 18, 11,  3, 15, 23, 13,  6, 14, 10, 12,  8,  4,  1,  5, 25,  2, 22, 21,  9,  0, 19},  // 1  UKW-B
        {  5, 21, 15,  9,  8,  0, 14, 24,  4,  3, 17, 25, 23, 22,  6,  2, 19, 10, 20, 16, 18,  1, 13, 12,  7, 11}   // 2  UKW-C
};

/*
    Rotor turnover locations for rotors I thru VIII
    rotors VI thru VIII have 2 notches, 99 never happens
*/
int t1[8] = { 16,  4, 21,  9, 25, 25, 25, 25 };
//             Q   E   V   J   Z   Z   Z   Z
int t2[8] = { 99, 99, 99, 99, 99, 12, 12, 12 };
//                                 M   M   M



// **********************************************************************
// **********************************************************************
// ***************** BEGIN USER ADJUSTABLE KEY SETTINGS *****************
// **********************************************************************
//***********************************************************************
/*
Example key values used in the settings below from this page:
https://cryptii.com/pipes/enigma-machine

Walzenlage          Ringstellung        Steckerverbindungen                 Grundstellung
VI   I   III        1 17 12             BQ CR DI EJ KW MT OS PX UZ GH       AAA

*/

// rotor Order, from left to right (Walzenlage)
int o[3] = { 3, 1, 0 };     // zero-based values from 0 to 7 (Pick 3 from Rotors I thru VIII)

// rotor Step position, from left to right (Grundstellung)
// these positions "increment" after every input, that is the power of enigma!
int s[3] = { 18, 5, 23 };   // zero-based values from 0 to 25

// rotor Ring, from left to right (Ringstellung)
int r[3] = { 19, 17, 10 };     // zero-based values from 0 to 25


// Plugs (Steckerverbindungen)
char p[26] = {
    //     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25
    //     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z
           0,  13,  23, 20, 4,  19,  6,  7,  9,  8, 14, 11, 12, 1, 10, 15, 16, 17, 18, 5, 3, 21, 22, 2, 24, 25
    //     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25  // NO PLUGS
};
char pi[26];  // inverse plugs

// **********************************************************************
// **********************************************************************
// ****************** END USER ADJUSTABLE KEY SETTINGS ******************
// **********************************************************************
// **********************************************************************



// Fills the inverse rotor wire tables for the 5 Rotors and the Plugs
void fill_inverses()
{
    int row, col;

    // Rotors
    for (row = 0; row < 8; row++)
        for (col = 0; col < 26; col++)
            wi[row][w[row][col]] = col; // do the reverse magic lookup

    // Plugs
    for (col = 0; col < 26; col++)
        pi[p[col]] = col;     // do the reverse magic lookup
}

/*
Returns x modulus y
Handles negatives "correctly" like most calculators do.
Examples:
     42 mod 10 = 2
    -42 mod 10 = 8
    y must be positive
*/
int mod(int x, int y)
{
    // subtract out the largest integer multiple of y
    x = x - y * (x / y);

    // move negs up to nearest pos
    if (x < 0) x += y;

    return x;
}


/*
Performs Enigma M3 style encryption
*/
char encrypt(char c)
{
    c -= 'A';  // convert from A-based index to Zero-based index

    // "Turn" the rotors and do the clock (modulo) arithmetic 

    // check if s0 and/or s1 are ready to step
    bool go0 = false, go1 = false;
    // rotor 1 will go if rotor 2 is at notch
    if (s[2] == t1[o[2]] || s[2] == t2[o[2]])
        go1 = true;
    // rotor 0 and rotor 1 will go if rotor 1 is at notch
    if (s[1] == t1[o[1]] || s[1] == t2[o[1]])
    {
        go0 = true; go1 = true;
    }

    // turn some rotors
    if (go0) ++s[0] %= 26;
    if (go1) ++s[1] %= 26;
    ++s[2] %= 26;    // rotor 2 always steps


    // Thru the plugs, the three rotors, the reflector, and back again!  It's palindromic!
    //    Before the f lookup, add each rotor's step position and subtract its ring position.
    //    Reverse the process for the fi lookup.  Use special mod cuz sometimes these calcs go way negative-ish.

                                                                     //cout << (char)(c + 'A') << "  ";
    c = p[c];           /*  plugs  */                                //cout << (char)(c + 'A') << "  ";
    // thru the rotors, from right to left
    c = mod(w[o[2]][mod(c + s[2] - r[2], 26)] - s[2] + r[2], 26);    //cout << (char)(c + 'A') << "  ";
    c = mod(w[o[1]][mod(c + s[1] - r[1], 26)] - s[1] + r[1], 26);    //cout << (char)(c + 'A') << "  ";
    c = mod(w[o[0]][mod(c + s[0] - r[0], 26)] - s[0] + r[0], 26);    //cout << (char)(c + 'A') << "  ";
    c = u[1][c];        /*  reflector UKW-B  */                      //cout << (char)(c + 'A') << "  ";
    // thru the rotors, from left to right
    c = mod(wi[o[0]][mod(c + s[0] - r[0], 26)] - s[0] + r[0], 26);   //cout << (char)(c + 'A') << "  ";
    c = mod(wi[o[1]][mod(c + s[1] - r[1], 26)] - s[1] + r[1], 26);   //cout << (char)(c + 'A') << "  ";
    c = mod(wi[o[2]][mod(c + s[2] - r[2], 26)] - s[2] + r[2], 26);   //cout << (char)(c + 'A') << "  ";
    c = pi[c];          /*  plugs  */                                //cout << (char)(c + 'A') << "  ";
    //cout << endl;

    return c + 'A';  // convert from Zero-based index to A-based index
}


/*
Yo, sup?
*/
int main()
{
    char c;     // the byte to encrypt
    char w;     // encrypted byte
    int count = 0;

    fill_inverses();  // initialize the inverse wiring tables

    // open source file
    ifstream fin("pText.Enigma.cryptii.com.txt", ios_base::binary);
    if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

    // open destination file
    ofstream fout("eText.txt", ios_base::binary);
    if (!fout) { cerr << "Output file could not be opened\n"; exit(1); }

    // for debugging each transformation
    //cout << "   p  " << o[2] << "  " << o[1] << "  " << o[0] << "  " << "u  " 
    //    << o[0] << "  " << o[1] << "  " << o[2] << "  p" << endl << endl;

    // read, encrypt, write
    while (!fin.eof())
    {
        fin.read(&c, 1);
        if (!fin.eof())
        {
            c = toupper(c);

            // skip spaces in the input
            if (c != ' ')
            {
                w = encrypt(c);
                fout.write(&w, 1);
                cout << w;
                count++;

                // output a space every 5 chars
                if (!(count % 5))
                {
                    w = ' ';
                    fout.write(&w, 1);
                    cout << w;
                }
            }
        }
    }

    fin.close();
    fout.close();

}
