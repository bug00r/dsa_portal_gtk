#include "alveran_lexicon_search.h"

void update_cat_and_group_selections(lexicon_ctx_t *lctx) {
	
	lexicon_search_selection_t	*lss = lctx->lss;
	GtkWidget* categories = lctx->ctrls.categories;
	GtkWidget* groups = lctx->ctrls.groups;
	
	//IupGetInt(categories, "VALUE");
	int selectCategory = gtk_combo_box_get_active(GTK_COMBO_BOX(categories));
	
	//lss->categories.selected = ( selectCategory == 1 ? selectCategory-1 : selectCategory-2 );
	lss->categories.selected = 	( selectCategory == 0 ? selectCategory : selectCategory-1 );

	int cnt_files = (selectCategory == 0 ? (int)lctx->xml_result->cnt : 1);
	
	lss->categories.cnt_files = cnt_files;
	
	lss->groups.selected =  gtk_combo_box_get_active(GTK_COMBO_BOX(groups));
	
	
	g_message("lss->categories.selected: %i\n", lss->categories.selected);
	g_message("lss->categories.cnt_files: %i\n", lss->categories.cnt_files);
	g_message("lss->groups.selected: %i\n", lss->groups.selected );

}

void add_node_attrs_to_combo(GtkComboBoxText *handle, xmlXPathObjectPtr xpathObj) {
	if ( xpathObj != NULL ) {
		xmlNodeSetPtr nodes = xpathObj->nodesetval;
		int size = (nodes) ? nodes->nodeNr : 0;
		xmlNodePtr cur;
		for(int i = 0; i < size; ++i) {
			cur = nodes->nodeTab[i];
			
			xmlChar *attr = xmlGetProp(cur, (const xmlChar*)"name");
			
			//IupSetStrAttribute(handle, "APPENDITEM", attr);
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(handle), (gchar*)attr);
	
			xmlFree(attr);
		}
	}
}

void add_node_attrs_to_handle(GtkContainer *handle, xmlXPathObjectPtr xpathObj) {
	if ( xpathObj != NULL ) {
		xmlNodeSetPtr nodes = xpathObj->nodesetval;
		int size = (nodes) ? nodes->nodeNr : 0;
		xmlNodePtr cur;
		for(int i = 0; i < size; ++i) {
			cur = nodes->nodeTab[i];
			
			xmlChar *attr = xmlGetProp(cur, (const xmlChar*)"name");
			//IupSetStrAttribute(handle, "APPENDITEM", attr);

			GtkWidget *entry = gtk_label_new ((gchar*)attr);
			gtk_widget_show(entry);
			gtk_container_add(handle, entry);
	
			xmlFree(attr);
		}
	}
}

void update_group_list(lexicon_ctx_t *lctx) {

	lexicon_search_selection_t	*lss = lctx->lss;
	GtkWidget* groups = lctx->ctrls.groups;

	//IupSetAttribute(groups, "REMOVEITEM", "ALL");
	gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(groups));
	//IupSetAttribute(groups, "APPENDITEM", "ALL");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(groups), "ALL");

	//resource_search_result_t *result = lctx->xml_result;
	unsigned int file_offset = lss->categories.selected;
	
	int cnt_files = lss->categories.cnt_files;
	if ( file_offset >= 0 ) {
	
		for( int cur_file = 0; cur_file < cnt_files ; ++cur_file ) {
	
			xml_ctx_t *xml_ctx = lctx->ctxs[file_offset + cur_file];

			if (xml_ctx == NULL) continue;
			
			xmlXPathObjectPtr xpathObj = xml_ctx_xpath(xml_ctx, "//group");
			
			add_node_attrs_to_combo(GTK_CONTAINER(groups), xpathObj);

			xmlXPathFreeObject(xpathObj);
			
		}
	
	}
	
	//IupSetAttribute(groups, "VALUE", "1");
	gtk_combo_box_set_active (GTK_COMBO_BOX(groups), 0);
}

void add_node_as_string(GtkWidget *text, xmlNodePtr node) {
	
	//IupSetAttribute(text, "VALUE", "");
	GtkTextBuffer * buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(text));
	gtk_text_buffer_set_text(buffer, "", 0);
	xmlAttr * attr = node->properties;

	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
	while(attr != NULL) {
		xmlChar *sattr = xmlGetProp(node, attr->name);
		//IupSetStrf(text, "APPEND", "%s:\t\t%s", attr->name, sattr);
		gchar *result = g_strdup_printf("%s:\t\t%s", attr->name, sattr);
		gtk_text_buffer_insert (buffer, &iter, result, -1);
		
		g_free(result);
		xmlFree(sattr);
		
		attr = attr->next;		
	}
}

