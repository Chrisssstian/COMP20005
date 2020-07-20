/* Takes studentID and their score from txt file and orders it by studentID
By Christian Drozdowicz 6/4/2019 */

#include <stdio.h>
#include <stdlib.h>

/* prototypes all functions */
void para_insert_sort(int* pri , int* sec, int n);
void int_sort(int A[], int n);

int
main(int argc, char **argv) {
  int n=0, stdnum[1000], stdmrk[1000];//initialise two variables and set to zero

  /* take user txt file */
  printf("Enter file with StudentID and Grades\n");
  while (scanf("%d %d", &stdnum[n], &stdmrk[n]) != EOF) {
    n++;
  }
  /* calls para_insert_sort */
  para_insert_sort(stdnum, stdmrk, n);

  /* prints ouput after being ordered */
  int i;
  for (i=0;i<n;i++) {
    printf("%5d %3d\n", stdnum[i], stdmrk[i]);
  }

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


void
para_insert_sort(int pri[], int sec[], int n) {
int i, j;
/* swap A[i] right into correct position */
  for (i=0;i<n;i++) {
    for(j=i-1;j>=0 && pri[j+1]>pri[j];j--) {
      int_swap(&pri[j], &pri[j+1]);
      int_swap(&sec[j], &sec[j+1]);

    }
  }
}
