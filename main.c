#include <stdio.h>
#include "big_int.h"

int main() {
    big_int *a = NULL;
    big_int *b = NULL;
    big_int *c = NULL;

    assign_int(&a, "0");
    print_int(a);
    assign_int(&b, "1");
    print_int(b);

    for(int i = 0; i < 20; i++){
        if (i == 10){
            printf("ok");
        }
        print_int(a);
        print_int(b);
        a = add_int(a, b);
    }
    return 0;
}
