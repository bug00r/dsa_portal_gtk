#include "alveran_app.h"
#include "alveran_app_win.h"


struct _AlveranApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(AlveranApp, alveran_app, GTK_TYPE_APPLICATION);

static void 
alveran_app_init (AlveranApp *app) 
{
    g_message("Alveran App init:");
}

static void
alveran_app_activate (GApplication *app) 
{
    g_message("Alveran App activate:");

    AlveranAppWindow *win = alveran_app_window_new (ALVERAN_APP (app));
    
    gtk_window_present (GTK_WINDOW (win));
}

static void 
alveran_app_open (GApplication *app,
                  GFile       **files,
                  gint          n_files,
                  const gchar  *hint) 
{
    g_message("Alveran APP open:");

    GList *windows = gtk_application_get_windows (GTK_APPLICATION (app));

    AlveranAppWindow *win;
    if(windows)
        win = ALVERAN_APP_WINDOW (windows->data);
    else 
        win = alveran_app_window_new (ALVERAN_APP (app));
    
    for ( int i = 0; i < n_files; i++)
        alveran_app_window_open (win, files[i]);
    
    gtk_window_present (GTK_WINDOW (win));
}

static void
alveran_app_class_init (AlveranAppClass *class)
{
    G_APPLICATION_CLASS (class)->activate = alveran_app_activate;
    G_APPLICATION_CLASS (class)->open = alveran_app_open;
}

AlveranApp *
alveran_app_new (void)
{
    return g_object_new (ALVERAN_APP_TYPE,
                         "application-id", "de.bug0r.alveran",
                         "flags", G_APPLICATION_HANDLES_OPEN,
                         NULL);  
}
