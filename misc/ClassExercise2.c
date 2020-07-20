/* comp20005 - Class Exercise: 2, March 2019
By Christian Drozdowicz 26/03/2019*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
  double next, max, min, sum;
  int n;

	printf("Enter values, control-D to end:\n");
	if (scanf("%lf", &next)!=1) {
		printf("\nNo data entered\n");
		exit(EXIT_FAILURE);
	}



	n = 1;
	max = min = sum = next;

	/* read further values and track the maximum and the minimum*/
	while (scanf("%lf", &next)==1) {

    /* checks for legal scores entered and returns when a value is illegal */
    if (next < 0 || next > 10) {
      printf("\nScores can only be between 0 and 10\n");
      return 0;
    }

		if (next>max) {
			max = next;
		}
    else if (next<min) {
      min = next;
    }
    /* track the amount of values read and the sum of all values read */
    sum += next;
		n += 1;
	}

  /* if less than 3 values read invalid */
  if (n < 3){
    printf("\n Must enter at least 3 scores\n");
    exit(EXIT_FAILURE);
  }


	printf("%d values read, maximum is %.2lf, minimum is %.2lf, "
    "the sum is %.2lf\n", n, max, min, sum);

  /* final score is average minus lowest and highest score */
  printf("\nfinal score is %.2lf\n", (sum-min-max)/(n-2));
  return 0;
}
