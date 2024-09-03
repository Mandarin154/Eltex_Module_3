#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char result[1024] = "";
    for (int i = 1; i < argc; i++) {
        strcat(result, argv[i]);
    }
    printf("Склеенная строка: %s\n", result);
    return 0;
}