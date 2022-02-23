//
// Created by grigorijivanenko on 23.02.2022.
//

#include "block.h"
#include <stdlib.h>
#include "MyQueueVector.h"
#define SIZE_MAX 30

Queue *createQueue() {
    printf("VECTOR---------------------------------------------------------------------------------\n");
    Queue *q = malloc(sizeof(Queue));
    q->size = 0;
    q->last = 0;
    for (int i = 0; i < SIZE_MAX; ++i) {
        q->data[i] = NULL;
    }
}


Block* front(Queue * q) {
    if (q->size == 0)
        return NULL;
    return q->data[(q->last + q->size - 1) % SIZE_MAX];
}

void pop(Queue *q) {
    if (q->size == 0) {
        printf("Error doing pop!\n");
        return;
    }
    q->data[(q->last + q->size - 1) % SIZE_MAX] = NULL;
    q->size -= 1;
}

int prev(int pos, int mod);

void push(Queue *q, Block* NewValue) {
    if (q->size == SIZE_MAX) {
        printf("ERROR, CAN NOT ADD NEW ELEMENT!\n");
        exit(1);
    }
    q->size += 1;
    q->last = prev(q->last, SIZE_MAX);
    q->data[q->last] = NewValue;
}

int prev(int pos, int mod) {
    if (pos == 0)
        return mod - 1;
    return pos - 1;
}



