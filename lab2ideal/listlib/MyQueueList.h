//
// Created by grigorijivanenko on 23.02.2022.
//

#ifndef LAB2_MYQUEUELIST_H
#define LAB2_MYQUEUELIST_H

#include "../main/block.h"

typedef struct Item {
    Block *data;
    struct Item* prev;
} Item;

typedef struct Queue {
    int size;
    int SIZE_MAX;
    Item *First;
    Item *Last;
} Queue;

Queue *createQueue(int SIZE);

Block* front(Queue* q);

int pop(Queue *q);

int push(Queue *q, Block*);

void kill(Queue *q);

#endif //LAB2_MYQUEUELIST_H
