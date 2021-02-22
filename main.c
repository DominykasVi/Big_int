#include <stdio.h>
#include "big_int.h"

int main() {
    big_int *a = NULL;
    big_int *b = NULL;
    big_int *c = NULL;

    assign_int(&a, "11325");
    print_int(a);
    assign_int(&b, "12");
    print_int(b);
    c = subtract_int(a, b);
    print_int(c);
    c = multiply_int(a, b);
    print_int(c);
    c = divide_int(a, b);
    print_int(c);
    return 0;
}
