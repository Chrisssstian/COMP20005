/*======================================================================
#      Assignment: 2
#     Description: Assignment 2, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 3 final product stage1
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* Definitions */
#define MAX_DATA 3000 /* max 250 years * 12 months = 3000 */
#define MONTHS 12
#define NO_DATA 0
#define NOT_VALIDATED 'N'


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

/* function prototypes */
int mygetchar(void);




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

            /* not being used for sample inputs but i feel this is needed for not breaking my program */
            /*else if (records[k].month != j && records[k].month < j) {
                printf("... %d %d ", records[k].month, j);
                k++;
            }*/

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
