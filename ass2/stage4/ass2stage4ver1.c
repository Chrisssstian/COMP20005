/*======================================================================
#      Assignment: 2
#     Description: Assignment 2, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1 stage4
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

#define MAX_YEARS 250

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
void stage_2(records_t records[], int valid_lines, double *median);
void stage_4(records_t records[], int valid_lines, int year, double *median);


void do_stage4(records_t records[], int valid_lines, int year, int stage, double *median);
void print_graph(int year, double month_rainfall[], double *median, int stage);
int calc_scale(double maximum);

/* function prototypes */
int mygetchar(void);
void check_month(records_t records[], int valid_lines, int stage, double *median);
double median_rainfall(double rainfallarray[], int count);
double compute_tau(double rainfallarray[], int count);
void stage_check(double rainfallarray[], int i, int count, int start_year, int end_year, int stage);



/* main program */
int
main(int argc, char *argv[]) {
	int i = 0, hcheck, valid_lines = 0, year;
	records_t records[MAX_DATA];
    double median[MONTHS];

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

    stage_2(records, valid_lines, median);
    /* get the year from command line */
    year = atoi(argv[1]);
    /* Now start stage 4 output */
    stage_4(records, valid_lines, year, median);
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


void
stage_2(records_t records[], int valid_lines, double *median) {
    check_month(records, valid_lines, STAGE_2, median);
    return;
}

/* stage 4 format */
void
stage_4(records_t records[], int valid_lines, int year, double *median) {
    do_stage4(records, valid_lines, year, STAGE_4, median);
    return;
}

void
do_stage4(records_t records[], int valid_lines, int year, int stage, double *median) {
    /* for loop to locate each year */
    int i, j;
    double month_rainfall[MONTHS];
    for(i=0, j=JAN; i<valid_lines && j<=MONTHS; i++) {

        if (records[i].year == year) {
            if (records[i].month == j) {
                month_rainfall[j] = records[i].rainfall;
            }
            j++;
        }
    }

    print_graph(year, month_rainfall, median, stage);
    return;
}

void
print_graph(int year, double month_rainfall[], double *median, int stage) {

    int i, j, scale, max_graph_value;
    double maximum = month_rainfall[0];

    for (i=0; i<MONTHS; i++) {
        if (month_rainfall[i] > maximum) {
            maximum = month_rainfall[i];
        }
    }
    
    scale = calc_scale(maximum);

    max_graph_value = scale * 24;
    printf("S%d, %d max is %.1lf, scale is %d\n", stage, year, maximum, scale);

    for (i=max_graph_value; i>0; i-=scale) {
        printf("%3d | ", i);
        for(j=JAN; j<=MONTHS; j++) {



            if ((month_rainfall[j] > i - scale) && (month_rainfall[j] <= i)) {
                if ((median[j] > i - scale) && (median[j] <= i)) {
                    printf("*%02d*", year%100);
                }
                else {
                    printf(" %02d ", year%100);
                }

                month_rainfall[j] -= scale;
            }

            else {

                if ((median[j] > i - scale) && (median[j] <= i)) {
                    printf("****");
                }
                else if (month_rainfall[j] == 0 ) {
                    printf("    ");
                }
                else {
                    printf("    ");
                }
            }
            printf(" ");

        }
        printf("\n");
    }
    printf("  0 +-----+----+----+----+----+----+----+----+----+----+----+----+\n");
    printf("     Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec ");


}

int
calc_scale(double maximum) {
    double calculation = maximum / 24;
    return round(calculation);
}
















/* This function does all the work for stage 2 and stage 3; checks and combines
 by each month and puts all information together for outputs of stage 2 and
 stage 3 */
void
check_month(records_t records[], int valid_lines, int stage, double *median) {
    int i, j, k, count[MONTHS], start_year, end_year;
    double rainfallarray[valid_lines];



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
        median[i] = median_rainfall(rainfallarray, count[i]);
        //stage_check(rainfallarray, i, count[i], start_year, end_year, stage);
    }

    return;
}


























/*
void
stage_check(double rainfallarray[], int i, int count, int start_year, int end_year, int stage) {
    double med_calc;



    if (stage == STAGE_2) {

        if (count !=0 ) {
            med_calc = median_rainfall(rainfallarray, count);
            printf("S%d, %s, %d values, %d-%d, mean of %lf\n", STAGE_2,
                months[i], count, start_year, end_year, med_calc);
        }
        else {
            printf("S%d, %s, %d values\n", STAGE_2, months[i], count);
        }
    }


}*/



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
