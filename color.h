
struct test_color
{
  float r,g,b;
};


#define OKAY 0
#define ERROR -1
#define CMAPENTRIES 80


extern struct test_color colormap[CMAPENTRIES];
void
build_colormap (struct test_color *colormap,
                int colormaplen);

int
interpolate (int element,
             int elem_count,
             struct test_color *output);
