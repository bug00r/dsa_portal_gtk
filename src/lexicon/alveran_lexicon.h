#ifndef ALVERAN_LEXICON_H
#define ALVERAN_LEXICON_H

#include "defs.h"

EXTERN_BLOB(zip_resource, 7z);

#include <gtk/gtk.h>
#include "gtk_resource.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "resource.h"
#include "regex_utils.h"
#include "xpath_utils.h"

#include "xml_utils.h"

#include "alveran_lexicon_type.h"
#include "alveran_lexicon_search.h"
#include "alveran_lexicon_callback.h"

void 		alveran_lexicon_init_app(GtkApplication *app);	
GtkWidget*	alveran_lexicon_widget_new(); 
void 		alveran_lexicon_widget_init(GtkWidget* widget); 
void 		alveran_lexicon_remove_from_app(GtkApplication *app);	

#endif