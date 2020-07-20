/* Asks users to input some text and calculates the number of chars, lines, words
By Christian Drozdowicz 16/03/2019 */
#include <stdio.h>

int
main(int argc, char const *argv[]) {
  int txt, ch_count, ln_count, wd_count, inaword;
  ch_count = ln_count = wd_count = inaword = 0;
/* asks for text input, user has to let program know they have finished
inputting by doing control+d to end the text */
  printf("Enter Text:\n");

/* continue while loop until End Of File (when text ends) */
  while ((txt = getchar()) != EOF ){

    /* check if character is between a-z or A-z if true let flaf inaword =1
    designate a word has ended */
    if ((txt >= 'A' && txt <= 'Z') || (txt >= 'a' && txt <= 'z')){
      inaword = 1;
    }

    /* if inaword is true set to false and count as word */
    else if (inaword){
      inaword = 0;
      wd_count++;
    }

    /* counts each newline (\n) to count lines */
    if (txt == '\n'){
      ln_count++;
    }

    /* everything that getchar goes through is a char so we set count including \n */
    ch_count++;
  }



  printf("Lines: %d\nWords: %d\nCharacters: %d\n",ln_count, wd_count, ch_count);
  return 0;
}

/* word count doesn't work if users double spaces or double lines as this is
very basic way to count words and does not account for these errors */
