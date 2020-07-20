/* Program calculates n Choose k Function
By Christian Drozdowicz 21/03/2019 */

#include <stdio.h>
#include <stdlib.h>

/* Prototype n_choose_k */
int n_choose_k(int n, int k);
/* prototype factorial function*/
int factorial(int x);

int
main(int argc, char const *argv[]) {

  int n, k, result;

  printf("Please enter the number of distinct items: ");
  if (scanf("%d", &n) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

/* If want to use this scanf if statement must make main an if statement-- */
  printf("Please enter the number of ways you want to choose the distinct item: ");
  if (scanf("%d", &k) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  /* Check no negative inputs otherwise exit program */
  else if (n < 0 || k < 0) {
    printf("Invalid input can't have any negative inputs\n");
    exit(EXIT_FAILURE);
  }



  else {
    result = n_choose_k(n, k);//Call Function n_choose_k
    printf("%d choose %d = %d\n", n, k, result);
  }

  return 0;
}

/* function n_choose_k takes two inputs and returns the form n!/((n-k)!*k!)
using factorial() function*/
int n_choose_k(int n, int k) {
  return (factorial(n) / (factorial(n-k) * factorial(k))); //calls factorial()
}

/* factorial function defintion uses recursion to find factorial of single
input */
int factorial(int x) {
  if (x == 0){
    return 1;//If input is zero factorial =1
  }
  else{
    return (x * factorial(x-1));
  }
}
