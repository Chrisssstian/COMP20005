/* Calculates Net Icome after taxes from Gross Income
 By Christian Drozdowicz*/

#include <stdio.h>
#include <stdlib.h>

/* percentages at each bracket +medicare levy */
#define RATE1 0
#define RATE2 0.19
#define RATE3 0.325
#define RATE4 0.37
#define RATE5 0.45
#define RATE6 0.475
#define LEVY1 0.015
#define LEVY2 0.025

/* takes into account all tax from previous brackets as move up brackets */
#define bracket1 0
#define bracket2 (bracket1 + (RATE1 * (18200-0)))
#define bracket3 (bracket2 + (RATE2 * (37000-18200)))
#define bracket4 (bracket3 + (RATE3 * (80000-37000)))
#define bracket5 (bracket4 + (RATE4 * (180000-80000)))
#define bracket6 (bracket5 + (RATE5 * (250000-180000)))

int
main(int argc, char const *argv[]) {
/*where "leftover" is the income left to tax at current bracket */
  double x, leftover, tax, levy;
/* requests gross income and stores it using scanf */
  printf("Type your gross income:$ ");

/* eliminates inputs with more or less than one input */
  if (scanf("%lf", &x) != 1) {
    printf("No value was entered\n");
    exit(EXIT_FAILURE);


/* eliminates negative gross income inputs */
  if (x < 0 ) {
    printf("Invalid Income\n");
    exit(EXIT_FAILURE);
  }

  }
/* first bracket */
  if (x >= 0 && x <= 18200) {
    leftover = x - 0;
    tax = bracket1 + (leftover * RATE1);
  }
/* second bracket */
  if (x > 18200 && x <= 37000) {
    leftover = x - 18200;
    tax = bracket2 + (leftover * RATE2);
  }
/* third bracket */
  if (x > 37000 && x <= 80000) {
    leftover = x - 37000;
    tax = bracket3 + (leftover * RATE3);
  }
/* fourth bracket */
  if (x > 80000 && x<= 180000) {
    leftover = x - 80000;
    tax = bracket4 + (leftover * RATE4);
  }
/* fifth bracket */
  if (x > 180000 && x <= 250000) {
    leftover = x - 180000;
    tax = bracket5 + (leftover * RATE5);
  }
/* sixth bracket */
  if (x > 250000){
    leftover = x - 250000;
    tax = bracket6 + (leftover * RATE6);
  }

/* medicare levy */
  if (x <= 100000) {
    levy = x * LEVY1;
  }
  else {
    levy = x * LEVY2;
  }

/* prints results */
  printf("Gross income: $%.2f\nless tax: -$%.2f\nless medicare: -$%.2f\nnet income: $%.2f\n",x,tax, levy, x - tax - levy);
  return 0;
}
