#include <stdio.h>
#include "student.h"
#include "../csv.h"

void road()
{
    student_t *students = NULL;

    csv_data_t *dataList = readCSV("score.csv");

    csv_data_t *c;
    for (c = dataList; c != NULL; c = c->next)
    {
        printf("%s\n", c->name);
    }
}

int main (void) {
    printf("Hello, World!\n");
    return 0;
}