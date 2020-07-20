/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 8 final product stage3
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

#include <stdlib.h>
#include <math.h> /* for sqrt function */

#define STAGE_1 1
#define STAGE_2 2
#define STAGE_3 3
#define STAGE_4 4

#define MAX_LINES 999 /* maximum number of lines */

#define DRONE_WEIGHT 3.8 /* drone weight with no load */
#define MAX_CARRY 5.8 /* maximum weight drone can carry */
#define ORIGIN_X 0.0 /* origin in x */
#define ORIGIN_Y 0.0 /* origin in y */
#define BATTERYOUT 0
#define BATTERYRET 1
#define EMPTY_DRONE_DIST (double) 6300/3.8 /* distance drone can travel with no load */
#define DRONE_SPEED 4.2 /* drones fly at constant 4.2 meters/second */


/* function prototypes */
void stage_3(double X[], double Y[], double KG[], int valid_lines);
void optimise(int valid_lines, double trip_batt[], double dist[], double ran[], double batt_out[], double batt_ret[], double time[], int stage);



void distance(double *dist, int valid_lines, double x1, double x2[], double y1, double y2[]);
void range(double *ran, int valid_lines, double load[]);
void battery_usage(double *batt, int valid_lines, double dist[], double ran[], int flag);
void flight_time(double *time, int valid_lines, double dist[]);
void pop_arrays(double X[], double Y[], double KG[], int stage, int valid_lines, double *dist, double *ran, double *batt_out, double *batt_ret, double *time, double *trip_batt);


int battery_check(int i, double trip_batt[], double *sum, int stage);
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

    /*double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];

    one for loop to populate all data arrays
    for (i=0;i<valid_lines;i++) {
        dist[i] = distance(ORIGIN_X, X[i], ORIGIN_Y, Y[i]);

        ran[i] = range(KG[i]);

        batt_out[i] = battery_usage(dist[i], ran[i]);
        batt_ret[i] = battery_usage(dist[i], EMPTY_DRONE_DIST);

        time[i] = flight_time(dist[i]);

        trip_batt[i] = batt_out[i] + batt_ret[i];

    }*/



    /* stage 3 output */
    stage_3(X, Y, KG, valid_lines);

    printf("\n");



    return 0;
}


/* prints out structure of data for stage 3, */
void
stage_3(double X[], double Y[], double KG[], int valid_lines) {
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    pop_arrays(X, Y, KG, STAGE_3, valid_lines, dist, ran, batt_out, batt_ret, time, trip_batt);



    double total_dist, total_time;
    optimise(valid_lines, trip_batt, dist, ran, batt_out, batt_ret, time, STAGE_3);
    total_dist = 2 * sum_array(dist, valid_lines); /* need to double the distance for out and return */
    total_time = sum_array(time, valid_lines);
    printf("S%d, total flight distance= %lf meters, total flight time= %lf seconds\n", STAGE_3, total_dist, total_time);

    return;
}

void pop_arrays(double X[], double Y[], double KG[], int stage, int valid_lines, double *dist, double *ran, double *batt_out, double *batt_ret, double *time, double *trip_batt) {
    int i;
    for(i=0;i<valid_lines;i++) {
        if (KG[i] > 5.8) {
            printf("Invalid Input - Package[%d] is over max drone carry weight\n", i);
            exit(EXIT_FAILURE);
        }
    }
    if (stage == STAGE_2 || stage == STAGE_3) {
        distance(dist, valid_lines, ORIGIN_X, X, ORIGIN_Y, Y);

    }
    /*else if (stage == STAGE_4) { BRING THIS BACK IN WHEN STAGE 4
        double cent_x, cent_y;
        cent_x = centroid(X, valid_lines);
        cent_y = centroid(Y, valid_lines);
        distance(dist, valid_lines, cent_x, X, cent_y, Y);
    }*/
    range(ran, valid_lines, KG);
    battery_usage(batt_out, valid_lines, dist, ran, BATTERYOUT);
    battery_usage(batt_ret, valid_lines, dist, ran, BATTERYRET);
    flight_time(time, valid_lines, dist);

    for (i=0;i<valid_lines;i++) {
        trip_batt[i] = batt_out[i] + batt_ret[i];
        if (trip_batt[i] > 100) {
            printf("Invalid Input - Package[%d] require more than 100%% battery\n", i);
            exit(EXIT_FAILURE);
        }

    }
}

