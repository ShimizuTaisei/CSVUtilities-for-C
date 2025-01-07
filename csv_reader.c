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

/**
 * @fn
 * @brief
 * Read the CSV file.
 * @param fileName The name of the file.
 * @return The list of the data.
 */
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