void update_result_display(lexicon_ctx_t *lctx, int sel_list_idx) {

	g_message("----- sel result idx: %i\n", sel_list_idx);

	if ( sel_list_idx >= 0 ) {
	
		lexicon_search_result_selection_t *lsrs = lctx->lsrs;
		
		xmlXPathObjectPtr *result = lsrs->xpath_result;
		
		int cnt_global_cache = 0;
		
		for ( unsigned int cnt_cache = 0; cnt_cache < lsrs->cnt_cache; ++cnt_cache) {
		
			xmlXPathObjectPtr cur_result = result[cnt_cache];
			
			g_message("check result cache %p %i\n", cur_result, cnt_cache);
			
			if ( cur_result != NULL ) {
				xmlNodeSetPtr nodes = cur_result->nodesetval;
				int size = (nodes) ? nodes->nodeNr : 0;
				
				g_message("cache exist with %i entries\n", size);
				
				if ( size > 0 ) {
					
					g_message("global cache change %i => %i \n", cnt_global_cache, cnt_global_cache + size);
					
					cnt_global_cache += size;
				
					if ( sel_list_idx <= cnt_global_cache ) {
					
						g_message("selected item is inside current cache %i < %i\n", sel_list_idx, cnt_global_cache);
					
						int cur_cache_index = sel_list_idx - (cnt_global_cache - size) - 1;
						
						g_message("selected item cache index %i = %i - %i - 1\n", cur_cache_index, cnt_global_cache, sel_list_idx);
						
						add_node_as_string(lctx->ctrls.result_text, nodes->nodeTab[cur_cache_index]);
						
						break;
					}
				}
			
			}
			
		}
		
	}
}

void refresh_search_result_list(lexicon_ctx_t *lctx) {
	
	lexicon_search_result_selection_t *lsrs = lctx->lsrs;
	GtkContainer *result_list = GTK_CONTAINER(lctx->ctrls.result_list);
	
	//IupSetAttribute(result_list, "REMOVEITEM", "ALL");
	//IupRefresh(IupGetParent(result_list));
	GList* list = gtk_container_get_children (result_list);
	for (GList *l = list; l != NULL; l = l->next)
	{
		gtk_container_remove(result_list, GTK_WIDGET(l->data));
	}
	
	for( int cur_file = 0; cur_file < lsrs->cnt_cache ; ++cur_file ) {
		
		xmlXPathObjectPtr xpathObj = lsrs->xpath_result[cur_file];
		
		add_node_attrs_to_handle(result_list, xpathObj);
	
	}
	
	//IupSetAttribute(result_list, "VALUE", "1");
	;
	gtk_list_box_select_row (GTK_LIST_BOX(result_list), 
			GTK_LIST_BOX_ROW(g_list_nth_data(gtk_container_get_children (result_list), 1)));

	update_result_display(lctx , 0);
	
}

void search(lexicon_ctx_t *lctx) {

	lexicon_search_selection_t	*lss = lctx->lss;
	
	//resource_search_result_t *result = lctx->xml_result;
	unsigned int file_offset = lss->categories.selected;
	
	int cnt_files = lss->categories.cnt_files;
	if ( file_offset >= 0 ) {
		
		GtkWidget * groups = lctx->ctrls.groups;
		GtkWidget * search_input = lctx->ctrls.search_input;
		
		//char *selected_group = IupGetAttribute(groups, "VALUESTRING");
		gchar *selected_group = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(groups));
		//char *search_string = IupGetAttribute(search_input, "VALUE");
		const gchar *search_string = gtk_entry_get_text (GTK_ENTRY(search_input));

		lexicon_search_result_selection_t *lsrs =lctx ->lsrs;
		alveran_lexicon_reset_search_result_selection(lsrs);
		lsrs->cnt_cache = cnt_files;
		
		for( int cur_file = 0; cur_file < cnt_files ; ++cur_file ) {

			xml_ctx_t *xml_ctx = lctx->ctxs[file_offset + cur_file];

			if (xml_ctx == NULL) continue;
			
			xmlXPathObjectPtr xpathObj = NULL;

			if ( gtk_combo_box_get_active(GTK_COMBO_BOX(groups)) == 0 ) {

				xpathObj = xml_ctx_xpath_format(xml_ctx, "//group/*[regexmatch(@name,'%s')]", search_string);

			} else {

				xpathObj = xml_ctx_xpath_format(xml_ctx, "//group[@name = '%s']/*[regexmatch(@name,'%s')]", selected_group, search_string);

			}
			
			lsrs->xpath_result[cur_file] = xpathObj;
			
		}
	
	}
	
	refresh_search_result_list(lctx);

}


