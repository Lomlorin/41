#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_WORK_LENGTH 50
#define MAX_POSITION_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 100

typedef struct Contact {
    char first_name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char work[MAX_WORK_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char social[MAX_SOCIAL_LENGTH];
    struct Contact* next;
    struct Contact* prev;
} Contact;

Contact* head = NULL;  // Голова списка
Contact* tail = NULL;  // Хвост списка

void add_contact() {
    Contact* new_contact = (Contact*)malloc(sizeof(Contact));
    if (!new_contact) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter name: \n");
    scanf("%s", new_contact->first_name);
    printf("Enter surname: \n");
    scanf("%s", new_contact->surname);

       printf("Enter last name (leave it blank if not needed): \n");
    getchar(); // Очищаем буфер ввода перед использованием fgets
    fgets(new_contact->last_name, MAX_NAME_LENGTH, stdin);
    new_contact->last_name[strcspn(new_contact->last_name, "\n")] = '\0';

    printf("Enter place of work (leave it blank if not needed): \n");
    fgets(new_contact->work, MAX_WORK_LENGTH, stdin);
    new_contact->work[strcspn(new_contact->work, "\n")] = '\0';

    printf("Enter position (leave it blank if not needed): \n");
    fgets(new_contact->position, MAX_POSITION_LENGTH, stdin);
    new_contact->position[strcspn(new_contact->position, "\n")] = '\0';

    printf("Enter phone number (leave it blank if not needed): \n");
    fgets(new_contact->phone, MAX_PHONE_LENGTH, stdin);
    new_contact->phone[strcspn(new_contact->phone, "\n")] = '\0';

    printf("Enter email address (leave it blank if not needed): \n");
    fgets(new_contact->email, MAX_EMAIL_LENGTH, stdin);
    new_contact->email[strcspn(new_contact->email, "\n")] = '\0';

    printf("Enter social network link (leave it blank if not needed): \n");
    fgets(new_contact->social, MAX_SOCIAL_LENGTH, stdin);
    new_contact->social[strcspn(new_contact->social, "\n")] = '\0';

    // Вставка в отсортированный список
    if (!head) {
        new_contact->next = NULL;
        new_contact->prev = NULL;
        head = tail = new_contact;
    } else {
        Contact* current = head;
        while (current && strcmp(current->surname, new_contact->surname) < 0) {
            current = current->next;
        }

        if (!current) {
            new_contact->next = NULL;
            new_contact->prev = tail;
            tail->next = new_contact;
            tail = new_contact;
        } else {
            new_contact->prev = current->prev;
            new_contact->next = current;
            if (current->prev) {
                current->prev->next = new_contact;
            } else {
                head = new_contact;
            }
            current->prev = new_contact;
        }
    }

    printf("Contact added.\n");
}

void edit_contact(char first_name[MAX_NAME_LENGTH], char surname[MAX_NAME_LENGTH]) {
    Contact* current = head;
    while (current) {
        if (strcmp(current->first_name, first_name) == 0 && strcmp(current->surname, surname) == 0) {
            printf("Editing contact: %s %s\n", current->first_name, current->surname);
            
            printf("Enter new place of work (leave it blank to keep current): \n");
            getchar();
            fgets(current->work, MAX_WORK_LENGTH, stdin);
            current->work[strcspn(current->work, "\n")] = '\0';

            printf("Enter new position (leave it blank to keep current): \n");
            fgets(current->position, MAX_POSITION_LENGTH, stdin);
            current->position[strcspn(current->position, "\n")] = '\0';

            printf("Enter new phone number (leave it blank to keep current): \n");
            fgets(current->phone, MAX_PHONE_LENGTH, stdin);
            current->phone[strcspn(current->phone, "\n")] = '\0';

            printf("Enter new email address (leave it blank to keep current): \n");
            fgets(current->email, MAX_EMAIL_LENGTH, stdin);
            current->email[strcspn(current->email, "\n")] = '\0';

            printf("Enter new social network link (leave it blank to keep current): \n");
            fgets(current->social, MAX_SOCIAL_LENGTH, stdin);
            current->social[strcspn(current->social, "\n")] = '\0';

            printf("The contact has been updated.\n");
            return;
        }
        current = current->next;
    }

    printf("The contact was not found.\n");
}

void delete_contact(char first_name[MAX_NAME_LENGTH], char surname[MAX_NAME_LENGTH]) {
    Contact* current = head;
    while (current) {
        if (strcmp(current->first_name, first_name) == 0 && strcmp(current->surname, surname) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            free(current);
            printf("The contact has been deleted.\n");
            return;
        }
        current = current->next;
    }

    printf("The contact was not found.\n");
}

void list_contacts() {
    if (!head) {
        printf("The phone book is empty.\n");
        return;
    }

    Contact* current = head;
    while (current) {
        printf("Name: %s\n", current->first_name);
        printf("Surname: %s\n", current->surname);
        if (strlen(current->last_name)) printf("Last name: %s\n", current->last_name);
        if (strlen(current->work)) printf("Place of work: %s\n", current->work);
        if (strlen(current->position)) printf("Position: %s\n", current->position);
        if (strlen(current->phone)) printf("Phone: %s\n", current->phone);
        if (strlen(current->email)) printf("Email: %s\n", current->email);
        if (strlen(current->social)) printf("Social network: %s\n", current->social);
        printf("\n");
        current = current->next;
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nPhone book:\n");
        printf("1. Add a contact\n");
        printf("2. Edit a contact\n");
        printf("3. Delete a contact\n");
        printf("4. Show all contacts\n");
        printf("5. Exit\n");
        printf("Select an action: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2: {
                char first_name[MAX_NAME_LENGTH], surname[MAX_NAME_LENGTH];
                printf("Enter the name of the contact to edit: \n");
                scanf("%s", first_name);
                printf("Enter the surname of the contact to edit: \n");
                scanf("%s", surname);
                edit_contact(first_name, surname);
                break;
            }
            case 3: {
                char first_name[MAX_NAME_LENGTH], surname[MAX_NAME_LENGTH];
                printf("Enter the name of the contact to delete: \n");
                scanf("%s", first_name);
                printf("Enter the surname of the contact to delete: \n");
                scanf("%s", surname);
                delete_contact(first_name, surname);
                break;
            }
            case 4:
                list_contacts();
                break;
            case 5:
                while (head) {
                    Contact* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Wrong choice. Try again.\n");
        }
    }

    return 0;
}
