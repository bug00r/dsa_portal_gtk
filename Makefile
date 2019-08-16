include ../make_config

CFLAGS+=-std=c11 -Wall

#-ggdb  -mwindows
#-pg for profiling 

GTK_LIBDIR:=$(shell pkg-config --libs-only-L gtk+-3.0)
GTK_LIBS:=$(shell pkg-config --libs-only-l --libs-only-other gtk+-3.0)
GTK_INCLUDE:=$(shell pkg-config --cflags-only-I gtk+-3.0)
CFLAGS+=$(shell pkg-config --cflags-only-other gtk+-3.0)


INCLUDEDIR=-I./src -I../utils/src -I../collections/dl_list
#INCLUDEDIR+=$(patsubst %,-I./src/%, lexicon taw_calc main hgen utils)
INCLUDEDIR+=$(GTK_INCLUDE)

_SRC_FILES=run_alveran alveran_app alveran_app_win

#_SRC_UTILS=utils/iup_std_callbacks utils/iup_tab_utils utils/iup_dlg_utils
#_SRC_PLUGIN_MAIN=main/plugin_main
#_SRC_PLUGIN_LEXICON=lexicon/plugin_lexicon lexicon/plugin_lexicon_ui lexicon/plugin_lexicon_ui_callback lexicon/plugin_lexicon_ui_search
#_SRC_PLUGIN_TAW_CALC=taw_calc/plugin_taw_calc
#_SRC_PLUGIN_HGEN=hgen/plugin_hgen hgen/plugin_hgen_ui \
				 hgen/plugin_hgen_ui_callback \
				 hgen/plugin_hgen_ui_hero_details \
				 hgen/plugin_hgen_ui_funcs \
				 hgen/plugin_hgen_ui_utils
				 

#_SRC_PLUGIN_FILES=$(_SRC_PLUGIN_MAIN) $(_SRC_PLUGIN_LEXICON) $(_SRC_PLUGIN_TAW_CALC) $(_SRC_PLUGIN_HGEN) $(_SRC_UTILS)
#$(_SRC_PLUGIN_MAIN) $(_SRC_PLUGIN_LEXICON) $(_SRC_PLUGIN_TAW_CALC) $(_SRC_PLUGIN_HGEN)

#_SRC_FILES+=$(_SRC_PLUGIN_FILES)

SRC+=$(patsubst %,src/%,$(patsubst %,%.c,$(_SRC_FILES)))
OBJ=$(patsubst %,$(BUILDPATH)/%,$(patsubst %,%.o,$(_SRC_FILES)))
BINNAME=dsa_portal
BIN=$(BINNAME).exe

ONW_LIBS=dl_list utils
#THIRD_PARTY_LIBS=exslt xslt xml2 archive crypto nettle regex zstd lzma z lz4 bz2 bcrypt freetype6 iconv
#REGEX_LIBS=pcre2-8
#this c flags is used by regex lib
#CFLAGS+=-DPCRE2_STATIC

#OS_LIBS=kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 uuid ole32 oleaut32 comctl32 ws2_32

USED_LIBS=$(patsubst %,-l%, $(ONW_LIBS) )
USED_LIBS+=$(GTK_LIBS)

USED_LIBSDIR=$(GTK_LIBDIR)

#ownlibs
USED_LIBSDIR+=-L./../collections/dl_list/$(BUILDPATH)
USED_LIBSDIR+=-L./../utils/$(BUILDPATH) 

all: mkbuilddir $(BUILDPATH)$(BIN)

$(BUILDPATH)$(BIN): $(_SRC_FILES)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILDPATH)$(BIN) $(INCLUDEDIR) $(USED_LIBSDIR) $(USED_LIBS) $(debug) $(release)
	ldd $(BUILDPATH)$(BIN) | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" $(BUILDPATH)

$(_SRC_FILES):
	$(CC) $(CFLAGS) -c src/$@.c -o $(BUILDPATH)$@.o $(INCLUDEDIR) $(debug)

.PHONY: clean mkbuilddir small smaller

mkbuilddir:
	mkdir -p $(BUILDDIR)

small:
	-strip $(BUILDPATH)$(BIN)

smaller:
	-upx $(BUILDPATH)$(BIN)
	
clean:
	-rm -dr $(BUILDROOT)
	