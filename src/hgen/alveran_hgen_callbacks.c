#include "alveran_hgen_callbacks.h"

static hgen_ctx_t * 
_alveran_hgen_get_context() 
{
    GtkApplication *app = GTK_APPLICATION(g_application_get_default());
	hgen_ctx_t * lctx = g_object_get_data(G_OBJECT(app), HGEN_CTX);

    return lctx;
}

G_MODULE_EXPORT void
alveran_hgen_hero_add_cb (GtkButton *button, gpointer user_data) 
{
    alveran_hgen_hero_add(_alveran_hgen_get_context());
}