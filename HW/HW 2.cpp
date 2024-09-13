#include <iostream>
#include <cstring>

int main() {
//1
    for(int i = 1; i <= 55; i++) {
        printf("%d", i^2 -1);
        printf(", ");
    }
printf("\n");
//2
    double pi = 0, term;
	int num = 2000, i, denom, sign = 1;

	printf("i   denom    term                                 pi\n");
	for (i = 0; i <= num; i++) {
		denom = i * 2 + 1;
		term = (1 / (double)denom);
		pi = pi + sign * term * 4;
		sign = sign * (-1);

		printf("%d   %d        %.30f     %.30f\n", i, denom, term, pi);
	}
printf("\n");
//3
    char x[] = "abc";
    for (char ch1 = 0; ch1 < 3; ch1++) {
        for (char ch2 = 0; ch2 < 3; ch2++) {
            for (char ch3 = 0; ch3 < 3; ch3++) {
                printf("{ %c%c%c } ", x[ch1], x[ch2], x[ch3]);
            }
        }
    }
printf("\n");
//4
    char sentence[] = "Jump in the Cadillac, girl, let's put some miles on it";
    printf("%c", sentence[0]);
    for(int i = 0; i < sizeof(sentence) - 1; i++) {
        if(sentence[i] == ' ') {
            char nextChar = sentence[i + 1];
            if(nextChar >= 'a' && nextChar <= 'z') {
                printf("%c", nextChar - 32);
            } else {
                printf("%c", nextChar);
            }
        }
    }
printf("\n");
//5
    char str[] = "aabbb";
    int strlength = strlen(str);

    for (int start = 0; start < strlength; start++) {
        for (int len = 1; len <= strlength - start; len++) {
            for (int i = start; i < start + len; i++) {
                printf("%c", str[i]);
            }
            printf("  ");
        }
    }
    printf("\n");
}
