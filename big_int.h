#ifndef BIG_INT_H
#define BIG_INT_H

//When creating int, create big_int* and assign NULL value.
//Pass into functions with &variable, the number you want to assign must be passed as a char array
//Example: big_int *a = NULL;
//         assign_int(&a, "11325");
//Big int can be added together, subtracted, multiplied and divided.
//Pass them as parameters into functions and return will be the result;
//Example: big_int *c;
//         c = subtract_int(a, b);
//There are extra help funtions as: print_int - prints big int
//delete_int - deletes variable
//copy_int - creates copy of a variable. Must copy must be pointer passed by address (&variable)
//Example: big_int *c;
//         copy_int(a, &c);

typedef struct big_int {
    char number;
    struct big_int *next;
    struct big_int *previous;
} big_int;

void assign_int(big_int **head, char *number);
big_int *subtract_int(big_int *first_number, big_int *second_number);
big_int *divide_int(big_int *dividend, big_int *divisor);
big_int *add_int(big_int *a, big_int *b);
big_int *multiply_int(big_int *a, big_int *b);
void print_int(big_int *head);
void delete_int(big_int *head);
void copy_int(big_int *original, big_int **copy);


#endif
