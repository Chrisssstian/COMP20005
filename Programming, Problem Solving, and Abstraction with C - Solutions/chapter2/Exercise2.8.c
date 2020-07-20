/* Take Fahrenheit input and converts and returns Celsius equivalent
  By Christian Drozdowicz*/

  #include <stdio.h>


  int
  main() {
    float t, x;

    printf("Type a temperature in degrees Fahrenheit: ");
    scanf("%f",&t);

    x = (t - 32) * 5/9;

    printf("Here is your temperature in degrees Celsius: %.2f\n",x);



    return 0;
  }
