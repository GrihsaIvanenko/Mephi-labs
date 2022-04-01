#ifndef LAB3B_ADDING_H
#define LAB3B_ADDING_H

#include "structs.h"

int addTwoKeys(Table *table);

int addInTable(Table *table, char *key1, char *key2, char *info, int release);

int addressItemListByData(Table *table, int data);

#endif //LAB3B_ADDING_H
