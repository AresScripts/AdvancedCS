#include <stdio.h>
#include <string.h>

typedef struct S_CompSciStudent {
    char firstName[10];
    char lastName[10];
    char letterGrade;
} CompSciStudent;

const int MAX_STUDENTS = 4;

void printList(CompSciStudent *students, int numStudents) {
    printf("Printing List...\n");
    for(int i = 0; i < numStudents; i++){
      if(students[i].letterGrade != '\0')
        printf("%s, %s:\t%c\n", students[i].lastName, students[i].firstName, students[i].letterGrade);
    }
}

int addStudent(CompSciStudent *student) {
    printf("Enter FirstName LastName LetterGrade: ");
    char input[32];
    fgets(input, 31, stdin);
    int ok = 0;

    int res = sscanf(input, "%s %s %c", &student->firstName, &student->lastName, &student->letterGrade);
    if(res == 3){
        ok = 1;
        printf("Added: %s,\t%s\t%c\n", student->lastName, student->firstName, student->letterGrade);
    }else
        printf("Sorry, error parsing input\n");
    return ok;
}

int removeStudent(CompSciStudent *student){
    printf("Enter index: ");
    return -1;
}

void main(){
    CompSciStudent students[MAX_STUDENTS];
    int numStudents = 0;

    char command[32];
    char input[32];

    while(fgets(input, 32, stdin)) {
        sscanf(input, "%s", command);
        if(strncmp(command, "quit", 4) == 0) {
            printf("\nExiting...\n");
            break;
        } else if(strncmp(command, "print", 5) == 0) {
            printList(students, numStudents);
        }else if(strncmp(command, "add", 3) == 0){
            if(numStudents < MAX_STUDENTS){
                numStudents += addStudent(&students[numStudents]);
            }else{
                printf("List is full. Could not add student\n\n");
            }
        }else if(strncmp(command, "remove", 7) == 0){
            printf("Remove has not been coded yet...");
        }
    }
    return;
}
