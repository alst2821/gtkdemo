#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "color.h"

struct rgb_color cc[] = {
  {    0 ,    0 ,   1 },        /* 4 */
  {    0 ,    1 ,   1 },        /* 3 */
  {    1 ,    1 ,   0 },        /* 2 */
  {    1 ,    0 ,   0 },        /* 1 */
  };

struct rgb_color colormap[CMAPENTRIES];

#ifdef COLOR
int
main (int   argc,
      char *argv[])
{

    build_colormap (colormap, CMAPENTRIES);
    /* for (i = 0; i < CMAPENTRIES; i++) */
    /* { */
    /*     struct rgb_color *c = &colormap[i]; */
    /* } */
    return 0;
}
#endif


/* 
   interpolate between entries in cc base color map 
   RETURNS 0 if okay, -1 on error
*/
int
interpolate (int element,
             int elem_count,
             struct rgb_color *output)
{
    int top, bottom;
    float delta;
    
    int maxindex = sizeof(cc)/sizeof(cc[0]) - 1;
    float x = (float) element / (elem_count - 1);
    
    if ( (element < 0) || (element > elem_count))
    {
        return ERROR;
    }
    top = (int) ceilf(x*maxindex);
    bottom = (int) floorf(x*maxindex);
    delta = x * maxindex - bottom;

    struct rgb_color *tt = &cc[(int)top];
    struct rgb_color *bb = &cc[(int)bottom];
    output->r = bb->r + (tt->r - bb->r) * delta;
    output->g = bb->g + (tt->g - bb->g) * delta;
    output->b = bb->b + (tt->b - bb->b) * delta;
#ifdef DEBUG_INTERPOLATION
    printf("delta %f "
           "top %f %f %f, "
           "bottom %f %f %f, "
           "interpolate %f %f %f\n",
           delta,
           tt->r, tt->g, tt->b,
           bb->r, bb->g, bb->b,
           output->r, output->g, output->b
        );
#endif   
    return OKAY;
}

void
build_colormap (struct rgb_color *colormap,
                int colormaplen)
{
    int i;
    for (i=0; i<colormaplen; i++)
    {
        assert (interpolate(i, colormaplen, &colormap[i]) == OKAY);
    }
}

