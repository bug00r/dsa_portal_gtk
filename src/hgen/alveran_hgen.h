#ifndef ALVERAN_HGEN_H
#define ALVERAN_HGEN_H

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
#include "xslt_utils.h"
#include "alveran_hgen_type.h"

void 		alveran_hgen_init_app(GtkApplication *app);	
GtkWidget*	alveran_hgen_widget_new(); 
void 		alveran_hgen_widget_init(GtkWidget* widget); 
void 		alveran_hgen_remove_from_app(GtkApplication *app);	

#endif