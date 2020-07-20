#include <stdio.h>

double sum_sequence(int n);

int
main(int argc, char **argv) {

    int n;
    printf("enter a number:\n");
    scanf("%d", &n);

    printf("sum = %lf\n", sum_sequence(n));
    return 0;
}

double sum_sequence(int n) {
    int i, j;
    int x;
    double sum=0.0;

    for(i=1; i<=n; i++) {
        //sum = 0.0;
        x = 1.0;
        for (j=1; j<=i; j++) {
            x *= j;
        }
        sum += 1.0/x;
    }
    return sum;
}
