/* Takes user defined length of integers into an array then calls int_sort to
check if next element is greater than previous and uses int_sort to swap if
true and prints the elements in decreasing order
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>


void int_swap (int *x, int *y);
void int_sort(int A[], int n);

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



  /* calls the int_sort function to sort */
  int_sort(A, n);

  return 0;
}

/* page 94 figure 6.7 int_swap defintion*/
void
int_swap(int *x, int *y) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

/* int_sort definition */
void
int_sort(int A[], int n) {
  int i, j, x;
  /* swap A[i] right into correct position */
  for (i=0;i<n;i++) {
    for(j=i-1;j>=0 && A[j+1]>A[j];j--) {
      int_swap(&A[j], &A[j+1]);
    }
  }
  /* for loop to show after elements after sorting */
  for(x=0;x<n;x++) {
    if(x == 0) {
      printf("after:  %4d ", A[x]);
    }
    else {
      printf("%4d ", A[x]);
    }
  }
  printf("\n");
}
