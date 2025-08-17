
#include <stdio.h>
#include <stdlib.h>

#include "my_sin.h"
#include "my_cos.h"
#include "my_tan.h"

#define PI 3.141592653589793

double deg2rad(double r)
{
  return r * PI / 180.0;
}

int main(int argc, char *argv[])
{
  if( argc != 2 )
    {
      printf("Usage: %s <floating point number\n", argv[0]);
    }
  else
    {
      printf("Sin(%s) = %6.3f\n", argv[1], my_sin(deg2rad(strtod(argv[1], NULL))));
      printf("Cos(%s) = %6.3f\n", argv[1], my_cos(deg2rad(strtod(argv[1], NULL))));
      printf("Tan(%s) = %6.3f\n", argv[1], my_tan(deg2rad(strtod(argv[1], NULL))));
    }

  return 0;
}
