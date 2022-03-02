#include <stdio.h>
#include <stdlib.h>
#include "inputOutput.h"

#ifdef VECTOR
#include "../vectorlib/MyQueueVector.h"
#else
#include "../listlib/MyQueueList.h"
#endif


double GenRandomDouble();
int FirstEvent(Queue *q, FILE *input, int SIZE, int *inputFinished);
int SecondEvent(Queue *q, FILE *output);
int main() {
    FILE *input = readInput();
    FILE *output = readOutput();
    printf("Enter a pozitive number - size of block\n");
    int SIZE = readBlockSize();
    int VECTOR_SIZE = 0;
    double P = readP();
#ifdef VECTOR
    printf("Enter a pozitive number - size of vector\n");
    VECTOR_SIZE = readBlockSize();
#endif
    printf("-----------------------------------end of input\n");
    Queue *q = createQueue(VECTOR_SIZE);
    int inputFinished = 0;
    int stopper = 0;
    while ((!inputFinished || q->size) && !stopper ) {
        double randomDouble = GenRandomDouble();
        printf("%f  %f\n", randomDouble, P);
        int status = 0;
        if (randomDouble <= P)
            status = FirstEvent(q, input, SIZE, &inputFinished);
        else
            status = SecondEvent(q, output);
        if (status == 1) {
            printf("Error doing event!\n");
            return 1;
        }
        printf("%d - qSIZE\n", q->size);
        //printf("Enter stopper");
        //scanf("%d", &stopper);
        printf("------------------------------------\n");
    }
    kill(q);
    fclose(input);
    fclose(output);
    return 0;
}



double GenRandomDouble() {
    int chisl = rand() + 1;
    return (double)(rand() % chisl) / (double)chisl;
}


Block *readBlock(FILE *input, int SIZE, int *inputFinished);
int FirstEvent(Queue *q, FILE *input, int SIZE, int *inputFinished) {
    if (*inputFinished) {
        printf("ReadAllData! ERROR!\n");
        return 0;
    }
    Block *newBlock = readBlock(input, SIZE, inputFinished);
    printf("%d = new size of block\n", newBlock->size);
    printf("Block readen!\n");
    return push(q, newBlock);
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
int SecondEvent(Queue *q, FILE *output) {
    Block *toPrint = front(q);
    if (toPrint == NULL) {
        printf("Error printing becaude of queue is empty!\n");
        return 0;
    }
    printBlock(toPrint, output);
    free(toPrint->data);
    free(toPrint);
    return pop(q);
}

void printBlock(Block *b, FILE *output) {
    //printf("KAKA\n");
    //printf("%d - size\n", b->size);
    for (int i = 0; i < b->size; ++i) {
        fputc((int)b->data[i], output);
    }
}