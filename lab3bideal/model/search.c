#include "structs.h"
#include "../view/viewCommands.h"
#include "../model/modelCommands.h"
#include <malloc.h>
#include "string.h"

int printRopeSearch(Table *table, int id);
int searchTwoKeys(Table *table) {
    char *key1 = dialogLine("Enter key1\n");
    char *key2 = dialogLine("Enter key2\n");
    int kolvo = 0;
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *itKey2 = getString(itemVector->key, table, NULL);
            if (strcmp(itKey2, key2) == 0) {
                int addressItemList = addressItemListByData(table, itemVector->data);
                ItemList *itemList = getItemList(table, addressItemList, NULL);
                char *itKey1 = getString(itemList->key, table, NULL);
                if (strcmp(itKey1, key1) == 0)
                    kolvo += printRopeSearch(table, itemVector->data);
                free(itKey1);
                free(itemList);
            }
            free(itKey2);
        }
        free(itemVector);
    }
    printf("%d Elems found!\n", kolvo);
    free(key1);
    free(key2);
    return 1;
}

int printRopeSearch(Table *table, int id) {
    int ans = 0;
    while (id != -1) {
        ++ans;
        Item *item = getItem(table, id, NULL);
        char *info = getString(item->info, table, NULL);
        printf("%s - info; %d - release\n", info, item->release);
        free(info);
        id = item->next;
        free(item);
    }
    return ans;
}

Table *creatResTable(Table *table);
void searchByKey1Release(Table *where, Table *ans, char *who, int release);
void searchByKey2Release(Table *where, Table *ans, char *who, int release);
int searchOneKey(Table *table) {
    Table *tableNew = creatResTable(table);
    const char *options[] = {
            "0. Search by Key1",
            "1. Search by Key2"
    };
    const int N = sizeof(options) / sizeof(options[0]);
    void (*search[ ])(Table *, Table *, char *, int) = {
            searchByKey1Release,
            searchByKey2Release
    };
    int res = dialogOptions(options, N);
    char *key = dialogLine("Enter key\n");
    search[res](table, tableNew, key, -1);
    free(key);
    killTable(tableNew);
    return 1;
}

Table *creatResTable(Table *table) {
    char *fileResult;
    while (1) {
        char *name = dialogLine("Enter name of file with results\n");
        fileResult = creat("../data/", name, ".bin");
        free(name);
        FILE *file = fopen(fileResult, "rb");
        if (file == NULL)
            break;
        fclose(file);
        printf("FILE EXISTS!\n");
        free(fileResult);
    }
    Table *tableNew = creatTable(table->keySpace2->tableSize,
                                 -1, 0, fileResult);
    free(fileResult);
    printToFileFirst(tableNew);
    return tableNew;
}

char *getKey2ByAddress(Table *table, int address);
void searchByKey1Release(Table *where, Table *ans, char *who, int release) {
    int id = where->keySpace1->head;
    int kolvo = 0;
    while (id != -1) {
        ItemList *itemList = getItemList(where, id, NULL);
        char *key1 = getString(itemList->key, where, NULL);
        if (strcmp(key1, who) == 0) {
            if (release == -1 || itemList->release == release) {
                ++kolvo;
                Item *item = getItem(where, itemList->data, NULL);
                char *info = getString(item->info, where, NULL);
                char *key2 = getKey2ByAddress(where, itemList->data);
                addInTable(ans, key1, key2, info, item->release);
                free(key2);
                free(info);
                free(item);
            }
        }
        free(key1);
        id = itemList->next;
        free(itemList);
    }
    printf("%d elem added!\n", kolvo);
}

int hasAddressInRope(Table *table, int id, int address);
char *getKey2ByAddress(Table *table, int address) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus == 1) {
            if (hasAddressInRope(table, itemVector->data, address) == 1) {
                char *ans = getString(itemVector->key, table, NULL);
                free(itemVector);
                return ans;
            }
        }
        free(itemVector);
    }
}

int hasAddressInRope(Table *table, int id, int address) {
    while (id != -1) {
        if (id == address)
            return 1;
        Item *item = getItem(table, id, NULL);
        id = item->next;
        free(item);
    }
    return 0;
}

int addRopeSearch(Table *where, Table *to, int id, int release,char *key2);
void searchByKey2Release(Table *where, Table *to, char *who, int release) {
    int kolvo = 0;
    for (int i = 0; i < where->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(where, i, NULL);
        if (itemVector->busyStatus == 1) {
            char *key = getString(itemVector->key, where, NULL);
            if (strcmp(key, who) == 0)
                kolvo += addRopeSearch(where, to, itemVector->data, release, key);
            free(key);
        }
        free(itemVector);
    }
    printf("%d elem added!\n", kolvo);
}

int addRopeSearch(Table *where, Table *to, int id, int release, char *key2) {
    int kolvo = 0;
    while (id != -1) {
         Item *item = getItem(where, id, NULL);
         if (release == -1 || item->release == release) {
             char *info = getString(item->info, where, NULL);
             int addressItemList = addressItemListByData(where, id);
             ItemList *itemList = getItemList(where, addressItemList, NULL);
             char *key1 = getString(itemList->key, where, NULL);
             addInTable(to, key1, key2, info, release);
             ++kolvo;
             free(key1);
             free(itemList);
             free(info);
         }
         id = item->next;
         free(item);
    }
    return kolvo;
}

int searchByKeyRelease(Table *table){
    Table *tableNew = creatResTable(table);
    const char *options[] = {
            "0. Search by Key1 and release",
            "1. Search by Key2 and release"
    };
    const int N = sizeof(options) / sizeof(options[0]);
    void (*search[ ])(Table *, Table *, char *, int) = {
            searchByKey1Release,
            searchByKey2Release
    };
    int res = dialogOptions(options, N);
    char *key = dialogLine("Enter key\n");
    int release = dialogInt("Enter release");
    search[res](table, tableNew, key, release);
    free(key);
    killTable(tableNew);
    return 1;
}