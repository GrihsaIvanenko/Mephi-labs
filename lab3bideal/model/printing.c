#include "structs.h"
#include <malloc.h>
#include "modelCommands.h"

void printBaseInfoConsole(FILE *file, Table *table);
void printKeySpace1Console(FILE *file, Table *table);
void printKeySpace2Console(FILE *file, Table *table);
void printItemsConsole(FILE *file, Table *table);
int printTableConsole(Table *table) {
    FILE *file = fopen(table->fileMain, "r+b");
    printf("----INFO ABOUT TABLE--------\n");
    printBaseInfoConsole(file, table);
    printKeySpace1Console(file, table);
    printKeySpace2Console(file, table);
    printItemsConsole(file, table);
    printf("---------END----------------\n");
    fclose(file);
    return 1;
}

void printBaseInfoConsole(FILE *file, Table *table) {
    fseek(file, 0, SEEK_SET);
    int keySpace2TableSize;
    fread(&keySpace2TableSize, sizeof(int), 1, file);
    int keySpace1Head;
    fread(&keySpace1Head, sizeof(int), 1, file);
    int keySpace2Timer;
    fread(&keySpace2Timer, sizeof(int), 1, file);
    printf("KEYSPACE2 TABLE SIZE: %d in file; %d in struct\n", keySpace2TableSize, table->keySpace2->tableSize);
    printf("KEYSPACE1 HEAD ADDRESS: %d in file; %d in struct\n", keySpace1Head, table->keySpace1->head);
    printf("KEYSPACE2 TIMER: %d in file; %d in struct\n", keySpace2Timer, table->keySpace2->timer);
    printf("-------------------------\n");
}

void printKeySpace1Console(FILE *file, Table *table) {
    int id = table->keySpace1->head;
    while (id != -1) {
        ItemList *itemList = getItemList(table, id, file);
        char *key = getString(itemList->key, table, file);
        printf("ADDRESS %d; NEXT %d; KEY %d; DATA %d; RELEASE %d; %s - key\n",
               id, itemList->next, itemList->key, itemList->data, itemList->release, key);
        id = itemList->next;
        free(key);
        free(itemList);
    }
    printf("-------------------------\n");
}

void printKeySpace2Console(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, file);
        if (itemVector->busyStatus == 0) {
            printf("%d ELEM: free\n", i);
        } else {
            char *key = getString(itemVector->key, table, file);
            printf("%d ELEM: KEY %d; DATA %d; %s - key\n", i, itemVector->key, itemVector->data, key);
            free(key);
        }
        free(itemVector);
    }
    printf("-------------------------\n");
}

void printRopeConsole(FILE *file, Table *table, int id);
void printItemsConsole(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, file);
        if (itemVector->busyStatus == 1)
            printRopeConsole(file, table, itemVector->data);
        free(itemVector);
    }
    printf("-------------------------\n");
}

void printRopeConsole(FILE *file, Table *table, int id) {
    while (id != -1) {
        Item *item = getItem(table, id, file);
        char *info = getString(item->info, table, file);
        printf("ADDRESS %d; NEXT %d; INFO %d; RELEASE %d; %s - info\n",
               id, item->next, item->info, item->release, info);
        id = item->next;
        free(info);
        free(item);
    }
    printf("------------\n");
}