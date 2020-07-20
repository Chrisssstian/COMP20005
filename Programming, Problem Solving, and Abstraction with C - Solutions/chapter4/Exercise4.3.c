/* Program that takes an input and stops when max spores reaches the input
By Christian Drozdowicz 15/03/2019 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char const *argv[]) {

  int a = 0, b = 1, next, input;
  printf("Please enter how max spores: ");

  if (scanf("%d", &input) != 1) {
    printf("No value was entered\n");
    exit(EXIT_FAILURE);
  }



  /* always first two output in Fibonacci */
  printf("%d\n%d\n",a,b);

  next = a + b;
  while (next <= input){
    printf("%d\n",next);
    a = b;
    b = next;
    next = a + b;
  }


  return 0;
}
