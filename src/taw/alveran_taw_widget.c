#include "alveran_taw_widget.h"



static void
alveran_taw_changed_cb (GtkComboBox *widget,
               gpointer     user_data) 
{

    GtkApplication *app = GTK_APPLICATION(g_application_get_default());

    gint category = gtk_combo_box_get_active (GTK_COMBO_BOX(g_object_get_data(G_OBJECT(app), "taw_category")));
    gint start = gtk_combo_box_get_active (GTK_COMBO_BOX(g_object_get_data(G_OBJECT(app), "taw_start")));
    gint end = gtk_combo_box_get_active (GTK_COMBO_BOX(g_object_get_data(G_OBJECT(app), "taw_end")));

    taw_col_t column = (taw_col_t)category;
	taw_result_t *taw_result = taw_calc(&column, start-4, end-3);

	if(taw_result->complete) 
    {    
        gchar *result = g_strdup_printf("%i AP", taw_result->complete->ap);
        gtk_label_set_text (GTK_LABEL(g_object_get_data(G_OBJECT(app), "taw_result")), result);
		g_free(result);

	}
	
	taw_result_free(&taw_result);

}

GtkWidget * alveran_taw_widget_new() 
{
    GtkBuilder *builder = gtk_builder_new_from_resource ("/de/bug0r/alveran/ui/taw.ui");
    gtk_builder_add_callback_symbol (builder, "alveran_taw_changed_cb", G_CALLBACK(alveran_taw_changed_cb));
    gtk_builder_connect_signals(builder, NULL);
    GtkWidget *taw_widget = GTK_WIDGET(gtk_builder_get_object (builder, "taw_box"));
    GtkContainer *taw_window = GTK_CONTAINER(gtk_builder_get_object (builder, "taw_window"));
    gtk_container_remove(GTK_CONTAINER(taw_window),taw_widget);
    g_object_unref(taw_window);

    GtkApplication *app = GTK_APPLICATION(g_application_get_default());
    g_object_set_data(G_OBJECT(app), "taw_category", GTK_WIDGET(gtk_builder_get_object (builder, "taw_category")));
    g_object_set_data(G_OBJECT(app), "taw_start", GTK_WIDGET(gtk_builder_get_object (builder, "taw_start")));
    g_object_set_data(G_OBJECT(app), "taw_end", GTK_WIDGET(gtk_builder_get_object (builder, "taw_end")));
    g_object_set_data(G_OBJECT(app), "taw_result", GTK_WIDGET(gtk_builder_get_object (builder, "taw_result")));

    return taw_widget;
}