/*
    Argument Validator

    Dan Ross Oct 2016

    Generates an argument in table format and checks the argument for validity.

    Given the propositions:
    
        p = "The moon is made of cheese."
        q = "Winter is coming."

    The following argument is VALID:
    
        "The moon is made of cheese or winter is coming.  The moon is not made of cheese. Therefor, winter is coming."
    
    Symbolically:

        P1:  pVq
        P2:  !p
         Q:  q

    As stored in Argument table for validation:

              P1   P2   Q
    p    q    pVq  !p   q

    0    0    0    1    0   //row0
    0    1    1    1    1   //row1
    1    0    1    0    0   //row2
    1    1    1    0    1   //row3

  //0    1    2    3    4

    HOWEVER, The following argument is INVALID:

    "The moon is made of cheese or winter is coming.  The moon is made of cheese. Therefor, winter is coming."

    Symbolically:

    P1:  pVq
    P2:  p
     Q:  q

    As stored in Argument table for validation:

              P1   P2   Q
    p    q    pVq  p    q

    0    0    0    0    0   //row0
    0    1    1    0    1   //row1
    1    0    1    1    0   //row2     INVALID HERE
    1    1    1    1    1   //row3
    
*/
#include <stdio.h>
#pragma warning( disable : 4805)
#pragma warning( disable : 4800)

// Required logic function prototypes, in operation precedence order.
// See previous homework for truth table definitions.
bool NOT(bool p);           //not
bool AND(bool p, bool q);   //and
bool OR(bool p, bool q);    //inclusive or
bool XOR(bool p, bool q);   //exclusive or
bool IMP(bool p, bool q);   //implication
bool BCN(bool p, bool q);   //bicondition
bool MAY(bool p, bool q);   //maybe
bool BEC(bool p, bool q);   //because


/*
    The Argument table

    Column format is lil propositions, big (compound) propositions, conclusion:
    p, q, ... z, P1, P2, ... PN,  Q

    Row format is all pqr value permutations in binary count order:
    00
    01
    10
    11
    etc...

*/
#define LOTS 42
bool Argument[LOTS][LOTS];
int NLilProps;   // how many lil propositions, p thru z
int NBigProps;   // how many big propositions, P1 thru PN


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
Looks at filled Argument array and checks if it contains a valid argument

THE RULE IS:
For every row where all Premises, PX are true, then Conclusion Q is also true. 

YOU WRITE THIS
MUST work for ANY sized argument without modification
*/
bool IsValid()
{
    int rows = my_pow(2, NLilProps);
    for (int row = 0; row < rows; row++) {
        bool allPremisesTrue = true;
        
        // Check all premises (from columns 2 to NBigProps - 1)
        for (int col = 2; col < 2 + NBigProps - 1; col++) {
            if (!Argument[row][col]) {
                allPremisesTrue = false;
                break;
            }
        }
        
        // If all premises are true, then conclusion (last column) must also be true
        if (allPremisesTrue && !Argument[row][NLilProps + NBigProps - 1]) {
            return false;
        }
    }
    return true;
}


// Does what its name suggests
void PrintArgument()
{
    for (int row = 0, rows = my_pow(2, NLilProps); row < rows; row++)
    {
        for (int col = 0, cols = NLilProps + NBigProps; col < cols; col++)
            printf("%d    ", Argument[row][col]);
        printf("\n");
    }
}


/*
Implements OR logical operation.

Why?  To show another a way to do this kinda thing.
    Has a nice function syntax, makes writing long logic expressions syntactically consistent.
    Makes other logic operations easy to implement.
    Contains efficient code tricks.
*/
bool OR(bool p, bool q)
{
    // What OR means
    bool T[4] = { 0, 1, 1, 1 };

    // calculate index with bit operations for more fasterness
    // then do a lookup, also fast
    return T[(p << 1) | q];
}


/*
Implements NOT logical operation
*/
bool NOT(bool p)
{
    // What NOT means
    bool T[2] = { 1, 0 };

    // lookup
    return T[p];
}

