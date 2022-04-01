#include <stdio.h>
#include "readBase.h"

int dialogOptions(const char *opts[], int size) {//size < 10!
    for (int i = 0; i < size; ++i)
        puts(opts[i]);
    int ans = readInt(0, size - 1);
    return ans;
}

int dialogInt(char *what) {
    puts(what);
    int ans = readInt(0, 1000);
    return ans;
}

char *dialogLine(char *what) {
    char *ans = readline(what);
    return ans;
}

void printVerdict(char *what) {
    puts(what);
}