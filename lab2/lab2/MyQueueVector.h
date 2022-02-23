//
// Created by grigorijivanenko on 23.02.2022.
//

#ifndef LAB2_MYQUEUEVECTOR_H
#define LAB2_MYQUEUEVECTOR_H

#include "block.h"
#define SIZE_MAX 30

typedef struct Queue {
    int size;
    Block *data[SIZE_MAX];
    int last;
} Queue;

Queue *createQueue();

Block* front(Queue* q);

void pop(Queue *q);

void push(Queue *q, Block*);

#endif //LAB2_MYQUEUEVECTOR_H
