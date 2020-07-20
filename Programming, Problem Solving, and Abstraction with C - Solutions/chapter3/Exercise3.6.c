#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char const *argv[]) {
  int x;
  printf("Enter amount in cents: \n" );

  /* remove obvious invalid */
  if (scanf("%d",&x) != 1){
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }

  printf("The coins required to make %d cents are: ",x);
  while (x > 0)
  {
    if (x >= 50) {
      printf("50");
      x = x - 50;
    }
    else if (x >= 20) {
      printf("20");
      x = x - 20;
    }
    else if (x >= 10) {
      printf("10");
      x = x - 10;
    }
    else if (x >= 5) {
      printf("5");
      x = x - 5;
    }
    else if (x >= 2) {
      printf("2");
      x = x - 2;
    }
    else if (x >= 1) {
      printf("1");
      x = x - 1;
    }

    if (x>0){
      printf(", ");
    }
  }

  printf("\n");
  return 0;
}
