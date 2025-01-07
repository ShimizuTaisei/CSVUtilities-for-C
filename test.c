#include  <stdio.h>
#include "csv.h"

int main(void)
{
    csv_data_t *data = readCSV("test.csv");
    return 0;
}