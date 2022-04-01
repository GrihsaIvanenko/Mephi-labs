#ifndef LAB3B_INIT_H
#define LAB3B_INIT_H

#include "structs.h"
#include <malloc.h>

Table *init();

Table *creatTable(int tableKeySpace2Size, int tableKeySpace1Head, int tableKeySpace2Timer, char *fileMain);

void printToFileFirst(Table *table);

#endif //LAB3B_INIT_H
