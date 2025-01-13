#include <stdlib.h>
#include <stdio.h>

#include "csv.h"

void writeHeader(const csv_row_t *row, FILE *fp)
{
    for (const csv_data_t *p = row->rowItems; p != NULL; p = p->next)
    {
        fputs(p->name, fp);
        if (p->next != NULL)
        {
            fputs(",", fp);
        }
    }
    fputs("\n", fp);
}

void writeValues(const csv_row_t *head, FILE *fp)
{
    for (const csv_row_t *p = head; p != NULL; p = p->next)
    {
        for (const csv_data_t *q = p->rowItems; q != NULL; q = q->next)
        {
            fputs(q->value, fp);
            if (q->next != NULL)
            {
                fputs(",", fp);
            }
        }
        fputs("\n", fp);
    }
}

void writeCSV(const csv_row_t *head, const char *fileName)
{
    FILE *fp = fopen(fileName, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", fileName);
        exit(1);
    }

    writeHeader(head, fp);
    writeValues(head, fp);
    fclose(fp);
}