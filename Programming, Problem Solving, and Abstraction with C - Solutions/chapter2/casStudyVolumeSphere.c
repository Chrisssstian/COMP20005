/* Calculates volume of a sphere with user input radius
  By Christian Drozdowicz*/

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(int argc, char const *argv[]) {

  double radius, volume = 0;
  printf("Enter a value in meters for radius: ");
  scanf("%lf", &radius);

  volume = (4.0/3.0)*PI*pow(radius,3);

  printf("When the radius of a sphere is %.2f, the volume is %f\n",radius, volume);


  return 0;
}

//will create roundoff errors as PI is only to 5 decimal places
