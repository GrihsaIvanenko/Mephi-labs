//
// Created by grigorijivanenko on 23.02.2022.
//

#ifndef LAB2_MYQUEUEVECTOR_H
#define LAB2_MYQUEUEVECTOR_H

#include "../main/block.h"

typedef struct Queue {
    int size;
    int SIZE_MAX;
    Block **data;
    int last;
} Queue;

Queue *createQueue(int SIZE);

Block* front(Queue* q);

int pop(Queue *q);

int push(Queue *q, Block*);

void kill(Queue *q);

#endif //LAB2_MYQUEUEVECTOR_H
