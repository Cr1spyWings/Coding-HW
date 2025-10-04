/*
	Floating point arithmetic the HARD way.
	
	Dan Ross   Jan 2013

	Converts a floating point number from a string representation to
	an 8-bit representation using only INTEGER operations.  And vice-versa.
	This is usually done for us	by the preprocessor/compiler and library
	functions like atof().

	This program illustrates that float operations are computationally expensive.
	Thus, they are either done in software to save chip space, or in specialized 
	hardware to save execution time - this is the classic tradeoff in computer science.
	
	Here, we are pretending that neither our hardware or our compiler support floating
	point operations.  So we have to make our own!
	
	BIT FORMAT:
	1 sign bit
	4 mantissa bits
	3 exponent bits in excess 4 format   (range is -4 to 3)
	EXAMPLE: 3.5 = 11.1 = 1.1100 x 2^1 = 0 1100 101

	RANGE:
	smallest magnitude:  binary 1.0000 x 2 ^ -4 = 00.06250000   
	largest magnitude:   binary 1.1111 x 2 ^  3 = 15.50000000     (2 leading digits req'd)
	highest precision:   binary 1.0001 x 2 ^ -4 = 00.06640625     (8 trailing digits req'd)

	INPUT STRINGS:
	Input strings must be of the form: -X.X
	with 1 to 2 leading zeros and 1 to 8 trailing zeros
	and an optional minus sign
	Examples:
		0.0
		00.0000
		-1.2
		42.7777
		00.06640625

	Note:  A Finite Acceptor in the preprocessor would check the string format
	before converting it to binary

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
	for(int i = 0; i < exp; i++)
		x *= base;
	
	return x;
}

/*
Prints each bit of a byte
*/
void print8bits(unsigned char x)
{
	for(unsigned char mask = 0x80; mask; mask >>= 1) {
		if(mask & x) 
			printf("1");
		else 
			printf("0");
	}
}

/*
Prints each bit of a 16 bit int
*/
void print16bits(unsigned short x)
{
	for(unsigned short mask = 0x8000; mask; mask >>= 1) {
		if(mask & x) 
			printf("1");
		else 
			printf("0");
	}
}

/*
Converts a floating point number from a string representation to
an 8-bit representation using only INTEGER operations.
*/
unsigned char my_atof(char * str)
{
	char strIn[20];

	// check if negative and remove sign for convenience
	int negative = 0;
	if(str[0] == '-') {
		negative = 1;
		strcpy(strIn, str + 1);
	} else
		strcpy(strIn, str);
	
	int len = strlen(strIn);

	// buffers for the whole and the fractional parts
	#define S_WHOLE_SIZE 3
	char s_whole[S_WHOLE_SIZE] = "00";
	#define S_FRACT_SIZE 9
	char s_fract[S_FRACT_SIZE] = "00000000";

	// find the decimal point
	int x = 0;
	while(strIn[x] != '.')x++;

	// copy wholepart to a string buffer in reverse order
	for(int i = x - 1, j = 0; i >= 0; i--, j++)
		s_whole[j] = strIn[i];

	// copy fraction to a string buffer in reverse order
	for(int i = x + 1, j = S_FRACT_SIZE - 2; i < len; i++, j--)
		s_fract[j] = strIn[i];

	// convert whole part from a string to binary
	unsigned char i_whole = 0;
	for(int i = 0; i < S_WHOLE_SIZE - 1; i ++)
		i_whole += (s_whole[i] - '0') * my_pow(10, i);

	// check for overflow 
	if(i_whole > 15){   // (2 ^ n) - 1   in general
		printf("atof conversion Overflow %s", str);
		exit(0);
	}
	
	// convert fractional part from a string to binary (x 100,000,000 decimal)
	unsigned long i_fract = 0;
	for(int i = 0; i < S_FRACT_SIZE - 1; i ++)
		i_fract += (s_fract[i] - '0') * my_pow(10, i);

	// convert the fraction from integer to our floating binary format
	unsigned long powof2 = 50000000;
	unsigned char b_fract = 0;		// bits to the right of the decimal point
	unsigned char mask = 0x80;
	for(int i = 0; i < S_FRACT_SIZE - 1; i ++) {
		if(i_fract >= powof2) {   // check if bit needed
			b_fract |= mask;	  // insert this bit
			i_fract -= powof2;	  // subtract value
		}
		mask >>= 1;
		powof2 >>= 1;
	}

	// now pack the unnormalized bits to a 'bit field'
	unsigned short buffer = 0;
	buffer = i_whole;        // put the whole part in the high byte
	buffer <<= 8;
    buffer |= b_fract;		 // put the fraction part in the low byte
    	
	// check for underflow
	if(!buffer && i_fract){
		printf("atof conversion Underflow %s", str);
		exit(0);
	}

	// normalize - find the first 1 from left to right
	int exponent = 7;
	unsigned short mask2 = 0x8000;
	while(!(buffer & mask2)) {
		exponent--;
		mask2 >>= 1;
	}
	
	// overflow and underflow checks
	if(exponent > 3){ 
		printf("atof conversion Overflow %s", str);
		exit(0);
	}
	if(exponent < -4){ 
		printf("atof conversion Underflow %s", str);
		exit(0);
	}

	// final packing
	unsigned char theFloat = 0;	
	buffer <<= (7 - exponent);				// align mantissa
	buffer >>= 8;							// scoot into low byte
	theFloat = buffer;						// pack the mantissa
	theFloat &= 0x78;						// mask off the other stuff
	exponent += 4;							// the excess 4 thing
	theFloat |= exponent;					// insert the exponent
	if(negative) theFloat |= 0x80;			// insert sign bit

	return theFloat;
}

