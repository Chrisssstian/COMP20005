/* Program to take date input and return what day number within the year
By Christian Drozdowicz */

#include <stdio.h>
#include <stdlib.h>

/* function takes the three inputs and uses it to determine the input month's max days */
int daysInMonth(int day, int month, int year){
  /* Focus on February */
    if (month == 2){
      /* Exactly divisible by 400 e.g. 1600, 2000 (leap year) */
      if (year%400 == 0) {
        return 29;
        /* filter invalid day entry for leap year february */
        if (day > 29){
          printf("Invalid input\n");
          exit(EXIT_FAILURE);
        }

      }
      /* Exactly divisible by 100 and not by 400 e.g. 1900, 2100 (not leap year) */
      else if (year%100 == 0){
        return 28;
        /* filter invalid day entry for non leap year february */
        if (day > 28){
          printf("Invalid input\n");
          exit(EXIT_FAILURE);
        }
      }
      /* Exactly divisible by 4 and neither by 100 nor 400 e.g. 2016, 2020 (leap year) */
      else if (year%4 == 0) {
        return 29;
        if (day > 29){
          printf("Invalid input\n");
          exit(EXIT_FAILURE);
        }
      }
      /* Not divisible by 4 or 100 or 400 e.g. 2017, 2018, 2019 (not a leap year) */
      else if (year%4 != 0 || year%100 != 0 || year%400 != 0){
        return 28;
        if (day > 28){
          printf("Invalid input\n");
          exit(EXIT_FAILURE);
        }
      }
    return 0;
    }

  /* for April, June, September, November */
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
      return 30;
      if (day > 30){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
    }

  /* for January, March, May, July, August, October */
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
      return 31;
      if (day > 31){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
    }

}

/* start main function */
int
main(int argc, char const *argv[]) {
  int day,month,year;
  printf("Enter date in format dd/mm/yyyy: \n" );

  /* remove obvious invalid */
  if (scanf("%d/%d/%d",&day,&month,&year) != 3){
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }
  if (day > 31 || month > 12) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }
  if (year <= 1753) {
    printf("Not accurate for this year and below\n");
    exit(EXIT_FAILURE);
  }

/* run through for loop for each month before the current month and add the total days of each */
  int i, dayCount = 0, totDayCount;
  for (i = month-1; i > 0; i--){
    dayCount += daysInMonth(day, i, year);
  }

  /* take total of days for each previous month and add the days for current month */
  totDayCount = day + dayCount;

  printf ("Day number: %d\n",totDayCount);
  return 0;
}
