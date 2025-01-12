#ifndef CSV_H
#define CSV_H

#define CSV_MAX_LINE_LEN 4096
#define CSV_MAX_NAME_LEN 256
#define CSV_MAX_VALUE_LEN 4096

typedef struct csv_data
{
    struct csv_data *next;
    struct csv_data *prev;

    unsigned int index;

    char name[CSV_MAX_NAME_LEN];
    char value[CSV_MAX_VALUE_LEN];
} csv_data_t;

typedef struct csv_row
{
    struct csv_row *next;
    struct csv_row *prev;

    unsigned int index;

    csv_data_t *rowItems;
} csv_row_t;

csv_row_t *readCSV(char *fileName);
csv_data_t *addDataList(csv_data_t **head, csv_data_t *new);
void removeDataList(csv_data_t **head);
csv_data_t *searchByIndex(csv_data_t *head, unsigned int index);
csv_data_t *searchByName(csv_data_t *head, const char *name);

csv_row_t *addDataToRow(csv_row_t *row, csv_data_t *data);
csv_row_t *addRowList(csv_row_t **head, csv_row_t *new);
void removeRowList(csv_row_t **head);

#endif