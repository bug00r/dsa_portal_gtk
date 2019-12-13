#include "alveran_hgen_callbacks.h"

static hgen_ctx_t * 
_alveran_hgen_get_context() 
{
    GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	hgen_ctx_t * lctx = g_object_get_data(G_OBJECT(app), HGEN_CTX);

    return lctx;
}

G_MODULE_EXPORT void
alveran_hgen_hero_add_new_cb (GtkButton *button, gpointer user_data) 
{
    alveran_hgen_hero_add_new(_alveran_hgen_get_context());
}

G_MODULE_EXPORT void
alveran_hgen_hero_remove_sel_cb (GtkButton *button, gpointer user_data) 
{
    alveran_hgen_hero_remove_sel(_alveran_hgen_get_context());
}

G_MODULE_EXPORT void
alveran_hgen_hero_select_cb (GtkTreeView *hero_list, gpointer user_data) 
{
    alveran_hgen_hero_select(_alveran_hgen_get_context());
}

G_MODULE_EXPORT void
alveran_hgen_hero_edit_cb (GtkButton *button, gpointer user_data) 
{
    alveran_hgen_hero_edit(_alveran_hgen_get_context());
}

G_MODULE_EXPORT void
alveran_hgen_hero_edit_done_cb (GtkButton *button, gpointer user_data) 
{
    alveran_hgen_hero_edit_done(_alveran_hgen_get_context());
}