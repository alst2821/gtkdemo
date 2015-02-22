#ifdef _COLOR_H_

struct rgb_color
{
  float r,g,b;
};


#define OKAY 0
#define ERROR -1
#define CMAPENTRIES 80


extern struct rgb_color colormap[CMAPENTRIES];
void
build_colormap (struct rgb_color *colormap,
                int colormaplen);

int
interpolate (int element,
             int elem_count,
             struct rgb_color *output);
#endif
