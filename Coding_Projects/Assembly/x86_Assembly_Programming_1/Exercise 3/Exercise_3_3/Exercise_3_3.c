#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)
typedef struct student_record
{
    char firstName[64];
    char middleName[64];
    char lastName[64];
    int class;
    int studentId;
} StudentRecord;

extern void PrintRecord(StudentRecord *pRecord);
void PrintRecordInC(StudentRecord* pRecord);

#if defined(_M_IX86)
# pragma comment(linker, "/INCLUDE:_mainCRTStartup")
#else
# pragma comment(linker, "/INCLUDE:mainCRTStartup")
#endif

int main()
{
    StudentRecord record;

    strcpy(record.firstName, "Susan");
    strcpy(record.middleName, "B.");
    strcpy(record.lastName, "Anthony");
    record.class = 5;
    record.studentId = 12345;

    printf("\nIn C:\n");
        
    PrintRecordInC(&record);

    printf("\nIn Assembly:\n");

    PrintRecord(&record);

    return 0;
}

void PrintRecordInC(StudentRecord *pRecord)
{
    printf("First Name:  %s\n", pRecord->firstName);
    printf("Last Name:   %s\n", pRecord->lastName);
    printf("Class:       %d\n", pRecord->class);
    printf("Student Id:  %d\n", pRecord->studentId);
}