#include "alveran_app_win.h"

struct _AlveranAppWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AlveranAppWindow, alveran_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
alveran_app_window_init (AlveranAppWindow *win)
{
    g_message("Alveran Main Window init:");
}

static void
alveran_app_window_class_init (AlveranAppWindowClass *class)
{
    g_message("Alveran Main Window Class init:");
}

AlveranAppWindow *
alveran_app_window_new (AlveranApp *app)
{
    return g_object_new (ALVERAN_APP_WINDOW_TYPE, "application", app, NULL);
}

void
alveran_app_window_open (AlveranAppWindow *win, GFile *file)
{
    g_message("Alveran Main Window open:");
}
