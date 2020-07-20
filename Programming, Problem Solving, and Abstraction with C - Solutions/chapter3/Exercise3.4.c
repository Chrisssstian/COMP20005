#include <stdio.h>
#include <stdlib.h>

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

/* Focus on February */
  if (month == 2){
    /* Exactly divisible by 400 e.g. 1600, 2000 (leap year) */
    if (year%400 == 0) {
      /* filter invalid day entry for leap year february */
      if (day > 29){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
      else if (day == 29){
        day = 1;
        month++;
      }
      /* any other day in february */
      else {
        day++;
      }
    }
    /* Exactly divisible by 100 and not by 400 e.g. 1900, 2100 (not leap year) */
    else if (year%100 == 0){
      /* filter invalid day entry for non leap year february */
      if (day > 28){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
      else if (day == 28){
        day = 1;
        month++;
      }
      /* any other day in february */
      else {
        day++;
      }
    }
    /* Exactly divisible by 4 and neither by 100 nor 400 e.g. 2016, 2020 (leap year) */
    else if (year%4 == 0) {
      if (day > 29){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
      else if (day == 29){
        day = 1;
        month++;
      }
      /* any other day in february */
      else {
        day++;
      }
    }
    /* Not divisible by 4 or 100 or 400 e.g. 2017, 2018, 2019 (not a leap year) */
    else if (year%4 != 0 || year%100 != 0 || year%400 != 0){
      if (day > 28){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
      }
      else if (day == 28){
        day = 1;
        month++;
      }
      /* any other day in february */
      else {
        day++;
      }
    }

  }

/* for April, June, September, November */
  else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day > 30){
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }
    /* reset month at the end of day 30 */
    else if (day == 30) {
      day = 1;
      month++;
    }
    /* any other day in these months */
    else {
      day++;
    }
  }

/* for January, March, May, July, August, October */
  else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10) {
    if (day > 31){
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }
    /* reset month at end of day 31 */
    else if (day == 31) {
      day = 1;
      month++;
    }
    /* any other day in these months */
    else {
      day++;
    }
  }

/* for December to reset the year at end of month */
  else if (month == 12) {
    if (day > 31){
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }
    else if (day == 31){
      day = 1;
      month = 1;
      year++;
    }
    /* any other day in December */
    else {
      day++;
    }
  }








  printf("The next date is: %02d/%02d/%d\n",day,month,year);


  return 0;
}
