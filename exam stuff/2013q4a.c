#include <stdio.h>

typedef struct {
    int d;
    double c[100];
} poly_t;

double poly_eval(poly_t P, double x);

int
main(int argc, char **argv) {
    poly_t P;

    double x;
    printf("enter the degree:\n");
    scanf("%d", &P.d);

    printf("enter the number:\n");
    scanf("%lf", &x);

    printf("enter the coefficients:\n");
    scanf("%lf,%lf,%lf,%lf", &P.c[0], &P.c[1], &P.c[2], &P.c[3]);

    printf("sum = %lf\n", poly_eval(P, x));
    return 0;
}

double poly_eval(poly_t P, double x) {
    int i, j;
    double sum=0.0, multi;

    for(i=0; i<=P.d; i++) {
        multi = 1.0;
        for (j=1; j<=i; j++) {
            multi *= x;

        }
        if (i == 0) {
            sum += P.c[i];
        }
        else {
            sum += P.c[i]*multi;
        }
    }
    return sum;
}
