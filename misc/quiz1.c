#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char const *argv[]) {
  int x, y;

  x = 1; y = 2;
  if (x>y)
      printf ("x=%d, y=%d\n", x, y);
      x = x+1;
  if (x<y)
      printf ("x=%d, y=%d\n", x, y);
      y = y+2;
  printf ("x=%d, y=%d\n", x, y);

  return 0;
}
