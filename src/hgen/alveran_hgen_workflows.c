#include "alveran_hgen_workflows.h"

void    
alveran_hgen_hero_add_new(hgen_ctx_t *hgen)
{
    dsa_hero_t *newhero = dsa_hero_new(hgen->heros, (const unsigned char*)"New Hero");

    alveran_uis_add_hero_new(hgen->ctrls.hero_list, newhero);
}

void    
alveran_hgen_hero_remove_sel(hgen_ctx_t *hgen)
{
    a_uis_selection_t selection;
    alveran_uis_get_tv_selection(hgen->ctrls.hero_list, &selection);

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero(&selection);
    
    xmlChar *name = dsa_heros_get_name(sel_hero);
    
    char * message = format_string_new("Den Helden '%s' wirklich löschen?", name);

    if (alveran_uis_get_yn_modal(message) == GTK_RESPONSE_YES) 
    {
        alveran_uis_rem_sel_hero(&selection);
        
        dsa_heros_delete_hero_obj(hgen->heros, sel_hero);
        
        alveran_uis_get_tv_selection(hgen->ctrls.hero_list, &selection);

        if(!selection.sel_did)
        {
            hgen_ui_ctrls_t *ctrls = &hgen->ctrls;
            alveran_uis_deactivate_if_not(2, ctrls->hero_delete_btn, 
                                             ctrls->hero_edit_btn);
        }
    }

    xmlFree(name);
    free(message);
}

void    
alveran_hgen_hero_select(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;
    alveran_uis_activate_if_not(2, ctrls->hero_delete_btn, 
                                   ctrls->hero_edit_btn);
}

void    
alveran_hgen_hero_edit(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;
    alveran_uis_deactivate_if_not(3, ctrls->hero_delete_btn, 
                                     ctrls->hero_edit_btn,
                                     ctrls->hero_list);
    alveran_uis_activate_if_not(2,  ctrls->hero_edit_done_btn,
                                    ctrls->hero_details);
}

void    
alveran_hgen_hero_edit_done(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;
    alveran_uis_activate_if_not(3, ctrls->hero_delete_btn, 
                                     ctrls->hero_edit_btn,
                                     ctrls->hero_list);
    alveran_uis_deactivate_if_not(2,  ctrls->hero_edit_done_btn,
                                      ctrls->hero_details);
}

void    
alveran_hgen_hero_gp_changed(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;
    gdouble gp = gtk_spin_button_get_value (GTK_SPIN_BUTTON(ctrls->hgen_gp));

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero_direct(GTK_TREE_VIEW(ctrls->hero_list));

    char * gp_str = format_string_new("%i", (gint)gp);

    dsa_heros_set_gp(sel_hero, (const unsigned char *)gp_str);

    free(gp_str);
}

void    
alveran_hgen_hero_name_changed(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    a_uis_selection_t selection;
    alveran_uis_get_tv_selection(hgen->ctrls.hero_list, &selection);

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero(&selection);
    
    const gchar * new_name = gtk_entry_get_text (GTK_ENTRY(ctrls->hgen_name));

    dsa_heros_set_name(sel_hero, (const unsigned char *)new_name);

    alveran_uis_set_hero_name(&selection, new_name);
}

static void 
_alveran_hgen_hero_add_cb_to_sel_hero(GtkWidget *combobox, 
                                      GtkWidget *hero_list, 
                                      dsa_heros_t *heros,
                                      void (*addingfunc)(dsa_heros_t*, dsa_hero_t*, const unsigned char*))
{
    gchar *sel_value = alveran_uis_get_cb_value_copy(GTK_COMBO_BOX(combobox));

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero_direct(GTK_TREE_VIEW(hero_list));

    addingfunc(heros, sel_hero, (const unsigned char*)sel_value);

    g_free(sel_value);
}

void    
alveran_hgen_hero_breed_changed(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    _alveran_hgen_hero_add_cb_to_sel_hero(ctrls->hgen_breed, ctrls->hero_list, hgen->heros,
                dsa_heros_add_breed);

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero_direct(GTK_TREE_VIEW(ctrls->hero_list));

    alveran_uis_init_hair_colors(ctrls->hgen_hair_color, sel_hero);
    alveran_uis_init_eye_colors(ctrls->hgen_eye_color, sel_hero);

    alveran_uis_init_height_limits(ctrls->hgen_height, sel_hero);
}

void    
alveran_hgen_hero_culture_changed(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    _alveran_hgen_hero_add_cb_to_sel_hero(ctrls->hgen_culture, ctrls->hero_list, hgen->heros,
                dsa_heros_add_culture);
}

void    
alveran_hgen_hero_profession_changed(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    _alveran_hgen_hero_add_cb_to_sel_hero(ctrls->hgen_profession, ctrls->hero_list, hgen->heros,
                dsa_heros_add_profession);
}

void    
alveran_hgen_hero_height_changed_manual(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    GtkSpinButton *hgen_height = GTK_SPIN_BUTTON(ctrls->hgen_height);

    int height_Addition = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(hgen_height));

    char * new_height = format_string_new("%i",height_Addition);

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero_direct(GTK_TREE_VIEW(ctrls->hero_list));

    dsa_heros_set_height_weight_by_value(sel_hero, (const unsigned char*)new_height);

    free(new_height);
}

gboolean    
alveran_hgen_hero_height_on_output(hgen_ctx_t *hgen)
{
    hgen_ui_ctrls_t *ctrls = &hgen->ctrls;

    dsa_hero_t * sel_hero = alveran_uis_get_sel_hero_direct(GTK_TREE_VIEW(ctrls->hero_list));

    xmlChar *val = dsa_heros_get_height(sel_hero);

    g_message("new height output %s", val);

    gtk_entry_set_text(GTK_ENTRY(ctrls->hgen_height), (gchar*)val);

    xmlFree(val);

    xmlChar *weight = dsa_heros_get_weight(sel_hero);
    
    gtk_label_set_text(GTK_LABEL(ctrls->hgen_weight),(const gchar*)weight);

    xmlFree(weight);

    return TRUE;
}



  //xmlSaveFileEnc("-", sel_hero->xml->doc,"UTF-8");
