#include <gtk/gtk.h>

static GtkWidget *window = NULL;
/* Pixmap for scribble area, to store current scribbles */
static cairo_surface_t *surface = NULL;

struct test_color
{
  float r,g,b;
};

struct test_color cc[] = {
  {    0 ,    0 ,   0 },
  {  0.5 ,  0.5 ,   0 },
  {  0.5 ,    0 ,  .5 },
  {    1 ,    0 ,   0 },
  {    0 ,  0.5 ,  .5 },
  {    0 ,    1 ,   0 },
  {    0 ,    0 ,   1 },
  { 0.33 , 0.33 , .33 },
  { 0.66 , 0.66 , .66 },
  {    1 ,    1 ,   0 },
  {    1 ,    0 ,   1 },
  {    1 ,  0.5 ,  .5 },
  {    0 ,    1 ,   1 },
  {   .5 ,    1 ,  .5 },
  {   .5 ,  0.5 ,   1 },
  {    1 ,    1 ,   1 }
  };

static gboolean
checkerboard_draw (GtkWidget *da,
                   cairo_t   *cr,
                   gpointer   data)
{
  gint i, j, xcount, width, height;
  gint colour_count = sizeof(cc)/sizeof(cc[0]);
#define CHECK_SIZE 10
#define SPACING 2

  /* At the start of a draw handler, a clip region has been set on
   * the Cairo context, and the contents have been cleared to the
   * widget's background color. The docs for
   * gdk_window_begin_paint_region() give more details on how this
   * works.
   */

  xcount = 0;
  width = gtk_widget_get_allocated_width (da);
  height = gtk_widget_get_allocated_height (da);
  i = SPACING;
  while (i < width)
    {
      j = SPACING;
      while (j < height)
        {
          cairo_set_source_rgb (cr, cc[xcount].r, cc[xcount].g, cc[xcount].b);

          /* If we're outside the clip, this will do nothing.
           */
          cairo_rectangle (cr, i, j, CHECK_SIZE, CHECK_SIZE);
          cairo_fill (cr);

          j += CHECK_SIZE + SPACING;
          ++xcount;
          if (xcount > colour_count)
            xcount = 0;
        }

      i += CHECK_SIZE + SPACING;
      ++xcount;
      if (xcount > colour_count)
        xcount = 0;
    }

  /* return TRUE because we've handled this event, so no
   * further processing is required.
   */
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
  GtkWidget *label;

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
       * Create the checkerboard area
       */

      label = gtk_label_new (NULL);
      gtk_label_set_markup (GTK_LABEL (label),
                            "<u>Checkerboard pattern</u>");
      gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

      frame = gtk_frame_new (NULL);
      gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
      gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);

      da = gtk_drawing_area_new ();
      /* set a minimum size */
      gtk_widget_set_size_request (da, 100, 100);

      gtk_container_add (GTK_CONTAINER (frame), da);

      g_signal_connect (da, "draw",
                        G_CALLBACK (checkerboard_draw), NULL);
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

  /* This is called in all GTK applications. Arguments are parsed
   * from the command line and are returned to the application.
   */
  gtk_init (&argc, &argv);

  window = do_drawingarea();
  gtk_widget_show (window);
  gtk_main ();

  return 0;
}
