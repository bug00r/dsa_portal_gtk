#include "alveran_lexicon.h"

static void _lexicon_prepare_(lexicon_ctx_t *_lctx) 
{	
	lexicon_ctx_t *lctx = _lctx;
	
	GtkWidget *categories = lctx->ctrls.categories;

	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(categories), "ALL");

	resource_search_result_t *result = lctx->xml_result;
	
	lctx->ctxs = malloc(result->cnt*sizeof(xml_ctx_t *));

	for(unsigned int cnt_files = 0; cnt_files < result->cnt; ++cnt_files) 
	{
		resource_file_t *file = result->files[cnt_files];
		
		xml_source_t * xml_src = xml_source_from_resfile(resource_file_copy_deep(file));
		lctx->ctxs[cnt_files] = xml_ctx_new(xml_src);
		
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(categories), (gchar*)file->name);
	}

	gtk_combo_box_set_active (GTK_COMBO_BOX(categories), 0);
	
	alveran_lexicon_reset_search_selection(lctx->lss);
	alveran_lexicon_create_search_result_selection(lctx->lsrs, result->cnt);	
	
	update_cat_and_group_selections(lctx);
	update_group_list(lctx);
	
}

void alveran_lexicon_init_app(GtkApplication *app) 
{
	
	archive_resource_t * ar = archive_resource_memory(&_binary_zip_resource_7z_start, (size_t)&_binary_zip_resource_7z_size);
	
	resource_search_result_t * result = archive_resource_search(ar, (const unsigned char*)"xml/.*.xml");

 	lexicon_ctx_t * lctx = alveran_lexicon_ctx_new();
	
	lctx->xml_result = result;

	g_object_set_data(G_OBJECT(app), "lctx", lctx);

	archive_resource_free(&ar);

}

void alveran_lexicon_remove_from_app(GtkApplication *app) 
{
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");
	
	alveran_lexicon_ctx_free(&lctx);
}

GtkWidget* alveran_lexicon_widget_new() 
{
	GtkBuilder *builder = gtk_builder_new_from_resource ("/de/bug0r/alveran/ui/lexicon.ui");
	#if 0
	//This has to be checked against error prone or security pitfalls
	alveran_lexicon_register_callbacks(builder);
	#endif
	gtk_builder_connect_signals(builder, NULL);
    GtkWidget *lexicon_widget = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_box"));
    GtkContainer *lexicon_window = GTK_CONTAINER(gtk_builder_get_object (builder, "lexicon_window"));
    gtk_container_remove(GTK_CONTAINER(lexicon_window),lexicon_widget);
    g_object_unref(lexicon_window);

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");
	
    lctx->ctrls.result_list = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_list"));
	lctx->ctrls.categories = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_categories"));
	lctx->ctrls.groups = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_groups"));
	lctx->ctrls.search_input = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_search_input"));
	lctx->ctrls.result_text = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_result_text"));
	
    return lexicon_widget;
}

void alveran_lexicon_widget_init(GtkWidget* widget) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	lexicon_ctx_t * lctx = g_object_get_data(G_OBJECT(app), "lctx");

	_lexicon_prepare_(lctx);
}
