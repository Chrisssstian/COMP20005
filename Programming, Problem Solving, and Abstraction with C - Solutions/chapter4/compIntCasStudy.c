/* Calculates growth of savings account from 1 to 7 years when input principal
 and monthly deposit (initial plus monthly must be same $ amount)
 By Christian Drozdowicz 13/03/2019
 */
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char const *argv[]) {

  /* used variables initialize*/
  double amt, new_amt, final_amt, percent, interest;;
  int limit;

  /* variables used for iterations */
  int i, k;
  double j;

  /* requests user enter desired equal payment savings */
  printf("Please enter Principal and monthly deposit: $" );
  scanf("%lf",&amt);
  printf("\nMonthly savings of $%.2lf, with monthly compound interest:\n\n",amt);
  /* initialize variable values */
  new_amt = final_amt = amt;

  /* first for loop to iterate through years */
  for (i = 1; i<8; i++){
    printf("After %d years |",i);

    /* second for loop to iterate through different interest rates */
    for (j = 2; j<8; j++){
      percent = j / 100.00;

      /* if | else if statements to change the upper guard of the third for loop based on what year it is */
      /*if (i == 1 ){
        limit = 11;
      }
      else if (i == 2 ){
        limit = 23;
      }
      else if (i == 3 ){
        limit = 35;
      }
      else if (i == 4 ){
        limit = 47;
      }
      else if (i == 5 ){
        limit = 59;
      }
      else if (i == 6 ){
        limit = 71;
      }
      else if (i == 7 ){
        limit = 83;
      }*/
      /* realised I didn't need all the if statements and just made limit an equation so can be scaled */
      limit = (i * 12)-1;
      /* third for loop to iterate through each month's compound interest as well as when the user adds in their equal payment each month*/
      for (k = 0; k < limit; k++){
        interest = final_amt * percent / 12;
        new_amt = final_amt + interest;
        final_amt = new_amt + amt;
      }
      /* prints final result for each interest rate make 10 spaces so table looks better */
      printf(" %10.2f", final_amt);
      /* resets final amount to zero ready for next interest rate */
      final_amt = amt;




    }
  /* breaks up output into new lines per each year */
    printf("\n");
  }
  printf("\n");

  return 0;
}
