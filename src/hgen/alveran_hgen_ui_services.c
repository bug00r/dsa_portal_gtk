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

static void 
__init_hero_cb_by_xpath_res(GtkComboBoxText *combobox, dsa_hero_t *hero, xmlXPathObjectPtr (*nodefunc)(dsa_hero_t *hero) ) 
{

	if ( combobox != NULL && hero != NULL && nodefunc != NULL ) {

        gtk_combo_box_text_remove_all(combobox);

		xmlXPathObjectPtr _nodes = nodefunc(hero);

		if ( xml_xpath_has_result(_nodes) ) {

			const int maxEntries = _nodes->nodesetval->nodeNr;
			xmlNodePtr *nodes = _nodes->nodesetval->nodeTab;

			for ( int cntentry = 0; cntentry < maxEntries; ++cntentry ) {
				xmlChar *name = xmlGetProp(nodes[cntentry], (xmlChar*)"name");

				gtk_combo_box_text_append_text(combobox, (const gchar*)name);

				xmlFree(name);
			}

		}

		gtk_combo_box_set_active (GTK_COMBO_BOX (combobox), 0);
		
		xmlXPathFreeObject(_nodes);
	}

}

void 
alveran_uis_init_hair_colors(GtkWidget* haircol, dsa_hero_t *hero)
{
    __init_hero_cb_by_xpath_res(GTK_COMBO_BOX_TEXT(haircol), hero, dsa_heros_get_hair_colors);
}

void 
alveran_uis_init_eye_colors(GtkWidget* eyecol, dsa_hero_t *hero)
{
    __init_hero_cb_by_xpath_res(GTK_COMBO_BOX_TEXT(eyecol), hero, dsa_heros_get_eye_colors);
}

void 
alveran_uis_init_height_limits(GtkWidget *heights, dsa_hero_t *hero)
{
    GtkSpinButton *spin = GTK_SPIN_BUTTON(heights);

    int height_min = dsa_heros_get_height_min(hero);

    char * new_height = format_string_new("%i",height_min);
    dsa_heros_set_height_weight_by_value(hero, (const unsigned char*)new_height);
    free(new_height);

    //the +1 is for increasement with outer bound included.
    gtk_spin_button_set_range(spin,(gdouble)height_min, 
                               (gdouble)(dsa_heros_get_height_max(hero) + 1));
    gtk_spin_button_set_value(spin, (gdouble)height_min);
}

void 
alveran_uis_combobox_search_and_set_active(GtkComboBox *combobox, const gchar *search_value)
{
    GtkTreeModel *model = GTK_TREE_MODEL(gtk_combo_box_get_model(combobox));
    GtkTreeIter iter;
    GValue temp = G_VALUE_INIT;
    if(gtk_tree_model_get_iter_first(model, &iter))
    {
        do 
        {
            gtk_tree_model_get_value (model, &iter, 0, &temp);

            const gchar* temp_val = g_value_get_string(&temp);

            int equals = g_strcmp0 (temp_val, search_value);

            if (equals==0) {
                gtk_combo_box_set_active_iter (combobox, &iter);
                break;
            }

            g_value_unset (&temp);

        } 
        while (gtk_tree_model_iter_next (model, &iter));
    }
}