#include  <stdio.h>
#include "csv.h"

int main(void)
{
    csv_row_t *data = readCSV("test.csv");
    return 0;
}