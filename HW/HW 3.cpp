/*
    Converts an integer from one base to another.

    Dan Ross
    Aug 2022

    Supports any base between 3 and 36.  Integers are represented
    as strings consisting of a subset of the following character mapping:

    0         1         2         3
    012345678901234567890123456789012345
    0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    EXAMPLE: 42 base10 = 101010 base2 = 2A base16 = 60 base 7 = 16 base36

    Also converts 3-letter base 4 sequences of the following digits

    GATC
    3210

    EXAMPLES:
        CCC = 0x4^2 + 0x4^1 + 0x4^0 =  0 +  0 + 0 =  0
        GGG = 3x4^2 + 3x4^1 + 3x4^0 = 48 + 12 + 3 = 63
        ACT = 2x4^2 + 0x4^1 + 1x4^0 = 32 +  0 + 1 = 33

    Also adds strings representing numbers in any base up to 35
    Examples:

    BEEF base 35 + FEED base 35 = QSSS base 35
    ABBA base 16 + ACDC base 16 = 15896 base 16
    PROF base 22 + ROSS base 22 = 2A99L base 22


*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning( disable : 4996) 
#pragma warning( disable : 4244) 

/*
Calculates base raised to the power exp
*/
int my_pow(int base, int  exp)
{
    int x = 1;
    for (int i = 0; i < exp; i++)
        x *= base;

    return x;
}

/*
Converts an alphanumeric string 's' representation of a base 'base' number
to internal binary format.
Returns the value as a 32 bit integer
*/
long my_atoi(char* s, int base)
{
    int dec = 0;
    for(int i = 0; i < sizeof(s); i++) {
        dec += static_cast<int>(s[i]) * my_pow(base, sizeof(s) - i);
    }
    return dec;
}

/*
Converts a 32 bit integer 'n' into an alphanumeric string 'sOut'
representation of a base 'base' number
*/
void my_itoa(long n, char* sOut, int base)
{
    // you must write this function so 
    // so return a dummy for now
    char s[36];
    int count = 0;
    int x = static_cast<int>(n);
    while(x != 0) {
        s[count] = x % base;
        x = x / base;
        count++;
    }
    char s2[sizeof(s)];
    for(int i = 0; i < count; i++) {
        s2[i] = s[count];
        count--;
    }
    strcpy(sOut, s2);
}


/*
Converts an integer to base 4 codon format
*/
void itoDNAcodon(char* codon, int i)
{
    // you must write this function so 
    // return a hard coded dummy value for now
    strcpy(codon, "ACT");
}


/*
Returns the base 4 value of a codon
*/
int DNAcodontoi(char codon[4])
{
    int d0, d1, d2, value;

    switch (codon[2])
    {
    case 'C':
        d0 = 0; break;
    case 'T':
        d0 = 1; break;
    case 'A':
        d0 = 2; break;
    case 'G':
        d0 = 3; break;
    }

    switch (codon[1])
    {
    case 'C':
        d1 = 0; break;
    case 'T':
        d1 = 1; break;
    case 'A':
        d1 = 2; break;
    case 'G':
        d1 = 3; break;
    }

    switch (codon[0])
    {
    case 'C':
        d2 = 0; break;
    case 'T':
        d2 = 1; break;
    case 'A':
        d2 = 2; break;
    case 'G':
        d2 = 3; break;
    }

    // the base 4 value of the codon
    value = d2 * 16 + d1 * 4 + d0;

    return value;
}



/*
Adds 2 numbers in any base.

Arguments:
input s1, s2, base, return sum
*/
void addInBase(char s1[], char s2[], char sum[], int base)
{
    // return a dummy for now until you get it actually working
    strcpy(sum, "1153");

    char n1[30], n2[30], n3[30];

    // initialize numerical arrays to all zeros
    {

    }

    // copy chars to numerical arrays in reverse order
    {
        // subtract '0'
        // if character > '9' then subtract another 7
    }

    // do the actual addition
    // loop thru the numerical array
    {
        // add
        // mod
        // div
    }

    // find first non zero from "left"

    // copy numbers back to string and reverse order
    {
        // add '0'
        // if number > 9 then add another 7

        // replace zeros with spaces
    }
    // add the null terminator

}



void main()
{
    char sIn[] = "16";
    char sOut[80];
    long n = 0;

    // convert some wacky base to internal representation
    n = my_atoi(sIn, 36);
    printf("%s base 36 is %d base 10\n", sIn, n);

    // convert back to some wacky base
    my_itoa(n, sOut, 11);
    printf("%d base 10 is %s base 11\n", n, sOut);

    // DO SEVERAL MORE

    // now do it with DNA 
    char muhGenes[4] = "ACT";
    n = DNAcodontoi(muhGenes);
    printf("%s in DNA is %d base 10\n", muhGenes, n);

    // back to DNA cuz we can
    char buffy[4];
    itoDNAcodon(buffy, n);
    printf("%d base 10 is %s in DNA\n", n, muhGenes);

    // test adding strings in arbitrary bases
    char s1[] = "543";
    char s2[] = "210";
    char sum[20];
    int b = 6;
    addInBase(s1, s2, sum, b);
    printf("%s + %s in base %d is %s\n", s1, s2, b, sum);

}