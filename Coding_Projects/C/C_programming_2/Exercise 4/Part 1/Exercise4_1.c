/*****************************************************
 *
 *  CSCV352 - Exercise4_1.c
 *
 *  Sample Solution
 *
******************************************************/
#include <stdio.h>
#include <string.h>


///////////////////////////////////////////////////////
//                CONSTANTS
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//               typedefs and structures
//////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//               globalVariables
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//                FunctionPrototypes
///////////////////////////////////////////////////////
int strend(char *s, char *t);
char* TrimRight(char* str, const char* trimChars);

/*****************************************************
 *
 *  Function:  main()
 *
 *  Parameters:
 *
 *      argc - main parameter for argument count
 *      argv - main parameter for argument values
 *
******************************************************/
int main(int argc, char *argv[]) 
{
    char baseString[1000];
	char findString[1000];

    // Obtain the string to search
	printf("Enter a string: ");
	fgets(baseString, sizeof(baseString), stdin);
	TrimRight(baseString, NULL);

    // Obtain the string to search for
	printf("Enter string to search for: ");
	fgets(findString, sizeof(findString), stdin);
	TrimRight(findString, NULL);

    // strend returns 1 if there is a match
	if (strend(baseString, findString))
	{
		printf("Search string was found!!\n");
	}
	else
	{
		printf("Search string was not found.\n");
	}
}

/*****************************************************
 *
 *  Function:  strend()
 *
 *  Parameters:
 *
 *      s - string to search
 *      t - string to search for
 *
******************************************************/
int strend(char *s, char *t)
{
	int retVal = 0;
	int sLen, tLen, i;
	char *sEnd;
	char *tEnd;

    sLen = strlen(s);					// get the length of each string
	tLen = strlen(t);

    if (sLen >= tLen){					// if word we're looking for is longer - dont bother
		sEnd = s + sLen;
		tEnd = t + tLen;				// set sEnd and tEnd to the address with the end of each string

		for (i = 0; i < tLen; i++){		// loop through the length of the search word
			sEnd = sEnd - 1;
			tEnd = tEnd - 1; 			// go backwards up the string
			if (*tEnd != *sEnd){		// if they don't match end loop
				break;
			}
			else{						// if they match 
				if (i == tLen - 1){		// and we've reached the end of our for loop
					retVal = 1;			// set retVal to 1
				}
			}
		}
	}

	return retVal;
} 

/******************************************************************************
 *
 * TrimRight()
 *
 * Removes characters from the end of a string, defaults to whitespace
 * characters is trimChars is null.
 *
 *****************************************************************************/
char* TrimRight(char* str, const char* trimChars)
{
	int i;

	if (trimChars == NULL)
	{
		trimChars = "\t\n\v\f\r ";
	}

	i = strlen(str) - 1;
	while (i >= 0 && strchr(trimChars, str[i]) != NULL)
	{
		str[i] = '\0';
		i--;
	}

	return str;
}