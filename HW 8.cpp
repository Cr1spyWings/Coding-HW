#include <iostream>

using namespace std;

bool Implication(bool a, bool b) {
    return !a || b;
}

bool Bicondition(bool a, bool b) {
    return a == b;
}

bool Maybe(bool a, bool b) {
    return a || b;
}

bool Because(bool a, bool b) {
    return !b || a;
}

bool And(bool a, bool b) {
    return a && b;
}

bool Or(bool a, bool b) {
    return a || b;
}

bool Xor(bool a, bool b) {
    return a != b;
}

bool Not(bool a) {
    return !a;
}

int main() {
    bool equiv = true;
    bool P1, P2;

    //Test A
    printf("p q | p | q | ~(~p & ~q)\n\n");
    for (bool p : {false, true}) {
        for (bool q : {false, true}) {
            P1 = Or(p, q);
            P2 = Not(And(Not(p), Not(q)));
            if (P1 != P2) equiv = false;
            printf("%d %d | %d | %d\n", p, q, P1, P2);
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");

    //Test B
    equiv = true;
    printf("p q r | p & (q -> r) | (p & q) ^ r \n\n");
    for (bool p : {false, true}) {
        for (bool q : {false, true}) {
            for (bool r : {false, true}) {
                P1 = And(p, Implication(q, r));
                P2 = Xor(And(p, q), r);
                if (P1 != P2) equiv = false;
                printf("%d %d %d | %d | %d\n", p, q, r, P1, P2);
            }
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");

    //Test C
    equiv = true;
    printf("p q | p <-> q | ~(p ^ q)\n\n");
    for (bool p : {false, true}) {
        for (bool q : {false, true}) {
            P1 = Bicondition(p, q);
            P2 = Not(Xor(p, q));
            if (P1 != P2) equiv = false;
            printf("%d %d | %d | %d\n", p, q, P1, P2);
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");

    //Test D
    equiv = true;
    printf("p q r | (p <-> q) -> r | p & (~q | r) \n\n");
    for (bool p : {false, true}) {
        for (bool q : {false, true}) {
            for (bool r : {false, true}) {
                P1 = Implication(Bicondition(p, q), r);
                P2 = And(p, Or(Not(q), r));
                if (P1 != P2) equiv = false;
                printf("%d %d %d | %d | %d\n", p, q, r, P1, P2);
            }
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");

    //Test E
    equiv = true;
    printf("p q r | ~(p -> (q & r)) | p & ~(q & r) \n\n");
    for(bool p : {false, true}) {
        for (bool q : {false, true}) {
            for (bool r : {false, true}) {
                P1 = Not((Implication(p, And(q, r))));
                P2 = And(p, Not(And(q, r)));
                if (P1 != P2) equiv = false;
                printf("%d %d %d | %d | %d\n", p, q, r, P1, P2);
            }
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");

    //Test F
    equiv = true;
    printf("p q | p | (p ? q) | p & (p @ q)\n\n");
    for (bool p : {false, true}) {
        for (bool q : {false, true}) {
            P1 = Or(p, Maybe(p, q));
            P2 = And(p, Because(p, q));
            if (P1 != P2) equiv = false;
            printf("%d %d | %d | %d\n", p, q, P1, P2);
        }
    }
    if (equiv) printf("These expressions are equivalent\n\n\n");
    else printf("These expressions are NOT equivalent\n\n\n");
}