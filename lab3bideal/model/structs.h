#ifndef LAB3B_STRUCTS_H
#define LAB3B_STRUCTS_H

typedef struct Item {
    int info;
    int release;
    int next;
} Item;

typedef struct ItemList {
    int key;
    int data;
    int next;
    int release;
} ItemList;

typedef struct ItemVector {
    int key;
    int data;
    int busyStatus;
} ItemVector;

typedef struct KeySpace1 {
    int head;
} KeySpace1;

typedef struct KeySpace2 {
    int tableSize;
    int timer;
} KeySpace2;

typedef struct Table {
    KeySpace1 *keySpace1;
    KeySpace2 *keySpace2;
    char *fileMain;
} Table;

#endif //LAB3B_STRUCTS_H
