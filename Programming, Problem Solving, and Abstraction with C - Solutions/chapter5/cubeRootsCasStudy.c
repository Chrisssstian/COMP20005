/* calculates cube root approximation accurate for values between 10^-6 to 10^6
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
  int i;
  /* If input outside accurate boundaries give warning */
  if (fabs(x) <= CUBE_LOWER || fabs(x) >= CUBE_UPPER) {
    printf("Answer may be inaccurate as outside the boundary\n");
  }
  /* iterate to get cube root of input */
  for (i = 0; i < CUBE_ITERATIONS; i++) {
    y = (2 * y + x / pow(y, 2))/3;
  }
  /* return the cube root in the form of a double */
  return y;

}
