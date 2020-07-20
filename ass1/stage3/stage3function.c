void
stage_3(int valid_lines, double dist[], double ran[], double batt_out[], double batt_ret[], double time[], double trip_batt[]) {
    optimise(valid_lines,trip_batt);

    return;
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

void
optimise(int valid_lines, double trip_batt[]) {
    int i, j, x;
    for (i=0;i<valid_lines;i++) {
            for (j=i-1; j>=0 && trip_batt[j] + trip_batt[j+1] > 100;j--) {
                int_swap(&trip_batt[j], &trip_batt[j+1])
            }

    }
    /* for loop to show after elements after sorting */
    for(x=0;x<valid_lines;x++) {
      if(x == 0) {
        printf("after:  trip_batt[%d] = %lf\n ", x, trip_batt[x]);
      }
      else {
        printf("%4d ", A[x]);
      }
    }
    printf("\n");
}

/* page 94 figure 6.7 int_swap defintion*/
void
int_swap(int *x, int *y) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}
