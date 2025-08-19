#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern char *FindLongestString(char *availableStrings[], int itemCount);
char *FindLongestStringInC(char* availableStrings[], int itemCount);

#if defined(_M_IX86)
# pragma comment(linker, "/INCLUDE:_mainCRTStartup")
#else
# pragma comment(linker, "/INCLUDE:mainCRTStartup")
#endif

int main()
{
    char *availableStrings[6];
    char* stringList[6];
    char* answer=NULL;
    int count=0;

    availableStrings[0] = "You can't see the forest through the trees";
    availableStrings[1] = "Try not. Do or do not. There is no try.";
    availableStrings[2] = "Shall we play a game?";
    availableStrings[3] = "Fortune favors the bold.";
    availableStrings[4] = "Time moves slowly, but passes quickly.";
    availableStrings[5] = "Beware; for I am fearless, and therefore powerful.";

    // Randomly place 
    memset(&stringList, 0, sizeof(stringList));
    srand(time(NULL));
    while (count < 6)
    {
        int pos = rand() % 6;
        if (stringList[pos] == NULL)
        {
            stringList[pos] = availableStrings[count++];
        }
    }

    printf("The longest string in the list is \"%s\"\n\n", FindLongestStringInC(availableStrings, 6));

    answer = FindLongestString(stringList, 6);
    if (answer != NULL)
    {
        printf("The longest string in the list is \"%s\"\n\n", answer);
    }
    else
    {
        printf("Function failed\n");
    }

    return 0;
}

char* FindLongestStringInC(char* pavailableStrings[], int count)
{
    char* pLongest = "";
    size_t iLongestLength = 0;

    for (int i = 0; i < count; ++i)
    {
        if (strlen(pavailableStrings[i]) > iLongestLength)
        {
            iLongestLength = strlen(pavailableStrings[i]);
            pLongest = pavailableStrings[i];
        }
    }
    return pLongest;
}