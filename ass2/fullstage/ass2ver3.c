/* Solution to comp20005 Assignment 2, 2019 semester 1.

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

   Signed by: [Christian Drozdowicz, 832391]
   Dated:     [16/05/2019]

*/

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
#define MAX_ROWS 24

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
void stage_1(records_t records[], int valid_lines);
void stage_2(records_t records[], int valid_lines, double *mean);
void stage_3(records_t records[], int valid_lines, double *mean);
void stage_4(records_t records[], int valid_lines, int year, double *mean);

/* function prototypes */
int mygetchar(void);
void check_month(records_t records[], int valid_lines, int stage, double *mean);
double mean_rainfall(double rainfallarray[], int count);
void print_stage(double rainfallarray[], int i, int count, int start_year,
	 	int end_year, double calculation, int stage);
double compute_tau(double rainfallarray[], int count);

void do_stage4(records_t records[], int valid_lines, int year, int stage,
     double *mean);
void print_graph(int year, double month_rainfall[], double *mean, int stage);
int calc_scale(double maximum);
int find_max_graph_value(double maximum, int scale);


/* main program */
int
main(int argc, char *argv[]) {
	int i = 0, hcheck, valid_lines = 0, year;
	records_t records[MAX_DATA];
    double mean[MONTHS];

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
    stage_1(records, valid_lines);
    printf("\n");
		/* Now start stage 2 output */
    stage_2(records, valid_lines, mean);
    printf("\n");
		/* Now start stage 3 output */
    stage_3(records, valid_lines, mean);
    printf("\n");
    /* get the year from command line */
    year = atoi(argv[1]);
        /* Now start stage 4 output */
    stage_4(records, valid_lines, year, mean);
    printf("\n");
    printf("Ta daa\n");

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

/* generates and prints the format for stage 1 */
void
stage_1(records_t records[], int valid_lines) {
    /* first print out the site and amount of datalines */
	printf("S1, site number %06d, %d datalines in input\n", records->station,
        valid_lines);

	int i, j, k;
    /* for loop to iterate through the data */
	for(i=0; i<valid_lines; i++) {
        /* print the year */
		printf("S1, %d:", records[i].year);

        /* nested for loop to check each month's data within the same year */
		for (k=i, j=1; k<i+MONTHS && j<MONTHS+1; k++, j++) {
            /* if month data doesn't exist print ... */
            if (records[k].month == NO_DATA) {
                printf(" ... ");
            }
            /* if month data skips a month the print ... and minus one from k
             count */
            else if (records[k].month != j && records[k].month > j) {
                printf(" ... ");
                k--;

            }
            /* once data has been checked to be correct */
            else {
                /* check for if data has been validated */
                if (records[k].check == NOT_VALIDATED) {
                    printf("%4s*", months[j]);
                }
                else {
                    printf("%4s ", months[j]);

                }
            }
		}
        /* change count i to count k minus 1 to start the next year */
        i = k-1;
        printf("\n");
	}
}

/* stage 2 format */
void
stage_2(records_t records[], int valid_lines, double *mean) {
    check_month(records, valid_lines, STAGE_2, mean);
    return;
}

/* stage 3 format */
void
stage_3(records_t records[], int valid_lines, double *mean) {
    check_month(records, valid_lines, STAGE_3, mean);
    return;
}

/* stage 4 format */
void
stage_4(records_t records[], int valid_lines, int year, double *mean) {
    do_stage4(records, valid_lines, year, STAGE_4, mean);
    return;
}

/* This function does all the work for stage 2 and stage 3; checks and combines
 by each month and puts all information together for outputs of stage 2 and
 stage 3 */
 void
 check_month(records_t records[], int valid_lines, int stage, double *mean) {
     int i, j, k, count[MONTHS], start_year, end_year;
     double rainfallarray[valid_lines], tau;

    /* fill an array for counting the amount of values for each month to set
     at zero*/
    for (i=JAN; i<=MONTHS; i++) {
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
                if (count[i] == 1) {
                    start_year = records[j+1].year;
                }
            }
        }
        mean[i] = mean_rainfall(rainfallarray, count[i]);
        tau = compute_tau(rainfallarray, count[i]);

        if (stage == STAGE_2) {
            print_stage(rainfallarray, i, count[i], start_year, end_year,
                 mean[i], stage);

        }
        else if (stage == STAGE_3) {
            print_stage(rainfallarray, i, count[i], start_year, end_year,
                 tau, stage);
        }
    }
    return;
}

void
print_stage(double rainfallarray[], int i, int count, int start_year,
	 	int end_year, double calculation, int stage) {

    if (stage == STAGE_2) {
        /* check if count has at least one item */
        if (count !=0 ) {
            printf("S%d, %s, %2d values, %4d-%4d, mean of %5.1lfmm\n", STAGE_2,
                months[i], count, start_year, end_year, calculation);
        }
        else {
            printf("S%d, %s, %2d values\n", STAGE_2, months[i], count);
        }
    }

    else if (stage == STAGE_3) {
        /* check if count has at least two items */
        if (count != 0 && count != 1) {
            printf("S%d, %s, %2d values, %4d-%4d, tau of %5.2lf\n", STAGE_3,
                months[i], count, start_year, end_year, calculation);

        }
        /* everything else just report the month with the value */
        else {
            printf("S%d, %s, %2d values\n", STAGE_3, months[i], count);
        }
    }
}

