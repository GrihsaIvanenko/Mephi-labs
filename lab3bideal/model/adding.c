#include "modelCommands.h"
#include "../view/viewCommands.h"
#include <string.h>

int addInTable(Table *table, char *key1, char *key2, char *info, int release);
int addTwoKeys(Table *table) {
    char *key1 = dialogLine("Enter first key\n");
    char *key2 = dialogLine("Enter second key\n");
    char *info = dialogLine("Enter info\n");
    int res = addInTable(table, key1, key2, info, -1);
    if (res == 0)
        printVerdict("Elem Added!\n");
    if (res == 1)
        printVerdict("KeySpace2 Exception!\n");
    free(key1);
    free(key2);
    free(info);
    return 1;
}

int checkKeySpace2(Table *table, char *key1, char *key2);
void addInRope(Table *table, int ropeId, char *key1, char *key2, char *info, int release);
void addInEmptyRope(Table *table, char *key1, char *key2, char *info, int release);
int addInTable(Table *table, char *key1, char *key2, char *info, int release) {
    int res = checkKeySpace2(table, key1, key2);
    if (res == 1)
        return 1;
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *myKey2 = getString(itemVector->key, table, NULL);
            if (strcmp(myKey2, key2) == 0) {
                addInRope(table, itemVector->data, key1, key2, info, release);
                free(myKey2);
                free(itemVector);
                return 0;
            }
            free(myKey2);
        }
        free(itemVector);
    }
    int id = (getHesh(key2) + table->keySpace2->timer) % table->keySpace2->tableSize;
    ItemVector  *itemVector = getItemVector(table, id, NULL);
    if (itemVector->busyStatus == 1) {
        free(itemVector);
        return 1;
    }
    free(itemVector);
    addInEmptyRope(table, key1, key2, info, release);
    return 0;
}

int addressItemListByData(Table *table, int data);
int checkKeySpace2(Table *table, char *key1, char *key2) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *myKey2 = getString(itemVector->key, table, NULL);
            if (strcmp(myKey2, key2) == 0) {
                int addr = addressItemListByData(table, itemVector->data);
                ItemList *itemList = getItemList(table, addr, NULL);
                char *myKey1 = getString(itemList->key, table, NULL);
                if (strcmp(myKey1, key1) != 0) {
                    free(itemList);
                    free(myKey1);
                    free(myKey2);
                    free(itemVector);
                    return 1;
                }
                free(itemList);
                free(myKey1);
            }
            free(myKey2);
        }
        free(itemVector);
    }
    return 0;
}

int addressItemListByData(Table *table, int data) {
    int id = table->keySpace1->head;
    while (id != -1) {
        ItemList *itemList = getItemList(table, id, NULL);
        if (data == itemList->data) {
            free(itemList);
            return id;
        }
        id = itemList->next;
        free(itemList);
    }
    return -1;
}

int creatItem(Table *table, char *info, int release);
void addItemList(Table *table, char *key1, int itemAddress, int release);
void addInRope(Table *table, int ropeId, char *key1, char *key2, char *info, int release) {
    int id = ropeId;
    while (1) {
        Item *item = getItem(table, id, NULL);
        if (item->next == -1) {
            free(item);
            break;
        }
        id = item->next;
        free(item);
    }
    Item *prev = getItem(table, id, NULL);
    int resRelease = prev->release + 1;
    if (release != -1)
        resRelease = release;
    int nwId = creatItem(table, info, resRelease);
    prev->next = nwId;
    writeItem(table, prev, id, NULL);
    addItemList(table, key1, nwId, prev->release + 1);
    free(prev);
}
void addInEmptyRope(Table *table, char *key1, char *key2, char *info, int release) {
    int resRelease = 1;
    if (release != -1)
        resRelease = release;
    int nwId = creatItem(table, info, resRelease);
    addItemList(table, key1, nwId, 1);
    int posInKeySpace2 = (getHesh(key2) + table->keySpace2->timer) % table->keySpace2->tableSize;
    table->keySpace2->timer = (table->keySpace2->timer + 1) % table->keySpace2->tableSize;
    FILE *file = fopen(table->fileMain, "r+b");
    fseek(file, sizeof(int) * 2, SEEK_SET);
    fwrite(&(table->keySpace2->timer), sizeof(int), 1, file);
    fseek(file, 0, SEEK_END);
    int keyId = ftell(file);
    writeString(ftell(file), key2, table, file);
    ItemVector *itemVector = getItemVector(table, posInKeySpace2, file);
    itemVector->busyStatus = 1;
    itemVector->data = nwId;
    itemVector->key = keyId;
    writeItemVector(table, itemVector, posInKeySpace2, file);
    free(itemVector);
    fclose(file);
}

int creatItem(Table *table, char *info, int release) {
    Item *item = malloc(sizeof(Item));
    item->next = -1;
    item->release = release;
    item->info = -1;
    FILE *file = fopen(table->fileMain, "r+b");
    fseek(file, 0, SEEK_END);
    int id = ftell(file);
    writeItem(table, item, id, file);
    fseek(file, 0, SEEK_END);
    item->info = ftell(file);
    writeString(ftell(file), info, table, file);
    writeItem(table, item, id, file);
    free(item);
    fclose(file);
    return id;
}


void addItemList(Table *table, char *key1, int itemAddress, int release) {
    ItemList *itemList = malloc(sizeof(ItemList));
    itemList->next = table->keySpace1->head;
    itemList->data = itemAddress;
    itemList->release = release;
    itemList->key = -1;
    FILE *file = fopen(table->fileMain, "r+b");
    fseek(file, 0, SEEK_END);
    itemList->key = ftell(file);
    writeString(ftell(file), key1, table, file);
    fseek(file, 0, SEEK_END);
    table->keySpace1->head = ftell(file);
    writeItemList(table, itemList, ftell(file), file);
    fseek(file, sizeof(int), SEEK_SET);
    fwrite(&(table->keySpace1->head), sizeof(int), 1, file);
    fclose(file);
    free(itemList);
}