#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  int input, prev;
  scanf("%d",&input);

  prev = input;

  while(scanf("%d",&input) == 1) {
    if (prev <= input) {
      prev = input;
    }
    else {
      printf("*** value %d is smaller than %d\n", input, prev);
    }
  }







  return 0;
}
