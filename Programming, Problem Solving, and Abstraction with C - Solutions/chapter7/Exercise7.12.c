/* takes input sentence and returns if palindrome or Not
By Christian Drozdowicz 7/4/2019 */

#include <stdio.h>
#include <string.h> //need this for strcmp below

int is_palindrome(char* str);

int
main(int argc, char **argv) {
  int i = 0;
  char input[1000];

  printf("Type a sentence (max 1000 characters): ");
  /* Use ^D to end */
  while (scanf("%c", &input[i]) == 1) {
    i++;
  }
  /* adds in null character where i will always not be used as it
  will be the count that ended the while loop; not sure if needed though */
  input[i] = '\0';
  printf("\n");


  if (is_palindrome(input)) {
    printf("Indeed my good sir it is\n");
  }
  else {
    printf("This ain't it chief\n");
  }

  return 0;
}


int
is_palindrome(char* str) {
  int i, len = 0;
  char cleaned[1000], inverted[1000];

  /* to clean the string of spaces and newlines etc and create new array */
  for(i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ' && str[i] != '\n') {
      cleaned[len] = str[i];
      len++;
    }
  }

  cleaned[len] = '\0'; //again adds in null character not sure if needed though

  /* inverts the array */
  for (i = 0; i<len; i++) {
    inverted[i] = cleaned[len-i-1];
  }
  inverted[len] = '\0';//again adds in null character not sure if needed though

  printf("String: %s\nCleaned: %s\nInverted: %s\n", str, cleaned, inverted);

  /* uses strcmp to compare the inverted and the cleaned array */
  if (strcmp(inverted, cleaned) == 0) {
    return 1;
  }
  return 0;
}
