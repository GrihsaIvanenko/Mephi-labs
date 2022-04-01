#include "structs.h"
#include "../view/viewCommands.h"
#include "../model/modelCommands.h"
#include <string.h>
#include <malloc.h>

int deleteByKey1Release(Table *table, int ind, char *key1, int release);
int deleteTwoKeys(Table *table) {
    int kolvo = 0;
    char *key1 = dialogLine("Enter key1\n");
    char *key2 = dialogLine("Enter key2\n");
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *key2Table = getString(itemVector->key, table, NULL);
            if (strcmp(key2, key2Table) == 0) {
                free(key2Table);
                free(itemVector);
                kolvo += deleteByKey1Release(table, i, key1, -1);
            } else {
                free(key2Table);
                free(itemVector);
            }
        } else {
            free(itemVector);
        }
    }
    free(key1);
    free(key2);
    printf("%d elems deleted!\n", kolvo);
    return 1;
}

int deleteByKey1RopeRelease(Table *table, int id, char *key1, int release, int *kolvo);
int deleteByKey1Release(Table *table, int ind, char *key1, int release) {
    int kolvo = 0;
    ItemVector *itemVector = getItemVector(table, ind, NULL);
    itemVector->data = deleteByKey1RopeRelease(table, itemVector->data, key1, release, &kolvo);
    if (itemVector->data == -1) {
        itemVector->busyStatus = 0;
        itemVector->key = -1;
    }
    writeItemVector(table, itemVector, ind, NULL);
    free(itemVector);
    return kolvo;
}

void deleteItemListByAddress(Table *table, int id);
void updateNext(Table *table, int idItem, int newNext);
int deleteByKey1RopeRelease(Table *table, int id, char *key1, int release, int *kolvo) {
    int prev = -1;
    int first = -1;
    while (id != -1) {
        int addressItemList = addressItemListByData(table, id);
        ItemList *itemList = getItemList(table, addressItemList, NULL);
        char *key1Table = getString(itemList->key, table, NULL);
        Item *item = getItem(table, id, NULL);
        if (strcmp(key1, key1Table) == 0) {
            if (release == -1 || release == itemList->release) {
                *kolvo = *kolvo + 1;
                deleteItemListByAddress(table, addressItemList);
                updateNext(table, prev, item->next);
            } else {
                if (prev == -1)
                    first = id;
                prev = id;
            }
        } else {
            if (prev == -1)
                first = id;
            prev = id;
        }
        id = item->next;
        free(item);
        free(key1Table);
        free(itemList);
    }
    return first;
}

void deleteItemListByAddress(Table *table, int id) {
    int idPrev = -1;
    int nw = table->keySpace1->head;
    while (nw != id) {
        ItemList *itemList = getItemList(table, nw, NULL);
        idPrev = nw;
        nw = itemList->next;
        free(itemList);
    }
    if (idPrev == -1) {
        ItemList *itemList = getItemList(table, nw, NULL);
        table->keySpace1->head = itemList->next;
        FILE *file = fopen(table->fileMain, "r+b");
        fseek(file, sizeof(int), SEEK_SET);
        fwrite(&(table->keySpace1->head), sizeof(int), 1,file);
        fclose(file);
        free(itemList);
    } else {
        ItemList *prevItemList = getItemList(table, idPrev, NULL);
        ItemList *newItemList = getItemList(table, nw, NULL);
        prevItemList->next = newItemList->next;
        writeItemList(table, prevItemList, idPrev, NULL);
        free(prevItemList);
        free(newItemList);
    }
}

void updateNext(Table *table, int idItem, int newNext) {
    if (idItem == -1)
        return;
    Item *item = getItem(table, idItem, NULL);
    item->next = newNext;
    writeItem(table, item, idItem, NULL);
    free(item);
}

void deleteFromTableByKey1Release(Table *table, char *key, int release);
void deleteFromTableByKey2Release(Table *table, char *key, int release);
int deleteOneKey(Table *table) {
    const char *options[] = {
            "0. Delete by Key1",
            "1. Delete by Key2"
    };
    const int N = sizeof(options) / sizeof(options[0]);
    void (*deleter[ ])(Table *,  char *, int) = {
            deleteFromTableByKey1Release,
            deleteFromTableByKey2Release
    };
    int res = dialogOptions(options, N);
    char *key = dialogLine("Enter key\n");
    deleter[res](table, key, -1);
    free(key);
    return 1;
}

int deleteByKeyRelease(Table *table) {
    const char *options[] = {
            "0. Delete by Key1 and release",
            "1. Delete by Key2 and release"
    };
    const int N = sizeof(options) / sizeof(options[0]);
    void (*deleter[ ])(Table *,  char *, int) = {
            deleteFromTableByKey1Release,
            deleteFromTableByKey2Release
    };
    int res = dialogOptions(options, N);
    char *key = dialogLine("Enter key\n");
    int release = dialogInt("Enter release");
    deleter[res](table, key, release);
    free(key);
    return 1;
}

void deleteFromTableByKey1Release(Table *table, char *key, int release) {
    int kolvo = 0;
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            free(itemVector);
            kolvo += deleteByKey1Release(table, i, key, release);
        } else {
            free(itemVector);
        }
    }
    printf("%d elems deleted!\n", kolvo);
}

int deleteRopeByRelease(Table *table, int id, int release, int *kolvo);
void deleteFromTableByKey2Release(Table *table, char *key, int release) {
    int kolvo = 0;
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *key2 = getString(itemVector->key, table, NULL);
            if (strcmp(key2, key) == 0) {
                itemVector->data = deleteRopeByRelease(table, itemVector->data, release, &kolvo);
                if (itemVector->data == -1) {
                    itemVector->busyStatus = 0;
                    itemVector->key = -1;
                }
                writeItemVector(table, itemVector, i, NULL);
            }
            free(key2);
        }
        free(itemVector);
    }
    printf("%d elems deleted!\n", kolvo);
}

int deleteRopeByRelease(Table *table, int id, int release, int *kolvo) {
    int prev = -1;
    int first = -1;
    while (id != -1) {
        int addressItemList = addressItemListByData(table, id);
        ItemList *itemList = getItemList(table, addressItemList, NULL);
        Item *item = getItem(table, id, NULL);
        if (release == -1 || release == itemList->release) {
            *kolvo = *kolvo + 1;
            deleteItemListByAddress(table, addressItemList);
            updateNext(table, prev, item->next);
        } else {
            if (prev == -1)
                first = id;
            prev = id;
        }
        id = item->next;
        free(item);
        free(itemList);
    }
    return first;
}