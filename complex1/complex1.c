
#include <complex.h>
#include <math.h>
#include <stdio.h>

int maxiteration = 80;

int escape(double complex c)
{
    double complex z = 0;
    double complex z1;
    int i = 0;
    while (i < maxiteration)
    {
        z1 = z*z + c;
        if (cabs(z1) > 2)
            return i;
        z = z1;
        i = i+1;
    }
    return maxiteration;
}

int
main (void)
{
    double minx = -1.0;
    double maxx = 1.0;
    double miny = -1.0;
    double maxy = 1.0;
    double deltax, deltay;
    int subdivisions = 10;
    deltax = (maxx - minx)/subdivisions;
    deltay = (maxy - miny) / subdivisions;
    double complex z = minx + I*miny;
    while (creal(z) <= maxx)
    {
        while (cimag(z) <= maxy)
        {
            printf ("%f + %f * i --> iterations %d\n", creal (z), cimag (z), escape(z));
            z = z + I * deltay;
        }
        z = creal(z) + deltax + I*miny;
    }
    return 0;
}
