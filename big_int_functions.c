#include "big_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void delete_int(big_int* head){
    big_int* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}

void memory_Allocation_Check(void* pointer){
    if(pointer == NULL){
        printf("Cannot allocate memory\n");
        exit(1);
    }
}

void assign_int(big_int** head, char* number){
    if (*head != NULL){
        delete_int(*head);
    }
    *head = NULL;
    long long i = 0;
    big_int* last_node = (big_int*) malloc (sizeof(struct big_int));
    while (number[i] != '\0'){

        char digit = number[i] - 48;

        if(number[i] == '-' && i == 0){
            ++i;
            digit = 0 - (number[i] - 48);
        } else if(number[i] == '+' && i == 0){
            ++i;
            digit = number[i] - 48;
        } else if (number[i] < 48 || number[i]  >57){
            *head = NULL;
            printf("Not valid input\n");
            return;
        }
        big_int* new_node = (big_int*) malloc (sizeof(struct big_int));

        memory_Allocation_Check(new_node);

        new_node->number = digit;
        new_node->next = NULL;

        if (*head == NULL) {
            new_node->previous = NULL;
            *head = new_node;
            last_node = new_node;
        } else {
            last_node->next = new_node;
            new_node->previous = last_node;
            last_node = new_node;
        }

        ++i;
        if(i == LONG_LONG_MAX){
            printf("Max size reached");
            break;
        }
    }
}

void print_int(big_int *head){
    big_int *current_node = head;
    if(current_node == NULL){
        printf("No data given\n");
        return;
    }

    while(current_node != NULL){
        if(current_node == head && current_node->number < 0){
            printf("-%c", 0 - (current_node->number) + 48);
        } else {
            printf("%c", (current_node->number)+48);
        }
        current_node = current_node->next;
    }
    printf("\n");
//    //print backwards
//    current_node = head;
//    while (current_node->next != NULL){
//        current_node = current_node->next;
//    }
//    while(current_node != NULL){
//        if(current_node == head && current_node->number < 0){
//            printf("-%c", 0 - (current_node->number) + 48);
//        } else {
//            printf("%c", (current_node->number)+48);
//        }
//        current_node = current_node->previous;
//    }
//    printf("\n");
}


