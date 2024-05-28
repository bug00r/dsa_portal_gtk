#include "alveran_hgen_type.h"

const char * const HGEN_CTX = "hctx";

hgen_ctx_t*
alveran_hgen_ctx_new(ArchiveResource * ar) 
{
    hgen_ctx_t * hctx = malloc(sizeof(hgen_ctx_t));
	hctx->heros = dsa_heros_new_archiv(ar);
    return hctx;
}

void
alveran_hgen_ctx_free(hgen_ctx_t** ctx)
{
    if ( ctx != NULL && *ctx != NULL ) {
        hgen_ctx_t* to_delete = *ctx;

        dsa_heros_free(&to_delete->heros);

        *ctx = NULL;
    }
    
}