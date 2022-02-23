//
// Created by grigorijivanenko on 23.02.2022.
//

#ifndef LAB2_MYQUEUELIST_H
#define LAB2_MYQUEUELIST_H

#include "block.h"

typedef struct Item {
    Block *data;
    struct Item* prev;
} Item;

typedef struct Queue {
    int size;
    Item *First;
    Item *Last;
} Queue;

Queue *createQueue();

Block* front(Queue* q);

void pop(Queue *q);

void push(Queue *q, Block*);

#endif //LAB2_MYQUEUELIST_H
