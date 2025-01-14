#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../csv.h"
#include "student.h"

student_t *readFile(char *fileName)
{
    student_t *students = NULL;

    csv_row_t *dataList = readCSV(fileName);

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

void writeFile(const student_t *list, const char *fileName)
{
    csv_row_t *csvRow = NULL;
    for (const student_t *p = list; p != NULL; p = p->next)
    {
        csv_row_t *newRow = (csv_row_t*)malloc(sizeof(csv_row_t));
        csv_data_t *newNum = (csv_data_t*)malloc(sizeof(csv_data_t));
        strcpy(newNum->name, "Num");
        sprintf(newNum->value, "%d", p->num);
        addDataToRow(newRow, newNum);

        for (subject_t *q = p->subjects; q != NULL; q = q->next)
        {
            csv_data_t *newScore = (csv_data_t*)malloc(sizeof(csv_data_t));
            strcpy(newScore->name, q->name);
            sprintf(newScore->value, "%d", q->score);
            addDataToRow(newRow, newScore);
        }
        addRowList(&csvRow, newRow);
    }

    writeCSV(csvRow, fileName);
}