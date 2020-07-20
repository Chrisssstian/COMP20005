/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 6 working to make it general for any use of stage11!!!!!!!1!1
======================================================================*/


/*  make sure line is within 80 charcters and tabs are 4 spaces or some shit  */

#include <stdio.h>

#include <stdlib.h>
#include <math.h> /* for sqrt function */

#define STAGE_1 1 /* stage1-4 for correct stage printf statements */
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
void stage_2(double X[], double Y[], double KG[], int valid_lines);

void distance(double *dist, int valid_lines, double x1, double x2[], double y1, double y2[]);
void range(double *ran, int valid_lines, double load[]);
void battery_usage(double *batt, int valid_lines, double dist[], double ran[], int flag);
void flight_time(double *time, int valid_lines, double dist[]);
void pop_arrays(double X[], double Y[], double KG[], int stage, int valid_lines, double *dist, double *ran, double *batt_out, double *batt_ret, double *time, double *trip_batt);


int battery_check(int i, double trip_batt[], double *sum);
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

    //double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];

    /* one for loop to populate all data arrays */

/*
    distance(dist, valid_lines, ORIGIN_X, X, ORIGIN_Y, Y);
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

    }*/

/* TESTING PURPOSES */
    /*for(i=0;i<valid_lines;i++) {
        printf("dist[%d] = %lf\n", i, dist[i]);
        printf("ran[%d] = %lf\n", i, ran[i]);
        printf("batt_out[%d] = %lf\n", i, batt_out[i]);
        printf("batt_ret[%d] = %lf\n", i, batt_ret[i]);
        printf("time[%d] = %lf\n", i, time[i]);


    }*/


    /* stage 2 output */
    stage_2(X, Y, KG, valid_lines);

    printf("\n");



    return 0;
}



/* prints out structure of data for stage 2, and populates arrays for use */
void
stage_2(double X[], double Y[], double KG[], int valid_lines) {
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    pop_arrays(X, Y, KG, STAGE_2, valid_lines, dist, ran, batt_out, batt_ret, time, trip_batt);

    double sum = 0, total_dist, total_time;
    int i, batteries = 1; /* always will have the starting battery */

    /* go through and check if battery is needed as well as print all necesaary data */
    for (i=0;i<valid_lines;i++) {
        if (battery_check(i, trip_batt, &sum) != 1) {
            batteries++;
        }
        printf("S2, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%", i, dist[i], batt_out[i], batt_ret[i]);
        printf("\n");
    }
    /* print battery count */
    printf("S2, total batteries required: %d\n", batteries);

    total_dist = 2 * sum_array(dist, valid_lines); /* need to double the distance for out and return */
    total_time = sum_array(time, valid_lines);
    printf("S2, total flight distance= %lf meters, total flight time= %lf seconds\n", total_dist, total_time);

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
battery_check(int i, double trip_batt[], double *sum) {
    *sum += trip_batt[i];
    if (*sum > 100) {
        *sum = trip_batt[i];
        printf("S2, Change the battery\n\n");
        return 0;
    }
    return 1;
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
