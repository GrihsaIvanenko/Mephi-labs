//
// Created by grigorijivanenko on 23.02.2022.
//

#include "block.h"
#include "MyQueueList.h"

Queue *createQueue() {
    printf("LIST---------------------------------------------------------------------------------\n");
    Queue *ans = malloc(sizeof(Queue));
    ans->First = NULL;
    ans->Last = NULL;
    ans->size = 0;
}


Block* front(Queue * q) {
    if (q->size == 0)
        return NULL;
    return q->First->data;
}

void pop(Queue *q) {
    if (q->size == 0) {
        printf("Error doing pop!\n");
        return;
    }
    q->size -= 1;
    if (q->size == 0) {
        free(q->First);
        q->First = NULL;
        q->Last = NULL;
        return;
    }
    Item *NewFirst = q->First->prev;
    free(q->First);
    q->First = NewFirst;
}

Item *creat(Block *block);

void push(Queue *q, Block* NewValue) {
    Item *it = creat(NewValue);
    q->size += 1;
    if (q->size == 1) {
        q->First = it;
        q->Last = it;
        return;
    }
    q->Last->prev = it;
    q->Last = it;
}

Item* creat(Block *newValue) {
    Item *ans = malloc(sizeof(Item));
    ans->prev = NULL;
    ans->data = newValue;
}


