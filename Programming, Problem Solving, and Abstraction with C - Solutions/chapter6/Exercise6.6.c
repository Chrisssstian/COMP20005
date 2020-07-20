/* Program that takes three integers and returns the smaller, middle and larger
of the two using pointers so it doesn't matter what order we return the values
in, a will always be the smaller and b always the middle and c always largest
By Christian Drozdowicz 26/03/2019 */
#include <stdio.h>

void int_sort2(int *p1, int *p2);
void int_sort3(int *p1, int *p2, int *p3);

int
main (int argc, char **argv) {
  int a, b, c;

  printf("Please enter three numbers: ");
  scanf("%d %d %d", &a, &b, &c);

  int_sort3(&a, &b, &c);

  printf("\n%d is smaller, %d is in the middle, %d is larger\n\n", a, b, c);
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
/* sort three variables using camparison between two cases each time into the
int_sort2 function */
void int_sort3(int *p1, int *p2, int *p3) {
  int_sort2(p1, p2);
  int_sort2(p2, p3);
  /* need this last one for case of input a=3,b=2,c=1 to work*/
  int_sort2(p1, p2);

}
