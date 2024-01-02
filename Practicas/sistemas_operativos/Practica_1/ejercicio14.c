#include "stdio.h"
#include "time.h"

int main()
{
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int year = tm_struct->tm_year;
    year += 1900;
    printf("Año actual: %d\n", year);

    return 0;
}