#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

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