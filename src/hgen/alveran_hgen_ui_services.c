#include "alveran_hgen_ui_services.h"

void 
alveran_uis_add_hero_new(GtkWidget *hero_tree_view, dsa_hero_t *new_hero)
{
    GtkListStore *hero_list_store = GTK_LIST_STORE(gtk_tree_view_get_model (GTK_TREE_VIEW(hero_tree_view)));
    
    GtkTreeIter iter;
    gtk_list_store_append(hero_list_store, &iter);
    gtk_list_store_set(hero_list_store, &iter, 
                       0, "New Hero",
                       1, new_hero,
                       -1);
}

void 
alveran_uis_get_tv_selection(GtkWidget *hero_tree_view, a_uis_selection_t *selection)
{
    selection->treeview = GTK_TREE_VIEW(hero_tree_view);
    selection->selction = gtk_tree_view_get_selection(selection->treeview);
    selection->model = gtk_tree_view_get_model (GTK_TREE_VIEW(selection->treeview));
    selection->sel_did = gtk_tree_selection_get_selected(selection->selction, &selection->model, &selection->iter);
}

dsa_hero_t * 
alveran_uis_get_sel_hero(a_uis_selection_t *selection)
{
    dsa_hero_t *found = NULL;
    if(selection->sel_did)
    {
        gtk_tree_model_get(selection->model, &selection->iter, 1, &found, -1);   
    }
    return found;
}

dsa_hero_t* 
alveran_uis_get_sel_hero_direct(GtkTreeView *hero_list)
{
    a_uis_selection_t selection;
    alveran_uis_get_tv_selection(GTK_WIDGET(hero_list), &selection);

    dsa_hero_t * selected_hero = alveran_uis_get_sel_hero(&selection);

    return selected_hero;
}

void
alveran_uis_rem_sel_hero(a_uis_selection_t *selection)
{
    if(selection->sel_did)
    {
        gtk_list_store_remove(GTK_LIST_STORE(selection->model), &selection->iter);
    }
}

int 
alveran_uis_get_yn_modal(const char *message)
{
     GtkDialog *dialog = GTK_DIALOG(gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_MODAL,
                                 GTK_MESSAGE_QUESTION,
                                 GTK_BUTTONS_YES_NO,
                                 message));

    gint result = gtk_dialog_run (GTK_DIALOG (dialog));
    
    gtk_widget_destroy (GTK_WIDGET(dialog));

    return result;
}

void 
alveran_uis_activate_if_not(uint32_t count, ...)
{
    va_list widgets;
	va_start(widgets, count);

    for ( int curWidget = count; curWidget--; )
    {
        GtkWidget *widget = GTK_WIDGET(va_arg(widgets, GtkWidget*));
        if(!gtk_widget_is_sensitive(widget))
        {
            gtk_widget_set_sensitive (widget, TRUE);
        }
    }

    va_end(widgets);
}

void 
alveran_uis_deactivate_if_not(uint32_t count, ...)
{
    va_list widgets;
	va_start(widgets, count);

    for ( int curWidget = count; curWidget--; )
    {
        GtkWidget *widget = GTK_WIDGET(va_arg(widgets, GtkWidget*));
        if(gtk_widget_is_sensitive(widget))
        {
            gtk_widget_set_sensitive (widget, FALSE);
        }
    }

    va_end(widgets);
}

void 
alveran_uis_set_hero_name(a_uis_selection_t *selection, const gchar * new_name)
{
    GtkListStore *hero_list_store = GTK_LIST_STORE(gtk_tree_view_get_model (GTK_TREE_VIEW(selection->treeview)));
    
    gtk_list_store_set(hero_list_store, &selection->iter, 
                       0, new_name,
                       -1);
}

gchar * 
alveran_uis_get_cb_value_copy(GtkComboBox *_comboBox)
{
    GtkComboBox *combo = _comboBox; 
    GtkTreeModel *model = gtk_combo_box_get_model(combo);

    gchar *selected_value = NULL;

    GtkTreeIter iter;
    if (gtk_combo_box_get_active_iter(combo, &iter))
    {
        gtk_tree_model_get(model, &iter, 0, &selected_value, -1);
    }

    return selected_value;
}
