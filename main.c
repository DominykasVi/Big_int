#include <stdio.h>
#include "big_int.h"

int main() {
    big_int *a = NULL;
    assign_int(&a, "123456789");
    print_int(a);
    assign_int(&a, "-123456789");
    print_int(a);
    assign_int(&a, "0");
    print_int(a);
    assign_int(&a, "-0");
    print_int(a);
    assign_int(&a, "+0");
    print_int(a);
    assign_int(&a, "-1");
    print_int(a);
    assign_int(&a, "+1");
    print_int(a);
    assign_int(&a, "2");
    print_int(a);
    assign_int(&a, "22");
    print_int(a);
    assign_int(&a, "-2");
    print_int(a);
    assign_int(&a, "-22");
    print_int(a);
    assign_int(&a, "1587434871844871438738743867167418741987499741897186374138673186748978");
    print_int(a);
    assign_int(&a, "-1587434871844871438738743867167418741987499741897186374138673186748978");
    print_int(a);
    assign_int(&a, "a");
    print_int(a);
    assign_int(&a, "1587434871a44871438738743867167418741987499741897186374138673186748978");
    print_int(a);
    assign_int(&a, "a1587434871a44871438738743867167418741987499741897186374138673186748978");
    print_int(a);
    assign_int(&a, "1587434871a44871438738743867167418741987499741897186374138673186748978a");
    print_int(a);
    return 0;
}
