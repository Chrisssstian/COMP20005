/* rewrote program on page 74 (figure 5.8) to deal with negative numbers
By Christian Drozdowicz 23/03/2019 */

#include <stdio.h>

int t_itr(int n);
int t_rec(int n);


int
main(int argc, char const *argv[]) {
  int n;
  printf("please enter an integer: ");
  scanf("%d", &n);


  printf("iteration: %d\nrecursion: %d\n", t_itr(n), t_rec(n));


  return 0;
}


int t_itr(int n) {
  int sum, i;
  sum = 0;
  for (i = 0; i <= n; i++) {
    sum += i;
  }
  return sum;
}


int t_rec(int n) {
  if (n < 0) {
    return 0;
  }
  else {
    return (n + t_rec(n-1));
  }
}
