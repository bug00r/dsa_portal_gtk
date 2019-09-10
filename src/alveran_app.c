#include "alveran_app.h"
#include "alveran_app_win.h"


struct _AlveranApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(AlveranApp, alveran_app, GTK_TYPE_APPLICATION);

static void
quit_cb (GSimpleAction *action,
         GVariant      *parameter,
         gpointer       user_data)
{
  g_message("quit app:");
  g_application_quit(user_data);
}

const GActionEntry app_actions[] = {
  { "quit", quit_cb }
};

static void
alveran_app_activate (GApplication *app,
                      gpointer      user_data) 
{
    g_message("Alveran App activate:");

    AlveranAppWindow *win = alveran_app_window_new (ALVERAN_APP (app));
    
    gtk_window_present (GTK_WINDOW (win));
}

static void 
alveran_app_open (GApplication *app,
                  GFile       **files,
                  gint          n_files,
                  const gchar  *hint,
                  gpointer      user_data) 
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
alveran_app_shutdown(GApplication *application,
                     gpointer      user_data) {
    g_message("Alveran APP shutdown:");

    alveran_lexicon_remove_from_app(GTK_APPLICATION(application));
    alveran_hgen_remove_from_app(GTK_APPLICATION(application));
}


static void 
alveran_app_init (AlveranApp *app) 
{
    g_message("Alveran App init:");
    g_action_map_add_action_entries (G_ACTION_MAP (app), app_actions, G_N_ELEMENTS (app_actions), app);

    g_signal_connect (app, "shutdown", G_CALLBACK (alveran_app_shutdown), NULL);
    g_signal_connect (app, "open", G_CALLBACK (alveran_app_open), NULL);
    g_signal_connect (app, "activate", G_CALLBACK (alveran_app_activate), NULL);

    guint32 *anumber = g_malloc(sizeof(guint32));
    *anumber = (guint32)666;
    g_object_set_data(G_OBJECT(app), "number", anumber);
}

static void
alveran_app_class_init (AlveranAppClass *class)
{
    //G_APPLICATION_CLASS (class)->activate = alveran_app_activate;
    //G_APPLICATION_CLASS (class)->open = alveran_app_open;
}

AlveranApp *
alveran_app_new (void)
{
    return g_object_new (ALVERAN_APP_TYPE,
                         "application-id", "de.bug0r.alveran",
                         "flags", G_APPLICATION_HANDLES_OPEN,
                         NULL);  
}
