/* Solution to comp20005 Assignment 1, 2019 semester 1.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: [Christian Wladyslaw Drozdowicz, 832391]
   Dated:     [12/04/2019]

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* for sqrt function */

/*  Flags to tell function what stage is calling it  */
#define STAGE_1 1
#define STAGE_2 2
#define STAGE_3 3
#define STAGE_4 4
/*  Flags to tell bsttery_usage function if it is out/ret battery  */
#define BATTERYOUT 0
#define BATTERYRET 1
/*  All other definitions  */
#define MAX_LINES 999 /* maximum data lines in any input file */
#define MAX_PERCENT 100 /* maximum percentage of any battery */
#define DRONE_WEIGHT 3.8 /* drone weight with no load */
#define MAX_CARRY 5.8 /* maximum weight drone can carry */
#define ORIGIN 0.0 /* origin for x and y */
#define EMPTY_DRONE_DIST (double) 6300/3.8/*distance drone can travel empty*/
#define DRONE_SPEED 4.2 /* drones fly at constant 4.2 meters/second */

/*  Stage function prototypes  */
void stage_1(double x_val[], double y_val[], double kg_val[], int valid_lines);
void stage_2(double x_val[], double y_val[], double kg_val[], int valid_lines);
void stage_3(double x_val[], double y_val[], double kg_val[], int valid_lines);
void stage_4(double x_val[], double y_val[], double kg_val[], int valid_lines);
/*  All other function prototypes  */
int mygetchar(void);
double centroid(double coord[], int valid_lines);
void non_seq_battery_check(int valid_lines, double trip_batt[], double dist[],
     double ran[], double batt_out[], double batt_ret[], double time[],
      int stage);
void distance(double *dist, int valid_lines, double x1, double x2[], double y1,
    double y2[]);
void range(double *ran, int valid_lines, double load[]);
void battery_usage(double *batt, int valid_lines, double dist[], double ran[],
    int flag);
void flight_time(double *time, int valid_lines, double dist[]);
void pop_arrays(double x_val[], double y_val[], double kg_val[], int stage,
     int valid_lines, double *dist, double *ran, double *batt_out,
      double *batt_ret, double *time, double *trip_batt);
int seq_battery_check(int i, double trip_batt[], double *sum, int stage);
double sum_array(double input[], int valid_lines);

/*  main program  */
int
main(int argc, char **argv) {
    int i = 0, hcheck, valid_lines = 0;
    double x_val[MAX_LINES], y_val[MAX_LINES], kg_val[MAX_LINES];
    /* checks for \r and skips header line of file */
    while ((hcheck = mygetchar()) != EOF) {
        if (hcheck == '\n') {
            break;
        }
    }
    /* populates 3 parallel arrays from input data */
    while (scanf("%lf\t%lf\t%lf\n", &x_val[i], &y_val[i], &kg_val[i]) == 3) {
        i++;
        valid_lines ++;
    }

    /* Now start stage 1 output */
    stage_1(x_val, y_val, kg_val, valid_lines);
    printf("\n");
    /* stage 2 output */
    stage_2(x_val, y_val, kg_val, valid_lines);
    printf("\n");
    /* stage 3 output */
    stage_3(x_val, y_val, kg_val, valid_lines);
    printf("\n");
    /* stage 4 output */
    stage_4(x_val, y_val, kg_val, valid_lines);
    printf("\n");
    /* bada bing bada boom we are done! */
    printf("Ta daa!\n");

    return 0;
}
/* provided mygetchar() function to deal with CR+LF windows newline sequence
that throws away the CR should one come through */
int
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

/* Generate the output format for stage 1 */
void
stage_1(double x_val[], double y_val[], double kg_val[], int valid_lines) {
    /* prints out the number of data lines read, first data
     line, last data line, and total kg needing to be deliver */
    printf("S%d, total data lines:%3d\n", STAGE_1, valid_lines);
    printf("S%d, first data line :  x=%6.1lf, y=%6.1lf, kg=%4.2lf\n",
        STAGE_1, x_val[0], y_val[0], kg_val[0]);
    printf("S%d, final data line :  x=%6.1lf, y=%6.1lf, kg=%4.2lf\n",
        STAGE_1, x_val[valid_lines-1], y_val[valid_lines-1],
            kg_val[valid_lines-1]);
    printf("S%d, total to deliver: %5.2lf kg\n",
        STAGE_1, sum_array(kg_val, valid_lines));
    return;
}

