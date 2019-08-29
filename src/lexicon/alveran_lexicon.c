#include "alveran_lexicon.h"

/**static void _lexicon_init_(void * data) {

	DEBUG_LOG("lexicon init\n");

	lexicon_ctx_t * mctx = (lexicon_ctx_t *)data;
	mctx->ctxs  = NULL;
	mctx->frame = NULL;
	
}

static void _lexicon_free_(void * data) {

	lexicon_ctx_t * lctx = (lexicon_ctx_t *)data;

	iup_xml_builder_free(&lctx->builder);

	xml_source_free(&lctx->ui_res);

	free(lctx);

	DEBUG_LOG("lexicon free\n");
}

static const char * _lexicon_name_(void * data) {
	
	UNUSED(data);

	DEBUG_LOG("lexicon name\n");

	return "Lexicon";
}

void * _lexicon_frame_(void * data) {

	DEBUG_LOG("lexicon frame\n");
	
	lexicon_ctx_t * lctx = (lexicon_ctx_t *)data;
	if ( lctx->frame == NULL ) {
		
		DEBUG_LOG("lexicon frame create new\n");

		lctx->builder = iup_xml_builder_new();

		iup_xml_builder_add_bytes(lctx->builder, "main",  
						(const char *)lctx->ui_res->src_data, 
						*lctx->ui_res->src_size);

		iup_xml_builder_add_callback(lctx->builder, "on_category_changed", (Icallback)on_category_changed_cb);
		iup_xml_builder_add_callback(lctx->builder, "on_group_changed", (Icallback)on_group_changed_cb);
		iup_xml_builder_add_callback(lctx->builder, "on_result_list_changed", (Icallback)on_result_list_changed_cb);
		iup_xml_builder_add_callback(lctx->builder, "on_search", (Icallback)search_button_callback);
		iup_xml_builder_add_callback(lctx->builder, "on_input_search", (Icallback)search_input_key_callback);

		iup_xml_builder_add_user_data(lctx->builder, "lctx", (char*)lctx);

		iup_xml_builder_parse(lctx->builder);

		Ihandle *mres = iup_xml_builder_get_result(lctx->builder, "main");

		lctx->ctrls.search_input = iup_xml_builder_get_name(mres, "search_input");
		lctx->ctrls.groups = iup_xml_builder_get_name(mres, "groups");
		lctx->ctrls.categories = iup_xml_builder_get_name(mres, "categories");
		lctx->ctrls.result_list = iup_xml_builder_get_name(mres, "result_list");
		lctx->ctrls.result_text = iup_xml_builder_get_name(mres, "result_text");

		lctx->frame = iup_xml_builder_get_main(mres);

	}
	return lctx->frame;
}

void _lexicon_prepare_(void * data) {
	
	DEBUG_LOG("lexicon prepare\n");

	lexicon_ctx_t *lctx = (lexicon_ctx_t *)data;
	
	Ihandle *categories = lctx->ctrls.categories;
	IupSetAttribute(categories, "APPENDITEM", "ALL");
	
	resource_search_result_t *result = lctx->xml_result;
	
	lctx->ctxs = malloc(result->cnt*sizeof(xml_ctx_t *));

	for(unsigned int cnt_files = 0; cnt_files < result->cnt; ++cnt_files) {
	
		resource_file_t *file = result->files[cnt_files];
		
		xml_source_t * xml_src = xml_source_from_resfile(resource_file_copy_deep(file));
		lctx->ctxs[cnt_files] = xml_ctx_new(xml_src);
		
		IupSetAttribute(categories, "APPENDITEM", file->name);
	}

	IupSetAttribute(categories, "VALUE", "1");
	
	lctx->lss = create_search_selection();	
	
	lctx->lsrs = create_search_result_selection(result->cnt);	
	
	update_cat_and_group_selections(lctx);
	update_group_list(lctx);
	
}

void _lexicon_cleanup_(void * data) {
	
	DEBUG_LOG("lexicon plugin cleanup\n");
	
	lexicon_ctx_t *lctx = (lexicon_ctx_t *)data;
	
	if ( lctx->ctxs != NULL ) {

		free(lctx->lss);

		reset_search_result_selection(lctx->lsrs);

		free(lctx->lsrs->xpath_result);
		free(lctx->lsrs);
		
		unsigned int max_docs =  lctx->xml_result->cnt;
		
		for ( unsigned int cur_doc = 0; cur_doc < max_docs ; ++cur_doc) {
			
			free_xml_ctx_src(&lctx->ctxs[cur_doc]);

		}

		free(lctx->ctxs);
		lctx->ctxs = NULL;
	}	
}

plugin_t * lexicon_plugin(plugin_t * plugin, void *data) {
	plugin->name = _lexicon_name_;
	plugin->frame = _lexicon_frame_;
	plugin->init = _lexicon_init_;
	plugin->free = _lexicon_free_;
	plugin->prepare = _lexicon_prepare_;
	plugin->cleanup = _lexicon_cleanup_;
	lexicon_ctx_t *plg_data = malloc(sizeof(lexicon_ctx_t));
	plugin->data = plg_data;
	archive_resource_t *archive = (archive_resource_t *)data;
	plg_data->ui_res = xml_source_from_resname(archive, "lexicon_ui");
	plg_data->lsrs = NULL;
	plg_data->lss = NULL;
	plg_data->builder = NULL;
	return plugin;
}

*/

