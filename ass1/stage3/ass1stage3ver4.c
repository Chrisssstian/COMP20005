/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 4 works for drones0 not drones1
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
    int i, k, j, x;
    int new_array[MAX_LINES];

    /* the flag array */
    for(i=0;i<valid_lines;i++) {
        new_array[i] = 0;
    }



    double sum = trip_batt[0];
    printf("S3, package= 0\n");


    for (j=0;j<valid_lines;j++) {


        //printf("%d\n", j);

        if(new_array[j] == 0 ) {

            for (k=j+1;k<valid_lines && new_array[k] == 0;k++) {
                if (sum + trip_batt[k] < 100) {
                    sum += trip_batt[k];

                    //printf("%lf\n", sum);
                    printf("S3, package= %d\n", k);
                    new_array[k] = 1; /* flag wev've used it already */
                    new_array[j] = 1;

                }
            }
            if (new_array[j] == 0) {
                new_array[j] = 1;
                printf("S3, package= %d\n", j);
            }
            sum = 0;

            printf("Change the battery\n");
        }




    }

    /* PRINT CHECKS */
    for(x=0;x<valid_lines;x++) {
        printf("after:  trip_batt[%d] = %lf\n ", x, trip_batt[x]);
    }
    printf("\n");
    for(x=0;x<valid_lines;x++) {
        printf("after:  flag[%d] = %d\n ", x, new_array[x]);
    }
    printf("\n");
    return;
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
