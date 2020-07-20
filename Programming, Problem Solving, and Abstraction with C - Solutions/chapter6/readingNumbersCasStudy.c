/* Program to take user define lower to upper bound then check user input is
within these boundaries
By Christian Drozdowicz 26/03/2019 */

#include <stdio.h>
#include <stdlib.h>

/* Define constants */
#define READ_OK 0
#define READ_ERROR 1

/* prototype read_num function */
int read_num(int lo, int hi, int *num);

int
main(int argc, char const *argv[]) {

  int lower, upper, valu;
  printf("Please enter a range in format low-high: ");
  scanf("%d-%d", &lower, &upper);

  /* implements check to make sure format is correctly input*/
  if (lower > upper) {
    printf("Lower Bound must be less than Upper Bound\n");
    exit(EXIT_FAILURE);
  }

  /* implements check in case we can't reach a READ_OK */
  if (read_num(lower, upper, &valu) != READ_OK){ //calls read_num
    printf("Read error, prgramo aborto\n");
    exit(EXIT_FAILURE);
  }

  /* prints out user input when is found inside designated bounds */
  printf("%d is within the designated bounds\n", valu);

  return 0;
}

/* read_num defintion */
int
read_num(int lo, int hi, int *num) {
  int next;
  printf("Please enter a number between %d and %d inclusive: ", lo, hi);

  while(scanf("%d", &next) == 1) {
    if (lo <= next && next <= hi) {
      *num = next;
      return READ_OK;
    }
    printf("%d is not within the bounds please try again: ", next);
  }
  /* no valid numbers found and scanf has failed */
  return READ_ERROR;
}
