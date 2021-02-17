#ifndef BIG_INT_H
#define BIG_INT_H

typedef struct big_int{
    char number;
    struct big_int* next;
    struct big_int* previous;
}big_int;

void assign_int(big_int** head, char* number);
big_int* subtract_big_int(big_int* first_number, big_int* second_number);
void print_int(big_int *head);
void delete_int(big_int* head);
void copy_int(big_int *original, big_int **copy);
big_int* divide_big_int(big_int* dividend, big_int* divisor);
big_int* addition(big_int *a, big_int *b);

#endif
