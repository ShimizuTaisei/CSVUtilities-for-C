#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "../csv.h"

student_t *road()
{
    student_t *students = NULL;

    csv_row_t *dataList = readCSV("score.csv");

    for (csv_row_t* c = dataList; c != NULL; c = c->next)
    {
        student_t *newStudent = (student_t*)malloc(sizeof(student_t));
        newStudent->num = strtol(searchByName(c->rowItems, "Num")->value, NULL, 10);
        for (csv_data_t *d = c->rowItems; d != NULL; d = d->next)
        {
            if (strcmp(d->name, "Num") != 0)
            {
                subject_t *newSubject = (subject_t*)malloc(sizeof(subject_t));
                strcpy(newSubject->name, d->name);
                newSubject->score = strtol(d->value, NULL, 10);
                newStudent->subjects = appendSubject(newSubject, newStudent->subjects);
            }
        }
        students = appendStudent(newStudent, students);
    }
    return students;
}

int main (void) {
    printf("Hello, World!\n");
    student_t *students = road();
    return 0;
}