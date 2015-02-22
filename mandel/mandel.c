#include <gtk/gtk.h>
#include <math.h>
#include <assert.h>
#include <complex.h>

#include "color.h"


static GtkWidget *window = NULL;
/* Pixmap for scribble area, to store current scribbles */
static cairo_surface_t *surface = NULL;

int maxiteration = CMAPENTRIES-1;

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


void
set_color (cairo_t *cr,
           int x, int y, int w, int h)
{
    double minx = -1.0;
    double maxx = 1.0;
    double miny = -1.0;
    double maxy = 1.0;
    double xx, yy;
    xx = minx + (maxx-minx) * ((float)x/w);
    yy = miny+ (maxy - miny) * ((float)y/h);
    double complex z = xx + I * yy;
    int index = escape(z);
    cairo_set_source_rgb(cr, colormap[index].r,
          colormap[index].g,
          colormap[index].b);
}

static gboolean
mandel_draw (GtkWidget *da,
                   cairo_t   *cr,
                   gpointer   data)
{
#define CHECK_SIZE 2
  gint width, height;
  width = gtk_widget_get_allocated_width (da);
  height = gtk_widget_get_allocated_height (da);
  int x, y;
  for (x = 0; x < width; x += CHECK_SIZE)
  {
      for (y=0; y < height; y += CHECK_SIZE)
      {
          set_color(cr, x,y,width,height);
          cairo_rectangle (cr, x, y, CHECK_SIZE, CHECK_SIZE);
          cairo_fill (cr);
      }
  }
  return TRUE;
}

static void
close_window (void)
{
  window = NULL;

  if (surface)
    cairo_surface_destroy (surface);
  surface = NULL;
  gtk_main_quit ();
}

GtkWidget *
do_drawingarea (void)
{
  GtkWidget *frame;
  GtkWidget *vbox;
  GtkWidget *da;

  if (!window)
    {
      window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      /* gtk_window_set_screen (GTK_WINDOW (window), */
      /*                        gtk_widget_get_screen (do_widget)); */
      gtk_window_set_title (GTK_WINDOW (window), "Drawing Area");

      g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

      gtk_container_set_border_width (GTK_CONTAINER (window), 8);

      vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
      gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
      gtk_container_add (GTK_CONTAINER (window), vbox);

      /*
       * Create the draw area
       */

      frame = gtk_frame_new (NULL);
      gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
      gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

      da = gtk_drawing_area_new ();
      /* set a minimum size */
      gtk_widget_set_size_request (da, 100, 100);

      gtk_container_add (GTK_CONTAINER (frame), da);

      g_signal_connect (da, "draw",
                        G_CALLBACK (mandel_draw), NULL);
    }

  if (!gtk_widget_get_visible (window))
    gtk_widget_show_all (window);
  else
    gtk_widget_destroy (window);

  return window;
}

int
main (int   argc,
      char *argv[])
{
  /* GtkWidget is the storage type for widgets */
  GtkWidget *window;
  
  build_colormap (colormap, CMAPENTRIES);
  
  /* This is called in all GTK applications. Arguments are parsed
   * from the command line and are returned to the application.
   */
  gtk_init (&argc, &argv);

  window = do_drawingarea();
  gtk_widget_show (window);
  gtk_main ();

  return 0;
}
