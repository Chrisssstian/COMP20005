/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 3 try some tricky stuff
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

#include <stdlib.h>
#include <math.h> /* for sqrt function */

#define MAX_LINES 999 /* maximum number of lines */

#define DRONE_WEIGHT 3.8 /* drone weight with no load */
#define MAX_CARRY 5.8 /* maximum weight drone can carry */
#define ORIGIN_X 0.0 /* origin in x */
#define ORIGIN_Y 0.0 /* origin in y */
#define EMPTY_DRONE_DIST (double) 6300/3.8 /* distance drone can travel with no load */
#define DRONE_SPEED 4.2 /* drones fly at constant 4.2 meters/second */


/* function prototypes */
void stage_3(int valid_lines, double dist[], double ran[], double batt_out[], double batt_ret[], double time[], double trip_batt[]);
void optimise(int valid_lines, double trip_batt[]);
void int_swap (double *x, double *y);


int battery_check(int i, double trip_batt[], double *sum);
double distance(double x1, double x2, double y1, double y2);
double battery_usage(double dist, double ran);
double range(double load);
double flight_time(double dist);
double sum_array(double A[], int valid_lines);



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

    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];

    /* one for loop to populate all data arrays */
    for (i=0;i<valid_lines;i++) {
        dist[i] = distance(ORIGIN_X, X[i], ORIGIN_Y, Y[i]);

        ran[i] = range(KG[i]);

        batt_out[i] = battery_usage(dist[i], ran[i]);
        batt_ret[i] = battery_usage(dist[i], EMPTY_DRONE_DIST);

        time[i] = flight_time(dist[i]);

        trip_batt[i] = batt_out[i] + batt_ret[i];

    }



    /* stage 2 output */
    stage_3(valid_lines, dist, ran, batt_out, batt_ret, time, trip_batt);

    printf("\n");



    return 0;
}


/* prints out structure of data for stage 2, and populates arrays for use */
void
stage_3(int valid_lines, double dist[], double ran[], double batt_out[], double batt_ret[], double time[], double trip_batt[]) {
    int i;
    double sum = 0;
    int batteries = 1; /* always will have the starting battery */
    for (i=0;i<valid_lines;i++) {

        if (battery_check(i, trip_batt, &sum) == 1) {
            printf("S2, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%", i, dist[i], batt_out[i], batt_ret[i]);

            trip_batt[i] = trip_batt[i+1];

        }
        else {
            printf("S2, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%", i, dist[i], batt_out[i], batt_ret[i]);

            batteries++;

        }
        printf("\n");
    }
    /* print battery count */
    printf("S2, total batteries required: %d\n", batteries);

    optimise(valid_lines,trip_batt);

    return;
}

int
battery_check(int i, double trip_batt[], double *sum) {
    *sum += trip_batt[i];
    if (*sum > 100) {
        *sum = trip_batt[i];
        printf("S2, Change the battery\n\n");
        return 0;
    }
    return 1;
}


void
optimise(int valid_lines, double trip_batt[]) {
    int k, j, x;
    //double new_array[MAX_LINES];

    double sum = trip_batt[0];
    printf("S3, package= %d\n", 0);
    for (j=0;j<valid_lines;j++) {

        for (k=j+1;k<valid_lines;k++) {

            if (sum + trip_batt[k] < 100) {
                sum += trip_batt[k];

                printf("%lf\n", sum);
                printf("S3, package= %d\n\n", k);

            }
            /*else {
                int_swap(&trip_batt[k], &trip_batt[valid_lines-1]);

                sum = trip_batt[j];
                printf("%lf\n\n", sum);
            }*/
        }
    }


    /* for loop to show after elements after sorting */
    for(x=0;x<valid_lines;x++) {
        printf("after:  trip_batt[%d] = %lf\n ", x, trip_batt[x]);
    }
    printf("\n");
}

/* page 94 figure 6.7 int_swap defintion*/
void
int_swap(double *x, double *y) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}




















/* returns the distance of input x and y coordinates from origin */
double
distance(double x1, double x2, double y1, double y2) {
    double p_dist;
    p_dist = ((x2 - x1)*(x2 - x1))+((y2 - y1)*(y2 - y1));
    return sqrt(p_dist);
}

/* returns the range of the drones using input of load kg */
double
range(double load) {
    return (double) 6300 / (DRONE_WEIGHT + load);
}

/* returns the battery usage of a specific delivery */
double
battery_usage(double dist, double ran) {
    return 100.0 * dist / ran; /* returned as a percent */
}

/* returns the total flight time of a specific delivery */
double
flight_time(double dist) {
    return 2 * dist / DRONE_SPEED; /* need to double for time out and return */
}

/* returns a sum of all array elements of specific array input */
double
sum_array(double A[], int valid_lines) {
    int i;
    double sum = 0;
    for (i=0;i<valid_lines;i++) {
        sum += A[i];
    }

    return sum;
}
