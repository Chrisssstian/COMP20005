/* Same as 7.3 but uses different sorting algorithm
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>


void int_swap (int *x, int *y);
void selection_sort(int A[], int n);
void rec_selection_sort(int A[], int n);

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



  /* calls the sorting functions */
  //selection_sort(A, n); FUNCTION DOESN'T WORK
  rec_selection_sort(A, n);

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

/* THIS DOESN'T WORK
void
selection_sort(int A[], int n) {
  int max, maxloc, i, x;
  while (n > 0) {
    max = A[0];
    maxloc = 0;

    for (i=1;i<n;i++) {
      if (A[i] > max) {
        max = A[i];
        maxloc = i;
      }
    }
    int_swap(&A[n-1], &A[maxloc]);
    n--;
  }

  for(x=0;x<n;x++) {
    if(x == 0) {
      printf("after iteration:  %4d ", A[x]);
    }
    else {
      printf("%4d ", A[x]);
    }
  }
  printf("\n");
}
*/




void
rec_selection_sort(int A[], int n) {
  int max, maxloc, i, x;
  if (n >= 0) {
    max = A[n-1];
    maxloc = n-1;

    for (i=n-1;i>=0;i--) {
      if (A[i] > max) {
        max = A[i];
        maxloc = i;
      }
    }
    int_swap(&A[maxloc], &A[n-1]);
    rec_selection_sort(A, n-1);
  }



  for(x=0;x<n;x++) {
    if(x == 0) {
      printf("after recursion:  %4d ", A[x]);
    }
    else {
      printf("%4d ", A[x]);
    }
  }
  printf("\n");
}
