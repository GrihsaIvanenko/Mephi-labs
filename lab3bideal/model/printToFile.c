#include "structs.h"
#include <malloc.h>
#include "modelCommands.h"

void printAllTable(FILE *output, Table *table);
void printToFile(Table *table) {
    char *tmpFileName =  creat("", table->fileMain, ".tmp");
    FILE *output = fopen(tmpFileName, "w+b");
    fclose(output);
    output = fopen(tmpFileName, "r+b");
    printAllTable(output, table);
    fclose(output);
    remove(table->fileMain);
    rename(tmpFileName, table->fileMain);
    free(tmpFileName);
}

void printBase(FILE *file, Table *table);
void printKeySpace2(FILE *file, Table *table);
void printKeySpace1(FILE *file, Table *table);
void printItems(FILE *file, Table *table);
void printKeysKeySpace1(FILE *file, Table *table);
void printKeysKeySpace2(FILE *file, Table *table);
void connectListAndItems(FILE *file, Table *table);
void printAllTable(FILE *output, Table *table) {
    printBase(output, table);
    printKeySpace2(output, table);
    printKeySpace1(output, table);
    printItems(output, table);
    printKeysKeySpace1(output, table);
    printKeysKeySpace2(output, table);
    connectListAndItems(output, table);
}

void printBase(FILE *file, Table *table) {
    fseek(file, 0, SEEK_SET);
    fwrite(&(table->keySpace2->tableSize), sizeof(int), 1, file);
    fwrite(&(table->keySpace1->head), sizeof(int), 1, file);
    fwrite(&(table->keySpace2->timer), sizeof(int), 1, file);
}

void printKeySpace2(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        itemVector->key = -1;
        itemVector->data = -1;
        writeItemVector(table, itemVector, i, file);
        free(itemVector);
    }
}

void printKeySpace1(FILE *file, Table *table) {
    int id = table->keySpace1->head;
    int prev = -1;
    while (id != -1) {
        ItemList *itemList = getItemList(table, id, NULL);
        int next = itemList->next;
        itemList->key = -1;
        itemList->data = -1;
        fseek(file, 0, SEEK_END);
        int myID = ftell(file);
        writeItemList(table, itemList, myID, file);
        fseek(file, 0, SEEK_END);
        if (next != -1)
            itemList->next = ftell(file);
        else
            itemList->next = -1;
        writeItemList(table, itemList, myID, file);
        id = next;
        free(itemList);
        if (prev == -1) {
            prev = 0;
            fseek(file, sizeof(int), SEEK_SET);
            fwrite(&(myID), sizeof(int), 1, file);

        }
    }
}

void printRope(FILE *file, Table *table, int id);
void printItems(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus != 0) {
            ItemVector *newItemVector = getItemVector(table, i, file);
            fseek(file, 0, SEEK_END);
            newItemVector->data = ftell(file);
            printRope(file, table, itemVector->data);
            writeItemVector(table, newItemVector, i, file);
            free(newItemVector);
        }
        free(itemVector);
    }
}

void printRope(FILE *file, Table *table, int id) {
    while (id != 0) {
        Item *item = getItem(table, id, NULL);
        int next = item->next;
        fseek(file, 0, SEEK_END);
        int myId = ftell(file);
        writeItem(table, item, myId, file);
        char *info = getString(item->info, table, NULL);
        fseek(file, 0, SEEK_END);
        item->info = ftell(file);
        writeString(ftell(file), info, table, file);
        if (next == -1) {
            writeItem(table, item, myId, file);
            free(item);
            free(info);
            return;
        }
        fseek(file, 0, SEEK_END);
        item->next = ftell(file);
        writeItem(table, item, myId, file);
        id = next;
        free(item);
        free(info);
    }
}

void printKeysKeySpace1(FILE *file, Table *table) {
    int oldId = table->keySpace1->head;
    int newId;
    fseek(file, sizeof(int), SEEK_SET);
    fread(&newId, sizeof(int), 1, file);
    while (oldId != -1) {
        ItemList *oldItemList = getItemList(table, oldId, NULL);
        ItemList *newItemList = getItemList(table, newId, file);
        char *key = getString(oldItemList->key, table, NULL);
        fseek(file, 0, SEEK_END);
        newItemList->key = ftell(file);
        writeString(ftell(file), key, table, file);
        writeItemList(table, newItemList, newId, file);
        oldId = oldItemList->next;
        newId = newItemList->next;
        free(key);
        free(newItemList);
        free(oldItemList);
    }
}

void printKeysKeySpace2(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        if (itemVector->busyStatus != 0) {
            char *key = getString(itemVector->key, table, NULL);
            ItemVector *inNew = getItemVector(table, i, file);
            fseek(file, 0, SEEK_END);
            inNew->key = ftell(file);
            writeString(ftell(file), key, table, file);
            writeItemVector(table, inNew, i, file);
            free(inNew);
            free(key);
        }
        free(itemVector);
    }
}

void connectListAndRope(FILE *file, Table *table, int oldId, int newId);
void connectListAndItems(FILE *file, Table *table) {
    for (int i = 0; i < table->keySpace2->tableSize; ++i) {
        ItemVector *itemVector = getItemVector(table, i, NULL);
        ItemVector *newItemVector = getItemVector(table, i, file);
        if (itemVector->busyStatus == 1) {
            connectListAndRope(file, table, itemVector->data, newItemVector->data);
        }
        free(itemVector);
        free(newItemVector);
    }
}

int getNumberByAddress(Table *table, int oldId);
int getIdByNumberInKeySpace1(FILE *file, int number, Table *table);
void connectListAndRope(FILE *file, Table *table, int oldId, int newId) {
    while (oldId != -1) {
        int posInKeySpace1 = getNumberByAddress(table, oldId);
        int addressInNew = getIdByNumberInKeySpace1(file, posInKeySpace1, table);
        ItemList *itemList = getItemList(table, addressInNew, file);
        itemList->data = newId;
        writeItemList(table, itemList, addressInNew, file);
        Item *oldItem = getItem(table, oldId, NULL);
        Item *newItem = getItem(table, newId, file);
        oldId = oldItem->next;
        newId = newItem->next;
        free(oldItem);
        free(newItem);
        free(itemList);
    }
}

int getNumberByAddress(Table *table, int oldId) {
    int id = table->keySpace1->head;
    int cnt = 0;
    while (id != -1) {
        ItemList *itemList = getItemList(table, id, NULL);
        if (itemList->data == oldId) {
            free(itemList);
            return cnt;
        }
        id = itemList->next;
        free(itemList);
        ++cnt;
    }
    return -1;
}

int getIdByNumberInKeySpace1(FILE *file, int number, Table *table) {
    int id;
    int cnt = 0;
    fseek(file, sizeof(int), SEEK_SET);
    fread(&id, sizeof(int), 1, file);
    while (id != -1) {
        ItemList *itemList = getItemList(table, id, file);
        if (number == cnt) {
            free(itemList);
            return id;
        }
        id = itemList->next;
        free(itemList);
        ++cnt;
    }
    return -1;
}