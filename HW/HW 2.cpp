#include <iostream>
#include <cstring>

using namespace std;

int main() {
//1
    for(int i = 1; i <= 55; i++) {
        printf("%d", i^2 -1, " , ");
    }
printf("/n");
//2
    double quarterpi = 0;
	int num = 2000000;
	int i;
	int denom;
	double term;
	int sign = 1;

	printf("i   denom    term                                 pi\n");
	for (i = 0; i <= num; i++)
	{
		denom = i * 2 + 1;
		term = (1 / (double)denom);
		quarterpi = quarterpi + sign * term;
		sign = sign * (-1);

		printf("%d   %d        %.30f     %.30f\n", i, denom, term, quarterpi * 4);
	}
printf("/n");
//3
    string x = "abc";
    for(char ch = 'a'; ch < 'd'; ch++) {
        printf("{ ");
        for(char ch = 'a'; ch < 'd'; ch++) {
            for(char ch = 'a'; ch < 'd'; ch++) {
                printf("%d", ch);
            }
        }
        printf(" } ");
    }
printf("/n");
//4
    char sentence[] = "Jump in the Cadillac, girl, let's put some miles on it";
    printf("%d", sentence[0]);
    for(int i = 0; i < sizeof(sentence); i++) {
        if(sentence[i] == ' ') printf("%d", toupper(sentence[i + 1]));
    }
printf("/n");
//5
    char str[] = "aabbb";
    int strlength = strlen(str);

    // for each group size g
    int g = strlength;
    while (g > 0)
    {
        int c = g;
        int istart = 0;
        int istop = strlength - g;

        do {     // doing this g times

            // output the substring here
            for (int i = istart; i <= istop; i++)
            {
                printf("%c", str[i]);
            }
            printf("  ");

            istart++; istop++;

            c--;
        } while (c > 0);

        g--;
    }
}
