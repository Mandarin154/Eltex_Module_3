#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_NUMBERS 100

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Используйте: %s (Число генерируемых чисел)\n", argv[0]);
    return 1;
  }

  int num_numbers = atoi(argv[1]);
  if (num_numbers <= 0 || num_numbers > MAX_NUMBERS) {
    fprintf(stderr, "Неверное число чисел, должно быть от 1 до %d.\n", MAX_NUMBERS);
    return 1;
  }

  int fd[2];
  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    return 1;
  }

    if (pid == 0) { // Дочерний процесс
    srand(time(NULL)); // Используем текущее время для случайности

    close(fd[0]);

    // Генерируем случайные числа и отправляем их родителю
    for (int i = 0; i < num_numbers; i++) {
      int random_number = rand() % 100; 
      write(fd[1], &random_number, sizeof(int));
    }

    close(fd[1]);

    exit(0);
  } else { // Родительский процесс
    close(fd[1]);

    FILE *fp = fopen("random_numbers.txt", "w");
    if (fp == NULL) {
      perror("fopen");
      return 1;
    }

    // Получаем числа от дочернего процесса и выводим их на экран и в файл
    for (int i = 0; i < num_numbers; i++) {
      int number;
      read(fd[0], &number, sizeof(int));
      printf("%d \n", number);
      fprintf(fp, "%d\n", number);
    }

    close(fd[0]);
    fclose(fp);

    wait(NULL);
  }

  return 0;
}