/*
Set operations

Dan Ross
   Original Feb 2013, 32bit extension Sep 2016
   Minor annotations, Sep 2020

Performs set operations.

Universe = {Bat, Cat, Chimp, Dog, Fish, Liger, Snake, Turtle}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#pragma warning( disable : 4996) 
#pragma warning( disable : 4244) 

// Start with a small universe
char Universe[8][10] = { "Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle" };
typedef unsigned char set;          // a set, by any other name, would smell as sweet.

// Then use this big universe
char BigUniverse[32][20] = {
    "Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle",
    "Bear", "Dragon", "Horse", "Wolf", "Rat", "Gerbil", "Rabbit", "Monkey",
    "Donkey", "Llama", "Zebra", "Hippopotamus", "Rhiceros", "Gecko", "Frog", "Sloth",
    "Deer", "Kangaroo", "Gorilla", "Alligator", "Panda", "Squirrel", "Duck", "Platypus" };
typedef unsigned long int set32;    // a set, but bigger


/*
Prints out a set in set-sequence notation
*/
void printSet(set32 A)
{
  printf("{ ");
    
    bool commaflag = false;
    for (int i = 0; i < 32; ++i) {
        if (A & (0x1UL << i)) {
            if (commaflag) printf(", ");
            printf("%s", BigUniverse[i]);
            commaflag = true;
        }
    }
    printf(" }");
}


/*
Prints each bit of a byte
*/
void print8bits(unsigned char x)
{
   for (unsigned char mask = 0x80; mask; mask >>= 1) {
      if (mask & x)
         printf("1");
      else
         printf("0");
   }
}


/*
Inserts an element of the universe into a set

Hashing calculation example: insert(A, "Chimp");
Asci C = 67, i = 105.   67 + 105 % 20 = 12, element 12 in the lookup table is 2.
So the index of Chimp = 2 in the Universe table, so we insert a bit into the set at bit position 2.
*/
void insert(set32& A, const char str[])
{
   // First we need to get the Universe index of this string
   // Use hashing instead of searching - cuz it is faster 
   // than searching, especially for a big universe.

   // You will have to modify this for the 32bit universe
   // If you do not know how to hash && do not want to learn now
   // then modify this to use a loop search lookup with strcmp

   // get a unique hash for each string
   // Calculate a hash value within the range 0 to 31
    int index = -1;
    for (int i = 0; i < 32; ++i) {
        if (strcmp(BigUniverse[i], str) == 0) {
            index = i;
            break;
        }
    }

    // Ensure the index is valid and within the range of 0 to 31
    if (index >= 0 && index < 32) {
        // Create a mask with the bit corresponding to the index set
        set32 mask = 0x1UL << index;
        // Insert this element into the set
        A |= mask;
    }
}


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


////////////// YOU WRITE THE FOLLOWING /////////////////

/*
Union
*/
set32 Union(set32 A, set32 B)
{
   A = A | B;
   return A;
}

/*
Intersection
*/
set32 Intersection(set32 A, set32 B)
{
   A = A & B;
   return A;
}

/*
Complement
*/
set32 Complement(set32 A)
{
   A = ~A;
   return A;
}

/*
Difference
*/
set32 Difference(set32 A, set32 B)
{
   A = A & ~B;
   return A;
}

/*
Cardinality
*/
int Cardinality(set32 A)
{
   int count = 0;
   while(A) {
      count += A & 1;
      A >>= 1;
   }
   return count;
}

/*
PowerSet  Algorithm:
*/
void printPowerSet(set32 A)
{
   int numElements = Cardinality(A);
    int numSubsets = (1 << numElements); // 2^numElements

    // Iterate through all possible subsets
    for (int subset = 0; subset < numSubsets; ++subset) {
        set32 subA = 0;
        int bitIndex = 0;

        // Build subset subA
        for (int i = 0; i < 32; ++i) {
            if (A & (0x1UL << i)) { // Check if the i-th bit is set in A
                if (subset & (1 << bitIndex)) { // If the bitIndex-th bit is set in subset
                    subA |= (0x1UL << i); // Include this element in subA
                }
                bitIndex++; // Move to the next bit
            }
        }

        // Print the subset
        printf("{");
        bool first = true;
        for (int i = 0; i < 32; ++i) {
            if (subA & (0x1UL << i)) { // Check if the i-th bit is set in subA
                if (!first) printf(", ");
                printf("%s", BigUniverse[i]);
                first = false;
            }
        }
        printf("}\n");
    }
}

bool IsSubset(set32 ASubset, set32 ASet) {
   return (ASubset & ASet) == ASubset;
}

bool IsProperSubset(set32 ASubset, set32 ASet) {
   bool isSubset = (ASubset & ASet) == ASubset;
   bool isNotEqual = ASubset != ASet;
   return isSubset && isNotEqual;
}

/*********************************************************
main - modify as necessary with various test data
*********************************************************/
int main(void) {
   set32 A = 0;

   insert(A, "Bat");
   insert(A, "Dragon");
   insert(A, "Hippopotamus");
   insert(A, "Gecko");
   insert(A, "Sloth");
   insert(A, "Deer");
   insert(A, "Kangaroo");

   printf("Set A: ");
   printSet(A);
   printf("\nCardinality: ");
   printf("%d", Cardinality(A));

   printf("\n\nPowerSet(A):\n");
   printPowerSet(A);

   set32 B = 0;
   insert(B, "Hippopotamus");
   insert(B, "Gecko");
   insert(B, "Sloth");
   insert(B, "Bat");
   insert(B, "Rhinoceros");
   insert(B, "Squirrel");
   insert(B, "Platypus");

   printf("\nSet B: ");
   printSet(B);

   set32 C = 0;
   insert(C, "Gecko");
   insert(C, "Sloth");
   insert(C, "Bat");
   insert(C, "Rhinoceros");
   insert(C, "Dog");
   insert(C, "Fish");
   insert(C, "Horse");
   insert(C, "Snake");
   insert(C, "Turtle");
   insert(C, "Donkey");
   insert(C, "Gorilla");
   insert(C, "Llama");
   printf("\nSet C: ");
   printSet(C);

   printf("\n(A Union B) Inter ~C: ");
   set32 D = Intersection(Union(A, B), ~C);
   printSet(D);

   printf("\nA Union (B Inter C): ");
   set32 E = Union(A, Intersection(B, C));
   printSet(E);

   printf("\n~(A Inter B): ");
   set32 G = ~Intersection(A, B);
   printSet(G);

   printf("\n(~A Union ~B): ");
   set32 H = Union(~A, ~B);
   printSet(H);

   printf("\nA Dif B: ");
   set32 F = Difference(A, B);
   printSet(F);

   if (IsSubset(A, B))
      printf("\nA is a subset of B");
   else
      printf("\nA is NOT a subset of B");

   if (IsProperSubset(A, B))
      printf("\nA is a proper subset of B");
   else
      printf("\nA is NOT a proper subset of B");

   printf("\n(~A Union ~B) Dif C: ");
   set32 I = Difference((~A, ~B), C);
   printSet(I);

   printf("\n(A Inter B) Union ~C: ");
   set32 J = Union(Intersection(A, B), ~C);
   printSet(J);

   printf("\n");
}