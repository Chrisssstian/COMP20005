/* Calculates integer quotient and remainder
By Christian Drozdowicz 28/03/2019 */

#include <stdio.h>
#include <stdlib.h>

/* prototype int_divide function */
void int_divide(int numerator, int denominator, int *quotient, int *remainder);

int
main (int argc, char **argv) {
  int num, den, quo, rem;

  printf("Please enter a Numerator/Denominator: ");

  /* while loop only executes as long as scanf has taken two valid arguments */
  while((scanf("%d/%d", &num, &den)) == 2) {
    int_divide(num, den, &quo, &rem);//Calls int_divide function
    printf("Numerator: %d\nDenominator: %d\nQuotient: %d\nRemainder: %d\n",
      num, den, quo, rem);
      break; //Ends loop when done


  }

  printf("\n");


  return 0;
}

/* int_divide definition */
void int_divide(int numerator, int denominator, int *quotient, int *remainder){
  *quotient = numerator / denominator;
  *remainder = numerator - *quotient * denominator;
}

/* REMAINDER MATH BECAUSE I HAD NO IDEA
1. Begin with writing down your problem. For example, you want to divide 346 by 7.
2. Decide on which of the numbers is the dividend, and which is the divisor. The dividend is the number that the operation is performed on - in this case, 346. The divisor is the number that actually "does the work" - in this case, 7.
3. Perform the division - you can use any calculator you want. You will get a result that most probably is not an integer - in this example, 49.4285714.
4. Round this number down. In our example, you will get 49.
5. Multiply the number you obtained in the previous step by the divisor. In our case, 49 * 7 = 343.
6. Subtract the number from the previous step from your dividend to get the remainder. 346 - 343 = 3.
7. You can always use our calculator with remainders instead and save yourself some time :)
*/
