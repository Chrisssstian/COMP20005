#include <stdio.h>
#include <stdlib.h>

int isDivisible(int n, int div);
int sumFactors(int stop, int num);
int isAmicable(int x, int y);
void error(int code);

int
main(int argc, char **argv) {
    int a, b, limit;

    printf("Enter the limiting integer: ");
    if (scanf("%d",&limit) != 1) {
        error(0);
    }


    if (limit <= 0) {
        error(2);
    }

    a = 1;
    b = 1;

    while (a < limit){
      if (isAmicable(a, b)){
        printf("%d and %d are amicable\n", a, b);
        a++;
        b = 1;
      }
      else if (b < a-1){
        b++;
      }
      else {
        a++;
        b = 1;
      }
    }


    return 0;
}



int
isAmicable(int a, int b){
  if (sumFactors(a-1, a) == b && sumFactors(b-1, b) == a) {
    return 1;
  }
  return 0;
}


int
sumFactors(int stop, int num) {
    /*
     * Calculates sum of factors until 'stop'
     * */
    if (stop == 0) {
        return 0;
    }
    return (isDivisible(num, stop))*stop + sumFactors(stop-1, num);
}

int
isDivisible(int n, int div) {
    if (n == (n / div) * div) {
        return 1;
    }
    return 0;
}

void
error(int code) {
    if (code == 0) {
        printf("Illegal input.");
    } else if(code == 1) {
        printf("Unknown.");
    } else if(code == 2) {
        printf("limit must be positive.");
    }

    printf("\n");
    exit(EXIT_FAILURE);
}
