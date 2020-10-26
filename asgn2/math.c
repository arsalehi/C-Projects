#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define EPSILON 1e-10
#define OPTIONS "sctea"

double Sin(void);
double Cos(void);
double Tan(void);
double Exp(void);

int main(int argc, char **argv) {

  int op = 0;
  op = getopt(argc, argv, OPTIONS);

  // Did not use a getopt() loop here so that it only processes first input
  // This way it is mutually exclusive
  switch (op) {
  case 's':
    Sin();
    break;
  case 'c':
    Cos();
    break;
  case 't':
    Tan();
    break;
  case 'e':
    Exp();
    break;
  case 'a':
    Sin();
    Cos();
    Tan();
    Exp();
    break;
  default:
    printf("Must include an argument: - (sctea)\n");
    break;
  }

  return 0;
}

double Sin(void) {

  // Print Header
  printf("x\t Sin\t\t Library \t Difference\n");
  printf("-\t ---\t\t ------- \t ----------\n");

  // Initialize Parts
  double sin_x = 0;
  double num = 0;
  double den = 0;
  double x_squared = 0;
  double x_norm = 0;

  // Loop through domain
  for (double x = -2 * M_PI; x < 2 * M_PI; x += (M_PI / 16)) {

    // Normalize so that function runs values between -pi and pi (Most accurate)
    x_norm = fmod(x, 2 * M_PI);

    if (x_norm < (-1 * M_PI)) {
      x_norm += (2 * M_PI);
    } else if (x_norm > M_PI) {
      x_norm -= (2 * M_PI);
    }

    x_squared = x_norm * x_norm;

    // Perform Padé approximation
    num =
        x_norm * ((x_squared * (52785432 - (479249 * x_squared)) - 1640635920) *
                      x_squared +
                  11511339840);
    den = (((18361 * x_squared + 3177720) * x_squared + 277920720) * x_squared +
           11511339840);
    sin_x = num / den;

    // Print output
    // printf("% 6.4lf \t% 10.8lf \t% 10.8lf \t% 12.10lf\n", x, sin_x, sin(x),
    // sin(x) - sin_x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, sin_x, sin(x),
           sin_x - sin(x));
  }

  return 0;
}

double Cos(void) {

  // Print Header
  printf("x\t Cos\t\t Library \t Difference\n");
  printf("-\t ---\t\t ------- \t ----------\n");

  // Initialize Values
  double cos_x = 0;
  double num = 0;
  double den = 0;
  double x_squared = 0;
  double x_norm = 0;

  // Loop through domain
  for (double x = -2 * M_PI; x < 2 * M_PI; x += (M_PI / 16)) {

    // Normalize so that function runs values between -pi and pi (Most accurate)
    x_norm = fmod(x, 2 * M_PI);

    if (x_norm < (-1 * M_PI)) {
      x_norm += (2 * M_PI);
    } else if (x_norm > M_PI) {
      x_norm -= (2 * M_PI);
    }

    x_squared = x_norm * x_norm;

    // Perfom Padé approximation
    num = ((x_squared * (1075032 - 14615 * x_squared) - 18471600) * x_squared +
           39251520);
    den = (((127 * x_squared + 16632) * x_squared + 1154160) * x_squared +
           39251520);
    cos_x = num / den;

    // Print output
    // printf("% 6.4lf \t% 10.8lf \t% 10.8lf \t% 12.10lf\n", x, cos_x, cos(x),
    // cos(x) - cos_x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, cos_x, cos(x),
           cos_x - cos(x));
  }

  return 0;
}

double Tan(void) {
  // Print Header
  printf("x\t Tan\t\t Library \t Difference\n");
  printf("-\t ---\t\t ------- \t ----------\n");

  // Initialize Values
  double tan_x = 0;
  double num = 0;
  double den = 0;
  double x_squared = 0;

  // Loop through domain
  for (double x = (M_PI / -3); x < (M_PI / 3); x += (M_PI / 16)) {

    x_squared = x * x;

    // Perform Padé approximation
    num =
        x * ((((x_squared - 990) * x_squared + 135135) * x_squared - 4729725) *
                 x_squared +
             34459425);
    den = 45 * ((((x_squared - 308) * x_squared + 21021) * x_squared - 360360) *
                    x_squared +
                765765);
    tan_x = num / den;

    // Print output
    // printf("% 6.4lf \t% 10.8lf \t% 10.8lf \t% 12.10lf\n", x, tan_x, tan(x),
    // tan(x) - tan_x);
    printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, tan_x, tan(x),
           tan(x) - tan_x);
  }

  return 0;
}

double Exp(void) {

  // Print Header
  printf("x\t Exp\t\t Library \t Difference\n");
  printf("-\t ---\t\t ------- \t ----------\n");

  // Loop through domain x from 0 --> 9
  for (long double x = 0; x < 9.1; x += 0.1) {

    long double prev = 1.0; // Imitates (x^n-1)/(n-1)!
    long double sum = prev; // Starts as prev, then increments as prev * x/n is
                            // added to form (x^n)/n!

    // Run Taylor approximation until prev converges/ becomes smaller than
    // Epsilon (1e-9)
    for (long double n = 1.0; fabsl(prev) > EPSILON; n += 1.0) {
      prev = x / n * prev;
      sum += prev;
    }

    // Print output
    // printf("% 6.4Lf \t% 10.8Lf \t% 10.8lf \t% 12.10Lf\n", x, sum, exp(x),
    // exp(x) - sum);
    printf("% 6.4Lf\t% 10.8Lf\t% 10.8lf\t% 12.10Lf\n", x, sum, exp(x),
           sum - exp(x));
  }

  return 0;
}
