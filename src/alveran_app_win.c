#include "alveran_app_win.h"

struct _AlveranAppWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AlveranAppWindow, alveran_app_window, GTK_TYPE_APPLICATION_WINDOW);

void
test_btn (GtkToolButton *toolbutton, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(g_application_get_default());
    guint32 *number = (guint32*)g_object_get_data(G_OBJECT(app), "number");
    g_message("Acallback test with app: %p with number %i", app, *number);
    *number += 1;
}

void
test2_btn (GtkToolButton *toolbutton, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(g_application_get_default());
    guint32 *number = (guint32*)g_object_get_data(G_OBJECT(app), "number");
    g_message("Acallback test2 with app: %p with number %i", app, *number);
}

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
    gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (class), "test_btn", G_CALLBACK(test_btn));
    gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (class), "test2_btn", G_CALLBACK(test2_btn));

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
