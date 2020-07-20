/* Takes input sequence on integers and displays basic graph of each value
 By Christian Drozdowicz 15/03/2019
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char const *argv[]) {
  int input = 0;
  printf("Enter numbers: ");

  /* whilse scanf is true loop*/
  int i;
  while (scanf(" %d",&input) != 0){

    printf("%4d |", input);

    /* for each row print * for length of input */
    for (i = 0; i < input; i++){
      printf("*");
    }
    /* new row */
    printf("\n");

  }
  printf("Graph Complete.\n");
  return 0;
}

/* not finished as not sure why program doesn't terminate itself when done */
