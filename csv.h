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
} csv_data_t ;

csv_data_t *addList(csv_data_t **head, csv_data_t *new);
void removeList(csv_data_t **head);
csv_data_t *readCSV(char *fileName);

#endif