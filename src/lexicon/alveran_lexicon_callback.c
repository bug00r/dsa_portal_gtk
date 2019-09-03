#include "alveran_lexicon_callback.h"

G_MODULE_EXPORT void
lexicon_search_cb (GtkButton *button, gpointer user_data) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	search(lctx);

}

G_MODULE_EXPORT void 
search_input_key_callback(GtkEntry *entry, gpointer user_data) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	search(lctx);

}

G_MODULE_EXPORT void
on_category_changed_cb (GtkComboBox *widget, gpointer user_data) 
{

		GtkApplication *app = GTK_APPLICATION(g_application_get_default());
		lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

		update_cat_and_group_selections(lctx);
		update_group_list(lctx);

}

G_MODULE_EXPORT void
on_group_changed_cb (GtkComboBox *widget, gpointer user_data) 
{
		
		GtkApplication *app = GTK_APPLICATION(g_application_get_default());
		lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

		if ( lctx->lss->groups.selected != gtk_combo_box_get_active(GTK_COMBO_BOX(widget))) {
			update_cat_and_group_selections(lctx);
			g_message("group changed by selection");
		}

}

G_MODULE_EXPORT void
on_result_list_changed_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data)
{
	
	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	update_result_display_by_selection(lctx);
}

#if 0
/**
 *  This usage has to check against G_MODULE_EXPORT based on error prone parts or security pitfalls, 
 *  but it look more elegant.
 * 
	void
	alveran_lexicon_register_callbacks(GtkBuilder *_builder) {
		
		GtkBuilder *builder = GTK_BUILDER(_builder);
		
		if (builder) {
			gtk_builder_add_callback_symbol (builder, "lexicon_search_cb", G_CALLBACK(lexicon_search_cb));
			gtk_builder_add_callback_symbol (builder, "on_category_changed_cb", G_CALLBACK(on_category_changed_cb));
			gtk_builder_add_callback_symbol (builder, "on_group_changed_cb", G_CALLBACK(on_group_changed_cb));
			gtk_builder_add_callback_symbol (builder, "on_result_list_changed_cb", G_CALLBACK(on_result_list_changed_cb));
			gtk_builder_add_callback_symbol (builder, "search_input_key_callback", G_CALLBACK(search_input_key_callback));
		
		}
	}
*/
#endif