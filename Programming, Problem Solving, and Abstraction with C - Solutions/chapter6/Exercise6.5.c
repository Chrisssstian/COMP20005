/* Program that takes two integers and returns the smaller and larger of the
two using pointers so it doesn't matter what order we return the values
in, a will always be the smaller and b always the larger
By Christian Drozdowicz 26/03/2019 */

#include <stdio.h>

void int_sort2(int *p1, int *p2);

int
main (int argc, char **argv) {
  int a, b;

  printf("Please enter two numbers: ");
  scanf("%d %d", &a, &b);

  int_sort2(&a, &b);

  printf("%d is smaller, %d is larger\n", a, b);
}

/* exchange the variables of the two variables indicated by their arguments and
swap a to be smallest and b to be largest if a > b at beginning*/
void int_sort2(int *p1, int *p2) {
  int tmp;
  if (*p1 > *p2) {
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
  }
}
