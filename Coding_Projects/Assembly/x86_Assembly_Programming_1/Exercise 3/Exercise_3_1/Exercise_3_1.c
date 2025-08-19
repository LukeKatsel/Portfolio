#include <stdio.h>
#include <string.h>

extern int mystrlen(char* string);

int main()
{
    char testString[] = "This is a test string";

    printf("The string is %d characters long.\n", strlen(testString));

    printf("The string is %d characters long.\n", mystrlen(testString));

    return 0;
}