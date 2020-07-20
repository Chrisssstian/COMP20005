/* Program to check what case is input character, if it is upper convert to
lower lowercase
By Christian Drozdowicz 23/03/2019*/

#include <stdio.h>
#include <stdlib.h>


int my_isupper(char c);
char my_toLower(char c);

main(int argc, char const *argv[]) {

  char input, lower;
  printf("Please input any alphabetical character\n");
  scanf("%c",&input);

  if (my_isupper(input) == 1){
    lower = my_toLower(input);

    printf("Is a capital letter, here is the lowercase version: %c\n",lower);
  }
  else {
    printf("Is a lowercase letter already\n");
  }


return 0;
}

/* checks if input is upper or lower case and returns true if upper */
int my_isupper(char c) {
  if (c >= 'A' && c <= 'Z'){
    return 1;
  }
  return 0;
}

/* converts input to ascii and adds 32 to get the lowercase equivalent
of letter and return to main string */
char my_toLower(char c) {
  int ascii = c;
  char lowercase;
  lowercase = ascii + 32;
  return lowercase;
}
