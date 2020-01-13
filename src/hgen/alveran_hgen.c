#include "alveran_hgen.h"

static xmlBuffer* __alveran_hgen_get_and_translate_ui(hgen_ctx_t * hctx) 
{
	GResource *resource = alveranapp_get_resource ();
	GBytes * hgen_ui_xslt = g_resource_lookup_data (resource, "/de/bug0r/alveran/ui/hgen_xslt.ui",
                        						    G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);

	gsize hgen_ui_xslt_size = g_bytes_get_size (hgen_ui_xslt);
	xml_source_t hgen_ui_xslt_src = { RESOURCE_FILE, &hgen_ui_xslt_size, g_bytes_get_data(hgen_ui_xslt, &hgen_ui_xslt_size), {NULL} };
	xml_ctx_t *hgen_ui_ctx = xml_ctx_new(&hgen_ui_xslt_src);

	xslt_ctx_t xslt_ctx;
	xslt_ctx_init(&xslt_ctx);

	xslt_ctx.xml = hctx->heros->heros;
	xslt_ctx.stylesheet = xsltParseStylesheetDoc(hgen_ui_ctx->doc);
	hgen_ui_ctx->doc = NULL;
	
	xmlDocPtr result = do_xslt(&xslt_ctx);

	xmlBuffer *buffer = xmlBufferCreate();
	xmlOutputBuffer *outputBuffer = xmlOutputBufferCreateBuffer( buffer, NULL );
	xmlSaveFormatFileTo( outputBuffer, result, "utf-8", 1 );

	xmlFreeDoc(result);

	free_xml_ctx(&hgen_ui_ctx);

	g_bytes_unref(hgen_ui_xslt);

	return buffer;
}

void alveran_hgen_init_app(GtkApplication *app) 
{	
	archive_resource_t *ar = archive_resource_memory(&_binary_zip_resource_7z_start, (size_t)&_binary_zip_resource_7z_size);

	hgen_ctx_t *hctx = alveran_hgen_ctx_new(ar);

	g_object_set_data(G_OBJECT(app), HGEN_CTX, hctx);

	archive_resource_free(&ar);

}

void alveran_hgen_remove_from_app(GtkApplication *app) 
{
	hgen_ctx_t *hctx = g_object_get_data(G_OBJECT(app), HGEN_CTX);
	
	alveran_hgen_ctx_free(&hctx);
}

GtkWidget* alveran_hgen_widget_new() 
{
	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	hgen_ctx_t * hctx = g_object_get_data(G_OBJECT(app), HGEN_CTX);

	xmlBuffer *buffer = __alveran_hgen_get_and_translate_ui(hctx);

	GtkBuilder *builder = gtk_builder_new_from_string ((const gchar *)buffer->content, buffer->use);

	xmlBufferFree( buffer );

	gtk_builder_connect_signals(builder, NULL);

    GtkWidget *hgen_widget = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_box"));

    GtkContainer *hgen_window = GTK_CONTAINER(gtk_builder_get_object (builder, "hgen_window"));
    gtk_container_remove(GTK_CONTAINER(hgen_window),hgen_widget);
    g_object_unref(hgen_window);

	hctx->ctrls.hero_list = GTK_WIDGET(gtk_builder_get_object (builder, "hero_list"));
	hctx->ctrls.hero_details = GTK_WIDGET(gtk_builder_get_object (builder, "hero_details"));
	hctx->ctrls.hero_delete_btn = GTK_WIDGET(gtk_builder_get_object (builder, "hero_delete_btn"));
	hctx->ctrls.hero_edit_btn = GTK_WIDGET(gtk_builder_get_object (builder, "hero_edit_btn"));
	hctx->ctrls.hero_edit_done_btn = GTK_WIDGET(gtk_builder_get_object (builder, "hero_edit_done_btn"));
	hctx->ctrls.hgen_gp = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_gp"));
	hctx->ctrls.hgen_name = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_name"));
	hctx->ctrls.hgen_breed = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_breed"));
	hctx->ctrls.hgen_culture = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_culture"));
	hctx->ctrls.hgen_profession = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_profession"));
	hctx->ctrls.hgen_height = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_height"));
    hctx->ctrls.hgen_eye_color = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_eye_color"));
	hctx->ctrls.hgen_hair_color = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_hair_color"));
	hctx->ctrls.hgen_weight = GTK_WIDGET(gtk_builder_get_object (builder, "hgen_weight"));

	return hgen_widget;
}

void alveran_hgen_widget_init(GtkWidget* widget) 
{

	GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	hgen_ctx_t * hctx = g_object_get_data(G_OBJECT(app), "hctx");

	//Todo init last hero file entries
}