/* generate the output format required for stage 2 */
void
stage_2(double x_val[], double y_val[], double kg_val[], int valid_lines) {
    /*  Populate arrays with pop_array function  */
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES],
        batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    pop_arrays(x_val, y_val, kg_val, STAGE_2, valid_lines, dist, ran, batt_out,
         batt_ret, time, trip_batt);

    int i;
    double sum = 0, total_dist, total_time;
    int batteries = 1; /* always will have the starting battery */

    /* check if battery change is needed as well as print all necesaary data */
    for (i=0; i<valid_lines; i++) {
        if (seq_battery_check(i, trip_batt, &sum, STAGE_2) != 1) {
            batteries++;
        }
        printf("S%d, package=%3d, distance=%6.1lfm, battery out=%4.1lf%%,"
             " battery ret=%4.1lf%%", STAGE_2, i, dist[i], batt_out[i],
                batt_ret[i]);
        printf("\n");
    }
    /* print battery count */
    printf("S%d, total batteries required:%4d\n",STAGE_2, batteries);

    /* need to double the distance for out and return */
    total_dist = 2 * sum_array(dist, valid_lines);
    total_time = sum_array(time, valid_lines);
    printf("S%d, total flight distance=%4.1lf meters, total flight time=%4.lf"
        " seconds\n", STAGE_2, total_dist, total_time);

    return;
}

/* generate the output format required for stage 3 */
void
stage_3(double x_val[], double y_val[], double kg_val[], int valid_lines) {
    /*  Populate arrays with pop_array function  */
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES],
        batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    pop_arrays(x_val, y_val, kg_val, STAGE_3, valid_lines, dist, ran, batt_out,
         batt_ret, time, trip_batt);

    /* make better use of each battery with STAGE_3 Flag */
    non_seq_battery_check(valid_lines, trip_batt, dist, ran, batt_out,
         batt_ret, time, STAGE_3);

    /* need to double the distance for out and return */
    double total_dist, total_time;
    total_dist = 2 * sum_array(dist, valid_lines);
    total_time = sum_array(time, valid_lines);
    printf("S%d, total flight distance=%4.1lf meters, "
        "total flight time=%4.lf seconds\n", STAGE_3, total_dist, total_time);
    return;
}

/* generate the output format required for stage 4 */
void
stage_4(double x_val[], double y_val[], double kg_val[], int valid_lines) {
    /*  Populate arrays with pop_array function  */
    double dist[MAX_LINES], ran[MAX_LINES], batt_out[MAX_LINES],
        batt_ret[MAX_LINES], time[MAX_LINES], trip_batt[MAX_LINES];
    pop_arrays(x_val, y_val, kg_val, STAGE_4, valid_lines, dist, ran, batt_out,
         batt_ret, time, trip_batt);

    /* make better use of each battery with STAGE_4 Flag */
    non_seq_battery_check(valid_lines, trip_batt, dist, ran, batt_out,
         batt_ret, time, STAGE_4);

    /* need to double the distance for out and return */
    double total_dist, total_time;
    total_dist = 2 * sum_array(dist, valid_lines);
    total_time = sum_array(time, valid_lines);
    printf("S%d, total flight distance=%4.1lf meters, total flight"
    " time=%4.lf seconds\n", STAGE_4, total_dist, total_time);
    return;
}

/* Populates all calculation arrays based on what stage has called it and
 provides necessary checks on data */
