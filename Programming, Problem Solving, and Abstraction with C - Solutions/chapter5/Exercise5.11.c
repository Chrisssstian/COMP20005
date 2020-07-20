/* follows calculation of 5.11 exercise
By Christian Drozdowicz 23/03/2019 */
#include <stdio.h>


double sum_sequence(int n);
int factorial(int x);
int supersum(int a);

int
main(int argc, char const *argv[]) {

  int n;
  printf("Please enter an integer: ");
  scanf("%d",&n);

  printf("%.4f\n", sum_sequence(n));
  return 0;
}

double sum_sequence(int n){
  double sum;
  while (n > 0) {
    sum += (double) supersum(n)/factorial(n);
    n--;
  }

  return sum;
}

int factorial(int x) {
  if (x == 0){
    return 1;//If input is zero factorial =1
  }
  else{
    return (x * factorial(x-1));
  }
}

int supersum(int a){
  if (a == 0){
    return 0;
  }
  return (a + supersum(a-1));
}
