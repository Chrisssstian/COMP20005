/*======================================================================
#      Assignment: 2
#     Description: Assignment 2, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 2 final product stage2
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

/*  Flags to tell function what stage is calling it  */
#define STAGE_1 1
#define STAGE_2 2
#define STAGE_3 3
#define STAGE_4 4

/* All other Definitions */
#define MAX_DATA 3000 /* max 250 years * 12 months = 3000 */
#define MONTHS 12
#define NO_DATA 0
#define NOT_VALIDATED 'N'
#define JAN 1

/* provided global variable */
char *months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/* defining types */
typedef struct {
	int station;
	int year;
	int month;
	double rainfall;
	char check;
} records_t;



/* stage function prototypes */
void stage_2(records_t records[], int valid_lines);

/* function prototypes */
int mygetchar(void);
void check_month(records_t records[], int valid_lines, int stage);
double median_rainfall(double rainfallarray[], int count);



/* main program */
int
main(int argc, char *argv[]) {
	int i = 0, hcheck, valid_lines = 0;
	records_t records[MAX_DATA];

    /* checks for \r and skips header line of file */
    while ((hcheck = mygetchar()) != EOF) {
        if (hcheck == '\n') {
            break;
        }
    }

    /* read data into arrays */
    while (scanf("IDCJAC0001,%d,%d,%d,%lf,%c\n", &records[i].station,
                &records[i].year, &records[i].month, &records[i].rainfall,
                    &records[i].check) == 5) {
        i++;
        valid_lines ++;
    }

    /* Now start stage 1 output */
    stage_2(records, valid_lines);
    printf("\n");

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

/* stage 2 format */
void
stage_2(records_t records[], int valid_lines) {
    check_month(records, valid_lines, STAGE_2);
    return;
}

/* This function does all the work for stage 2 and stage 3; checks and combines
 by each month and puts all information together for outputs of stage 2 and
 stage 3 */
void
check_month(records_t records[], int valid_lines, int stage) {
    int i, j, k, count[MONTHS], start_year, end_year;
    double rainfallarray[valid_lines], med_calc;

    /* fill an array for counting the amount of values for each month to set
     at zero*/
    for (i=0; i<=MONTHS; i++) {
        count[i] = 0;
    }

    /* for loop to locate each month */
    for (i=JAN; i<=MONTHS; i++) {
        /* let k start at zero */
        k = 0;
        /* nested for loop to go through all of the data */
        for (j=0; j<valid_lines; j++) {
            /* finds when the current month we are looking at is equal to
            month in the structure data  */
            if (records[j].month == i) {
                /* adds a count */
                count[i]++;
                /* updates to find the final year data was present */
                end_year = records[j].year;
                /* array to record all rainfall for each month */
                rainfallarray[k] = records[j].rainfall;
                /* increase k */
                k++;
                /* check to find the start year */
                if (count[i] == JAN) {
                    start_year = records[j].year;
                }
            }
        }
        /*check which stage called this function, print output for that stage*/
        if (stage == STAGE_2) {
            /* check if count has at least one item */
            if (count[i] !=0 ) {
                med_calc = median_rainfall(rainfallarray, count[i]);
                printf("S%d, %s, %d values, %d-%d, mean of %lf\n", STAGE_2,
                    months[i], count[i], start_year, end_year, med_calc);
            }
            else {
                printf("S%d, %s, %d values\n", STAGE_2, months[i], count[i]);
            }
        }
    }
    return;
}

/* Returns the median of all array elements of input array */
double
median_rainfall(double rainfallarray[], int count) {
    int i;
    double sum = 0, median;
    for (i=0; i<count; i++) {
        sum += rainfallarray[i];
    }
    median = sum/count;
    return median;
}
