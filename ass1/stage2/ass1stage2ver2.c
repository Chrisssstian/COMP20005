/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 2
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

#include <stdlib.h>
#include <math.h>

#define MAX_LINES 999 /* maximum number of lines */

#define DRONE_WEIGHT 3.8 /* drone weight with no load */
#define MAX_CARRY 5.8 /* maximum weight drone can carry */
#define ORIGIN_X 0.0 /* origin in x */
#define ORIGIN_Y 0.0 /* origin in y */
#define EMPTY_DRONE_DIST (double) 6300/3.8 /* distance drone can travel with no load */



/* function prototypes */
void stage_2(double X[], double Y[], double KG[], int valid_lines);
double distance(double x_coord, double y_coord);
double battery_usage(double dist, double ran);
double range(double load);
double battery_check(int i, double trip_batt[], int valid_lines);


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


/* prints out structure of data for stage 2, and populates arrays for use */
void
stage_2(double X[], double Y[], double KG[], int valid_lines) {
    int i;
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], trip_batt[MAX_LINES];

    /* one for loop to populate all arrays */
    for (i=0;i<valid_lines;i++) {
        dist[i] = distance(X[i], Y[i]);

        ran[i] = range(KG[i]);

        batt_out[i] = battery_usage(dist[i], ran[i]);
        batt_ret[i] = battery_usage(dist[i], EMPTY_DRONE_DIST);

        trip_batt[i] = batt_out[i] + batt_ret[i];

    }

    double sum = 0;
    int count = 1;
    for (i=0;i<valid_lines;i++) {
        sum += trip_batt[i];
        if (sum > 100) {
            sum = trip_batt[i];
            printf("S2, Change the battery\n\n");
            count++;
        }
        printf("S2, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%", i, dist[i], batt_out[i], batt_ret[i]);
        printf("\n");
    }
    printf("S2, total batteries required: %d", count);

  return;
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

/*void
battery_check(int i, double trip_batt[]) {
    double sum = 0;




    return *sum;
}*/
