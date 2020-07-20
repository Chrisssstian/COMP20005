#include <stdio.h>

double summation(int n, double x);

int
main(int argc, char **argv) {

  int n;
  double x;

  printf("Enter n and x: ");
  scanf("%d %lf", &n, &x);



  printf("\nthe summation of %d and %lf is: %lf\n", n, x, summation(n, x));

  return 0;
}


double summation(int n, double x) {
  int i, j;
  double pow=1, sum=0;

  for (i=1;i<=n;i++){
    pow = 1;
    for(j=0;j<i;j++) {
      pow *= x;
      printf("%d\n", j);
      printf("%lf\n", pow);


    }
    sum += pow / i;
  }
  return sum;
}
