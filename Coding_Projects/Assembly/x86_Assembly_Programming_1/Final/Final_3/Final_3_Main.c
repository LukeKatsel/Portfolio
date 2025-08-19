#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void SwapCase(char *targetString);
void SwapCaseInC(char* targetString);

#if defined(_M_IX86)
# pragma comment(linker, "/INCLUDE:_mainCRTStartup")
#else
# pragma comment(linker, "/INCLUDE:mainCRTStartup")
#endif

int main()
{
    char inputString[32];

    while (1)
    {
        printf("Please enter a string (hit enter to quit): ");
        fgets(inputString, sizeof(inputString), stdin);

        // fgets includes \n, if that's all we get the exit.
        if (inputString[0] == '\n' && strlen(inputString) == 1)
        {
            break;
        }

        printf("Your string before SwapCase: \n\t%s", inputString);
        
        SwapCase(inputString);

        printf("Your string after SwapCase: \n\t%s", inputString);
        
        printf("\n\n");
    }
    return 0;
}

void SwapCaseInC(char* targetString)
{
    int i = 0;

    while (targetString[i] != 0)
    {
        // if we are lowercase
        if (targetString[i] >= 'a' && targetString[i] <= 'z')
        {
            // subtract 0x20 to match the lowercase character
            targetString[i] = targetString[i] - 0x20;
        }
        else if (targetString[i] >= 'A' && targetString[i] <= 'Z')
        {
            // add 0x20 to match the uppercase character
            targetString[i] = targetString[i] + 0x20;
        }
        ++i;
    }
}