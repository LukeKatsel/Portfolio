#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FirmwareSlice {          // structure to hold slice info
    char *name;                 // slice name
    long offset;                // offset from 0x0 - got from binwalk
    long size;                  // size of slice - calculated by subtracting binwalk offsets
};

struct FirmwareSlice firmware_slices[] = {  // array of firmware slices
    {"u-boot.bin.img", 0x0, 0x2c5f1},
    {"u-boot.env.img", 0x2c5f1, 0x303},
    {"romfs-x.squashfs.img", 0x2c8f4, 0x2d50e5},
    {"user-x.squashfs.img", 0x3019d9, 0x3e659b},
    {"web-x.squashfs.img", 0x6e7f74, 0x3fa11},
    {"custom-x.cramfs.img", 0x727985, 0x2f202},
    {"InstallDesc", 0x756b87, 0x474}        // this is the one we want to edit
};

void unpack(char *filename);    // function to unpack the .bin file
void pack(char *filename);      // function to repack the .bin file

int main(int argc, char *argv[]) {  //main function - need to accept command line args
    if (argc != 3) {            // requires 3 args 
        printf("Usage: %s [unpack/pack] [firmware_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // the 2nd command line arg determines the function
    if (strcmp(argv[1], "unpack") == 0) {
        unpack(argv[2]);    // pass filename to function
    } 
    else if (strcmp(argv[1], "pack") == 0) {
        pack(argv[2]);      // pass filename to function
    } 
    else {
        printf("Invalid command\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void unpack(char *filename) {
    FILE *file = fopen(filename, "rb");    // file pointer to .bin file read binary mode
    if (file == NULL) {                    // error checking
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sizeof(firmware_slices) / sizeof(firmware_slices[0]); i++) {    // iterate through all of the slices
        FILE *outfile = fopen(firmware_slices[i].name, "wb");   // create/open file to write slice to

        if (outfile == NULL) {          // error checking
            perror("Error creating output file");
            exit(EXIT_FAILURE);
        }

        fseek(file, firmware_slices[i].offset, SEEK_SET);  // move to beginning of slice
        char buffer[firmware_slices[i].size];       //load size of slice
        size_t bytesRead = fread(buffer, 1, firmware_slices[i].size, file); // read the desired slice

        fwrite(buffer, 1, bytesRead, outfile);  // write to new file
        fclose(outfile);    // close the new file

        printf("Wrote %lx bytes to %s \n", bytesRead, firmware_slices[i].name);   // report progress to command line
    }

    fclose(file);   // close the .bin file
}

void pack(char *filename) {
    FILE *file = fopen(filename, "wb");     // open the .bin file for writing
    if (file == NULL) {                     // error checking

        perror("Error creating output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < sizeof(firmware_slices) / sizeof(firmware_slices[0]); i++) { // iterate through all of the slices
        FILE *infile = fopen(firmware_slices[i].name, "rb");    // open the new slice files for reading

        if (infile == NULL) {           // error checking
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }

        fseek(infile, 0, SEEK_END);     // move pointer to end of file
        long fileSize = ftell(infile);  // get file size 
        rewind(infile);                 // set pointer back to beginning of file

        char buffer[fileSize];          // create buffer array of file size elements
        fread(buffer, 1, fileSize, infile); // read the slice file into buffer
        fwrite(buffer, 1, fileSize, file);  // write buffer to .bin file
        long padding = firmware_slices[i].size - fileSize;  // padding to keep size consistent

        printf("Wrote %lx bytes to %s\n", fileSize, firmware_slices[i].name); // report to command line
        printf("Padding: %lx\n", padding);  // report padding to command line
        
        for (long j = 0; j < padding; j++) {
            fputc('\0', file);              // append padding to file
        }

        fclose(infile);                 // close the slice file
    }

    fclose(file);                       // close the .bin file
}
