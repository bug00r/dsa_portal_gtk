#ifndef ALVERAN_HGEN_TYPE_H
#define ALVERAN_HGEN_TYPE_H

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include "resource.h"
#include "hero.h"

extern const char * const HGEN_CTX;

typedef struct {
	GObject   *hgen_look_buffer;
	GObject   *hgen_title_buffer;
	GObject   *hgen_story_buffer;
	GObject   *hgen_status_buffer;
	GtkWidget *hgen_pro_avail;
	GtkWidget *hgen_pro_cur_list;
	GtkWidget *hgen_contra_avail;
	GtkWidget *hgen_contra_cur_list;
	GtkWidget *hgen_special_avail;
	GtkWidget *hgen_special_cur_list;
	GtkWidget *hgen_height_rnd_btn;
	GtkWidget *hgen_eye_color_rnd_btn;
	GtkWidget *hgen_hair_color_rnd_btn;
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
	DsaHeros * heros;
	hgen_ui_ctrls_t ctrls;
} hgen_ctx_t;

hgen_ctx_t*
alveran_hgen_ctx_new(ArchiveResource * ar);

void
alveran_hgen_ctx_free(hgen_ctx_t** ctx);

#endif