/*======================================================================
#         FileName: ass1.c
#     Description: Assignment 1, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1 works fully for drones0/1 but not print batteries
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
void stage_4(double X[], double Y[], double KG[], int valid_lines);
double centroid(double coord[], int valid_lines);


void optimise(int valid_lines, double trip_batt[], double dist[], double ran[], double batt_out[], double batt_ret[], double time[]);
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


    /* stage 2 output */
    stage_4(X, Y, KG, valid_lines);

    printf("\n");



    return 0;
}


/* prints out structure of data for stage 2, and populates arrays for use */
void
stage_4(double X[], double Y[], double KG[], int valid_lines) {
    int i;
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES], batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    double cent_x, cent_y;


    cent_x = centroid(X, valid_lines);
    cent_y = centroid(Y, valid_lines);

    printf("x = %lf y = %lf\n", cent_x, cent_y);
    /* one for loop to populate all arrays */
    for (i=0;i<valid_lines;i++) {
        dist[i] = distance(cent_x, X[i], cent_y, Y[i]);

        ran[i] = range(KG[i]);

        batt_out[i] = battery_usage(dist[i], ran[i]);
        batt_ret[i] = battery_usage(dist[i], EMPTY_DRONE_DIST);

        time[i] = flight_time(dist[i]);

        trip_batt[i] = batt_out[i] + batt_ret[i];

    }



    double total_dist, total_time;

    optimise(valid_lines, trip_batt, dist, ran, batt_out, batt_ret, time);

    total_dist = 2 * sum_array(dist, valid_lines); /* need to double the distance for out and return */
    total_time = sum_array(time, valid_lines);
    printf("S4, total flight distance= %lf meters, total flight time= %lf seconds\n", total_dist, total_time);


    return;
}



double
centroid(double coord[], int valid_lines) {
    double sum;
    sum = sum_array(coord, valid_lines);
    return (1.0/valid_lines)*sum;
}






void
optimise(int valid_lines, double trip_batt[], double dist[], double ran[], double batt_out[], double batt_ret[], double time[]) {
    int i, k, j, x=0, count = 1, batteries = 1;
    int new_array[MAX_LINES];

    /* the flag array */
    for(i=0;i<valid_lines;i++) {
        new_array[i] = 0;
    }



    double sum = 0;
    //printf("S3, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", x, dist[x], batt_out[x], batt_ret[x]);

    /* for loop checks current element against all elements to the right of it that are flagged as 0 or not been used yet */
    for (j=0;j<valid_lines;j++) {
        printf("j = %d\n", j);
        if (new_array[j] == 0) {
            printf("S3, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", j, dist[j], batt_out[j], batt_ret[j]);
            new_array[j] = 1;
            count++;
            sum += trip_batt[j];
        }
        for (k=j+1;k<valid_lines;k++) {
            //printf("%d\n", k);
            if (new_array[k] == 1 && k<valid_lines-1) {
                k++;
                //printf("%d\n", k);
            }
            if (new_array[k] == 0) {
                printf("k = %d\n", k);

                if (sum + trip_batt[k] < 100) {
                    sum += trip_batt[k];

                    printf("sum = %lf\n", sum);
                    printf("S3, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", k, dist[k], batt_out[k], batt_ret[k]);
                    new_array[k] = 1; /* change flag to used */
                    new_array[j] = 1; /* change flag to used */

                    count++;/* adds count to guard against too many "change the battery" prints */
                }

            }

            /* in the event that the current j element can't be added to any remaining elements */
            /*else if (new_array[j] == 0) {
                new_array[j] = 1;
                printf("S3, package= %d, distance= %.1lfm, battery out=%.1lf%%, battery ret=%.1lf%%\n", j, dist[j], batt_out[j], batt_ret[j]);
                count++;
                break;
            }*/

        }
        printf("count = %d\n", count);
        /* reset the sum back to zero */
        sum = 0;

        /* only print if count is less than valid lines to stop whole bunch of prints at end of loop */
        if(count< valid_lines) {
            printf("S3, Change the battery\n");
            /* count batteries used */
            batteries++;
        }
    }

    /* print battery count */
    printf("S3, total batteries required: %d\n", batteries);



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
