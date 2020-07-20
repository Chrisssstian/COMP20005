/*======================================================================
#      Assignment: 2
#     Description: Assignment 2, sem 1, 2019
#            Name: Christian Drozdowicz
#       StudentID: 832391
#        version: 1 finalshit don't work
======================================================================*/

#include <stdio.h>
#include <stdlib.h>

/* provided global variable */
char *months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/* defining types */
typedef struct {
	int month;
	double rainfall;
	char check;
} records_month_t;

typedef struct {
	int station;
	int year;
	records_month_t month[12];
} records_year_t;



/* function prototypes */
int mygetchar(void);
//void stage_1(records_year_t records[], int valid_lines);




int
main(int argc, char *argv[]) {

	int i = 0, k, hcheck, valid_lines = 0;
	records_year_t records[1000];

    /* checks for \r and skips header line of file */
    while ((hcheck = mygetchar()) != EOF) {
        if (hcheck == '\n') {
            break;
        }
    }


    /* read data into arrays */
    while (scanf("IDCJAC0001,%d,%d,", &records[i].station, &records[i].year) == 2) {
		for(k=0; k<records[i].year; k++) {
			scanf(",%d,%lf,%c\n", &records[i].month[k].month, &records[i].month[k].rainfall, &records[i].month[k].check);
		}
        i++;
        valid_lines ++;
    }

    printf("%d ", records[0].month[0].month);

/*
	for(i=0; i< valid_lines; i++) {
		printf("station = %d, year= %d, ",records[i].station, records[i].year);
        for (k=0; k<12; k++) {
            printf("month= %d, rainfall= %lf, check= %c", records[i].month[k].month, records[i].month[k].rainfall, records[i].month[k].check);
        }
        printf("\n");
    }
	printf("valid_lines = %d\n", valid_lines);
*/


    /* Now start stage 1 output */
    //stage_1(records, valid_lines);
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





/*
void
stage_1(records_year_t records[], int valid_lines) {
	printf("S1, site number %d, %d datalines in input\n", records[0].station, valid_lines);

	int i, k;
    printf("%d ", records[0].month[2].month);

	for(i=0; i<valid_lines; i+=12) {
		printf("S1, %d: ", records[i].year);

		for(k=0;k<2;k++) {
			/*if (records[i].month[k].month != k+1) {
				printf(" %d - ", k);
                printf("%d ", records[i].month[k].month);
			}


			else if (records[i].month[k].check == 'N'){
				printf("%s* ", months[k+1]);
			}
			else {
				printf("%s ", months[k+1]);
            }*/
        /*    printf("%d ", records[i].month[k].month);
		}

        printf("\n");

	}
}*/
