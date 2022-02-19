#include <stdio.h>
#include <readline/readline.h>
#include <malloc.h>

//функции для ввода
int isPositiveNumber(char *s) {
    for (int i = 0; s[i] != '\0'; ++i)
        if (!('0' <= s[i] && s[i] <= '9'))
            return 0;
    return 1;
}

int convert(char *s) {
    if (strlen(s) >= 11)
        return -1;
    long long val = 0;
    for (int i = 0; s[i] != '\0'; ++i)
        val = val * 10 + (s[i] - '0');
    if (val < (1ll << 31))
        return (int)val;
    return -1;
}

int readPositiveInteger(char *inp) {
    while (1) {
        char *s = readline(inp);
        if (isPositiveNumber(s)) {
            int ans = convert(s);
            if (ans != -1) {
                free(s);
                return ans;
            }
        }
        free(s);
        printf("Not a positive number or it`s very big\n");
    }
}

//структуры
typedef struct Line {
    int len;
    int *data;
} Line;

typedef struct Matrix {
    int len;
    Line *data;
} Matrix;

//функции для выполнения задания
void swap(long long *f1, long long *f2) {
    long long tmp = *f1;
    *f1 = *f2;
    *f2 = tmp;
}

void next(long long *f1, long long *f2) {
    *f1 = *f1 + *f2;
    swap(f1, f2);
}

void prev(long long *f1, long long *f2) {
    *f2 = *f2 - *f1;
    swap(f1, f2);
}

void add(Line *l, int number) {
    long long f1 = 0;
    long long f2 = 1;
    while (f2 <= number) {
        next(&f1, &f2);
    }
    (*l).len = 0;
    (*l).data = malloc(0);
    while (number) {
        while (f1 > number)
            prev(&f1, &f2);
        (*l).len += 1;
        (*l).data = realloc((*l).data, (*l).len * sizeof(int));
        (*l).data[(*l).len - 1] = (int)f1;
        number -= (int)f1;
    }
}

//сам мейн)
int main() {
    //ввод данных + выполнение задания в отдельной функции
    int m = readPositiveInteger("Enter m:\n");
    Matrix mat;
    mat.len = m;
    mat.data = malloc(m * sizeof(Line));
    Line input;
    input.len = m;
    input.data = malloc(m * sizeof(int));
    for (int i = 0; i < m; ++i) {
        int el = readPositiveInteger("Enter new element:\n");
        input.data[i] = el;
        add(&(mat.data[i]), el);
        printf("%d elem read!\n", i + 1);
    }
    //вывод входных данных и результата работы
    printf("Input data contains %d elements\n", m);
    for (int i = 0; i < m; ++i)
        printf("%d ", input.data[i]);
    printf("\nAnd result of work is\n");
    for (int i = 0; i < m; ++i) {
        printf("%d line contains %d elems: ", i + 1, mat.data[i].len);
        for (int j = 0; j < mat.data[i].len; ++j)
            printf("%d ", mat.data[i].data[j]);
        printf("\n");
    }
    //очистка памяти
    free(input.data);
    for (int i = 0; i < m; ++i) {
        free(mat.data[i].data);
    }
    free(mat.data);
    return 0;
}
