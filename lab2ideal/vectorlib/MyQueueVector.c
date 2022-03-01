//
// Created by grigorijivanenko on 23.02.2022.
//

#include "../main/block.h"
#include <stdlib.h>
#include "MyQueueVector.h"

Queue *createQueue(int SIZE) {
    printf("VECTOR---------------------------------------------------------------------------------\n");
    Queue *q = malloc(sizeof(Queue));
    q->size = 0;
    q->last = 0;
    q->SIZE_MAX = SIZE;
    q->data = malloc(q->SIZE_MAX * sizeof(Block*));
    for (int i = 0; i < q->SIZE_MAX; ++i) {
        q->data[i] = NULL;
    }
    return q;
}


Block* front(Queue * q) {
    if (q->size == 0)
        return NULL;
    return q->data[(q->last + q->size - 1) % q->SIZE_MAX];
}

int pop(Queue *q) {
    if (q->size == 0) {
        printf("Error doing pop!\n");
        return 1;
    }
    q->data[(q->last + q->size - 1) % q->SIZE_MAX] = NULL;
    q->size -= 1;
    return 0;
}

int prev(int pos, int mod);

int push(Queue *q, Block* NewValue) {
    printf("LOL\n");
    printf("%d bladokadabra\n", q->size);
    if (q->size == q->SIZE_MAX) {
        printf("ERROR, CAN NOT ADD NEW ELEMENT!\n");
        return 1;
    }
    printf("KEK\n");
    q->size += 1;
    q->last = prev(q->last, q->SIZE_MAX);
    printf("LAST %d\n", q->last);
    q->data[q->last] = NewValue;
    return 0;
}

int prev(int pos, int mod) {
    if (pos == 0)
        return mod - 1;
    return pos - 1;
}

void kill(Queue *q) {
    free(q->data);
    free(q);
}

