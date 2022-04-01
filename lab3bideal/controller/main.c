#include "../view/viewCommands.h"
#include "../model/modelCommands.h"
#include <malloc.h>

int main() {
    const char *options[] = {
            "0. Exit",
            "1. Add by two keys",
            "2. Search by two keys",
            "3. Delete by two keys",
            "4. Search by one key",
            "5. Delete by one key",
            "6. Print table",
            "7. Search by key and release",
            "8. Delete by key and release"
    };
    int (*fptr[ ])(Table *) = {
                NULL,
            addTwoKeys,
            searchTwoKeys,
            deleteTwoKeys,
            searchOneKey,
            deleteOneKey,
            printTableConsole,
            searchByKeyRelease,
            deleteByKeyRelease
    };
    const int N = sizeof(options) / sizeof(options[0]);

    Table *table = init();
    int stat;
    while (stat = dialogOptions(options, N))
        if (!fptr[stat](table))
            break;
    finish(table);
    return 0;
}

