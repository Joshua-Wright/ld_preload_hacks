#include <stdio.h>
#include "libmain.h"

extern "C" {
int rand() {
    puts("Do not use rand()");
    static auto *old_rand = get_old_function(&rand);
    return old_rand();
}
}