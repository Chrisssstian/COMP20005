/* Program to take two input integers and return the largest of the two inputs
By Christian Drozdowicz 21/03/2019 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* Prototype function max_2_ints */
int max_2_ints(int a, int b);

int
main(int argc, char *argv[]) {

  int first, second, larger;

  printf("Please enter the first number: ");
  if (scanf("%d", &first) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

/* If want to use this scanf if statement must make main an if statement-- */
  printf("Please enter the second number: ");
  if (scanf("%d", &second) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

/* --like the if here */
  if (first == second) {//Check numbers are equal
    printf("Numbers are equal\n");
  }
  else {
    larger = max_2_ints(first, second);//Call function
    printf("Bigger number is: %d\n", larger);//Print result of function
  }





  return 0;
}

/* Defining the function to check which input is larger */
int max_2_ints(int a, int b){

  if (a > b){
    return a;
  }
  else {
    return b;
  }
}
