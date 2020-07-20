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
void stage_1(records_t records[], int valid_lines);
void stage_2(records_t records[], int valid_lines);
void stage_3(records_t records[], int valid_lines);

/* function prototypes */
int mygetchar(void);
void check_month(records_t records[], int valid_lines, int stage);
double median_rainfall(double rainfallarray[], int count);
void print_stage(double rainfallarray[], int i, int count, int start_year,
	 	int end_year, int stage);
double compute_tau(double rainfallarray[], int count);


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
    stage_1(records, valid_lines);
    printf("\n");
		/* Now start stage 2 output */
    stage_2(records, valid_lines);
    printf("\n");
		/* Now start stage 3 output */
    stage_3(records, valid_lines);
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
stage_2(records_t records[], int valid_lines) {
    check_month(records, valid_lines, STAGE_2);
    return;
}

/* stage 3 format */
void
stage_3(records_t records[], int valid_lines) {
    check_month(records, valid_lines, STAGE_3);
    return;
}

/* This function does all the work for stage 2 and stage 3; checks and combines
 by each month and puts all information together for outputs of stage 2 and
 stage 3 */
void
check_month(records_t records[], int valid_lines, int stage) {
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
        print_stage(rainfallarray, i, count[i], start_year, end_year, stage);
    }
    return;
}

void
print_stage(double rainfallarray[], int i, int count, int start_year,
	 	int end_year, int stage) {
    double med_calc, tau;

    if (stage == STAGE_2) {
        /* check if count has at least one item */
        if (count !=0 ) {
            med_calc = median_rainfall(rainfallarray, count);
            printf("S%d, %s, %2d values, %4d-%4d, mean of %5.1lfmm\n", STAGE_2,
                months[i], count, start_year, end_year, med_calc);
        }
        else {
            printf("S%d, %s, %2d values\n", STAGE_2, months[i], count);
        }
    }

    else if (stage == STAGE_3) {
        /* check if count has at least two items */
        if (count != 0 && count != 1) {
            tau = compute_tau(rainfallarray, count);
            printf("S%d, %s, %2d values, %4d-%4d, tau of %5.2lf\n", STAGE_3,
                months[i], count, start_year, end_year, tau);

        }
        /* everything else just report the month with the value */
        else {
            printf("S%d, %s, %2d values\n", STAGE_3, months[i], count);
        }
    }
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

/* returns the tau value from input array */
double
compute_tau(double rainfallarray[], int count) {
    int i, j, n, delta = 0;
    double tau, fraction;

    /* set n to count to closely resemble mathematical notation */
    n = count;
    /* given fraction */
    fraction =  (1.0 / (n * (n-1) / 2));

    /* coded version of mathematical notation of the:
        sum from i=0 to i = n-2
            of the sum from j=i+1 to j = n-1
                of delta(r_i, r_j)
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
