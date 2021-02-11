#include <stdlib.h>
#include <stdio.h>

typedef struct bigint{
    char number;
    struct bigint *next;
    struct bigint *prev;
}bigint;

struct bigint *stringtolist(char *string, bigint *bit);
void printList( bigint* node);


int main () {
    bigint *a=NULL;
    char string[100]="32111";
    a=stringtolist(string,a);
    printList(a);
    return 0;
}

struct bigint *stringtolist(char *string, bigint *head){
    //printf("%s",string);

    bigint *new_node=(bigint*)malloc(sizeof(bigint));
    bigint *fake;
    fake=head;
    new_node->number=string[0];
    new_node->next=NULL;
    
    new_node->prev = NULL;
    head = new_node;

    int counter=1;
    while(string[counter]!='\0'){
        bigint *new=(bigint*)malloc(sizeof(bigint));
        new->number= string[counter];
        new->next=NULL;
        fake=fake->next;
        fake->next=new;
        printf("i am here");
        new->prev=fake;
        counter++;
    }
    return head;
}

void printList( bigint* node)
{
    bigint* last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL) {
        printf(" %d ", node->number);
        last = node;
        node = node->next;
    }
 
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        printf(" %d ", last->number);
        last = last->prev;
    }
}