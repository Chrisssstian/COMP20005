#include <stdio.h>

int f(int, int, int, int);
int max_2_ints(int, int);

int main(int argc, char *argv[]){
  int num1, num2, num3, num4, result;
  int n;
  printf("Enter sets of four values, EOF to end\n");
  while (scanf("%d %d %d %d", &num1, &num2, &num3, &num4) == 4) {
    result = f(num1, num2, num3, num4);
    printf("f on %d and %d and %d and %d is %d\n", num1, num2, num3, num4, result);
    n=n+1;
  }
  printf("%d sets processed\n",n);
}



int max_2_ints(int a, int b){
  /* returns 0 (false) if all inputs are equal  for the equal check above in main */
  if (a == b) {
    return 0;
  }
  if (a > b){
    return a;
  }
  else {
    return b;
  }
}


/*max_4_ints uses recursion and calls on max_2_ints to do this */
int f(int a, int b, int c, int d){
  return max_2_ints(max_2_ints(a,b), max_2_ints(c,d)); //Calls max_2_ints 3 times in the form f(f(x,y), f(x,y))
}
