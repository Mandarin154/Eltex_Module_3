#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void sum(int argc, char *argv[]) {
  int sum = 0;
  for (int i = 1; i < argc; i++) {
    sum += atoi(argv[i]);
  }
  printf("Сумма: %d\n", sum);
}

void concat(int argc, char *argv[]) {
  char result[1024] = "";
  for (int i = 1; i < argc; i++) {
    strcat(result, argv[i]);
  }
  printf("Склеенная строка: %s\n", result);
}

void max(int argc, char *argv[]) {
  int max = atoi(argv[1]);
  for (int i = 2; i < argc; i++) {
    int current = atoi(argv[i]);
    if (current > max) {
      max = current;
    }
  }
  printf("Наибольшее значение: %d\n", max);
}

void find_longest(int argc, char *argv[]) {
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
}

int main() {
  char command[1024];
  char *args[1024];

  while (1) {
    printf("> ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Удаляем символ перевода строки

    // Разделяем строку на аргументы
    int argc = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
      args[argc++] = token;
      token = strtok(NULL, " ");
    }
    args[argc] = NULL; // Устанавливаем последний элемент массива в NULL

    if (strcmp(args[0], "sum") == 0) {
      sum(argc, args);
    } else if (strcmp(args[0], "concat") == 0) {
      concat(argc, args);
    } else if (strcmp(args[0], "max") == 0) {
      max(argc, args);
    } else if (strcmp(args[0], "longest") == 0) {
      find_longest(argc, args);
    } else if (strcmp(args[0], "exit") == 0) {
      break;
    } else {
      printf("Неизвестная команда.\n");
    }
  }

  return 0;
}