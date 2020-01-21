#ifndef ALVERAN_HGEN_UI_SERVICES_H
#define ALVERAN_HGEN_UI_SERVICES_H

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include "alveran_hgen_type.h"

typedef struct {
    GtkTreeView *treeview;
    GtkTreeSelection *selction;
    GtkTreeModel *model;
    GtkTreeIter iter;
    int sel_did;
} a_uis_selection_t;

void alveran_uis_add_hero_new(GtkWidget *hero_tree_view, dsa_hero_t *new_hero);
void alveran_uis_rem_sel_hero(a_uis_selection_t *selection);
void alveran_uis_get_tv_selection(GtkWidget *hero_tree_view, a_uis_selection_t *selection);

dsa_hero_t* alveran_uis_get_sel_hero(a_uis_selection_t *selection);
dsa_hero_t* alveran_uis_get_sel_hero_direct(GtkTreeView *hero_list);

int alveran_uis_get_yn_modal(const char *message);

void alveran_uis_activate_if_not(uint32_t count, ...);
void alveran_uis_deactivate_if_not(uint32_t count, ...);

void alveran_uis_set_hero_name(a_uis_selection_t *selection, const gchar * new_name);

gchar * alveran_uis_get_cb_value_copy(GtkComboBox *comboBox);

void alveran_uis_init_hair_colors(GtkWidget* haircol, dsa_hero_t *hero);
void alveran_uis_init_eye_colors(GtkWidget* eyecol, dsa_hero_t *hero);

void alveran_uis_init_height_limits(GtkWidget *heights, dsa_hero_t *hero);

void alveran_uis_combobox_search_and_set_active(GtkComboBox *combobox, const gchar *search_value);

gchar * alveran_ui_txtbuf_get_text_complete(GtkTextBuffer *buffer);

void alveran_uis_pcs_adding(GtkComboBox *avails, GtkTreeView *dest, dsa_heros_t *heros, dsa_hero_t *hero, 
                       void (*add_func)(dsa_heros_t*, dsa_hero_t*, const unsigned char *));

void alveran_uis_rem_pcs_tv_selection(GtkWidget *tree_view, dsa_hero_t *hero, void (*rem_func)(dsa_hero_t*, const unsigned char*));
#endif