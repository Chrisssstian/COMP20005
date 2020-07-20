#include <stdio.h>
#include <stdlib.h>


int is_prime(int n);
double prime_density(int first, int last);

int
main(int argc, char **argv) {
  int first, last;

  printf("Enter two integers: ");
  scanf("%d %d", &first, &last);

  printf("%lf is the prime density\n", prime_density(first, last));

  return 0;
}

int is_prime(int n) {
  int i, flag = 0;
  for(i = 2; i <= n/2; ++i){
        if(n%i == 0){
            flag = 1;
            break;
        }
    }

    if (n == 1) {
      printf("1 is neither a prime nor a composite number.");
      exit (EXIT_FAILURE);
    }
    else {
        if (flag == 0)
          return 1;
        else
          return 0;
    }
}

double prime_density(int first, int last) {
  int i;
  double count = 0.0, equ;

  i = first;

  if (last < first) {
    return 0.0;
  }

  else {
    while (i <= last){
      if (is_prime(i) != 0){
        count++;
      }
      i++;
    }
    equ = count / i;
    return equ;
  }
}
