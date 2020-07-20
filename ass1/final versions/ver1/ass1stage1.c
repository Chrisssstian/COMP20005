/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1 final product stage1
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

/* constants stages1-4 to help with printing correct outputs */
#define STAGE_1 1
#define STAGE_2 2
#define STAGE_3 3
#define STAGE_4 4

#define MAX_LINES 999 /* maximum data lines in any input file */

/* function prototypes */
void stage_1(double X[], double Y[], double KG[], int valid_lines);

/* main program */
int
main(int argc, char **argv) {
    int i = 0, hcheck, valid_lines =0;
    double X[MAX_LINES], Y[MAX_LINES], KG[MAX_LINES];
    /* checks and skips header line of file */
    while ((hcheck = getchar()) != EOF) {
        if (hcheck == '\n') {
            break;
        }
    }
    /* populates 3 parallel arrays from input data */
    while (scanf("%lf\t%lf\t%lf\n", &X[i], &Y[i], &KG[i]) == 3) {
        i++;
        valid_lines ++;
    }

    /* stage 1 output */
    stage_1(X, Y, KG, valid_lines);
    printf("\n");



    return 0;
}

/* --------------------DELETE THIS------------ */
void
test_input(double X[], double Y[], double KG[], int valid_lines) {
  int i, j, k;
  printf("THIS IS JUST A TEST FOR INPUT AND DELETE LATER\n");
  for (i=0;i<valid_lines;i++) {
    printf("X[%d] = %4.1lf", i, X[i]);
    printf("\n");

  }
  printf("\n");

  for(j=0;j<valid_lines;j++) {
    printf("Y[%d] = %4.1lf", j, Y[j]);
    printf("\n");

  }
  printf("\n");

  for(k=0;k<valid_lines;k++) {
    printf("KG[%d] = %4.2lf", k, KG[k]);
    printf("\n");

  }
  printf("\n");

}
/*--------------------------------------------*/


/* prints out number of data lines read, first data line, last data line,
and total kg needing to be deliver */
void
stage_1(double X[], double Y[], double KG[], int valid_lines) {
    int i;
    double sum = 0;
    printf("S%d, total data lines: %d\n", STAGE_1, valid_lines);
    printf("S%d, first data line: x=%6.1lf, y=%6.1lf, kg=%4.2lf\n", STAGE_1, X[0], Y[0], KG[0]);
    printf("S%d, final data line: x=%6.1lf, y=%6.1lf, kg=%4.2lf\n", STAGE_1, X[valid_lines-1], Y[valid_lines-1], KG[valid_lines-1]);

    for (i=0;i<valid_lines;i++) {
        sum += KG[i];
    }
    printf("S%d, total to deliver: %5.2lf kg\n", STAGE_1, sum);
    return;
}
