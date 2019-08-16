#include <gtk/gtk.h>

#include "alveran_app.h"

int
main (int    argc,
      char **argv)
{
  return g_application_run(G_APPLICATION(alveran_app_new()), argc, argv);
}
