/*
This program takes a date and calculates the date of the next day.
*/
#include <stdio.h>
#include <stdlib.h>

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12

#define MONTHS_IN_YEAR 12
#define MAX_MONTH_LENGTH 31
#define MIN_YEAR 1753

int
main(int argc, char *argv[]) {

    int day = 0; int month = 0; int year = 0;
    int length_of_month = 0; int i; int daySum = 0;

    printf("Enter the date in format dd/mm/yyy: ");

    if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
        printf("An error occured. Please try again.\n");
        exit(EXIT_FAILURE);
    }

    if (day > MAX_MONTH_LENGTH) {
        printf("There're a maximum of 31 days in a month.\n");
        exit(EXIT_FAILURE);
    }

    if (month > MONTHS_IN_YEAR) {
        printf("There're only 12 months in a year.\n");
        exit(EXIT_FAILURE);
    }

    if (year < 1753) {
        printf("The current calendar begin in 1753.\n");
        exit(EXIT_FAILURE);
    }
    if (month == JAN) {
        daySum += day;
    } else {
        for (i=0; i<month; i++) {
            if (i == FEB) {
            length_of_month = 28 +
            (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0));
            }
            if (i == SEP || i == APR || i == JUN || i == NOV) {
                length_of_month = 30;
            }
            if (i == JAN || i == MAR || i == MAY || i == JUL || i == AUG || i == OCT || i == DEC) {
                length_of_month = 31;
            }
            daySum += length_of_month;
        }
        daySum += day;
    }


    printf("%d/%d/%d is day number %d in the year.\n", day, month, year, daySum);

    return 0;
}
