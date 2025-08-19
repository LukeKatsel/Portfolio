/*****************************************************
 *
 *  CSCV352 - Exercise4_4.c
 *
 *  Student:  <Student's Name>
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
void DumpHex(const void* data, size_t size, int width);


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
    unsigned char segmentBuffer[1500];
    int bytesRead;

    // Read the TCP segment from stdin
    bytesRead = fread(segmentBuffer, 1, 1500, stdin);

    // Uncomment this line to dump the packet to the console
//    DumpHex(segmentBuffer, bytesRead, 16);

    // ADD YOUR CALL TO DisplayTCPSegment() HERE

    return 0;

}

/*******************************************************************
 * 
 *   DumpHex()
 * 
 *   Formatted output of raw data.
 * 
*******************************************************************/
void DumpHex(const void* data, size_t size, int width) 
{
	char ascii[17];
	size_t i, j;

	ascii[width] = '\0';
	for (i = 0; i < size; ++i) 
    {
        // Print the value
		printf("%02X ", ((unsigned char*)data)[i]);

        // save the ascii display value in the relative position
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') 
        {
			ascii[i % width] = ((unsigned char*)data)[i];
		} 
        else 
        {
			ascii[i % width] = '.';
		}


		if ((i+1) % (width / 2) == 0 || i+1 == size) 
        {
			printf(" ");
			if ((i+1) % width == 0) 
            {
				printf("|  %s \n", ascii);
			} 
            else if (i+1 == size) 
            {
				ascii[(i+1) % width] = '\0';
				if ((i+1) % width <= (width / 2)) 
                {
					printf(" ");
				}
				for (j = (i+1) % width; j < width; ++j) 
                {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}