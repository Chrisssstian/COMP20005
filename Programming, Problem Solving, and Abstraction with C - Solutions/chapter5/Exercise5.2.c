/* Function that builds on top of Exercise5.1, now take 4 inputs and return
the largest of the 4 Numbers
By Christian Drozdowicz 21/03/2019 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Prototyping both max_2ints and max_4_ints*/
int max_2_ints(int a, int b);
int max_4_ints(int a, int b, int c, int d);

int
main(int argc, char *argv[]) {

  int first, second, third, fourth, larger;

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

  printf("Please enter the third number: ");
  if (scanf("%d", &third) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  printf("Please enter the fourth number: ");
  if (scanf("%d", &fourth) != 1) {
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

/* --like the if here */
  if (max_4_ints(first, second, third, fourth) == 0) {//Check if func returns false
    printf("Numbers are equal\n");
  }
  else {
    larger = max_4_ints(first, second, third, fourth);//Call max_4_ints func
    printf("Bigger number is: %d\n", larger);
  }


  return 0;
}


/* Use this from Exercise5.1*/
int max_2_ints(int a, int b){
  /* returns 0 (false) if all inputs are equal  for the equal check above in main */
  if (a == b) {
    return 0;
  }
  if (a > b){
    return a;
  }
  else {
    return b;
  }
}


/*max_4_ints uses recursion and calls on max_2_ints to do this */
int max_4_ints(int a, int b, int c, int d){
  return max_2_ints(max_2_ints(a,b), max_2_ints(c,d)); //Calls max_2_ints 3 times in the form f(f(x,y), f(x,y)) 
}
