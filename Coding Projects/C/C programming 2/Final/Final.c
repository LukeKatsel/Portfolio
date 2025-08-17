#include <stdio.h>
#include <string.h>

typedef struct {
    char firstName[50];
    char middleName[50];
    char lastname[50];
} Name;

typedef struct {
    Name studentName;
    int studentId;
    int studentYear;
    int schoolId;
} Student;

void PrintStudentName(Student *pStudent){
    printf("%s %c. %s", pStudent->studentName.firstName, pStudent->studentName.middleName[0], pStudent->studentName.lastname);
}

int main(void){



    return 0;
}