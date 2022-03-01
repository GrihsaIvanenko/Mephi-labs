#include <stdio.h>
#include "readline.h"
#include <string.h>
#include <malloc.h>

FILE *readInput() {
    FILE *ans = NULL;
    while (ans == NULL) {
        char *fname = readline("Enter Input file\n");
        ans = fopen(fname, "r");
        if (ans == NULL)
            printf("Error opening %s\n", fname);
        free(fname);
    }
    return ans;
}

FILE *readOutput() {
    FILE *ans = NULL;
    while (ans == NULL) {
        char *fname = readline("Enter Output file\n");
        ans = fopen(fname, "w");
        if (ans == NULL)
            printf("Error opening %s\n", fname);
        free(fname);

    }
    return ans;
}

int readInt();
int readBlockSize() {
    int ans = -1;
    while (ans == -1) {
        ans = readInt();
        if (ans == -1)
            printf("Error in input!\n");
    }
    return ans;
}

int AllDigits(char *s);
long long convert(char *s);
int readInt() {
    char *s = readline("Enter a positive number\n");
    int ans = -1;
    if (!(strlen(s) == 0 || strlen(s) > 10 || !AllDigits(s))) {
        long long val = convert(s);
        if (val > 0 && val < (1ll << 31))
            ans = (int)val;
    }
    free(s);
    return ans;
}

int AllDigits(char *s) {
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] < '0' || s[i] > '9')
            return 0;
    return 1;
}

long long convert(char *s) {
    long long ans = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        ans = ans * 10 + (s[i] - '0');
    return ans;
}

double readDouble();
double readP() {
    printf("Enter a number from 0 to 1 - P\n");
    double ans = -1;
    int ok = 0;
    while (ok == 0) {
        ans = readDouble();
        if (0.0 <= ans && ans <= 1.0)
            ok = 1;
        else
            printf("Error in input!\n");
    }
    return ans;
}

int AllDigitsOrPonint(char *s);
double convertDouble(char *s);
double readDouble() {
    char *s = readline("Enter a positive number\n");
    double ans = -1;
    if (!(strlen(s) == 0 || strlen(s) > 10 || !AllDigitsOrPonint(s))) {
        ans = convertDouble(s);
    }
    free(s);
    return ans;
}

int AllDigitsOrPonint(char *s) {
    int cnt = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] < '0' || s[i] > '9') {
            if (s[i] == '.')
                ++cnt;
            else
                return 0;
        }
    if (cnt <= 1)
        return 1;
    else
        return 0;
}

double convertDouble(char *s) {
    double firstPart = 0;
    double secondPart = 0;
    int sawPoint = 0;
    double pw = 1.0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            sawPoint = 1;
        } else if (sawPoint == 0) {
            firstPart = firstPart * 10.0 + (s[i] - '0');
        } else {
            pw /= 10.0;
            secondPart += (s[i] - '0') * pw;
        }
    }
    return firstPart + secondPart;
}