/*
Converts a floating point number from an 8-bit representation
to a string representation using only INTEGER operations.
*/
void my_ftoa(unsigned char f, char * strOut)
{
	int ch_p = 0;	// pointer to string chars
	
	if(f & 0x80) strOut[ch_p++] = '-';		// is it negative
	
	int exponent;
	exponent = (f & 0x07) - 4;				// get the exponent
	f &= 0x78;								// mask off everything except mantissa
	f |= 0x80;								// put on the leading 1

	// now pack the normalized bits to a 'bit field' so we can de-normalize it
	unsigned short buffer = 0;
	buffer = f;
	buffer <<= 8;							// scoot into high byte
	buffer >>= (7 - exponent);				// de-normalize

	// get the whole part
	unsigned char i_whole;					// bits to left of decimal
	i_whole = (buffer & 0xFF00) >> 8;

	// get the fractional part
	unsigned char b_fract;					// bits to right of decimal
	b_fract = (buffer & 0x00FF);

	// add up the bit values in the mantissa using INTEGERS only
	unsigned long i_fract = 0;
	if(b_fract & 0x80) i_fract += 50000000;
	if(b_fract & 0x40) i_fract += 25000000;
	if(b_fract & 0x20) i_fract += 12500000;
	if(b_fract & 0x10) i_fract +=  6250000;
	if(b_fract & 0x08) i_fract +=  3125000;
	if(b_fract & 0x04) i_fract +=  1562500;
	if(b_fract & 0x02) i_fract +=   781250;
	if(b_fract & 0x01) i_fract +=   390625;

	// convert to decimal string format 00.00000000 with optional leading '-'
	// first do the integer part

	// do the tens
	strOut[ch_p] = '0';
	while(i_whole >= 10){	// tens
		strOut[ch_p]++;		// count by characters
		i_whole -= 10;
	}
	ch_p++;					// next write spot
	
	// do the ones
	strOut[ch_p] = '0';
	while(i_whole >= 1){ 
		strOut[ch_p]++;  
		i_whole -= 1;
	}
	ch_p++;
	
	strOut[ch_p] = '.';			// decimal point
	ch_p++;

	// now do the fractional part

	// do the '10,000,000'
	strOut[ch_p] = '0';
	while(i_fract >= 10000000){ 
		strOut[ch_p]++;  
		i_fract -= 10000000;
	}
	ch_p++;

	// do the '1,000,000'
	strOut[ch_p] = '0';
	while(i_fract >= 1000000){ 
		strOut[ch_p]++;  
		i_fract -= 1000000;
	}
	ch_p++;

	// do the '100,000'
	strOut[ch_p] = '0';
	while(i_fract >= 100000){ 
		strOut[ch_p]++;  
		i_fract -= 100000;
	}
	ch_p++;

	// do the '10,000'
	strOut[ch_p] = '0';
	while(i_fract >= 10000){ 
		strOut[ch_p]++;  
		i_fract -= 10000;
	}
	ch_p++;

	// do the 'thousands'
	strOut[ch_p] = '0';
	while(i_fract >= 1000){ 
		strOut[ch_p]++;  
		i_fract -= 1000;
	}
	ch_p++;

	// do the 'hundreds'
	strOut[ch_p] = '0';
	while(i_fract >= 100){ 
		strOut[ch_p]++;  
		i_fract -= 100;
	}
	ch_p++;

	// do the 'tens'
	strOut[ch_p] = '0';
	while(i_fract >= 10){ 
		strOut[ch_p]++;  
		i_fract -= 10;
	}
	ch_p++;

	// do the 'ones'
	strOut[ch_p] = '0';
	while(i_fract >= 1){ 
		strOut[ch_p]++;  
		i_fract -= 1;
	}
	ch_p++;

	strOut[ch_p] = 0;	// null terminator
}

