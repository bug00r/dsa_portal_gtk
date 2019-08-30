#ifndef ALVERAN_LEXICON_SEARCH_H
#define ALVERAN_LEXICON_SEARCH_H

#include <gtk/gtk.h>

#include "alveran_lexicon_type.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

//OLD
//#include "plugin.h"
#include "resource.h"
#include "regex_utils.h"
#include "xpath_utils.h"

#include "xml_source.h"

#include "xml_utils.h"


/**

void update_cat_and_group_selections(lexicon_ctx_t *lctx);

void add_node_attrs_to_handle(Ihandle *handle, xmlXPathObjectPtr xpathObj);

void update_group_list(lexicon_ctx_t *lctx);

char* add_node_as_string(Ihandle *text, xmlNodePtr node);

void update_result_display(lexicon_ctx_t *lctx, int sel_list_idx);

void refresh_search_result_list(lexicon_ctx_t *lctx);

void search(lexicon_ctx_t *lctx);

*/

void update_cat_and_group_selections(lexicon_ctx_t *lctx);

void add_node_attrs_to_handle(GtkContainer *handle, xmlXPathObjectPtr xpathObj);

void update_group_list(lexicon_ctx_t *lctx);

void add_node_as_string(GtkWidget *text, xmlNodePtr node);

void update_result_display(lexicon_ctx_t *lctx, int sel_list_idx);

void refresh_search_result_list(lexicon_ctx_t *lctx);

void search(lexicon_ctx_t *lctx);

#endif