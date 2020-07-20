#include <stdio.h>

int
main(int argc, char const *argv[]) {
  double p, new_p, final_p, interest;
  printf("Please enter Principal and monthly deposit: $" );
  scanf("%lf",&p);

  double percent = 0.02;
  new_p = final_p = p;
  int k;

  for (k = 0; k < 11; k++){
    interest = final_p * percent / 12;

    new_p = final_p + interest;
    printf("%f\n",new_p);


    final_p = new_p + p;
  }
  printf(" %.2f\n", final_p);


  return 0;
}
