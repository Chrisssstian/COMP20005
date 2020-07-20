#include <stdio.h>

typedef struct {
    int d;
    double c[100];
} poly_t;

poly_t poly_eval(poly_t P);

int
main(int argc, char **argv) {
    poly_t P, deriv;
    int i;

    printf("enter the degree:\n");
    scanf("%d", &P.d);


    printf("enter the coefficients:\n");
    scanf("%lf,%lf,%lf,%lf", &P.c[0], &P.c[1], &P.c[2], &P.c[3]);

    deriv = poly_eval(P);

    printf("derivative degree = %d\n", deriv.d);

    for (i=0; i<=deriv.d; i++){
        printf("i = %d, value = %lf\n", i, deriv.c[i]);
    }
    return 0;
}

poly_t poly_eval(poly_t P) {
    int i;
    poly_t deriv;

    deriv.d = P.d-1;
    
    for(i=1; i<=P.d; i++) {
        if (i == 1) {
            deriv.c[i-1] = P.c[i];
        }
        else {
            deriv.c[i-1] = i*P.c[i];
        }
    }
    return deriv;
}
