//
// Created by grigorijivanenko on 24.02.2022.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>

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