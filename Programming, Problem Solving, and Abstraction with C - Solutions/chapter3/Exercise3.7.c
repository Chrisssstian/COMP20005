/* Take Fahrenheit input and converts and returns Celsius equivalent
  By Christian Drozdowicz*/

  #include <stdio.h>
  #include <stdlib.h>

  int
  main() {
    double q, x;
    char u;

    printf("Enter quantity with unit: ");
    if (scanf("%lf%c",&q,&u) != 2){
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }



    if (u == 'F'){
      x = (q - 32) * 5/9;
      printf("Here is your temperature in degrees Celsius: %.2fC\n",x);
    }

    else if (u == 'C'){
      x = (q * 9/5) + 32;
      printf("Here is your temperature in degrees Fahrenheit: %.2fF\n",x);
    }

    else if (u == 'M'){
      x = q * 1.60934;
      printf("Here is your distance from miles to kilometers: %.2fK\n",x);
    }

    else if (u == 'K'){
      x = q / 1.60934;
      printf("Here is your distance from kilometers to miles: %.2fM\n",x);
    }

    else if (u == 'P'){
      x = q * 453.59237;
      printf("Here is your weight from pounds to grams: %.2fG\n",x);
    }

    else if (u == 'G'){
      x = q / 453.59237;
      printf("Here is your weight from pounds to grams: %.2fP\n",x);
    }

    else {
      printf("Invalid input\n");
      exit(EXIT_FAILURE);
    }

    return 0;
  }