void pop_arrays(double x_val[], double y_val[], double kg_val[], int stage,
     int valid_lines, double *dist, double *ran, double *batt_out,
      double *batt_ret, double *time, double *trip_batt) {
    /*  Check for a package that is too heavy assuming 5.8 is legal and
    anything over 5.8 is illegal */
    int i;
    for(i=0; i<valid_lines; i++) {
        if (kg_val[i] > MAX_CARRY) {
            printf("Invalid Input-Package[%d] is over max drone carry weight"
                "\n", i);
            exit(EXIT_FAILURE);
        }
    }
    /*  Populate Distance array based on stage (origin/centroid)  */
    if (stage == STAGE_2 || stage == STAGE_3) {
        distance(dist, valid_lines, ORIGIN, x_val, ORIGIN, y_val);

    }
    else if (stage == STAGE_4) {
        double cent_x, cent_y;
        cent_x = centroid(x_val, valid_lines);
        cent_y = centroid(y_val, valid_lines);
        printf("S%d, centroid location x=%6.1lfm, y=%6.1lfm\n", STAGE_4,
            cent_x, cent_y);
        distance(dist, valid_lines, cent_x, x_val, cent_y, y_val);
    }
    /*  Populate the rest of calculations  */
    range(ran, valid_lines, kg_val);
    battery_usage(batt_out, valid_lines, dist, ran, BATTERYOUT);
    battery_usage(batt_ret, valid_lines, dist, ran, BATTERYRET);
    flight_time(time, valid_lines, dist);
    /*  Lastly check no package takes up >100 percent  */
    for (i=0; i<valid_lines; i++) {
        trip_batt[i] = batt_out[i] + batt_ret[i];
        if (trip_batt[i] > MAX_PERCENT) {
            printf("Invalid Input-Package[%d] require more than 100%% battery"
            "\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return;
}

/* returns the calculation provided to find the centroid location */
double
centroid(double coord[], int valid_lines) {
    double sum;
    sum = sum_array(coord, valid_lines);
    return (1.0/valid_lines)*sum;
}

/* Uses a pointer to a sum that can be called on multiple times to remember
the sum from each call, and when the sum is found to be >100 reset the sum
to the current element and print the message and keep going!*/
int
seq_battery_check(int i, double trip_batt[], double *sum, int stage) {
    *sum += trip_batt[i];
    if (*sum > MAX_PERCENT) {
        *sum = trip_batt[i];
        printf("S%d, change the battery\n", stage);
        return 0;
    }
    return 1;
}

/* Non-sequentially process the input trip_batt array make better use of each
 battery and print out all necessary messages when needed */
void
non_seq_battery_check(int valid_lines, double trip_batt[], double dist[],
     double ran[], double batt_out[], double batt_ret[], double time[],
      int stage) {
    /*iteration, sum and count variables, (batteries start at 1 for
    first battery, count exists for guard implementation)*/
    int i, k, j, count = 1, batteries = 1;
    double sum = 0;
    /* create a flag array to check if current element has been used */
    int flag_array[MAX_LINES];

    /* populate the flag array default to 0 (0 = not been used)*/
    for(i=0; i<valid_lines; i++) {
        flag_array[i] = 0;
    }

    /* for loop checks current element against all elements to the right of it
     that are flagged as 0 (not been used yet) */
    for (j=0; j<valid_lines; j++) {

        /* if current j element has been used already force next iteration */
        if (flag_array[j] == 1) {
            continue;
        }

        /* if current j element has not been used already to change to used */
        if (flag_array[j] == 0) {
            printf("S%d, package=%3d, distance=%6.1lfm, battery out=%4.1lf%%,"
                " battery ret=%4.1lf%%\n", stage, j, dist[j], batt_out[j],
                    batt_ret[j]);
            /* change element j flag to used */
            flag_array[j] = 1;
            /* add j element to current sum */
            sum += trip_batt[j];
            /* increase count */
            count++;
        }

        /* nested for loop to check j element against all other
        non used elements */
        for (k=j+1; k<valid_lines; k++) {
            if (flag_array[k] == 0) {
                if (sum + trip_batt[k] < MAX_PERCENT) {
                    sum += trip_batt[k];
                    printf("S%d, package=%3d, distance=%6.1lfm,"
                    " battery out=%4.1lf%%, battery ret=%4.1lf%%\n", stage, k,
                        dist[k], batt_out[k], batt_ret[k]);
                    /* change element k flag to used */
                    flag_array[k] = 1;
                    /* increase count */
                    count++;
                }
            }
        }
        /* use count to guard against too many change the battery prints */
        if( (count <= valid_lines)) {
            printf("S%d, change the battery\n", stage);
            batteries++;
        }
        /* reset sum to zero for next used */
        sum = 0;
    }
    /* print battery count */
    printf("S%d, total batteries required:%4d\n", stage, batteries);
    return;
}

/* Populates the distance array using input x1, x2 and y1, y2 coordinates
 from from the input */
void
distance(double *dist, int valid_lines, double x1, double x2[],
    double y1, double y2[]) {
        int i;
        double p_dist[MAX_LINES];
        for(i=0; i<valid_lines; i++) {
            /* calculation for distance given */
            p_dist[i] = ((x2[i]-x1)*(x2[i]-x1)) + ((y2[i]-y1)*(y2[i]-y1));
            dist[i] = sqrt(p_dist[i]);
        }
        return;
    }

/* Populates the range of the drone based on the package into an array */
void
range(double *ran, int valid_lines, double load[]) {
    int i;
    for (i=0; i<valid_lines; i++) {
        /* calculation for range given */
        ran[i] = 6300 / (DRONE_WEIGHT + load[i]);
    }
    return;
}

/* Populates the battery out/battery return of a specific delivery and uses a
 variable "flag" to know if it is an out/ret array being input*/
void
battery_usage(double *batt, int valid_lines, double dist[], double ran[],
    int flag) {
        int i;
        double ret_ran[MAX_LINES], equ[MAX_LINES];;
        /* if/else if to check whether out or ret */
        if (flag == BATTERYRET) {
            /*populates a simple array filled with EMPTY_DRONE_DIST for ret*/
            for(i=0; i<valid_lines; i++) {
                ret_ran[i] = EMPTY_DRONE_DIST;
            }
            for(i=0; i<valid_lines; i++) {
                /* calculation give and calculated as a percent */
                equ[i] = 100.0 * dist[i] / ret_ran[i];
                batt[i] = equ[i];
            }
        }
        else if (flag == BATTERYOUT) {
            for(i=0; i<valid_lines; i++) {
                /* calculation give and calculated as a percent */
                equ[i] = 100.0 * dist[i] / ran[i];
                batt[i] = equ[i];
            }
        }
        return;
}

/* Populates the total flight times of each delivery into an array */
void
flight_time(double *time, int valid_lines, double dist[]) {
    int i;
    for(i=0; i<valid_lines; i++) {
        /* need to double for time out and return */
        time[i] = 2 * dist[i] / DRONE_SPEED;
    }
    return;
}

/* Returns a sum of all array elements of input array */
double
sum_array(double input[], int valid_lines) {
    int i;
    double sum = 0;
    for (i=0; i<valid_lines; i++) {
        sum += input[i];
    }
    return sum;
}


/* programming is fun */