int
battery_check(int i, double trip_batt[], double *sum, int stage) {
    *sum += trip_batt[i];
    if (*sum > 100) {
        *sum = trip_batt[i];
        printf("S%d, Change the battery\n\n", stage);
        return 0;
    }
    return 1;
}




void
optimise(int valid_lines, double trip_batt[], double dist[], double ran[], double batt_out[], double batt_ret[], double time[], int stage) {
    int i, k, j, count = 1, batteries = 1;
    int flag_array[MAX_LINES]; /* to check if current element has been used or not using 0 or 1 */
    double sum = 0;

    /* populate the flag array default to 0 (not been used)*/
    for(i=0;i<valid_lines;i++) {
        flag_array[i] = 0;
    }


    /* for loop checks current element against all elements to the right of it that are flagged as 0 (not been used yet) */
    for (j=0;j<valid_lines;j++) {

        /* check to see if current j element has been used already and to force next iteration if it has */
        if (flag_array[j] == 1) {
            continue;
        }

        /* check to see if current j element has not been used already and to change to used if executed */
        if (flag_array[j] == 0) {
            printf("S%d, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", stage, j, dist[j], batt_out[j], batt_ret[j]);
            flag_array[j] = 1;
            count++; /* adds count to guard against too many "change the battery" prints */
            sum += trip_batt[j]; /* add j element to current sum */
        }

        /* nested for loop to check j element against all other non used yet elements */
        for (k=j+1;k<valid_lines;k++) {


            if (flag_array[k] == 0) {

                if (sum + trip_batt[k] < 100) {
                    sum += trip_batt[k];

                    printf("S%d, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", stage, k, dist[k], batt_out[k], batt_ret[k]);
                    flag_array[k] = 1; /* change element k flag to used */

                    count++;/* adds count to guard against too many "change the battery" prints */
                }

            }

        }

        /* only print if count is less than or equal to valid lines to stop whole bunch of prints at end of loop */
        if( (count <= valid_lines)) {
            printf("S%d, Change the battery\n", stage);
            batteries++;
        }

        /* reset sum to zero for next used */
        sum = 0;
    }

    /* print battery count */
    printf("S%d, total batteries required: %d\n", stage, batteries);


    return;

}

























/* returns the distance of input x and y coordinates from origin */
void
distance(double *dist, int valid_lines, double x1, double x2[], double y1, double y2[]) {
    int i;
    double p_dist[MAX_LINES];
    for(i=0;i<valid_lines;i++) {
        p_dist[i] = ((x2[i] - x1)*(x2[i] - x1))+((y2[i] - y1)*(y2[i] - y1));
        dist[i] = sqrt(p_dist[i]);
    }
    return;
}

/* returns the range of the drones using input of load kg */
void
range(double *ran, int valid_lines, double load[]) {
    int i;
    for (i=0;i<valid_lines;i++) {
        ran[i] = 6300 / (DRONE_WEIGHT + load[i]);
    }
    return;
}

/* returns the battery usage of a specific delivery */
void
battery_usage(double *batt, int valid_lines, double dist[], double ran[], int flag) {
    int i;
    double ret_ran[MAX_LINES], equ[MAX_LINES];;
    if (flag == 1) {
        for(i=0;i<valid_lines;i++) {
            ret_ran[i] = EMPTY_DRONE_DIST;
        }
        for(i=0;i<valid_lines;i++) {
            equ[i] = 100.0 * dist[i] / ret_ran[i]; /* returned as a percent */
            batt[i] = equ[i];
        }
    }
    else if (flag == 0) {
        for(i=0;i<valid_lines;i++) {
            equ[i] = 100.0 * dist[i] / ran[i]; /* returned as a percent */
            batt[i] = equ[i];
        }
    }
    return;
}

/* returns the total flight time of a specific delivery */
void
flight_time(double *time, int valid_lines, double dist[]) {
    int i;
    for(i=0;i<valid_lines;i++) {
        time[i] = 2 * dist[i] / DRONE_SPEED; /* need to double for time out and return */
    }
    return;
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
