#ifndef ALVERAN_HGEN_TYPE_H
#define ALVERAN_HGEN_TYPE_H

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include "resource.h"
#include "hero.h"

extern const char * const HGEN_CTX;

typedef struct {
	GtkWidget *hgen_height_rnd_btn;
	GtkWidget *hgen_eye_color;
	GtkWidget *hgen_hair_color;
	GtkWidget *hgen_height;
	GtkWidget *hgen_weight;
	GtkWidget *hgen_profession;
	GtkWidget *hgen_culture;
	GtkWidget *hgen_breed;
	GtkWidget *hgen_name;
	GtkWidget *hgen_gp;
	GtkWidget *hero_edit_done_btn;
	GtkWidget *hero_details;
	GtkWidget *hero_list;
	GtkWidget *hero_delete_btn;
	GtkWidget *hero_edit_btn;
	GtkWidget *hero_save_btn;
	GtkWidget *hero_tabs;
} hgen_ui_ctrls_t;

typedef struct _hgen_ctx_ {
	dsa_heros_t * heros;
	hgen_ui_ctrls_t ctrls;
} hgen_ctx_t;

hgen_ctx_t*
alveran_hgen_ctx_new(archive_resource_t * ar);

void
alveran_hgen_ctx_free(hgen_ctx_t** ctx);

#endif