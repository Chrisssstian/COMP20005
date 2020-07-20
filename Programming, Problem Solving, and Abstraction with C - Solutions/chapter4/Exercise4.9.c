/* Finds the next prime after number entered even if numbered entered is a
prime itself
By Christian Drozdowicz 16/03/2019 */

#include <stdio.h>

int
main(int argc, char const *argv[]) {

  int n, isprime, divisor, x;
  printf("Enter a number n: ");
  scanf("%d", &n);

/* initialize isprime check to false to start while loop */
  isprime = 0;
/* x starts at the next number after input number */
  x = n + 1;

/* while loop iterates as long as isprime is false */
  while (isprime == 0){

    /* switch isprime to true in order to deal with 1,2 etc. */
    isprime = 1;
    /* start for loop looking for next prime */
    for (divisor = 2; divisor * divisor <= x; divisor++){
      /* if x mod divisor has no remainder then x is not a prime and switch
      isprime back to false and increment x */
      if (x % divisor == 0){
        isprime = 0;
        x++;
      }
    }
  }
  printf("The next prime is: %d\n", x);
  return 0;
}
