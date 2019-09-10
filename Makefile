include ../make_config

COPYDLLS:=
ifeq ($(DLLS),1)
	COPYDLLS:=copydlls
endif

CFLAGS+=-std=c11 -Wall

#-ggdb  -mwindows
#-pg for profiling 

GTK_LIBDIR:=$(shell pkg-config --libs-only-L gtk+-3.0)
GTK_LIBS:=$(shell pkg-config --libs-only-l --libs-only-other gtk+-3.0)
GTK_INCLUDE:=$(shell pkg-config --cflags-only-I gtk+-3.0)
CFLAGS+=$(shell pkg-config --cflags-only-other gtk+-3.0)

XSLT_LIBS:=$(shell xslt-config --libs)
XSLT_INCLUDE:=$(shell xslt-config --cflags)

XML2_LIBS:=$(shell xml2-config --libs)
XML2_INCLUDE:=$(shell xml2-config --cflags)

#ICU_LIBS:=$(shell icu-config --ldflags)
ICU_INCLUDE:=$(shell icu-config --cppflags)

ICONV_LIBS:=$(shell pkg-config --libs iconv)
ICONV_INCLUDE:=$(shell pkg-config --cflags iconv)

FREETYPE_LIBS:=$(shell pkg-config --libs freetype2)
FREETYPE_INCLUDE:=$(shell pkg-config --cflags freetype2)

ARCHIVE_LIBS:=$(shell pkg-config --libs --static libarchive)
ARCHIVE_INCLUDE:=$(shell pkg-config --cflags libarchive)

PCRE2_LIBS:=$(shell pcre2-config --libs8)

GLIB_COMPILE_RESOURCES:=$(shell pkg-config --variable=glib_compile_resources gio-2.0)
RESFILENAME:=gtk_resource
RESRC:=$(patsubst %,$(BUILDPATH)/%,$(patsubst %,%.c, $(RESFILENAME)))

INCLUDEDIR=$(GTK_INCLUDE) $(XSLT_INCLUDE) $(XML2_INCLUDE) $(ICU_INCLUDE) $(ICONV_INCLUDE) $(FREETYPE_INCLUDE) \
			$(ARCHIVE_INCLUDE)
INCLUDEDIR+=-I./src -I../collections/dl_list -I../utils/src -I../dsa_core/src -I./$(BUILDPATH)
INCLUDEDIR+=$(patsubst %,-I./src/%, lexicon taw hgen)


_SRC_FILES=run_alveran alveran_app alveran_app_win taw/alveran_taw_widget \
		   lexicon/alveran_lexicon lexicon/alveran_lexicon_search lexicon/alveran_lexicon_callback lexicon/alveran_lexicon_type \
		   hgen/alveran_hgen hgen/alveran_hgen_type


SRC+=$(patsubst %,src/%,$(patsubst %,%.c,$(_SRC_FILES)))
OBJ=$(patsubst %,$(BUILDPATH)/%,$(patsubst %,%.o, $(RESFILENAME) $(_SRC_FILES)))

BINNAME=dsa_portal
BIN=$(BINNAME).exe

ONW_LIBS=dsa_core utils dl_list

USED_LIBS=$(patsubst %,-l%, $(ONW_LIBS))
USED_LIBS+=$(GTK_LIBS) $(XSLT_LIBS) $(XML2_LIBS) $(ICU_LIBS) $(FREETYPE_LIBS) $(ARCHIVE_LIBS) $(PCRE2_LIBS)

USED_LIBSDIR=$(GTK_LIBDIR)

#ownlibs
USED_LIBSDIR+=-L./../collections/dl_list/$(BUILDPATH)
USED_LIBSDIR+=-L./../utils/$(BUILDPATH) 
USED_LIBSDIR+=-L./../dsa_core/$(BUILDPATH)

all: mkbuilddir hero_ui_xslt $(BUILDPATH)$(BIN) $(COPYDLLS)

$(BUILDPATH)$(BIN): $(RESRC) $(_SRC_FILES)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILDPATH)$(BIN) $(INCLUDEDIR) $(USED_LIBSDIR) $(USED_LIBS) $(debug) $(release)

$(COPYDLLS):
	ldd $(BUILDPATH)$(BIN) | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" $(BUILDPATH)

$(_SRC_FILES):
	$(CC) $(CFLAGS) -c src/$@.c -o $(BUILDPATH)$@.o $(INCLUDEDIR) $(debug)

$(RESRC): src/resource/alveranapp.gresource.xml src/resource/ui/window.ui
	cd src/resource; \
	$(GLIB_COMPILE_RESOURCES) alveranapp.gresource.xml --target=./../../$@ --sourcedir=. --generate-source; \
	$(GLIB_COMPILE_RESOURCES) alveranapp.gresource.xml --target=./../../$(patsubst %.c,%.h,$@) --sourcedir=. --generate-header;
	$(CC) $(CFLAGS) -c $@ -o $(RESRC:.c=.o) $(INCLUDEDIR) $(debug)

hero_ui_xslt:
	xsltproc -o src/resource/ui/hgen_xslt.ui --stringparam talents ../../../../dsa_core/data/xml/talents.xml \
	--stringparam breeds ../../../../dsa_core/data/xml/breeds.xml --stringparam cultures ../../../../dsa_core/data/xml/cultures.xml \
	--stringparam basehero ../../../../dsa_core/data/xml/bsehero.xml src/resource/xslt/hgen.ui.xslt src/resource/ui/hgen_raw.ui

hero_ui_xslt2:
	xsltproc -o $(BUILDPATH)$(PS)test_hgenui.ui src/resource/ui/hgen_xslt.ui ../dsa_core/data/xml/breeds.xml

.PHONY: cleanall clean mkbuilddir small smaller

mkbuilddir:
	-mkdir -p $(BUILDDIR)
	-mkdir -p $(BUILDPATH)$(PS)taw
	-mkdir -p $(BUILDPATH)$(PS)lexicon
	-mkdir -p $(BUILDPATH)$(PS)hgen

small:
	-strip $(BUILDPATH)$(BIN)

smaller: small
	-upx $(BUILDPATH)$(BIN)

smallest: small
	-upx --best --ultra-brute $(BUILDPATH)$(BIN)
	
clean:
	-rm -r $(BUILDPATH)*.c $(BUILDPATH)*.o $(BUILDPATH)$(PS)taw$(PS)*.o $(BUILDPATH)*.exe $(BUILDPATH)*.h \
	$(BUILDPATH)$(PS)lexicon$(PS)*.o $(BUILDPATH)$(PS)hgen$(PS)*.o

cleanall:
	-rm -dr $(BUILDROOT)
	