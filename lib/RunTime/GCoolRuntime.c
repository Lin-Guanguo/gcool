#include <stdlib.h>
#include <stdio.h>

void* gcool_malloc(size_t size) {
    return malloc(size);
}

void gcool_printInt(long long int i) {
    printf("%lld", i);
}

void gcool_printFloat(double f) {
    printf("%lf", f);
}

void gcool_printBool(long long int b) {
    if (b & 1) 
        printf("true");
    else 
        printf("false");
}

void gcool_printEndLine() {
    printf("\n");
}