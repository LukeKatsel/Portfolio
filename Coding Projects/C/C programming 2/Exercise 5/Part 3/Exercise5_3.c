#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 60
#define MAX_EMAIL_ADDRESS 250

#pragma pack(1)
typedef struct {
char firstName[MAX_NAME];
char lastName[MAX_NAME];
char middleName[MAX_NAME];
char emailAddress[MAX_EMAIL_ADDRESS];
int grade; // on a 100% scale
} StudentInformation;


int main(int argc, char *argv[]){


    FILE *file;
    int fileSize, entries, i, count = 0, infoSize = sizeof(StudentInformation);
    StudentInformation *students = NULL; 
    argv[1] = "students.bin";

    if ((file = fopen(argv[1], "rb")) != NULL){
        fseek(file, 0, SEEK_END);

        fileSize = ftell(file);
        entries = fileSize / infoSize;

        fseek(file, 0, SEEK_SET);
        
        students = malloc(entries); 

        if (students == NULL)
		{
			printf("Critical memory error\n");
			exit(0);
		}

        while (fread(&students[count], infoSize, 1, file) == 1){
            count++;
        }
        
        for (i = 0; i < entries; i++){

            printf("%s,%s\t\t%s\t\t%d\n", students[i].lastName, students[i].firstName, students[i].emailAddress, students[i].grade);
            
        }

        free(students);
        fclose(file);
    }
    else{
        printf("Could not open file!\n");
    }
    return 0;
}