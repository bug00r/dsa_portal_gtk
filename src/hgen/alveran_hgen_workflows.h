#ifndef ALVERAN_HGEN_WORKFLOWS_H
#define ALVERAN_HGEN_WORKFLOWS_H

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include "alveran_hgen_services.h"
#include "alveran_hgen_ui_services.h"

void    alveran_hgen_hero_add_new(hgen_ctx_t *hgen);
void    alveran_hgen_hero_remove_sel(hgen_ctx_t *hgen);
void    alveran_hgen_hero_select(hgen_ctx_t *hgen);
void    alveran_hgen_hero_edit(hgen_ctx_t *hgen);
void    alveran_hgen_hero_edit_done(hgen_ctx_t *hgen);

#endif