// Logical AND
bool AND(bool p, bool q) {
    bool T[4] = { 0, 0, 0, 1 };
    return T[(p << 1) | q];
}

// Logical XOR (exclusive OR)
bool XOR(bool p, bool q) {
    bool T[4] = { 0, 1, 1, 0 };
    return T[(p << 1) | q];
}

// Logical Implication (p -> q, equivalent to !p OR q)
bool IMP(bool p, bool q) {
    bool T[4] = { 1, 1, 0, 1 };
    return T[(p << 1) | q];
}

// Logical Biconditional (p <-> q, equivalent to (p AND q) OR (!p AND !q))
bool BCN(bool p, bool q) {
    bool T[4] = { 1, 0, 0, 1 };
    return T[(p << 1) | q];
}

// "MAY" operation (interpret as NAND or similar custom behavior)
bool MAY(bool p, bool q) {
    bool T[4] = { 1, 1, 1, 0 };
    return T[(p << 1) | q];
}

// "BEC" operation (interpret as NOR or similar custom behavior)
bool BEC(bool p, bool q) {
    bool T[4] = { 1, 0, 0, 0 };
    return T[(p << 1) | q];
}

/* 
    "I'd like to have an argument, please."
    "I'm not allowed to argue unless you've paid."
    "...No it isn't."
*/
int main(void)
{

    // A fancy interactive parser would determine these values from user console input
    NLilProps = 2;
    NBigProps = 3;   // includes Q

    // **** THIS IS THE BEGINNING OF ONE ARGUMENT VALIDITY CHECK ****

    int rows = my_pow(2, NLilProps);    // how many rows
    int row = 0;                        // current row

    /* 
    Stores pqr permutations and a series of Compound Propositions (an Argument) into the Argument table.
    Calculates the value of HARDCODED compound (big) propositions for each value tuple of (lil) propositions
    For the homework, write similar loops and modify them with hardcoded big P's and Q for each of the Arguments, 
    print the new argument table and the validity check.  Easy peasy.
    Repeat as necesary for each Argument.
    */
    while (row < rows)
    {
        bool q = row & 1; bool p = row & 2;
        
        // NOTE: An INTERACTIVE version could send string expressions to an evaluator here
        bool P1 = OR(p, q);   // something like P1 = eval(strP1, p, q);  where str1 is "pVq" entered by the user.
        bool P2 = NOT(p);
        bool Q = q;

        // Fill the argument table
        Argument[row][0] = p;
        Argument[row][1] = q;
        Argument[row][2] = P1;
        Argument[row][3] = P2;
        Argument[row][4] = Q;

        row++;
    }
    
    // print out each argument
    printf("          P1   P2   Q\n");
    printf("p    q    pVq  !p   q\n\n");
    PrintArgument();
        
    // "Open the pod bay doors please HAL"
    // References are from the classic movie "2001: A Space Odyssey" REQUIRED viewing for all CS majors.
    if (IsValid())
        printf("Your argument is valid, Dave.  I enjoy working with humans.\n");
    else
        printf("I'm sorry Dave, but I'm afraid your argument is invalid.\n");

    // **** THIS IS THE END OF ONE ARGUMENT VALIDITY CHECK ****
    // COPY, PASTE, MODIFY FOR EACH ARGUMENT VALIDITY CHECK
    // **** BEGINNING OF ARGUMENT 2 ****
    NLilProps = 3;
    NBigProps = 3;
    rows = my_pow(2, NLilProps);
    row = 0;

    while (row < rows) {
        bool r = row & 1; 
        bool q = (row & 2) >> 1;
        bool p = (row & 4) >> 2;

        bool P1 = IMP(p, r);
        bool P2 = IMP(p, q);
        bool Q = IMP(p, AND(r, q));

        Argument[row][0] = p;
        Argument[row][1] = q;
        Argument[row][2] = r;
        Argument[row][3] = P1;
        Argument[row][4] = P2;
        Argument[row][5] = Q;
        row++;
    }

    printf("\nArgument 2:\n");
    printf("p    q    r    p->r p->q p->(rAq)\n");
    PrintArgument();
    printf(IsValid() ? "Valid\n" : "Invalid\n");

    // **** END OF ARGUMENT 2 ****

    // **** BEGINNING OF ARGUMENT 3 ****
    NLilProps = 2;
    NBigProps = 2;
    rows = my_pow(2, NLilProps);
    row = 0;

    while (row < rows) {
        bool s = row & 1; 
        bool q = (row & 2) >> 1;

        bool P1 = AND(q, NOT(q));
        bool Q = OR(q, s);

        Argument[row][0] = q;
        Argument[row][1] = s;
        Argument[row][2] = P1;
        Argument[row][3] = Q;
        row++;
    }

    printf("\nArgument 3:\n");
    printf("q    s    pA!p qVs\n");
    PrintArgument();
    printf(IsValid() ? "Valid\n" : "Invalid\n");

    // **** END OF ARGUMENT 3 ****

    // **** BEGINNING OF ARGUMENT 4 ****
    NLilProps = 4;
    NBigProps = 3;
    rows = my_pow(2, NLilProps);
    row = 0;

    while (row < rows) {
        bool s = row & 1; 
        bool r = (row & 2) >> 1;
        bool q = (row & 4) >> 2;
        bool p = (row & 8) >> 3;

        bool P1 = AND(IMP(p, q), IMP(r, s));
        bool P2 = OR(p, r);
        bool Q = OR(q, s);

        Argument[row][0] = p;
        Argument[row][1] = q;
        Argument[row][2] = r;
        Argument[row][3] = s;
        Argument[row][4] = P1;
        Argument[row][5] = P2;
        Argument[row][6] = Q;
        row++;
    }

    printf("\nArgument 4:\n");
    printf("p    q    r    s    (p->q)A(r->s) pVr qVs\n");
    PrintArgument();
    printf(IsValid() ? "Valid\n" : "Invalid\n");

    // **** END OF ARGUMENT 4 ****

    // **** BEGINNING OF ARGUMENT 5 ****
    NLilProps = 3;
    NBigProps = 3;
    rows = my_pow(2, NLilProps);
    row = 0;

    while (row < rows) {
        bool r = row & 1; 
        bool q = (row & 2) >> 1;
        bool p = (row & 4) >> 2;

        bool P1 = XOR(p, q);
        bool P2 = BCN(q, r);
        bool Q = r;

        Argument[row][0] = p;
        Argument[row][1] = q;
        Argument[row][2] = r;
        Argument[row][3] = P1;
        Argument[row][4] = P2;
        Argument[row][5] = Q;
        row++;
    }

    printf("\nArgument 5:\n");
    printf("p    q    r    p+q  q<->r  r\n");
    PrintArgument();
    printf(IsValid() ? "Valid\n" : "Invalid\n");

    // **** END OF ARGUMENT 5 ****

    // **** BEGINNING OF ARGUMENT 6 ****
    NLilProps = 3;
    NBigProps = 3;
    rows = my_pow(2, NLilProps);
    row = 0;

    while (row < rows) {
        bool r = row & 1; 
        bool q = (row & 2) >> 1;
        bool p = (row & 4) >> 2;

        bool P1 = MAY(p, r);
        bool P2 = BEC(p, q);
        bool Q = BCN(q, OR(r, p));

        Argument[row][0] = p;
        Argument[row][1] = q;
        Argument[row][2] = r;
        Argument[row][3] = P1;
        Argument[row][4] = P2;
        Argument[row][5] = Q;
        row++;
    }

    printf("\nArgument 6:\n");
    printf("p    q    r    p?r  p@q  q<->(r+p)\n");
    PrintArgument();
    printf(IsValid() ? "Valid\n" : "Invalid\n");

    // **** END OF ARGUMENT 6 ****
}