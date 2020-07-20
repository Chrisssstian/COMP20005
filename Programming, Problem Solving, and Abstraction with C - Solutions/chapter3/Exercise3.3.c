/* takes a,b,c input and writes roots of equation ax^2+bx+c=0
  By Christian Drozdowicz*/

  #include <stdio.h>
  #include <math.h>


  int
  main(int argc, char const *argv[]) {
    float a,b,c,discriminant,root;
    printf("please enter a value for a: ");
    scanf("%f",&a);
    printf("please enter a value for b: ");
    scanf("%f",&b);
    printf("please enter a value for c: ");
    scanf("%f",&c);

    discriminant = pow(b,2)-4*a*c;
    printf("the discriminant is: %.2f\n",discriminant);

/* remove case where x would no longer be in equation */
    if (a == 0 && b == 0) {
      printf("Invalid input for finding roots\n");
    }

/* special case where a is zero */
    else if (a == 0){
      root = - c / b;
      printf("This is a special case where a=0 thus root is: %.2f\n",root);
    }
/* discriminant is less than zero case */
    else if (discriminant < 0) {
      printf("There are no real roots\n");
    }

/* discriminant is equal to zero */
    else if (discriminant == 0) {
      /* special case where b and c are equal to zero */
      if (b == 0 && c == 0){
        root = 0;
      }
      else {
        root = -b / 2*a;
      }
      printf("There is one real root: %.2f\n",root);
    }
/* discriminant is greater than zero */
    else if (discriminant > 0) {
      float root1, root2;
      root1 = (-b + sqrt(discriminant))/ 2*a;
      root2 = (-b - sqrt(discriminant)) / 2*a;
      printf("There are two real roots: %.2f, %.2f\n",root1,root2);
    }




    return 0;
  }
