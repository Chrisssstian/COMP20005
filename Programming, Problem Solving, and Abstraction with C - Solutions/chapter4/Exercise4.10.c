#include <stdio.h>

int
main(int argc, char const *argv[]) {
  int prev_ch, ch, incomment = 0, newlinelast = 1;

  while ((ch = getchar()) != EOF){
    prev_ch = ch;
    if (ch == '/' && newlinelast) {
      incomment = 1;
    }
    if (!incomment) {
      putchar(ch);
    }
    if (ch == '\n') {
      incomment = 0;
      newlinelast = 1;
    }
    else {
      newlinelast = 0;
    }
  }
  return 0;
}
/* DON'T KNOW HOW OR WHAT TO DO */
