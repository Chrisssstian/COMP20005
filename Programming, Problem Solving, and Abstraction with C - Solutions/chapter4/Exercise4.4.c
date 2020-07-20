/* Calculates and creates a table of ASCII characters from 32 to 126
 By Christian Drozdowicz 15/03/2019
 */
#include <stdio.h>

int
main(int argc, char const *argv[]) {

  /* variables used for iterations */
  int i, j;

  /* prints header row and top of table */
  printf("\n     +0 +1 +2 +3 +4 +5 +6 +7\n");
  printf("    +-------------------------\n");

  /* first for loop to iterate through rows */
  for (i = 32; i<128; i += 8){
    /* prints current value per row as well as left hand side of table*/
    printf("%3d |",i);

    /* second for loop to iterate through columns */
    for (j = 0; j<8; j++){
      /* prints the character that corresponds to the current cell in table */
      printf(" %c ",i+j);
    }
  /* breaks up output into new lines per each year */
    printf("\n");
  }

  /* creates break at end of program to keep it nice on the eyes*/
  printf("\n");

  return 0;
}
