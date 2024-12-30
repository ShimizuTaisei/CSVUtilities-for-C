#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

void readHeader(csv_data_t **dataList, char str[])
{
    const char *token = strtok(str, ",");
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

void readValues(csv_data_t **dataList, csv_data_t *headerList, char str[])
{
    char *token = strtok(str, ",");
    unsigned int index = 0;
    while (token != NULL)
    {
        csv_data_t *header = searchByIndex(headerList, index);

        csv_data_t *new = (csv_data_t *) malloc(sizeof(csv_data_t));
        new->index = index;
        strcpy(new->name, header->name);
        strcpy(new->value, token);
        addList(dataList, new);

        token = strtok(NULL, ",");
        index++;
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

/**
 * @fn
 * @brief
 * Search the list by index.
 * @param head The double pointer to the head of the list.
 * @param index The query for searching by index.
 * @return The result of the search.
 */
csv_data_t *searchByIndex(csv_data_t *head, unsigned int index)
{
    for (csv_data_t* p = head; p != NULL; p = p->next)
    {
        if (p->index == index)
        {
            return p;
        }
    }
    return NULL;
}

/**
 * @fn
 * @brief
 * Search the list by name.
 * @param head The double pointer to the head of the list.
 * @param name The query for searching by name.
 * @return The result of the search.
 */
csv_data_t *searchByName(csv_data_t *head, const char *name)
{
    for (csv_data_t* p = head; p != NULL; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            return p;
        }
    }
    return NULL;
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

    csv_data_t *headerList = NULL;
    csv_data_t *dataList = NULL;

    unsigned int line = 1;
    char str[CSV_MAX_LINE_LEN];
    while (fgets(str, CSV_MAX_LINE_LEN, fp))
    {
        if (line <= 1)
        {
            readHeader(&headerList, str);
        } else
        {
            readValues(&dataList, headerList, str);
        }
        line++;
    }

    return dataList;
}