#ifndef ALVERAN_APP_WIN_H
#define ALVERAN_APP_WIN_H

#include <gtk/gtk.h>

#include "alveran_app.h"
#include "gtk_resource.h"

#include "alveran_taw_widget.h"

#define ALVERAN_APP_WINDOW_TYPE (alveran_app_window_get_type ())
G_DECLARE_FINAL_TYPE (AlveranAppWindow, alveran_app_window, ALVERAN, APP_WINDOW, GtkApplicationWindow)

AlveranAppWindow *alveran_app_window_new (AlveranApp *app);
void              alveran_app_window_open(AlveranAppWindow *win,
                                          GFile            *file);

#endif