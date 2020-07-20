/* Finds the value of logstar (how many time you can take a log of argument
before getting a value less than 1) to log base 2 of input
By Christian Drozdowicz 23/03/2019*/

#include <stdio.h>
#include <math.h>

double logstar(double n);

int
main(int argc, char const *argv[]) {
  double n;
  printf("Please entera value to logstar: ");
  scanf("%lf", &n);

  printf("%.lf is the value of logstar\n", logstar(n));
  return 0;
}

/* uses recursion to count number of logs abocve zero and stops when first log
less than one is found */
double logstar(double n) {
  double new_n = log(n) / log(2);
  if (new_n < 0) {
    return 0;
  }
  return (1 + logstar(new_n));
}
