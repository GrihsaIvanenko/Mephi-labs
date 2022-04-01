#include "structs.h"
#include "../view/viewCommands.h"
#include "../model/modelCommands.h"

Table *readTableFromFile(FILE *file, char *fileName);
Table *initFirst(char *fileMain);
Table *init() {
    char *tableName = dialogLine("Enter table name\n");
    char *fileMain = creat("../data/", tableName, ".bin");
    FILE *file = fopen(fileMain, "r+b");
    if (file == NULL) {
        initFirst(fileMain);
        file = fopen(fileMain, "r+b");
    }
    Table *ans = readTableFromFile(file, fileMain);
    fclose(file);
    free(tableName);
    free(fileMain);
    return ans;
}

Table *creatTable(int tableKeySpace2Size, int tableKeySpace1Head, int tableKeySpace2Timer, char *fileMain);
Table *readTableFromFile(FILE *file, char *fileName) {
    int tableKeySpace2Size, tableKeySpace1Head, tableKeySpace2Timer;
    fseek(file, 0, SEEK_SET);
    fread(&tableKeySpace2Size, sizeof(int), 1, file);
    fread(&tableKeySpace1Head, sizeof(int), 1, file);
    fread(&tableKeySpace2Timer, sizeof(int), 1, file);
    Table *ans = creatTable(tableKeySpace2Size, tableKeySpace1Head, tableKeySpace2Timer, fileName);
    return ans;
}

KeySpace1 *creatKeySpace1(int head);
KeySpace2 *creatKeySpace2(int mySize, int timer);
Table *creatTable(int tableKeySpace2Size, int tableKeySpace1Head, int tableKeySpace2Timer, char *fileMain) {
    Table *ans = malloc(sizeof(Table));
    ans->keySpace1 = creatKeySpace1(tableKeySpace1Head);
    ans->keySpace2 = creatKeySpace2(tableKeySpace2Size, tableKeySpace2Timer);
    ans->fileMain = strcop(fileMain);
    return ans;
}

KeySpace1 *creatKeySpace1(int head) {
    KeySpace1 *keySpace1 = malloc(sizeof(KeySpace1));
    keySpace1->head = head;
    return keySpace1;
}

KeySpace2 *creatKeySpace2(int mySize, int timer) {
    KeySpace2 *keySpace2 = malloc(sizeof(KeySpace2));
    keySpace2->tableSize = mySize;
    keySpace2->timer = timer;
    return keySpace2;
}


void printToFileFirst(Table *table);
Table *initFirst(char *fileMain) {
    int tableKeySpace2Size = dialogInt("Enter KeySpace2 size");
    Table *table = creatTable(tableKeySpace2Size, -1, 0, fileMain);
    printToFileFirst(table);
    killTable(table);
}

void printToFileFirst(Table *table) {
    FILE *file = fopen(table->fileMain, "w+b");
    fseek(file, 0, SEEK_SET);
    fwrite(&(table->keySpace2->tableSize), sizeof(int), 1, file);
    fwrite(&(table->keySpace1->head), sizeof(int), 1, file);
    fwrite(&(table->keySpace2->timer), sizeof(int), 1, file);
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        int nol = 0;
        int mins1 = -1;
        fwrite(&nol, sizeof(int), 1, file);
        fwrite(&mins1, sizeof(int), 1, file);
        fwrite(&mins1, sizeof(int), 1, file);
    }
    fclose(file);
}
