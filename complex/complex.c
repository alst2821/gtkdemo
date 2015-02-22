/* check that exp(i * pi) == -1 */
#include <math.h>		/* for atan */
#include <stdio.h>
#include <complex.h>

int
main (void)
{
  double pi = 4 * atan (1.0);
  double complex z = cexp (I * pi);
  printf ("%f + %f * i\n", creal (z), cimag (z));
  double complex y = z * z;
  printf ("%f + %f * i\n", creal (y), cimag (y));
  return 0;
}
