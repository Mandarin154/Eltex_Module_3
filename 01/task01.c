#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Необходимо указать хотя бы одну сторону!\n");
    return 1;
  }

  int num_sides = argc - 1;
  int parent_sides = num_sides / 2;
  int child_sides = num_sides - parent_sides;

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
    return 1;
  }

  // Дочерний процесс
  if (pid == 0) {
    for (int i = 1; i <= child_sides; i++) {
      int side = atoi(argv[parent_sides + i]);
      int area = side * side;
      printf("Дочерний процесс: Сторона %d, Площадь %d\n", side, area);
    }
    exit(0);
  } else {
    // Родительский процесс
    for (int i = 1; i <= parent_sides; i++) {
      int side = atoi(argv[i]);
      int area = side * side;
      printf("Родительский процесс: Сторона %d, Площадь %d\n", side, area);
    }

    wait(NULL);
  }

  return 0;
}