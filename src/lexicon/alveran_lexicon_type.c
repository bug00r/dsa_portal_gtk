#include "alveran_lexicon_type.h"

/*
void reset_search_selection(lexicon_search_selection_t	*lss) {
	
	if(lss != NULL) {
		
		lss->categories.selected = -1;
		lss->categories.cnt_files = -1;
		
		lss->groups.selected= -1;
	}
	
}

lexicon_search_selection_t* create_search_selection() {
	
	lexicon_search_selection_t *lss = malloc(sizeof(lexicon_search_selection_t));
	
	reset_search_selection(lss);
	
	return lss;
}

void reset_search_result_selection(lexicon_search_result_selection_t	*lsrs) {
	
	if(lsrs != NULL) {
	
		DEBUG_LOG_ARGS("lsrs (%p) must clean result (%p)\n", lsrs, lsrs->xpath_result);
	
		for ( unsigned int cnt_cache = lsrs->cnt_cache ; cnt_cache--; ) {
			xmlXPathFreeObject(lsrs->xpath_result[cnt_cache]);	
			lsrs->xpath_result[cnt_cache] = NULL;
		}
	}
	
}

lexicon_search_result_selection_t* create_search_result_selection(unsigned int cnt_file_cache) {
	
	lexicon_search_result_selection_t *lsrs = malloc(sizeof(lexicon_search_result_selection_t));
	lsrs->xpath_result = malloc(cnt_file_cache * sizeof(xmlXPathObjectPtr));
	lsrs->cnt_cache = cnt_file_cache;
	
	for ( unsigned int cnt_cache = cnt_file_cache; cnt_file_cache--; ) {
		lsrs->xpath_result[cnt_file_cache] = NULL;
	}
	
	reset_search_result_selection(lsrs);
	
	return lsrs;
}
*/

void 
alveran_lexicon_reset_search_selection(lexicon_search_selection_t	*lss) 
{
	if(lss != NULL) {
		
		lss->categories.selected = -1;
		lss->categories.cnt_files = -1;
		
		lss->groups.selected= -1;
	}
}

lexicon_search_selection_t* 
alveran_lexicon_create_search_selection() 
{
		
	lexicon_search_selection_t *lss = malloc(sizeof(lexicon_search_selection_t));
	
	alveran_lexicon_reset_search_selection(lss);
	
	return lss;
}

void 
alveran_lexicon_reset_search_result_selection(lexicon_search_result_selection_t	*lsrs) 
{
	if(lsrs != NULL) {
	
		g_message("lsrs (%p) must clean result (%p)", lsrs, lsrs->xpath_result);
	
		for ( unsigned int cnt_cache = lsrs->cnt_cache ; cnt_cache--; ) {
			xmlXPathFreeObject(lsrs->xpath_result[cnt_cache]);	
			lsrs->xpath_result[cnt_cache] = NULL;
		}
	}
}

lexicon_search_result_selection_t* 
alveran_lexicon_create_search_result_selection(unsigned int cnt_file_cache) 
{
	lexicon_search_result_selection_t *lsrs = malloc(sizeof(lexicon_search_result_selection_t));
	lsrs->xpath_result = malloc(cnt_file_cache * sizeof(xmlXPathObjectPtr));
	lsrs->cnt_cache = cnt_file_cache;
	
	for ( unsigned int cnt_cache = cnt_file_cache; cnt_cache--; ) {
		lsrs->xpath_result[cnt_cache] = NULL;
	}
	
	alveran_lexicon_reset_search_result_selection(lsrs);
	
	return lsrs;
}

lexicon_ctx_t*
alveran_lexicon_ctx_new() 
{
	lexicon_ctx_t* new_ctx = malloc(sizeof(lexicon_ctx_t));

	if (new_ctx) {
		new_ctx->ctxs  = NULL;
	}

	return new_ctx;
}

void
alveran_lexicon_ctx_free(lexicon_ctx_t **_lctx) 
{
	lexicon_ctx_t **__lctx = _lctx;
	lexicon_ctx_t *lctx = *__lctx;

	if ( lctx && lctx->ctxs != NULL ) {

		free(lctx->lss);

		alveran_lexicon_reset_search_result_selection(lctx->lsrs);

		free(lctx->lsrs->xpath_result);
		free(lctx->lsrs);
		
		/*unsigned int max_docs =  lctx->xml_result->cnt;
		
		for ( unsigned int cur_doc = 0; cur_doc < max_docs ; ++cur_doc) {
			
			free_xml_ctx_src(&lctx->ctxs[cur_doc]);

		}*/

		resource_search_result_full_free(&lctx->xml_result);

		free(lctx->ctxs);
		lctx->ctxs = NULL;
	}

	free(lctx);
	*_lctx = NULL;
	
}
		