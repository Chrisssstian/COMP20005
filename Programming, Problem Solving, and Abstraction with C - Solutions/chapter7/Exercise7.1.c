/* Takes user defined length of integers into an array then checks if array
only contains zeros or Not
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>

/* prototypes all_zero function */
int all_zero(int A[], int n);

int
main(int argc, char **argv) {
  int n=0, x=0; //initialise two variables and set to zero

  /* take a user defined input length for array */
  printf("Enter the amount of values you wish to input: ");
  scanf("%d", &n);

  /* Initialise array A to have size n from scanf */
  int A[n];
  printf("Enter %d integers: ", n);

  /* loop to fill array with user values */
  while (x<n){

    /* a better check for illegal characters here rather than in while
    loop, this way it will end program instead of just cutting the array short
    when an illegal character was found*/
    if (scanf("%d", &A[x]) == 0) {
      printf("A[%d] is an invalid input\n",x);
      exit(EXIT_FAILURE);
    }

    /* just prints the array with its index back to the user */
    else {
      printf("A[%d] = %d\n", x, A[x]);
      x++;
    }
  }



  /* calls the all_zero function to check */
  if (all_zero(A, n)) {
    printf("All zero\n");
  } else {
    printf("Not all zero\n");
  }

  return 0;
}

/* all_zero function definition checks from last entry in array to first */
int
all_zero(int A[], int n) {
  while (n-1 >= 0) { //Beacuse array starts at 0 not 1 so 0 to n-1 is bounds
    if (A[n-1] != 0) {//returns 0 once a single non-zero is found in array
      printf("\nA[%d] = %d is not zero \n", n-1, A[n-1]);
      return 0;
    }
    n--;
  }
  return 1;
}
