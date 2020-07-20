/* Takes an input of change and converts to valid cents
(only using coins: 50, 20, 10, 1) and prints out how many of each
By Christian Drozdowicz 30/03/2019 */

#include <stdio.h>
#include <stdlib.h>

/* Protoype functions */
int try_one_coin(int *cents, int coin);
void print_change(int cents);
int round_to_five(int cents);

#define COIN_50 50
#define COIN_20 20
#define COIN_10 10
#define COIN_5 5
#define COIN_2 1
#define MAX_CENTS 1000



int
main(int argc, char **argv) {
  int dollars, cents, total, final, rounded;
  printf("Please enter amount to ten dollars (form $xx.yy): $");

  /* filters scanf is true */
  if (scanf("%d.%d",&dollars, &cents) != 2){
    printf("Invalid input\n");
    exit(EXIT_FAILURE);
  }
  /* filters negative values */
  if (dollars < 0 || cents < 0) {
    printf("Invalid input must be positive values\n");
    exit(EXIT_FAILURE);
  }

  total = (dollars * 100) + cents;
  /* filters if input is greater than $10 */
  if (total > MAX_CENTS){
    printf("Invalid input must be below $10\n");
    exit(EXIT_FAILURE);
  }

  /* calls round_to_five function to round the cents into viable denominations
  to be given back in valid coins */
  rounded = round_to_five(cents);
  final = (dollars * 100) + rounded; // add the rounded coins
  printf("\nYour rounded change in valid coins is: $%d.%d\n", dollars, rounded);
  print_change(total); //Call print_change using the rounded final total
  printf("\n");
  return 0;
}

/* try_one_coin definition, uses while loop to check the input cents against
the coin we are checking each time and once checked minusing that value each
time and return the count */

/* *cents is a pointed so doesnt forget for next test of different coin
but same cents for each input */
int
try_one_coin(int *cents, int coin) {
  int i = 0;
  while (*cents >= coin) {
    i++;
    *cents -= coin;
  }
  return i;
}

/* print_change defintion that call on try_one_coin to test each coin with
amount and prints out the final count for each coin */
void
print_change(int cents) {
  int fif, twn, ten, fiv;
  fif = try_one_coin(&cents, COIN_50);
  twn = try_one_coin(&cents, COIN_20);
  ten = try_one_coin(&cents, COIN_10);
  fiv = try_one_coin(&cents, COIN_5);

  printf("%d : %d coins\n%d : %d coins\n%d : %d coins\n%d : %d coins\n",
  COIN_50, fif, COIN_20, twn, COIN_10, ten, COIN_5, fiv);
}


/* round_to_five function that evaluates the last digit of the input to either
round up or down to the nearest five or not change if value is 0 or 5 */
int
round_to_five(int cents) {
  int last_digit;
  last_digit = cents % 10;

/* if and else if statements very messy right now but it works well */
/* if last digit is one or two minus to round down */
  if (last_digit == 1 || last_digit == 2){
      cents = cents - last_digit;
    }
/* if last digit is 3 or 4 round up to 5 */
  else if (last_digit == 3 || last_digit == 4){
      if (last_digit == 3) {
        cents = cents + 2;
      }
      if (last_digit == 4) {
        cents = cents + 1;
      }
    }
/* if last digit is 6 or 7 round down to 5 */
  else if (last_digit == 6 || last_digit == 7){
    if (last_digit == 6) {
      cents = cents - 1;
    }
    if (last_digit == 7) {
      cents = cents - 2;
    }
  }
/* if last digit is 8 or 9 round up to 10*/
  else if (last_digit == 8 || last_digit == 9){
    if (last_digit == 8) {
      cents = cents + 2;
    }
    if (last_digit == 9) {
      cents = cents + 1;
    }
  }

  return cents;
}

/*
>HAVE NOT FIGURED OUT HOW TO DEAL WITH INPUTS LIKE $5.5, $8.7
>HAVE NOT FIGURED OUT HOW TO DEAL WITH $0.98 WHICH ROUNDS TO $0.100
>HAVE NOT FIGURED OUT HOW TO IMPLEMENT $1 AND $2 COINS
 */
