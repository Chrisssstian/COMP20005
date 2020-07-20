/* Class Exercise from lecture By Christian Drozdowicz 17/03/2019 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
  double x, y;
  printf("Please enter the first floating point value: ");

  /* this scanf makes sure it is a numeric input otherwise failure */
  if (scanf("%lf", &x) != 1) {
    printf("Invalid\n");
    exit(EXIT_FAILURE);
  }
  printf("Please enter the second floating point value: ");
  if (scanf("%lf", &y) != 1) {
    printf("Invalid\n");
    exit(EXIT_FAILURE);
  }

  else if (((x > y) && (x - y <= 0.000006)) || ((y > x) && (y - x <= 0.000006))) {
    printf("Nearly Equal\n");
  }

  else if (x < 0 || y < 0) {
    printf("here is the sum of %lf and %lf which = %lf\n", x, y, x+y);
  }

  else {
    printf("here is the product of %lf and %lf which = %lf\n", x, y, x*y);
  }



  return 0;
}
