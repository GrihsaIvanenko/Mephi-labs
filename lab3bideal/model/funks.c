#include <string.h>
#include <malloc.h>
#include "modelCommands.h"

char *creat(char *first, char *second, char *third) {
    int lenFirst = (int)strlen(first);
    int lenSecond = (int)strlen(second);
    int lenThird = (int)strlen(third);
    int len = lenFirst + lenSecond + lenThird;
    char *ans = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < lenFirst; ++i)
        ans[i] = first[i];
    for (int i = 0; i < lenSecond; ++i)
        ans[i + lenFirst] = second[i];
    for (int i = 0; i < lenThird; ++i)
        ans[i + lenFirst + lenSecond] = third[i];
    ans[len] = '\0';
    return ans;
}


char *strcop(char *it) {
    if (it == NULL)
        return NULL;
    char *ans = malloc(sizeof(char) * (strlen(it) + 1));
    for (int i = 0; i <= strlen(it); ++i)
        ans[i] = it[i];
    return ans;
}

int getHesh(char *s) {
    if (s == NULL)
        return 0;
    const long long MOD = 1000000007;
    const long long P = 997;
    long long ans = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        ans = (ans * P + (long long)(s[i])) % MOD;
    }
    int answer = (int)ans;
    return answer;
}
