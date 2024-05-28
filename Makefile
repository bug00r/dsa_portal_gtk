#MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

INSTALL_ROOT?=$(BUILDPATH)

ifeq ($(DEBUG),1)
	export debug=-ggdb -Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-ggdb -Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-ggdb -Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg= -Doutput=1
endif

BIT_SUFFIX=

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

CFLAGS+= -DIN_LIBXML -std=c11 -Wall $(debug)

COPYDLLS:=
ifeq ($(DLLS),1)
	COPYDLLS:=copydlls
endif


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
INCLUDEDIR+=-I./src -I/c/dev/include -I$(BUILDPATH)
INCLUDEDIR+=$(patsubst %,-I./src/%, lexicon taw hgen mapeditor)


_SRC_FILES=run_alveran alveran_app alveran_app_win taw/alveran_taw_widget \
		   lexicon/alveran_lexicon lexicon/alveran_lexicon_search lexicon/alveran_lexicon_callback lexicon/alveran_lexicon_type \
		   hgen/alveran_hgen hgen/alveran_hgen_type hgen/alveran_hgen_services hgen/alveran_hgen_ui_services \
		   hgen/alveran_hgen_callbacks hgen/alveran_hgen_workflows \
		   mapeditor/alveran_mapeditor


SRC+=$(patsubst %,src/%,$(patsubst %,%.c,$(_SRC_FILES)))
OBJ=$(patsubst %,$(BUILDPATH)/%,$(patsubst %,%.o, $(RESFILENAME) $(_SRC_FILES)))

BINNAME=dsa_portal
BIN=$(BINNAME).exe

ONW_LIBS=dsa_core resource xml_utils pcre2_utils utils dl_list

USED_LIBS=$(patsubst %,-l%, $(ONW_LIBS))
USED_LIBS+=$(GTK_LIBS) $(XSLT_LIBS) $(XML2_LIBS) $(ICU_LIBS) $(FREETYPE_LIBS) $(ARCHIVE_LIBS) $(PCRE2_LIBS)

USED_LIBSDIR=$(GTK_LIBDIR)

#ownlibs
USED_LIBSDIR+=-L/c/dev/lib

XML_DIR:=../../../../dsa_core/data/xml/
X_P=--stringparam

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
	xsltproc -o src/resource/ui/hgen_xslt.ui $(X_P) talents $(XML_DIR)talents.xml $(X_P) breeds $(XML_DIR)breeds.xml \
	$(X_P) cultures $(XML_DIR)cultures.xml $(X_P) professions $(XML_DIR)professions.xml \
	$(X_P) procontra $(XML_DIR)procontra.xml $(X_P) basehero $(XML_DIR)bsehero.xml \
	$(X_P) specialabilities $(XML_DIR)specialabilities.xml src/resource/xslt/hgen.ui.xslt src/resource/ui/hgen_raw.ui


.PHONY: cleanall clean mkbuilddir small smaller

mkbuilddir:
	-mkdir -p $(BUILDDIR)
	-mkdir -p $(BUILDPATH)$(PS)taw
	-mkdir -p $(BUILDPATH)$(PS)lexicon
	-mkdir -p $(BUILDPATH)$(PS)hgen
	-mkdir -p $(BUILDPATH)$(PS)mapeditor

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
	