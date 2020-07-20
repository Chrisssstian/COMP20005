/* Takes user defined length of integers into an array then prints out the
most frequent value in array
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>



void frequency(int A[], int n);

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
  frequency(A, n);

  return 0;
}



/* frequency definition */
void
frequency(int A[], int n) {
  int i, j, x, count, freq[100];
  /* nested for loop to find duplicates and count into a new array */
  for (i=0;i<n;i++) {
    freq[i] = 1;
    count = 1;
    for(j=i+1;j<n;j++) {
      if (A[i] == A[j]) {
        count++;
        freq[j] = 0;
      }
    }
    if(freq[i] != 0) {
      freq[i] = count;
    }
  }

  /* finds the most frequent */
  int most_freq, maxcount = 0;
  for(x=0;x<n;x++) {
    if(freq[x] != 0 && freq[x]>maxcount) {
      maxcount = freq[x];
      most_freq = A[x];
    }
  }
  printf("%d occurs %d times\n", most_freq, maxcount);
}
