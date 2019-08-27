#include "alveran_app_win.h"

struct _AlveranAppWindow
{
    GtkApplicationWindow parent;

    GtkWidget *tool_stack;
    GtkWidget *stack_switch;
};

G_DEFINE_TYPE(AlveranAppWindow, alveran_app_window, GTK_TYPE_APPLICATION_WINDOW);


static void
taw_open_cb (GtkToolButton *toolbutton, gpointer data)
{
    g_message("adding taw bar");
    GtkStackSwitcher *stack_switch = (GtkStackSwitcher*)((AlveranAppWindow*)gtk_widget_get_toplevel (GTK_WIDGET(toolbutton)))->stack_switch;
    GtkStack * stack = gtk_stack_switcher_get_stack (GTK_STACK_SWITCHER(stack_switch));
    
    g_message("switchers stack %p", stack);

    if (stack == NULL) {
        stack = (GtkStack*)((AlveranAppWindow*)gtk_widget_get_toplevel (GTK_WIDGET(toolbutton)))->tool_stack;
        gtk_stack_switcher_set_stack (GTK_STACK_SWITCHER(stack_switch), stack);
    }
    
    g_message("found stack ptr %p",stack);

    if (stack) {
        GtkWidget *taw_window = GTK_WIDGET(gtk_stack_get_child_by_name(stack,(const gchar*)"taw-calc2"));
        g_message("found taw_calc %p", taw_window);
        if (taw_window == NULL) {
            GtkBuilder *builder = gtk_builder_new_from_resource ("/de/bug0r/alveran/ui/taw.ui");
            taw_window = GTK_WIDGET(gtk_builder_get_object (builder, "taw_box"));
            GtkContainer *taw_window_ = GTK_CONTAINER(gtk_builder_get_object (builder, "taw_window"));
            gtk_container_remove(GTK_CONTAINER(taw_window_),taw_window);

            gtk_stack_add_titled (stack, taw_window, (const gchar*)"taw-calc2", (const gchar*)"taw-calc2");
            gtk_widget_show(taw_window);
            g_object_unref(taw_window_);
        }
        gtk_stack_set_visible_child_name(stack, (const gchar*)"taw-calc2");
    }

    

    //todo add private part of application window
    //add application window to application set_object
    //get default app and get stack for adding widget

}

static void
open_taw_cb (GtkToolButton *toolbutton, gpointer data)
{
    g_message("adding taw bar");
    GtkStackSwitcher *stack_switch = (GtkStackSwitcher*)((AlveranAppWindow*)gtk_widget_get_toplevel (GTK_WIDGET(toolbutton)))->stack_switch;
    GtkStack * stack = gtk_stack_switcher_get_stack (GTK_STACK_SWITCHER(stack_switch));
    
    g_message("switchers stack %p", stack);

    if (stack == NULL) {
        stack = (GtkStack*)((AlveranAppWindow*)gtk_widget_get_toplevel (GTK_WIDGET(toolbutton)))->tool_stack;
        gtk_stack_switcher_set_stack (GTK_STACK_SWITCHER(stack_switch), stack);
    }
    
    g_message("found stack ptr %p",stack);

    if (stack) {
        GtkWidget *taw_window = GTK_WIDGET(gtk_stack_get_child_by_name(stack,(const gchar*)"taw-calc"));
        g_message("found taw_calc %p", taw_window);
        if (taw_window == NULL) {
            GtkBuilder *builder = gtk_builder_new_from_resource ("/de/bug0r/alveran/ui/taw.ui");
            taw_window = GTK_WIDGET(gtk_builder_get_object (builder, "taw_box"));
            GtkContainer *taw_window_ = GTK_CONTAINER(gtk_builder_get_object (builder, "taw_window"));
            gtk_container_remove(GTK_CONTAINER(taw_window_),taw_window);
            gtk_stack_add_titled (stack, taw_window, (const gchar*)"taw-calc", (const gchar*)"taw-calc");

            g_object_unref(taw_window_);
        }
        gtk_stack_set_visible_child_name(stack, (const gchar*)"taw-calc");
    }

    

    //todo add private part of application window
    //add application window to application set_object
    //get default app and get stack for adding widget

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
    gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (class), "taw_open_cb", G_CALLBACK(taw_open_cb));
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
