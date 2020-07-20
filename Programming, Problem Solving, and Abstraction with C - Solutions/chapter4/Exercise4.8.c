/* Uses backbone code from page 54. Program goes through the 3n+1 sequence
 between 1 and the user input and finds the length of longest cycles and
 what seed between 1 and user input was used for the longest cycle
 By Christian Drozdowicz 16/03/2019*/

#include <stdio.h>

#define PERLINE 8

int
main(int argc, char const *argv[]) {
  int x, n=0, max, nmax, seedmax, cycles, cyclesmax;


  printf("Enter starting value for n: ");
  scanf("%d",&nmax);



  cyclesmax = 0;

  for(x = 0; x <= nmax; x++){
    max = n;
    cycles = 0;
    n = x;
    printf("----%3d--------------------------------------------------\n", x);
    while (n>1) {
      printf("%5d ", n);

      if (n%2==0){
        n = n/2;
      }
      else {
        n = 3*n + 1;
      }

      if (n>max){
        max = n;
      }

      cycles++;
      if (cycles%PERLINE == 0){
        printf("\n");
      }
    }

    if (cycles > cyclesmax){
      cyclesmax = cycles;
      seedmax = x;
    }

    printf("\n%d cycles consumed, maximum was %d\n\n", cycles, max);
  }









printf("\nMax cycle: %d, seed: %d\n", cyclesmax, seedmax);
return 0;
}
