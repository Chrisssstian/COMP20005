/* Program that ask user first for a base number and a power number in the form
a^b and returns the answer (WATCH OUT FOR INTEGER OVERFLOW)
By Christian Drozdowicz 21/03/2019 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Prototype function int_pow */
int int_pow(int a, int b);
/* Prototype recursive function */
int int_pow_rec(int a, int b);

int
main(int argc, char *argv[]) {

  int base, power, answer1, answer2;

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
    answer1 = int_pow(base, power);//Calls the function int_pow
    answer2 = int_pow_rec(base, power);
    printf("iteration: %d ^ %d = %d\nrecursion: %d ^ %d = %d\n", base, power, answer1, base, power, answer2); //prints in the form a ^ b = x
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
/* raises first input to second but uses recursion this time */
int int_pow_rec(int bas, int pow) {
  if(pow == 0){
    return 1;
  }
  return bas * int_pow_rec(bas, pow-1);
}
