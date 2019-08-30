#include "alveran_lexicon_callback.h"

/**int search_button_callback(Ihandle *search_button) {

	lexicon_ctx_t *lctx = (lexicon_ctx_t*)IupGetAttribute(search_button, "lctx");

	DEBUG_LOG("trigger search\n");

	search(lctx);
	
	return IUP_DEFAULT;
}

int search_input_key_callback(Ihandle *ih, int c) {

	if ( c == K_CR ) {
	
		DEBUG_LOG("hit enter key in search input\n");

		lexicon_ctx_t *lctx = (lexicon_ctx_t*)IupGetAttribute(ih, "lctx");

		search(lctx);
	}
	
	return IUP_DEFAULT;
}

int on_category_changed_cb(Ihandle *ih, char *text, int item, int state) {
	
	(void)text;
	(void)item;

	if ( state == 1 ) {
	
		DEBUG_LOG_ARGS("changed to %s\n", IupGetAttribute(ih, "VALUESTRING"));
		
		lexicon_ctx_t *lctx = (lexicon_ctx_t*)IupGetAttribute(ih, "lctx");

		update_cat_and_group_selections(lctx);
		update_group_list(lctx);
	}
	
	return IUP_DEFAULT;
}

int on_group_changed_cb(Ihandle *ih, char *text, int item, int state) {
	
	(void)text;
	(void)item;

	if ( state == 1 ) {
	
		DEBUG_LOG_ARGS("changed to %s\n", IupGetAttribute(ih, "VALUESTRING"));
		
		lexicon_ctx_t *lctx = (lexicon_ctx_t*)IupGetAttribute(ih, "lctx");

		update_cat_and_group_selections(lctx);
	}
	
	return IUP_DEFAULT;
}

int on_result_list_changed_cb(Ihandle *ih, char *text, int item, int state) {

	(void)text;

	if ( state == 1 ) {
	
		DEBUG_LOG_ARGS("changed to %s or %s\n", IupGetAttribute(ih, "VALUESTRING"), text);
		
		lexicon_ctx_t *lctx = (lexicon_ctx_t*)IupGetAttribute(ih, "lctx");

		update_result_display(lctx, item);
		
	}
	
	return IUP_DEFAULT;
}

*/

static void
lexicon_search_cb (GtkButton *button, gpointer user_data) {

	g_message("trigger search");

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	search(lctx);

	/*GtkApplication *app = GTK_APPLICATION(g_application_get_default());
    GtkContainer *list = GTK_CONTAINER(g_object_get_data(G_OBJECT(app), "lexicon_list"));

	for (int i = 0; i < 1000; ++i ) {
		GtkWidget *entry = gtk_label_new ("test");
		gtk_widget_show(entry);
		gtk_container_add(list, entry);
	}*/
}



void
alveran_lexicon_register_callbacks(GtkBuilder *_builder) {
	
	GtkBuilder *builder = GTK_BUILDER(_builder);
	
	if (builder) {
		gtk_builder_add_callback_symbol (builder, "lexicon_search_cb", G_CALLBACK(lexicon_search_cb));
	}
}

