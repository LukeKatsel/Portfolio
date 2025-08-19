#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {
    
    FILE* fileinput;
    int fileContents;
    int count = 0;
    int usernum;
    int found = 0;


    printf("Enter an interger: ");
    scanf("%d", &usernum);
    
    fileinput = fopen("Wednesdays_data.dat", "r");
    if (fileinput == NULL) {
        printf("file not found\n");
    }

    else {

        while (fscanf(fileinput, "%d", &fileContents) != EOF) {

            count = count + 1;
         
            if (usernum == fileContents) {

                found = found + 1;
            }

        }
      
          

        printf("There are a total of %d intergers in the file \n", count);
        printf("The integer %d was found %d times", usernum, found);
    }

    


    return(0);
}