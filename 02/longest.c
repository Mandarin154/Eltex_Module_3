#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Не переданы аргументы.\n");
        return 1;
    }

    int max_length = strlen(argv[1]);
    char *longest_string = argv[1];
    for (int i = 2; i < argc; i++) {
        int current_length = strlen(argv[i]);
        if (current_length > max_length) {
            max_length = current_length;
            longest_string = argv[i];
        }
    }
    printf("Самая длинная строка: %s\n", longest_string);
    return 0;
}