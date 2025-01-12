#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"


/**
 * @fn
 * @brief
 * 文字列の末尾の改行文字を削除する
 * @param str 対象の文字列
 */
void removeTrailingNewLine(char *str) {
    const size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


void readHeader(csv_data_t** dataList, char str[])
{
    const char* token = strtok(str, ",");
    unsigned int index = 0;
    while (token != NULL)
    {
        csv_data_t* new = (csv_data_t*)malloc(sizeof(csv_data_t));
        strcpy(new->name, token);
        new->index = index++;
        new->next = NULL;
        new->prev = NULL;
        addDataList(dataList, new);
        token = strtok(NULL, ",");
    }
}

void readValues(csv_data_t** dataList, csv_data_t* headerList, char str[])
{
    char* token = strtok(str, ",");
    unsigned int index = 0;
    while (token != NULL)
    {
        csv_data_t* header = searchByIndex(headerList, index);

        csv_data_t* new = (csv_data_t*)malloc(sizeof(csv_data_t));
        new->index = index;
        strcpy(new->name, header->name);
        strcpy(new->value, token);
        addDataList(dataList, new);

        token = strtok(NULL, ",");
        index++;
    }
}

csv_row_t* readCSV(char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", fileName);
    }

    csv_data_t* headerList = NULL;
    csv_row_t* rowList = NULL;

    unsigned int line = 1;
    char str[CSV_MAX_LINE_LEN];
    while (fgets(str, CSV_MAX_LINE_LEN, fp))
    {
        removeTrailingNewLine(str);
        if (line <= 1)
        {
            readHeader(&headerList, str);
        }
        else
        {
            csv_data_t* dataList = NULL;
            readValues(&dataList, headerList, str);

            csv_row_t* row = (csv_row_t*)malloc(sizeof(csv_row_t));
            addDataToRow(row, dataList);
            addRowList(&rowList, row);
        }
        line++;
    }

    fclose(fp);

    return rowList;
}