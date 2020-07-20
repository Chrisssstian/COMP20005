/*======================================================================
#      Assignment: 2
#     Description: Assignment 2, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1 final product stage2
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* Definitions */
#define MONTHS 12
#define NO_DATA 0
#define NOT_VALIDATED 'N'

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12



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
/*
typedef struct {
    int month;
    int count;
    int year;
} data_t;*/


/* stage function prototypes */
void stage_2(records_t records[], int valid_lines);

/* function prototypes */
int mygetchar(void);
void check_month(records_t records[], int valid_lines);





/* main program */
int
main(int argc, char *argv[]) {

	int i = 0, hcheck, valid_lines = 0;
	records_t records[2000];

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

void
stage_2(records_t records[], int valid_lines) {

    check_month(records, valid_lines);



}

void
check_month(records_t records[], int valid_lines) {
    int i, k, j, count[12];

    for (i=0; i<12; i++) {
        count[i] = 0;
    }

    for (i=1; i<12; i++) {
        for (j=0; j<valid_lines; j++) {

            if (records[j].month == i) {
                count[i]++;
            }
        }
        printf("S2, %s", months[1]);

        /*for (k=0, j=1; k<valid_lines && j<MONTHS+1; k++, j++) {

            count[j]++;


            if (records[i].month == JAN) {
                printf("%s ", months[JAN]);

                count++;
            }
            else if (records[i].month == FEB) {
                printf("%s ", months[FEB]);
            }
            else if (records[i].month == MAR) {
                printf("%s ", months[MAR]);
            }
            else if (records[i].month == APR) {
                printf("%s ", months[APR]);
            }
            else if (records[i].month == MAY) {
                printf("%s ", months[MAY]);
            }
            else if (records[i].month == JUN) {
                printf("%s ", months[JUN]);
            }
            else if (records[i].month == JUL) {
                printf("%s ", months[JUL]);
            }
            else if (records[i].month == AUG) {
                printf("%s ", months[AUG]);
            }
            else if (records[i].month == SEP) {
                printf("%s ", months[SEP]);
            }
            else if (records[i].month == OCT) {
                printf("%s ", months[OCT]);
            }
            else if (records[i].month == NOV) {
                printf("%s ", months[NOV]);
            }
            else if (records[i].month == DEC) {
                printf("%s ", months[DEC]);
            }
        }*/


        printf("\n");
    }
    for(i=0; i<12; i++) {
        printf("%d ", count[i]);
    }

}
