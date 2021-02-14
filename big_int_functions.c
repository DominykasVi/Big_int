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

void copy_int(big_int *original, big_int **copy){
    big_int* last_node = (big_int*) malloc (sizeof(big_int));
    memory_Allocation_Check(last_node);
    last_node->number = original->number;
    last_node->next = NULL;
    last_node->previous = NULL;
    *copy = last_node;
    while(original->next != NULL){
        original = original->next;
        big_int* new_node = (big_int*) malloc (sizeof(struct big_int));
        memory_Allocation_Check(new_node);
        new_node->number = original->number;
        new_node->previous = last_node;
        new_node->next = NULL;
        last_node->next = new_node;
        last_node = new_node;
    }
}

void pure_subtraction(big_int *bigger, big_int* smaller){
    int carry = 0;
    char bigger_num;
    char smaller_num;
    while(smaller->previous != NULL){
        bigger_num = bigger->number;
        smaller_num = smaller->number;

        if(carry > 0){
            --carry;
            if(bigger_num == 0){
                ++carry;
                bigger_num += 9;
            } else {
                --bigger_num;
            }
        }

        if(smaller_num > bigger_num){
            ++carry;
            bigger_num += 10;
        }

        bigger->number = bigger_num - smaller_num;
        bigger = bigger->previous;
        smaller = smaller->previous;
    }

    bigger_num = bigger->number;
    smaller_num = smaller->number;

    if(carry > 0){
        --carry;
        if(bigger_num == 0){
            ++carry;
            bigger_num += 9;
        } else {
            --bigger_num;
        }
    }
    if(smaller_num > bigger_num){
        ++carry;
        bigger_num += 10;
    }
    bigger->number = bigger_num - smaller_num;

    while(carry != 0){
        bigger = bigger->previous;
        --carry;
        if(bigger->number == 0){
            ++carry;
            bigger->number += 10;
            bigger = bigger->previous;
        } else {
            --(bigger->number);
        }
    }

    while(bigger->previous != NULL){
        bigger = bigger->previous;
    }
}

void remove_zeroes(big_int** head){
    big_int *current = *head;
    big_int *previous = NULL;
    while(current->number == 0){
        previous = current;
        current = current->next;
        previous->next = NULL;
        free(previous);
    }
    *head = current;
}

big_int* subtract_big_int(big_int* first_number, big_int* second_number){
    big_int *difference = malloc(sizeof (big_int));

    big_int *first_copy = NULL;
    copy_int(first_number, &first_copy);
    big_int *second_copy = NULL;
    copy_int(second_number, &second_copy);

    int type = 1;
    //TYPE: 10 - first is smaller than second
    //TYPE: 100 - second is smaller
    //TYPE: 20 - both minus, first is smaller than second
    //TYPE: 200 - both minus, second is smaller

    if(first_number->number >= 0 && second_number->number < 0){//10-(-1) or 0 -(-1)
        second_copy->number = 0 - second_copy->number;
        //addition();
        printf("Temp, case 1");
        return difference;
    } else if(first_number->number < 0 && second_number->number > 0){//-10-1
        first_copy->number = 0 - first_copy->number;//-10->10
        second_copy->number = 0 - second_copy->number;//-1->1
        //addition();//10+1=11
        //restore correct numbers
        difference->number = 0 - difference->number;//11->-11
        printf("Temp, case 2");
        return difference;
    } else if(first_number->number < 0 && second_number->number < 0){//-10-(-1)->-10+1->10-1->9->-9
        first_copy->number = 0 - first_copy->number;//-10->10
        second_copy->number = 0 - second_copy->number;//-1->1
        ++type;//TEMP
        //printf("Temp, case 3");
        //10 -1 = 9, then turn 9 to -9
        //return difference;
    }

    big_int *first_tmp = malloc(sizeof ( big_int));
    memory_Allocation_Check(first_tmp);
    first_tmp = first_copy;

    big_int *second_tmp = malloc(sizeof ( big_int));
    memory_Allocation_Check(second_tmp);
    second_tmp = second_copy;

    while (first_tmp->next != NULL || second_tmp->next != NULL){
        if(first_tmp->next == NULL){
            type *= 10;
            while (second_tmp->next != NULL){
                second_tmp = second_tmp->next;
            }
            break;
        }else if(second_tmp->next == NULL){
            type *= 100;
            while (first_tmp->next != NULL){
                first_tmp = first_tmp->next;
            }
            break;
        }

        first_tmp = first_tmp->next;
        second_tmp = second_tmp->next;
    }

    if(type < 10){
        if(first_copy->next == NULL && second_copy->next == NULL){
            if(first_copy->number > second_copy->number){
                difference->number = first_copy->number - second_copy->number;
                if(type == 2){
                    difference->number = 0 - difference->number;
                }
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            } else if (first_copy->number < second_copy->number){
                difference->number = first_copy->number - second_copy->number;
                if(type == 2){
                    difference->number = 0 - difference->number;
                }
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            } else {
                difference->number = 0;
                difference->next = NULL;
                difference->previous = NULL;
                return difference;
            }
        }

        while (first_copy->next != NULL || second_copy->next != NULL){
            if(first_copy->number > second_copy->number){
                type *= 100;
                break;
            } else if(first_copy->number < second_copy->number){
                type *= 10;
                break;
            } else{
                first_copy = first_copy->next;
                second_copy = second_copy->next;
                if(first_copy->next == NULL && second_copy->next == NULL){//are equal
                    difference->number = 0;
                    difference->next = NULL;
                    difference->previous = NULL;
                    return difference;
                }
            }
        }
    }

    //printf("%d\n" ,type);
    switch (type) {
        case 10:
            pure_subtraction(second_tmp, first_tmp);
            remove_zeroes(&second_copy);
            second_copy->number = 0 - second_copy->number;
            difference = second_copy;
            delete_int(first_copy);
            return difference;
        case 100:
            pure_subtraction(first_tmp, second_tmp);
            remove_zeroes(&first_copy);
            difference = first_copy;
            delete_int(second_copy);
            return difference;
        case 20:
            pure_subtraction(second_tmp, first_tmp);
            remove_zeroes(&second_copy);
            difference = second_copy;
            delete_int(first_copy);
            return difference;
        case 200:
            pure_subtraction(first_tmp, second_tmp);
            remove_zeroes(&first_copy);
            difference = first_copy;
            difference->number = 0 - first_copy->number;
            delete_int(second_copy);
            return difference;
        default:
            return difference;
    }
//    if(type == 10){
//        pure_subtraction(second_tmp, first_tmp);
//        remove_zeroes(&second_copy);
//        second_copy->number = 0 - second_copy->number;
//        difference = second_copy;
//        delete_int(first_copy);
//        return difference;
//    } else if(type == 100){
//        pure_subtraction(first_tmp, second_tmp);
//        remove_zeroes(&first_copy);
//        difference = first_copy;
//        delete_int(second_copy);
//        return difference;
//    } else if(type == 20){
//        pure_subtraction(second_tmp, first_tmp);
//        remove_zeroes(&second_copy);
//        difference = second_copy;
//        delete_int(first_copy);
//    } else if(type == 200){
//        pure_subtraction(first_tmp, second_tmp);
//        remove_zeroes(&first_copy);
//        difference = first_copy;
//        difference->number = 0 - first_copy->number;
//        delete_int(second_copy);
//    }
//    return difference;
}


