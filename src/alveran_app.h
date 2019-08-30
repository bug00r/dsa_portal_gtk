#ifndef ALVERAN_APP_H
#define ALVERAN_APP_H

#include <gtk/gtk.h>

#include "alveran_lexicon.h"

#define ALVERAN_APP_TYPE (alveran_app_get_type ())
G_DECLARE_FINAL_TYPE(AlveranApp, alveran_app, ALVERAN, APP, GtkApplication);

AlveranApp* alveran_app_new(void);

#endif