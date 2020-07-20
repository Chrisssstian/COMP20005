#include <stdio.h>
#include <math.h>

double my_fabs(double n);

int
main(int argc, char **argv) {
    double n;
    printf("enter a number:\n");
    scanf("%lf", &n);

    printf("fabs = %lf\n", fabs(n));
    printf("my_fabs = %lf\n", my_fabs(n));

    return 0;
}

double my_fabs(double n) {
    if (n<0) {
        return n*(-1);
    }
    else {
        return n;
    }
}
