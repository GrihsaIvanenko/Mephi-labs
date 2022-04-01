#ifndef LAB3B_FILE_H
#define LAB3B_FILE_H

#include "structs.h"
#include <stdio.h>

ItemVector *getItemVector(Table *table, int id, FILE *file);

void writeItemVector(Table *table, ItemVector *itemVector, int itPos, FILE *file);

ItemList *getItemList(Table *table, long address, FILE *file);

void writeItemList(Table *table, ItemList *itemList, long where, FILE *file);

Item *getItem(Table *table, long address, FILE *file);

void writeItem(Table *table, Item *item, long address, FILE *file);

char *getString(int address, Table *table, FILE *file);

void writeString(int address, char *who, Table *table, FILE *file);

#endif //LAB3B_FILE_H
