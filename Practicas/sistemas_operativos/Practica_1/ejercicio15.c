#include "stdio.h"
#include "time.h"
#include "string.h"

int main()
{
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int year = tm_struct->tm_year;
    year += 1900;
    char formatedDate[60];
    strftime(formatedDate, 60, "%A, %d de %B de %Y, %H:%M\n", tm_struct);
    printf("%s", formatedDate);

    return 0;
}