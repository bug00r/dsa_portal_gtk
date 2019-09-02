#include "alveran_lexicon_search.h"

void update_cat_and_group_selections(lexicon_ctx_t *lctx) 
{	
	lexicon_search_selection_t	*lss = lctx->lss;
	GtkWidget* categories = lctx->ctrls.categories;
	GtkWidget* groups = lctx->ctrls.groups;
	
	int selectCategory = gtk_combo_box_get_active(GTK_COMBO_BOX(categories));
	
	lss->categories.selected = 	( selectCategory == 0 ? selectCategory : selectCategory-1 );

	int cnt_files = (selectCategory == 0 ? (int)lctx->xml_result->cnt : 1);
	
	lss->categories.cnt_files = cnt_files;
	
	lss->groups.selected =  gtk_combo_box_get_active(GTK_COMBO_BOX(groups));
	
	#if debug > 0
		g_message("lss->categories.selected: %i\n", lss->categories.selected);
		g_message("lss->categories.cnt_files: %i\n", lss->categories.cnt_files);
		g_message("lss->groups.selected: %i\n", lss->groups.selected );
	#endif
}

void add_node_attrs_to_combo(GtkComboBoxText *handle, xmlXPathObjectPtr xpathObj) 
{
	if ( xpathObj != NULL ) 
	{
		xmlNodeSetPtr nodes = xpathObj->nodesetval;
		int size = (nodes) ? nodes->nodeNr : 0;
		xmlNodePtr cur;
		
		for(int i = 0; i < size; ++i) 
		{
			cur = nodes->nodeTab[i];
			
			xmlChar *attr = xmlGetProp(cur, (const xmlChar*)"name");
			
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(handle), (gchar*)attr);
	
			xmlFree(attr);
		}
	}
}

void add_node_attrs_to_handle(GtkContainer *handle, xmlXPathObjectPtr xpathObj) 
{	
	if ( xpathObj != NULL ) 
	{
		xmlNodeSetPtr nodes = xpathObj->nodesetval;
		int size = (nodes) ? nodes->nodeNr : 0;
		xmlNodePtr cur;
		for(int i = 0; i < size; ++i) 
		{
			cur = nodes->nodeTab[i];
			
			xmlChar *attr = xmlGetProp(cur, (const xmlChar*)"name");

			GtkWidget *entry = gtk_label_new ((gchar*)attr);
			gtk_label_set_xalign (GTK_LABEL(entry), 0.0);
			g_object_set_data(G_OBJECT(entry), "data", (gpointer)cur);
			gtk_widget_show(entry);
			gtk_container_add(handle, entry);
	
			xmlFree(attr);
		}
	}
}

void update_group_list(lexicon_ctx_t *lctx) {

	lexicon_search_selection_t	*lss = lctx->lss;
	GtkWidget* groups = lctx->ctrls.groups;

	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(groups));

	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(groups), "ALL");

	unsigned int file_offset = lss->categories.selected;
	
	int cnt_files = lss->categories.cnt_files;
	if ( file_offset >= 0 ) 
	{
		for( int cur_file = 0; cur_file < cnt_files ; ++cur_file ) 
		{
			xml_ctx_t *xml_ctx = lctx->ctxs[file_offset + cur_file];

			if (xml_ctx == NULL) continue;
			
			xmlXPathObjectPtr xpathObj = xml_ctx_xpath(xml_ctx, "//group");
			
			add_node_attrs_to_combo(GTK_COMBO_BOX_TEXT(groups), xpathObj);

			xmlXPathFreeObject(xpathObj);	
		}
	}
	
	gtk_combo_box_set_active (GTK_COMBO_BOX(groups), 0);
}

void add_node_as_string(GtkWidget *text, xmlNodePtr node) {
	
	GtkTextBuffer * buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(text));
	gtk_text_buffer_set_text(buffer, "", 0);

	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	if (node != NULL) 
	{		
		xmlAttr * attr = node->properties;

		while(attr != NULL) 
		{
			xmlChar *sattr = xmlGetProp(node, attr->name);

			gchar *result = g_strdup_printf("%s:\t\t%s\n", attr->name, sattr);
			gtk_text_buffer_insert (buffer, &iter, result, -1);
			
			g_free(result);
			xmlFree(sattr);
			
			attr = attr->next;		
		}
	} else 
	{
		gtk_text_buffer_insert (buffer, &iter, "ERROR Node is NULL", -1);
	}

}

void update_result_display_by_selection(lexicon_ctx_t *lctx) 
{	
	GtkListBoxRow *row = gtk_list_box_get_selected_row (GTK_LIST_BOX(lctx->ctrls.result_list));

	if (row != NULL) 
	{
		xmlNodePtr curdata = g_object_get_data(G_OBJECT(gtk_bin_get_child (GTK_BIN(row))), "data");
	
		add_node_as_string(lctx->ctrls.result_text, curdata);
	}
}

void refresh_search_result_list(lexicon_ctx_t *lctx) {
	
	lexicon_search_result_selection_t *lsrs = lctx->lsrs;
	GtkContainer *result_list = GTK_CONTAINER(lctx->ctrls.result_list);
	
	GList* list = gtk_container_get_children (result_list);
	for (GList *l = list; l != NULL; l = l->next)
	{
		gtk_container_remove(result_list, GTK_WIDGET(l->data));
	}
	
	for( int cur_file = 0; cur_file < lsrs->cnt_cache ; ++cur_file ) {
		
		xmlXPathObjectPtr xpathObj = lsrs->xpath_result[cur_file];
		
		add_node_attrs_to_handle(result_list, xpathObj);
	
	}
	
	gtk_list_box_select_row (GTK_LIST_BOX(result_list), 
			GTK_LIST_BOX_ROW(g_list_nth_data(gtk_container_get_children (result_list), 0)));

	update_result_display_by_selection(lctx);
}

void search(lexicon_ctx_t *lctx) {

	lexicon_search_selection_t	*lss = lctx->lss;
	
	unsigned int file_offset = lss->categories.selected;
	
	int cnt_files = lss->categories.cnt_files;
	if ( file_offset >= 0 ) 
	{	
		GtkWidget * groups = lctx->ctrls.groups;
		GtkWidget * search_input = lctx->ctrls.search_input;
		
		gchar *selected_group = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(groups));

		const gchar *search_string = gtk_entry_get_text (GTK_ENTRY(search_input));

		lexicon_search_result_selection_t *lsrs =lctx ->lsrs;
		alveran_lexicon_reset_search_result_selection(lsrs);
		lsrs->cnt_cache = cnt_files;
		
		for( int cur_file = 0; cur_file < cnt_files ; ++cur_file ) 
		{
			xml_ctx_t *xml_ctx = lctx->ctxs[file_offset + cur_file];

			if (xml_ctx == NULL) continue;
			
			xmlXPathObjectPtr xpathObj = NULL;

			if ( gtk_combo_box_get_active(GTK_COMBO_BOX(groups)) == 0 ) 
			{
				xpathObj = xml_ctx_xpath_format(xml_ctx, "//group/*[regexmatch(@name,'%s')]", search_string);
			} else 
			{
				xpathObj = xml_ctx_xpath_format(xml_ctx, "//group[@name = '%s']/*[regexmatch(@name,'%s')]", selected_group, search_string);
			}
			
			lsrs->xpath_result[cur_file] = xpathObj;	
		}
	
	}
	
	refresh_search_result_list(lctx);
}