/*
 How to init plugin
 	mctx->archive = archive_resource_memory(&_binary_zip_resource_7z_start, (size_t)&_binary_zip_resource_7z_size);
	mctx->ui_archive = archive_resource_memory(&_binary_zip_ui_resource_7z_start, (size_t)&_binary_zip_ui_resource_7z_size);
	
	mctx->ui_res = xml_source_from_resname(mctx->ui_archive, "main_ui");

	mctx->xml_result = archive_resource_search(mctx->archive, "xml/.*.xml");
	
	mctx->cntplugins = 3;
	mctx->plugins = malloc( mctx->cntplugins * sizeof(plugin_t*));
	
	mctx->plugins[0] = new_plugin();
	plugin_t *plugin = mctx->plugins[0];
	lexicon_plugin(plugin, mctx->ui_archive);
	((lexicon_ctx_t*)plugin->data)->xml_result = mctx->xml_result;
	plugin->init(plugin->data);
*/
void alveran_lexicon_init_app(GtkApplication *app) {
	archive_resource_t * ar = archive_resource_memory(&_binary_zip_resource_7z_start, (size_t)&_binary_zip_resource_7z_size);
	resource_search_result_t * result = archive_resource_search(ar, "xml/.*.xml");

	for(unsigned int cnt_files = 0; cnt_files < result->cnt; ++cnt_files) {
	
		resource_file_t *file = result->files[cnt_files];
		
		xml_source_t * xml_src = xml_source_from_resfile(resource_file_copy_deep(file));
		xml_ctx_t *ctx = xml_ctx_new(xml_src);
		
		g_message("load ctx from file %s", file->name);

		free_xml_ctx_src(&ctx);
	}


	archive_resource_free(&ar);
	resource_search_result_full_free(&result);
}

GtkWidget* alveran_lexicon_widget_new() {
	GtkBuilder *builder = gtk_builder_new_from_resource ("/de/bug0r/alveran/ui/lexicon.ui");

    GtkWidget *lexicon_widget = GTK_WIDGET(gtk_builder_get_object (builder, "lexicon_box"));
    GtkContainer *lexicon_window = GTK_CONTAINER(gtk_builder_get_object (builder, "lexicon_window"));
    gtk_container_remove(GTK_CONTAINER(lexicon_window),lexicon_widget);
    g_object_unref(lexicon_window);

    return lexicon_widget;
}
