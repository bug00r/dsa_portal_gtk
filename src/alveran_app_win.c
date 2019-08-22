#include "alveran_app_win.h"

struct _AlveranAppWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AlveranAppWindow, alveran_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{
  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
  if (GTK_IS_CONTAINER (widget))
    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
}

static void
alveran_app_window_init (AlveranAppWindow *win)
{
    g_message("Alveran Main Window init:");
    gtk_widget_init_template(GTK_WIDGET (win));
    
    GtkStyleProvider *provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
    gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER (provider), "/de/bug0r/alveran/css/default.css");

    apply_css (GTK_WIDGET(win), provider);
}

static void
alveran_app_window_class_init (AlveranAppWindowClass *class)
{
    g_message("Alveran Main Window Class init:");

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),"/de/bug0r/alveran/ui/window.ui");
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
