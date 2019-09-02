#include "alveran_lexicon_callback.h"

static void
lexicon_search_cb (GtkButton *button, gpointer user_data) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	search(lctx);

}

void 
search_input_key_callback(GtkEntry *entry, gpointer user_data) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	search(lctx);

}

void
on_category_changed_cb (GtkComboBox *widget, gpointer user_data) 
{

		GtkApplication *app = GTK_APPLICATION(g_application_get_default());
		lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

		update_cat_and_group_selections(lctx);
		update_group_list(lctx);

}

void
on_group_changed_cb (GtkComboBox *widget, gpointer user_data) 
{
		
		GtkApplication *app = GTK_APPLICATION(g_application_get_default());
		lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

		if ( lctx->lss->groups.selected != gtk_combo_box_get_active(GTK_COMBO_BOX(widget))) {
			update_cat_and_group_selections(lctx);
			g_message("group changed by selection");
		}

}

void
on_result_list_changed_cb (GtkListBox *box, GtkListBoxRow *row, gpointer user_data)
{
	
	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	update_result_display_by_selection(lctx);
}

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

