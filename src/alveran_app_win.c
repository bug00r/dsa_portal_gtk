#include "alveran_app_win.h"

struct _AlveranAppWindow
{
    GtkApplicationWindow parent;

    GtkWidget *tool_stack;
    GtkWidget *stack_switch;
};

G_DEFINE_TYPE(AlveranAppWindow, alveran_app_window, GTK_TYPE_APPLICATION_WINDOW);

static GtkStack *
alveran_app_get_stack(GtkWidget *widget) {

    GtkStackSwitcher *stack_switch = (GtkStackSwitcher*)((AlveranAppWindow*)gtk_widget_get_toplevel (widget))->stack_switch;
    GtkStack * stack = gtk_stack_switcher_get_stack (GTK_STACK_SWITCHER(stack_switch));

    return stack;
}  

static void
open_taw_cb (GtkToolButton *toolbutton, gpointer data)
{

    GtkStack *stack = alveran_app_get_stack(GTK_WIDGET(toolbutton));

    if (stack) {
        GtkWidget *taw_widget = GTK_WIDGET(gtk_stack_get_child_by_name(stack,(const gchar*)"taw-calc"));
        g_message("found taw_calc %p", taw_widget);
        if (taw_widget == NULL) {
            GtkWidget *taw_widget = alveran_taw_widget_new();
            gtk_stack_add_titled (stack, taw_widget, (const gchar*)"taw-calc", (const gchar*)"taw-calc");
        }
        gtk_stack_set_visible_child_name(stack, (const gchar*)"taw-calc");
    }

}

static void
open_lexicon_cb (GtkToolButton *toolbutton, gpointer data)
{

    GtkStack *stack = alveran_app_get_stack(GTK_WIDGET(toolbutton));

    if (stack) 
    {
        GtkWidget *lexicon_widget = GTK_WIDGET(gtk_stack_get_child_by_name(stack,(const gchar*)"lexicon"));
        g_message("found taw_calc %p", lexicon_widget);
        if (lexicon_widget == NULL) 
        {
            alveran_lexicon_init_app(GTK_APPLICATION(g_application_get_default()));
            GtkWidget *lexicon_widget = alveran_lexicon_widget_new();
            gtk_stack_add_titled (stack, lexicon_widget, (const gchar*)"lexicon", (const gchar*)"lexicon");
        }
        gtk_stack_set_visible_child_name(stack, (const gchar*)"lexicon");
        alveran_lexicon_widget_init(lexicon_widget);
    }

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
    gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (class), "open_taw_cb", G_CALLBACK(open_taw_cb));
    gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (class), "open_lexicon_cb", G_CALLBACK(open_lexicon_cb));
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), AlveranAppWindow, tool_stack);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), AlveranAppWindow, stack_switch);
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
