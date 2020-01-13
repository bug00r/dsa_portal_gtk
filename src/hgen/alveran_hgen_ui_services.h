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

void alveran_uis_init_height_limits(GtkSpinButton *heights, dsa_hero_t *hero);

#endif