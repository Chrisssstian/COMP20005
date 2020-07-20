/* calculates cube root approximation accurate for values between 10^-6 to 10^6
and implements a new function to check if they are near equal
By Christian Drozdowicz 19/03/2019*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* define constants used */
#define CUBE_UPPER 1e-6
#define CUBE_LOWER 1e+6
#define CUBE_ITERATIONS 25

/* prototype cube_root function */
double cube_root(double x);
/* prototype near equal function */
int near_equal(double x1, double x2);

int
main(int argc, char const *argv[]) {

  double n, c_root;
/* ask user for value */
  printf("Please enter a value for n: \n");
  /* check if scanf is true */
  if (scanf("%lf", &n) != 1) {
    printf("No value was entered\n");
    exit(EXIT_FAILURE);
  }

  c_root = cube_root(n);

  printf("This is the approximate cube root: %16.9e\n", c_root);

  return 0;
}


/* cube_root function definition */
double cube_root(double x){
  /* initialise y = 1.0 for approximation calculation Newton Raphson method */
  double y = 1.0;
  int loops = 0;
  /* If input outside accurate boundaries give warning */
  if (fabs(x) <= CUBE_LOWER || fabs(x) >= CUBE_UPPER) {
    printf("Answer may be inaccurate as outside the boundary\n");
  }

  /* while loop  */

  while (!near_equal(x, y*y*y)){
    y = (2 * y + x / pow(y, 2))/3;
    loops++;
  }
  printf("looped %d times\n", loops);
  /* return the cube root in the form of a double */
  return y;
}


int near_equal(double x1, double x2) {
  double difference;
  if(x1 < x2){
    double temp;
    temp = x1;
    x1 = x2;
    x2 = temp;
  }
  difference = x1 - x2;
  if (difference != 0) {
    if (difference / x1 > 0.0001) {
      return 0;
    }
  }
  return 1;
}
