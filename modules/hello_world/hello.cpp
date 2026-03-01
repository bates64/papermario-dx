#include "common.h"

__attribute__((constructor))
void hello() {
    printf("Hello, world!\n");
}
