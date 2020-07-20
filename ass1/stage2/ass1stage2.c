/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

#include <stdlib.h>
#include <math.h>

#define MAX_LINES 999

#define DRONE_WEIGHT 3.8
#define MAX_CARRY 5.8
#define ORIGIN_X 0.0
#define ORIGIN_Y 0.0
#define EMPTY_DRONE_DIST (double) 6300/3.8



/* function prototypes */
void stage_2(double X[], double Y[], double KG[], int valid_lines);
double distance(double x_coord, double y_coord);
double battery_usage(double dist, double ran);
double range(double load);
int battery_check(double curr, double next);


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

    /* stage 2 output */
    stage_2(X, Y, KG, valid_lines);
    printf("\n");



    return 0;
}


/* prints out number of data lines read, first data line, last data line,
and total kg needing to be deliver */
void
stage_2(double X[], double Y[], double KG[], int valid_lines) {
    int i;
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], trip_batt[MAX_LINES];

    /* ONE FOR LOOP TO POPUALTE ARRAYS */
    for (i=0;i<valid_lines;i++) {
        dist[i] = distance(X[i], Y[i]);

        ran[i] = range(KG[i]);

        batt_out[i] = battery_usage(dist[i], ran[i]);
        batt_ret[i] = battery_usage(dist[i], EMPTY_DRONE_DIST);

        trip_batt[i] = batt_out[i] + batt_ret[i];

    }

    for (i=0;i<valid_lines;i++) {
        printf("package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%", i, dist[i], batt_out[i], batt_ret[i]);
        printf("\n");
        if (battery_check(trip_batt[i], trip_batt[i+1]) == 0 && i<valid_lines-1) {
            printf("Change the battery\n");
        }
    }

/* ============FOR TESTING ============ */
    /*for (i=0;i<valid_lines;i++) {
      printf("dist[%d] = %4.1lf", i, dist[i]);
      printf("\n");

    }
    printf("\n");

    for (i=0;i<valid_lines;i++) {
      printf("range[%d] = %4.1lf", i, ran[i]);
      printf("\n");

    }
    printf("\n");

    for (i=0;i<valid_lines;i++) {
      printf("batout[%d] = %4.1lf", i, batt_out[i]);
      printf("\n");

    }
    printf("\n");
    for (i=0;i<valid_lines;i++) {
      printf("batret[%d] = %4.1lf", i, batt_ret[i]);
      printf("\n");

    }
    for (i=0;i<valid_lines;i++) {
      printf("trip_batt[%d] = %4.1lf", i, trip_batt[i]);
      printf("\n");

  }*/

}

double
distance(double x_coord, double y_coord) {
    double p_dist;
    p_dist = ((x_coord - ORIGIN_X)*(x_coord - ORIGIN_X))+((y_coord - ORIGIN_Y)*(y_coord - ORIGIN_Y));
    return sqrt(p_dist);
}

double
range(double load) {
    return (double) 6300 / (DRONE_WEIGHT + load);
}

double
battery_usage(double dist, double ran) {
    return 100.0 * dist / ran; /* returned as a percent */
}

int
battery_check(double curr, double next) {
    if ((100 - curr - next) >= 0) {
        return 1;
    }
    else {
        return 0;
    }
}
