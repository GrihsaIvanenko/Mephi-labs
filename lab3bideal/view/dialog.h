#ifndef LAB3B_DIALOG_H
#define LAB3B_DIALOG_H

int dialogOptions(const char *opts[], int size);

char *dialogLine(char *what);

int dialogInt(char *what);

void printVerdict(char *what);

#endif //LAB3B_DIALOG_H
