/* Program that ask user first for a base number and a power number in the form
a^b and returns the answer (WATCH OUT FOR INTEGER OVERFLOW)
By Christian Drozdowicz 21/03/2019 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Prototype function int_pow */
int int_pow(int a, int b);

int
main(int argc, char *argv[]) {

  int base, power, answer;

  printf("Please enter the base number: ");
  if (scanf("%d", &base) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

/* If want to use this scanf if statement must make main an if statement-- */
  printf("Please enter the power want to raise to: ");
  if (scanf("%d", &power) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }
/* else to get the scanf check to work*/
  else {
    answer = int_pow(base, power);//Calls the function int_pow
    printf("%d ^ %d = %d\n", base, power, answer); //prints in the form a ^ b = x
  }


  return 0;
}

/* int_pow defintion takes two inputs first base second power */
int int_pow(int bas, int pow){
/* function count variables */
  int i, answer;
  answer = 1;//initialise answer at 1
  /* for loop to run through calculation */
  for (i = pow; i > 0; i--){
    answer *= bas;
  }
  /* returns the final answer to be put back into main func */
  return answer;
}
