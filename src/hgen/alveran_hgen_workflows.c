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
    }

    xmlFree(name);
    free(message);
}