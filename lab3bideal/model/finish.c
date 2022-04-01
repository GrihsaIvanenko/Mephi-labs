#include "structs.h"
#include "malloc.h"
#include "modelCommands.h"

void killTable(Table *table);
void finish(Table *table) {
    printToFile(table);
    killTable(table);
}

void killKeySpace1(KeySpace1 *keySpace1);
void killKeySpace2(KeySpace2 *keySpace2);
void killTable(Table *table) {
    killKeySpace1(table->keySpace1);
    killKeySpace2(table->keySpace2);
    free(table->fileMain);
    free(table);
}

void killKeySpace1(KeySpace1 *keySpace1) {
    free(keySpace1);
}

void killKeySpace2(KeySpace2 *keySpace2) {
    free(keySpace2);
}