void
do_stage4(records_t records[], int valid_lines, int year, int stage,
     double *mean) {
    /* for loop to locate each year */
    int i, j;
    double month_rainfall[MONTHS];
    /* for loop to find relevant information from commmand line input year */
    for(i=0, j=JAN; i<valid_lines && j<=MONTHS; i++) {
        /* if we find the correct year in the data file */
        if (records[i].year == year) {
            /* if the data file is the correct month add to month_rainfall
             array */
            if (records[i].month == j) {
                month_rainfall[j] = records[i].rainfall;
            }
            /* else if month data is missing, the current j element in
             month_rainfall array is zero, the next element in month_rainfall
              is equal to the current element from the data */
            else if (records[i].month != j){
                month_rainfall[j] = 0;
                month_rainfall[j+1] = records[i].rainfall;
                /* increment j again to skip look for the month we have just
                 added */
                j++;

            }
            j++;

        }
    }


    print_graph(year, month_rainfall, mean, stage);
    return;
}


/* prints all elements and structure of the graph require in stage 4 */
void
print_graph(int year, double month_rainfall[], double *mean, int stage) {

    int i, j, scale, max_graph_value;
    double maximum, max_rain = month_rainfall[JAN], max_mean = mean[JAN];

    /* find the maximum rainfall for the given year */
    for (i=JAN; i<=MONTHS; i++) {
        if (month_rainfall[i] > max_rain) {
            max_rain = month_rainfall[i];
        }
        if(mean[i] > max_mean) {
            max_mean = mean[i];
        }
    }

    /* find the maximum of either the rainfall or the mean  */
    maximum = max_rain;
    if (max_rain < max_mean) {
        maximum = max_mean;
    }
    /* call scale function to calculate the graph's scale */
    scale = calc_scale(maximum);

    /* call find_max_graph_value function to calculate the graph's maximum
    scale value */
    max_graph_value = find_max_graph_value(maximum, scale);

    /* print the year selected, maximum rainfall, and the scale */
    printf("S%d, %d max is %.1lf, scale is %d\n", stage, year, max_rain, scale);

    /* now start printing the graph structure in nested for loop */
    for (i=max_graph_value; i>0; i-=scale) {
        /* printing the y axis of the graph */
        printf("%3d | ", i);
        /* for each scale value find which months have a value to be printed */
        for(j=JAN; j<=MONTHS; j++) {
            /* if current month's value holds for v-scale<r<=v */
            if ((month_rainfall[j] > i - scale) && (month_rainfall[j] <= i)) {
                /* if current month's mean value holds for v-scale<r<=v */
                if ((mean[j] > i - scale) && (mean[j] <= i)) {
                    printf("*%02d*", year%100);
                }

                /* if not just print the last two digits of the year */
                else {
                    printf(" %02d ", year%100);
                }
                /* decrease the current month value by the scale factor for the
                next iteration */
                month_rainfall[j] -= scale;
            }
            /* if current month's value doesn't hold for v-scale<r<=v */
            else {
                /* if current month's mean value holds for v-scale<r<=v */
                if ((mean[j] > i - scale) && (mean[j] <= i)) {
                    printf("****");
                }
                /* if current month's rainfall = 0, just print spaces */
                else if (month_rainfall[j] == 0 ) {
                    printf("    ");
                }
                /* else just print the spaces */
                else {
                    printf("    ");
                }
            }
            /* extra space to correctly space out elements in the grapg */
            printf(" ");
        }
        printf("\n");
    }
    /* print the x axis of the graph */
    printf("  0 +-----+----+----+----+----+----+----+----+----+----+"
    "----+----+\n");
    /* print the x axis names of each month */
    for (i=0; i<= MONTHS; i++) {
        printf("%4s ", months[i]);
    }
    return;
}

/* returns the maximum graph value used for the scale on the y axis of
the graph */
int
find_max_graph_value(double maximum, int scale) {
    int max_graph_value, i;


    /* default maximum graph value is set to scale * 24*/
    max_graph_value = scale * MAX_ROWS;

    /* if max_graph_value is less than 24, let the max_graph_value be ceiling
     function of maximum value with scale 1 */
    if (max_graph_value <= MAX_ROWS) {
        max_graph_value = ceil(maximum);
    }

    /* else; find when max_graph_value is the lowest scale value above the
     maximum rainfall */

    else {
        for (i=MAX_ROWS; i>=0; i--) {
            if (maximum < max_graph_value) {
                max_graph_value -= scale;
            }
            else if (maximum > max_graph_value) {
                max_graph_value += scale;
            }
        }

    }
    return max_graph_value;
}

/* returns the scale for the current graph that has called it */
int
calc_scale(double maximum) {
    /* given calculation to find the scale */
    double calculation = maximum / 24;
    /* use ceiling function to always round up decimal to next integer */
    return ceil(calculation);
}

/* Returns the mean of all array elements of input array */
double
mean_rainfall(double rainfallarray[], int count) {
    int i;
    double sum = 0, mean;
    for (i=0; i<count; i++) {
        sum += rainfallarray[i];
    }
    mean = sum/count;
    return mean;
}

/* returns the tau value from input array */
double
compute_tau(double rainfallarray[], int count) {
    int i, j, n, delta = 0;
    double tau, fraction;

    /* set n to count to closely resemble mathematical notation */
    n = count;
    /* given fraction */
    fraction =  (1.0 / (n * (n-1) / 2));

    /* coded version of mathematical notation from assignment specification
    to find monotonic increase/decrease/stay the same */
    for (i=0; i<=n-2; i++) {
        for (j=i+1; j<=n-1; j++) {
            /* find when r_i < r_j */
            if (rainfallarray[i] < rainfallarray[j]) {
                delta += 1.0;
            }
            /* find when r_i > r_j */
            else if (rainfallarray[i] > rainfallarray[j]) {
                delta -= 1.0;
            }
            /*everything else is +0 or in other words do nothing to delta sum*/
        }
    }
    /* finally combine fraction multiplied with delta to compute tau */
    tau = fraction * delta;
    /* return tau... YAY! */
    return tau;
}

/* programming is fun */
