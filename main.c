#include <stdio.h>

#ifdef TYPE
#include "MyQueueList.h"
#else
#include "MyQueueVector.h"
#endif

#include <stdlib.h>

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

FILE* readInput();
FILE *readOutput();
int readBlockSize();
double readP();
double GenRandomDouble();
void FirstEvent(Queue *q, FILE *input, int SIZE, int *inputFinished);
void SecondEvent(Queue *q, FILE *output);
int main() {
    FILE *input = readInput();
    FILE *output = readOutput();
    int SIZE = readBlockSize();
    double P = readP();
    printf("-----------------------------------end of input\n");
    Queue *q = createQueue();
    int inputFinished = 0;
    int stopper = 0;
    while ((!inputFinished || q->size) && !stopper ) {
        double randomDouble = GenRandomDouble();
        printf("%f  %f\n", randomDouble, P);
        if (randomDouble <= P)
            FirstEvent(q, input, SIZE, &inputFinished);
        else
            SecondEvent(q, output);
        printf("%d - qSIZE\n", q->size);
        //printf("Enter stopper");
        //scanf("%d", &stopper);
        printf("------------------------------------\n");
    }
    free(q);
    fclose(input);
    fclose(output);
    return 0;
}

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
    printf("Enter a pozitive number - size of block\n");
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

double GenRandomDouble() {
    int chisl = rand() + 1;
    return (double)(rand() % chisl) / (double)chisl;
}


Block *readBlock(FILE *input, int SIZE, int *inputFinished);
void FirstEvent(Queue *q, FILE *input, int SIZE, int *inputFinished) {
    if (*inputFinished) {
        printf("ReadAllData! ERROR!\n");
        return;
    }
    Block *newBlock = readBlock(input, SIZE, inputFinished);
    printf("%d = new size of block\n", newBlock->size);
    printf("Block readen!\n");
    push(q, newBlock);
}

Block* readBlock(FILE *input, int SIZE, int *inputFinished) {
    Block *ans = malloc(sizeof(Block));
    ans->size = 0;
    ans->data = malloc(0 * sizeof(char));
    for (int i = 0; i < SIZE; ++i) {
        int val = fgetc(input);
        if (val == -1) {
            *inputFinished = 1;
            return ans;
        }
        ans->size += 1;
        ans->data = realloc(ans->data, ans->size * sizeof(char));
        ans->data[ans->size - 1] = (char)val;
    }
    return ans;
}

void printBlock(Block *toPrint, FILE *output);
void SecondEvent(Queue *q, FILE *output) {
    Block *toPrint = front(q);
    if (toPrint == NULL) {
        printf("Error printing becaude of queue is empty!\n");
        return;
    }
    printBlock(toPrint, output);
    free(toPrint->data);
    free(toPrint);
    pop(q);
}

void printBlock(Block *b, FILE *output) {
    //printf("KAKA\n");
    //printf("%d - size\n", b->size);
    for (int i = 0; i < b->size; ++i) {
        fputc((int)b->data[i], output);
    }
}