#ifndef ALVERAN_LEXICON_TYPE_H
#define ALVERAN_LEXICON_TYPE_H

#include <gtk/gtk.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "xpath_utils.h"

#include "xml_source.h"

#include "xml_utils.h"

typedef struct {
	int selected;
	int cnt_files;
} lexicon_category_t;

typedef struct {
	int selected;
} lexicon_group_t;

typedef struct {
	lexicon_category_t 	categories;
	lexicon_group_t		groups;
} lexicon_search_selection_t;

typedef struct {
	int cnt_cache;
	xmlXPathObjectPtr *xpath_result;
} lexicon_search_result_selection_t;

typedef struct {
	GtkWidget *categories;
	GtkWidget *groups;
	GtkWidget *search_input;
	GtkWidget *result_list;
	GtkWidget *result_text;

} lexicon_ctrls_t;

typedef struct _lexicon_ctx_ {
	resource_search_result_t *xml_result;
	xml_ctx_t **ctxs;
	lexicon_search_selection_t	*lss;
	lexicon_search_result_selection_t *lsrs;
	lexicon_ctrls_t ctrls;
} lexicon_ctx_t;

lexicon_ctx_t*
alveran_lexicon_ctx_new();

void
alveran_lexicon_ctx_free(lexicon_ctx_t **lctx);

void 
alveran_lexicon_reset_search_selection(lexicon_search_selection_t	*lss);

lexicon_search_selection_t* 
alveran_lexicon_create_search_selection();

void 
alveran_lexicon_reset_search_result_selection(lexicon_search_result_selection_t	*lsrs);

lexicon_search_result_selection_t* 
alveran_lexicon_create_search_result_selection(unsigned int cnt_file_cache);

#endif