#ifndef ALVERAN_HGEN_WORKFLOWS_H
#define ALVERAN_HGEN_WORKFLOWS_H

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include "alveran_hgen_services.h"
#include "alveran_hgen_ui_services.h"

void        alveran_hgen_hero_add_new               (hgen_ctx_t *hgen);
void        alveran_hgen_hero_remove_sel            (hgen_ctx_t *hgen);
void        alveran_hgen_hero_select                (hgen_ctx_t *hgen);
void        alveran_hgen_hero_edit                  (hgen_ctx_t *hgen);
void        alveran_hgen_hero_edit_done             (hgen_ctx_t *hgen);
void        alveran_hgen_hero_gp_changed            (hgen_ctx_t *hgen);
void        alveran_hgen_hero_name_changed          (hgen_ctx_t *hgen);
void        alveran_hgen_hero_breed_changed         (hgen_ctx_t *hgen);
void        alveran_hgen_hero_culture_changed       (hgen_ctx_t *hgen);
void        alveran_hgen_hero_profession_changed    (hgen_ctx_t *hgen);
void        alveran_hgen_hero_height_changed_manual (hgen_ctx_t *hgen);
void        alveran_hgen_hero_height_changed_rnd    (hgen_ctx_t *hgen);
gboolean    alveran_hgen_hero_height_on_output      (hgen_ctx_t *hgen);
void        alveran_hgen_hero_hair_color_changed    (hgen_ctx_t *hgen);
void        alveran_hgen_hero_hair_color_changed_rnd(hgen_ctx_t *hgen);
void        alveran_hgen_hero_eye_color_changed     (hgen_ctx_t *hgen);
void        alveran_hgen_hero_eye_color_changed_rnd (hgen_ctx_t *hgen);
void        alveran_hgen_hero_look_changed          (hgen_ctx_t *hgen);
void        alveran_hgen_hero_status_changed        (hgen_ctx_t *hgen);
void        alveran_hgen_hero_title_changed         (hgen_ctx_t *hgen);
void        alveran_hgen_hero_story_changed         (hgen_ctx_t *hgen);
void        alveran_hgen_hero_attribute_changed_manual(hgen_ctx_t *hgen, const gchar* attr_short_name, int new_val);

#endif