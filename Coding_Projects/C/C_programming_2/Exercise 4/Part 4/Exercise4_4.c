/*****************************************************
 *
 *  CSCV352 - Exercise4_4.c
 *
 *  Luke Katsel
 *
******************************************************/
#include <stdio.h>
#include <string.h>

#define CONGESTION_WINDOW_REDUCED 0x80
#define ECN_ECHO 0x40
#define URGENT 0x20
#define ACKNOWLEDGEMENT 0x10
#define PUSH 0x08
#define RESET 0x04
#define SYN 0x02
#define FIN 0x01

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
int DisplayTCPSegment(unsigned char *pSegment, int segmentLen);


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
    DumpHex(segmentBuffer, bytesRead, 16);

    DisplayTCPSegment(segmentBuffer, bytesRead);

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

int DisplayTCPSegment(unsigned char *pSegment, int segmentLen){

	unsigned short sourcePort = 0, destPort = 0;
	int sequenceNumber = 0, ackNumber = 0;
	unsigned char flags = 0;

	sourcePort += *pSegment << 8;				// increment through pointer shifting the values down the varriables
	pSegment++;
	sourcePort += *pSegment;
	pSegment++;
	destPort += *pSegment << 8;
	pSegment++;
	destPort += *pSegment;
	pSegment++;
	sequenceNumber += *pSegment << 24;
	pSegment++;
	sequenceNumber += *pSegment << 16;
	pSegment++;
	sequenceNumber += *pSegment << 8;
	pSegment++;
	sequenceNumber += *pSegment;
	pSegment++;
	ackNumber += *pSegment << 24;
	pSegment++;
	ackNumber += *pSegment << 16;
	pSegment++;
	ackNumber += *pSegment << 8;
	pSegment++;
	ackNumber += *pSegment;
	pSegment++;
	pSegment++;
	flags += *pSegment;							// flags is the last one 

	if ((flags & CONGESTION_WINDOW_REDUCED) != 0){
		flags = 128;							// if statements to determine which flag is thrown 
	}
	else if ((flags & ECN_ECHO) != 0){
		flags = 64;
	}
	else if ((flags & URGENT) != 0){
		flags = 32;
	}
	else if ((flags & ACKNOWLEDGEMENT) != 0){
		flags = 16;
	}
	else if ((flags & PUSH) != 0){
		flags = 8;
	}
	else if ((flags & RESET) != 0){
		flags = 4;
	}
	else if ((flags & SYN) != 0){
		flags = 2;
	}
	else if ((flags & FIN) != 0){
		flags = 1;
	}


	printf("\nTCP Header Feilds\n");					// print statements 
	printf("\tSource Port:\t%12d\n", sourcePort);
	printf("\tDest Port:\t%12d\n", destPort);
	printf("\tSequence No:\t%12u\n", sequenceNumber);
	printf("\tAck No:\t%12u\n", ackNumber);
	printf("\tFlags:\t%12d\n\t", flags);

	switch (flags)										// switch statements to print abbreviation for flag 
	{
	case 1:
		printf("FIN\n\n");
		break;
	case 2:
		printf("SYN\n\n");
		break;
	case 4:
		printf("RST\n\n");
		break;
	case 8:
		printf("PSH\n\n");
		break;
	case 16:
		printf("ACK\n\n");
		break;
	case 32:
		printf("URG\n\n");
		break;
	case 64:
		printf("ECE\n\n");
		break;
	case 128:
		printf("CWR\n\n");
		break;
	default:
		break;
	}

	return 0;
}