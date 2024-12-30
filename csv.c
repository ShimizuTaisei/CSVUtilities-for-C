#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

void readHeader(csv_data_t **dataList, char str[])
{
    char *token = strtok(str, ",");
    unsigned int index = 0;
    while (token != NULL)
    {
        csv_data_t *new = (csv_data_t *) malloc(sizeof(csv_data_t));
        strcpy(new->name, token);
        new->index = index++;
        new->next = NULL;
        new->prev = NULL;
        addList(dataList, new);
        token = strtok(NULL, ",");
    }
}

csv_data_t *addList(csv_data_t **head, csv_data_t *new)
{
    if (*head == NULL)
    {
        *head = (csv_data_t*) malloc(sizeof(csv_data_t));
        **head = *new;
    } else
    {
        csv_data_t *p;
        for (p = *head; p->next != NULL; p = p->next) {}
        p->next = new;
        new->prev = p;
    }
    return *head;
}

void removeList(csv_data_t **head)
{
    csv_data_t *p = *head;
    while (p != NULL)
    {
        csv_data_t* target = p;
        p = p->next;
        free(target);
    }
}

csv_data_t *readCSV(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", fileName);
    }

    csv_data_t *dataList = NULL;

    unsigned int line = 1;
    char str[CSV_MAX_LINE_LEN];
    while (fgets(str, CSV_MAX_LINE_LEN, fp))
    {
        if (line <= 1)
        {
            readHeader(&dataList, str);
        }
        printf("%s", str);
        line++;
    }

    return dataList;
}