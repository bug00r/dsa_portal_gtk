#ifndef ALVERAN_LEXICON_H
#define ALVERAN_LEXICON_H

#include "defs.h"

EXTERN_BLOB(zip_resource, 7z);

#include <gtk/gtk.h>
#include "gtk_resource.h"

/*#include "defs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iup.h>
#include <cd.h>
#include <cdiup.h>
#include <wd.h>
*/

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

//old implementation
//#include "plugin.h"

#include "resource.h"
#include "regex_utils.h"
#include "xpath_utils.h"

#include "xml_utils.h"

#include "alveran_lexicon_type.h"
#include "alveran_lexicon_search.h"
#include "alveran_lexicon_callback.h"

//OLD interface
//plugin_t * lexicon_plugin(plugin_t *plugin, void *data);

//NEW Interface
void 		alveran_lexicon_init_app(GtkApplication *app);	
GtkWidget*	alveran_lexicon_widget_new(); 
void 		alveran_lexicon_remove_from_app(GtkApplication *app);	

#endif