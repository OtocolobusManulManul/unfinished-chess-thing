#include <stdio.h>

int main (void)
{
    FILE* file = fopen("startingboard.txt", "r");

    char c = getc(file);
    printf("%c", c);
    c = getc(file);
    printf("%c", c);
    return 0;
}