
#include "stdlib.h" // работа с памятью
#include "stdio.h" // работа с вводом и выводом
#include "string.h" // работа со строками

#define UNUSED(variable) (void)variable



void squareByPtr ( int * numPtr ) { *numPtr = *numPtr * *numPtr ;}

int main(int argc, char** argv) {
    int x = 5;
    squareByPtr (& x);
    printf("%d", x);

    UNUSED(argc);
    UNUSED(argv);

    return 0;
}
