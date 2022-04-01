#include "structs.h"
#include <malloc.h>
#include <string.h>

ItemVector *getItemVector(Table *table, int itPos, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    long posRead = (long)((sizeof(int) * 3) + (sizeof(int) * 3) * itPos);
    fseek(file, posRead, SEEK_SET);
    ItemVector *ans = malloc(sizeof(ItemVector));
    fread(&(ans->busyStatus), sizeof(int), 1, file);
    fread(&(ans->key), sizeof(int), 1, file);
    fread(&(ans->data), sizeof(int), 1, file);
    if (wasOpen == 1)
        fclose(file);
    return ans;
}

void writeItemVector(Table *table, ItemVector *itemVector, int itPos, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    long posWrite = (long)((sizeof(int) * 3) + (sizeof(int) * 3) * itPos);
    fseek(file, posWrite, SEEK_SET);
    fwrite(&(itemVector->busyStatus), sizeof(int), 1, file);
    fwrite(&(itemVector->key), sizeof(int), 1, file);
    fwrite(&(itemVector->data), sizeof(int), 1, file);
    if (wasOpen == 1) {
        fclose(file);
    }
}

ItemList *getItemList(Table *table, long address, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, address, SEEK_SET);
    ItemList *ans = malloc(sizeof(ItemList));
    fread(&(ans->key), sizeof(int), 1, file);
    fread(&(ans->data), sizeof(int), 1, file);
    fread(&(ans->next), sizeof(int), 1, file);
    fread(&(ans->release), sizeof(int), 1, file);
    if (wasOpen == 1)
        fclose(file);
    return ans;
}

void writeItemList(Table *table, ItemList *itemList, long where, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, where, SEEK_SET);
    fwrite(&(itemList->key), sizeof(int), 1, file);
    fwrite(&(itemList->data), sizeof(int), 1, file);
    fwrite(&(itemList->next), sizeof(int), 1, file);
    fwrite(&(itemList->release), sizeof(int), 1, file);
    if (wasOpen == 1) {
        fclose(file);
    }
}

Item *getItem(Table *table, long address, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, address, SEEK_SET);
    Item *ans = malloc(sizeof(Item));
    fread(&(ans->next), sizeof(int), 1, file);
    fread(&(ans->release), sizeof(int), 1, file);
    fread(&(ans->info), sizeof(int), 1, file);
    if (wasOpen == 1)
        fclose(file);
    return ans;
}

void writeItem(Table *table, Item *item, long address, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, address, SEEK_SET);
    fwrite(&(item->next), sizeof(int), 1, file);
    fwrite(&(item->release), sizeof(int), 1, file);
    fwrite(&(item->info), sizeof(int), 1, file);
    if (wasOpen == 1) {
        fclose(file);
    }
}

char *getString(int address, Table *table, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, address, SEEK_SET);
    int len;
    fread(&len, sizeof(int), 1, file);
    char *ans = malloc(sizeof(ans));
    fread(ans, sizeof(char), len, file);
    if (wasOpen == 1) {
        fclose(file);
    }
    return ans;
}

void writeString(int address, char *who, Table *table, FILE *file) {
    int wasOpen = 0;
    if (file == NULL)
        wasOpen = 1;
    if (wasOpen == 1) {
        file = fopen(table->fileMain, "r+b");
    }
    fseek(file, address, SEEK_SET);
    int len = strlen(who) + 1;
    fwrite(&len, sizeof(int), 1, file);
    fwrite(who, sizeof(char), len, file);
    if (wasOpen == 1) {
        fclose(file);
    }
}