/*
Adds two 8-bit floating point numbers.
*/
unsigned char addFloats(unsigned char f1, unsigned char f2) {
    unsigned char mantissa1, mantissa2;
    int exponent1, exponent2, exponentResult;
    unsigned int mantissaResult;
    unsigned char sign1, sign2;

    sign1 = (f1 >> 7) & 0x01;
    exponent1 = (f1 >> 4) & 0x0F;
    mantissa1 = (f1 & 0x0F) | 0x10;

    sign2 = (f2 >> 7) & 0x01;
    exponent2 = (f2 >> 4) & 0x0F;
    mantissa2 = (f2 & 0x0F) | 0x10;
	
    if (exponent1 > exponent2) {
        mantissa2 >>= (exponent1 - exponent2);
        exponentResult = exponent1;
    } else if (exponent1 < exponent2) {
        mantissa1 >>= (exponent2 - exponent1);
        exponentResult = exponent2;
    } else {
        exponentResult = exponent1;
    }

    if (sign1 == sign2) {
        mantissaResult = mantissa1 + mantissa2;
    } else {
        if (mantissa1 >= mantissa2) {
            mantissaResult = mantissa1 - mantissa2;
        } else {
            mantissaResult = mantissa2 - mantissa1;
            sign1 = sign2; 
        }
    }

    if (mantissaResult >= 0x20) {
        mantissaResult >>= 1;
        exponentResult++;
    }

    if (exponentResult > 0x0F) {
        exponentResult = 0x0F;
    } else if (exponentResult < 0) {
        exponentResult = 0;
    }

    return (sign1 << 7) | (exponentResult << 4) | (mantissaResult & 0x0F);
}


/*
Multiplies two 8-bit floating point numbers.
*/
unsigned char multiplyFloats(unsigned char f1, unsigned char f2) {
    unsigned char mantissa1, mantissa2;
    int exponent1, exponent2, exponentResult;
    unsigned int mantissaResult;
    unsigned char sign1, sign2, resultSign;

    sign1 = (f1 >> 7) & 0x01;
    exponent1 = (f1 >> 4) & 0x0F;
    mantissa1 = (f1 & 0x0F) | 0x10; 

    sign2 = (f2 >> 7) & 0x01;
    exponent2 = (f2 >> 4) & 0x0F;
    mantissa2 = (f2 & 0x0F) | 0x10; 

    mantissaResult = mantissa1 * mantissa2;

    if (mantissaResult >= 0x100) {
        mantissaResult >>= 1;
        exponent1++;
    }

    exponentResult = (exponent1 + exponent2 - 7);

    if (exponentResult > 0x0F) {
        exponentResult = 0x0F;
    } else if (exponentResult < 0) {
        exponentResult = 0; 
    }

    resultSign = sign1 ^ sign2;

    return (resultSign << 7) | (exponentResult << 4) | ((mantissaResult >> 4) & 0x0F);
}


int main()
{
	char strIn1[40] = "0.125";
	char strIn2[40] = "4.5";
    char strIn3[40] = "3.25";
	char strIn4[40] = "0.5";
	char strOut[40];
    char strOut2[40];
	unsigned char f1;
	unsigned char f2;
	unsigned char f3; 
    unsigned char f4;
    unsigned char f5;
    unsigned char f6;

	// Multiply some stuff
	f1 = my_atof(strIn1);
	f2 = my_atof(strIn2);
	f3 = multiplyFloats(f1, f2);
	my_ftoa(f3, strOut);
	printf("%s * %s = %s\n", strIn1, strIn2, strOut);

    f5 = my_atof(strIn3);
    f6 = my_atof(strIn4);
    f3 = multiplyFloats(f5, f6);
    my_ftoa(f3, strOut);
	printf("%s * %s = %s\n", strIn3, strIn4, strOut);

    f3 = multiplyFloats(f1, f5);
    my_ftoa(f3, strOut);
	printf("%s * %s = %s\n", strIn1, strIn3, strOut);

    // Add some stuff
    f4 = addFloats(f1, f2);
    my_ftoa(f4, strOut2);
    printf("%s + %s = %s\n", strIn1, strIn2, strOut2);

    f4 = addFloats(f5, f6);
    my_ftoa(f4, strOut2);
    printf("%s + %s = %s\n", strIn3, strIn4, strOut2);

    f4 = addFloats(f2, f6);
    my_ftoa(f4, strOut2);
    printf("%s + %s = %s\n", strIn2, strIn4, strOut2);

    return 0;
}
