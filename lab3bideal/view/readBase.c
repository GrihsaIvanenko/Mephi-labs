#include <stdio.h>
#include <string.h>
#include <malloc.h>

char* readline(char *kek) {
    printf("%s", kek);
    char buf[51] = {0};
    char *res = NULL;
    int len = 0;
    int res_read = 0;
    do {
        res_read = scanf("%50[^\n]", buf);
        if (res_read > 0) {
            int new_part_len = strlen(buf);
            int new_len = len + new_part_len;
            res = realloc(res, new_len + 1);
            memcpy(res + len, buf, new_part_len);
            len = new_len;
            res[len] = '\0';
        } else if (res_read == 0) {
            scanf("%*c");
        } else {
            if (!res) {
                return NULL;
            }
        }
    } while (res_read > 0);
    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

int AllDigits(char *s);
long long convert(char *s);
int readInt(int MIN, int MAX) {//only not negative integers!
    char *errmsg = "";
    while (1) {
        char *s = readline(errmsg);
        int ans = -1;
        if (!(strlen(s) == 0 || strlen(s) > 10 || !AllDigits(s))) {
            long long val = convert(s);
            if (MIN <= val && val <= MAX) {
                ans = (int) val;
                free(s);
                return ans;
            }
        }
        printf("Enter integer in [%d, %d]\n", MIN, MAX);
        free(s);
    }
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

