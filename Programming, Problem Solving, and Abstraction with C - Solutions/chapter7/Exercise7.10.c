/* Takes user defined length of integers into an array then prints out the
number of inversions (inversions description on page 127)
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>


int calc_inv(int A[], int n);


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
    /* increase x */
    x++;
  }
  /* print how many values were input */
  printf("%d values read into the array\n", x);

  /* for loop show before elements */
  for(x=0;x<n;x++) {
    if(x == 0) {//need this for first element to add in 'before'
      printf("before: %4d ", A[x]);
    }
    else {
      printf("%4d ", A[x]);
    }
  }
  printf("\n");



  /* calls the frequency function to sort */

  printf("%d inversions altogether\n", calc_inv(A, n));
  return 0;


}

/* pretty obvious with inversion definition */
int
calc_inv(int A[], int n) {
    int i, inv=0;
    for(i=0; i<n-1; i++) {
        if(i > 0 && A[i] < A[i-1]) {
            printf("%d < %d\n",A[i], A[i-1]);
            /* check behind */
            inv++;
        }
        if(i < n-1 && A[i] > A[i+1]) {
            printf("%d > %d\n",A[i], A[i+1]);
            /* check infront */
            inv++;
        }
    }

    return inv;
}
