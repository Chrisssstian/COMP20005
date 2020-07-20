/* Prints out all INT_MAX,INT_MIN, FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX values
  By Christian Drozdowicz*/

  #include <stdio.h>
  #include <limits.h>
  #include <float.h>


  int
  main(int argc, char const *argv[]) {
    printf("INT_MAX = %d,\n INT_MIN = %d,\n FLT_MIN = %f,\n FLT_MAX = %f,\n DBL_MIN = %f,\n DBL_MAX = %f\n",
    INT_MAX,INT_MIN, FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX );
    return 0;
  }
