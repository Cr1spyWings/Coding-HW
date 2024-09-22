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
#include <ctype.h>
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
    long dec = 0;
    int len = strlen(s);
    
    if (base < 2 || base > 36) {
        return -1; 
    }

    for (int i = 0; i < len; i++) {
        char c = s[i];
        int value;

        if (isdigit(c)) {
            value = c - '0'; 
        } else if (isalpha(c)) {
            value = tolower(c) - 'a' + 10;
        } else {
            return -1;
        }

        if (value >= base) {
            return -1; 
        }

        dec += value * my_pow(base, len - i - 1);
    }
    return dec;
}

/*
Converts a 32 bit integer 'n' into an alphanumeric string 'sOut'
representation of a base 'base' number
*/
void my_itoa(long n, char* sOut, int base)
{
    if (base < 2 || base > 36) {
        strcpy(sOut, "Invalid base");
        return;
    }

    if (n < 0 && base == 10) {
        *sOut++ = '-';
        n = -n;
    }

    char s[36]; 
    int count = 0;

    do {
        int digit = n % base;
        s[count++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
        n /= base;
    } while (n > 0);

    for (int i = 0; i < count; i++) {
        sOut[i] = s[count - 1 - i];
    }
    sOut[count] = '\0';
}


/*
Converts an integer to base 4 codon format
*/
void itoDNAcodon(char* codon, int i)
{
    char bases[] = {'A', 'C', 'G', 'T'};
    int index = 0;

    for (int j = 0; j < 3; j++) {
        codon[2 - j] = bases[i % 4]; 
        i /= 4; 
    }

    codon[3] = '\0';
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
    char n1[30], n2[30], n3[30], result[30];
    int maxLen = (strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2)) + 1;

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    for (int i = 0; i < len1; i++) {
        if (s1[len1 - 1 - i] >= '0' && s1[len1 - 1 - i] <= '9') {
            n1[i] = s1[len1 - 1 - i] - '0';
        } else {
            n1[i] = s1[len1 - 1 - i] - 'A' + 10; 
        }
    }
    
    for (int i = 0; i < len2; i++) {
        if (s2[len2 - 1 - i] >= '0' && s2[len2 - 1 - i] <= '9') {
            n2[i] = s2[len2 - 1 - i] - '0';
        } else {
            n2[i] = s2[len2 - 1 - i] - 'A' + 10; 
        }
    }
    
    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int sumDigit = n1[i] + n2[i] + carry;
        result[i] = sumDigit % base; 
        carry = sumDigit / base;
    }

    int start = maxLen - 1;
    while (start >= 0 && result[start] == 0) {
        start--;
    }

    int sumIndex = 0;
    for (int i = start; i >= 0; i--) {
        if (result[i] < 10) {
            sum[sumIndex++] = result[i] + '0';
        } else {
            sum[sumIndex++] = result[i] - 10 + 'A'; 
        }
    }
    
    if (sumIndex == 0) {
        sum[sumIndex++] = '0';
    }
    
    sum[sumIndex] = '\0';
}



int main()
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
    char sIn2[] = "A4";
    char sOut2[35];
    long n2 = 0;

    n2 = my_atoi(sIn2, 19);
    printf("%s base 19 is %d base 10\n", sIn2, n2);

    my_itoa(n2, sOut2, 3);
    printf("%d base 10 is %s base 3\n", n2, sOut2);

    // now do it with DNA 
    char muhGenes[4] = "ACT";
    n = DNAcodontoi(muhGenes);
    printf("%s in DNA is %d base 10\n", muhGenes, n);

    // back to DNA cuz we can
    char buffy[4];
    itoDNAcodon(buffy, n);
    printf("%d base 10 is %s in DNA\n", n, muhGenes);

    char muhGenes2[4] = "GAT";
    n = DNAcodontoi(muhGenes2);
    printf("%s in DNA is %d base 10\n", muhGenes2, n);

    char buffy2[4];
    itoDNAcodon(buffy2, n);
    printf("%d base 10 is %s in DNA\n", n, muhGenes2);

    // test adding strings in arbitrary bases
    char s1[] = "543";
    char s2[] = "210";
    char sum[20];
    int b = 6;
    addInBase(s1, s2, sum, b);
    printf("%s + %s in base %d is %s\n", s1, s2, b, sum);

    char s3[] = "824";
    char s4[] = "55";
    char sum2[20];
    int b2 = 4;
    addInBase(s3, s4, sum2, b2);
    printf("%s + %s in base %d is %s\n", s3, s4, b2, sum2);

    char s5[] = "387";
    char s6[] = "621";
    char sum3[20];
    int b3 = 14;
    addInBase(s5, s6, sum3, b3);
    printf("%s + %s in base %d is %s\n", s5, s6, b3, sum3);

}