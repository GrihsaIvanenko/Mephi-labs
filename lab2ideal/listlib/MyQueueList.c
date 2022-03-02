//
// Created by grigorijivanenko on 23.02.2022.
//

#include "../main/block.h"
#include "MyQueueList.h"

Queue *createQueue(int SIZE) {
    printf("LIST---------------------------------------------------------------------------------\n");
    Queue *ans = malloc(sizeof(Queue));
    ans->First = NULL;
    ans->Last = NULL;
    ans->size = 0;
    return ans;
}


Block* front(Queue * q) {
    if (q->size == 0)
        return NULL;
    return q->First->data;
}

int pop(Queue *q) {
    if (q->size == 0) {
        printf("Error doing pop!\n");
        return 1;
    }
    q->size -= 1;
    if (q->size == 0) {
        free(q->First);
        q->First = NULL;
        q->Last = NULL;
        return 0;
    }
    Item *NewFirst = q->First->prev;
    free(q->First);
    q->First = NewFirst;
    return 0;
}

Item *creat(Block *block);

int push(Queue *q, Block* NewValue) {
    Item *it = creat(NewValue);
    q->size += 1;
    if (q->size == 1) {
        q->First = it;
        q->Last = it;
        return 0;
    }
    q->Last->prev = it;
    q->Last = it;
    return 0;
}

Item* creat(Block *newValue) {
    Item *ans = malloc(sizeof(Item));
    ans->prev = NULL;
    ans->data = newValue;
}


void kill(Queue *q) {
    free(q);
}