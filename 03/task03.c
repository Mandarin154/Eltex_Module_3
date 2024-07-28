#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 100
#define MAX_SOCIAL_LENGTH 100
#define MAX_CONTACTS 100

typedef struct Contact {
  char name[MAX_NAME_LENGTH];
  char surname[MAX_NAME_LENGTH];
  char thirdname[MAX_NAME_LENGTH];
  char company[MAX_NAME_LENGTH];
  char post[MAX_NAME_LENGTH];
  char phone[MAX_PHONE_LENGTH];
  char email[MAX_EMAIL_LENGTH];
  char social_links[MAX_SOCIAL_LENGTH];
} Contact;

int main() {
  Contact contacts[MAX_CONTACTS];
  int num_contacts = 0;

  FILE *file = fopen("contacts.txt", "r");
  if (file != NULL) {
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                 contacts[num_contacts].name,
                 contacts[num_contacts].surname,
                 contacts[num_contacts].thirdname,
                 contacts[num_contacts].company,
                 contacts[num_contacts].post,
                 contacts[num_contacts].phone,
                 contacts[num_contacts].email,
                 contacts[num_contacts].social_links) == 8) {
      num_contacts++;
    }
    fclose(file);
  }

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);

  while (1) {
    printf("Введите команду (add - добавить контакт, list - показать список, exit - выход): ");
    char command[20];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0; // Удаляем символ переноса строки

    if (strcmp(command, "add") == 0) {
      printf("Введите имя: ");
      fgets(contacts[num_contacts].name, sizeof(contacts[num_contacts].name), stdin);
      contacts[num_contacts].name[strcspn(contacts[num_contacts].name, "\n")] = 0;

      printf("Введите фамилию: ");
      fgets(contacts[num_contacts].surname, sizeof(contacts[num_contacts].surname), stdin);
      contacts[num_contacts].surname[strcspn(contacts[num_contacts].surname, "\n")] = 0;

      printf("Введите отчество: ");
      fgets(contacts[num_contacts].thirdname, sizeof(contacts[num_contacts].thirdname), stdin);
      contacts[num_contacts].thirdname[strcspn(contacts[num_contacts].thirdname, "\n")] = 0;

      printf("Введите компанию: ");
      fgets(contacts[num_contacts].company, sizeof(contacts[num_contacts].company), stdin);
      contacts[num_contacts].company[strcspn(contacts[num_contacts].company, "\n")] = 0;

      printf("Введите должность: ");
      fgets(contacts[num_contacts].post, sizeof(contacts[num_contacts].post), stdin);
      contacts[num_contacts].post[strcspn(contacts[num_contacts].post, "\n")] = 0;

      printf("Введите номер телефона: ");
      fgets(contacts[num_contacts].phone, sizeof(contacts[num_contacts].phone), stdin);
      contacts[num_contacts].phone[strcspn(contacts[num_contacts].phone, "\n")] = 0;

      printf("Введите адрес электронной почты: ");
      fgets(contacts[num_contacts].email, sizeof(contacts[num_contacts].email), stdin);
      contacts[num_contacts].email[strcspn(contacts[num_contacts].email, "\n")] = 0;

      printf("Введите ссылки на соц сети (разделенные пробелами): ");
      fgets(contacts[num_contacts].social_links, sizeof(contacts[num_contacts].social_links), stdin);
      contacts[num_contacts].social_links[strcspn(contacts[num_contacts].social_links, "\n")] = 0;

      num_contacts++;
    } else if (strcmp(command, "list") == 0) {
      if (num_contacts == 0) {
        printf("Список контактов пуст.\n");
      } else {
        for (int i = 0; i < num_contacts; i++) {
          printf("Имя: %s\n", contacts[i].name);
          printf("Фамилия: %s\n", contacts[i].surname);
          printf("Отчество: %s\n", contacts[i].thirdname);
          printf("Компания: %s\n", contacts[i].company);
          printf("Должность: %s\n", contacts[i].post);
          printf("Телефон: %s\n", contacts[i].phone);
          printf("Email: %s\n", contacts[i].email);
          printf("Соц сети: %s\n\n", contacts[i].social_links);
        }
      }
    } else if (strcmp(command, "exit") == 0) {
      break;
    } else {
      printf("Неизвестная команда.\n");
    }
  }

  file = fopen("contacts.txt", "w");
  if (file == NULL) {
    printf("Ошибка открытия файла.\n");
    return 1;
  }

  for (int i = 0; i < num_contacts; i++) {
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s\n",
            contacts[i].name,
            contacts[i].surname,
            contacts[i].thirdname,
            contacts[i].company,
            contacts[i].post,
            contacts[i].phone,
            contacts[i].email,
            contacts[i].social_links);
  }

  fclose(file);

  return 0;
}