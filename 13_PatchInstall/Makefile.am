bin_PROGRAMS = guess
pkgdata_DATA = ru/LC_MESSAGES/guess.mo
pkgdatadir = $(localedir)/ru/LC_MESSAGES
TMP_POT = tmp.pot
NEW_POT = new.pot
LOCALE_DIR = ru/LC_MESSAGES
AM_CPPFLAGS = -D LOCALEDIR='"$(localedir)"'
GENERATES = $(LOCALE_DIR)/guess.mo $(TMP_POT) $(NEW_POT) guess

all: guess $(LOCALE_DIR)/guess.mo

$(LOCALE_DIR)/guess.mo: ru.po
	mkdir -p $(LOCALE_DIR)
	msgfmt $< -o $@

ru.po: $(TMP_POT)
	msgmerge -U $@ $<

$(TMP_POT): guess.pot guess.c
	xgettext -k_ -c guess.c -o $(NEW_POT)
	cp $< $@
	msgmerge -U $@ $(NEW_POT)

clean: 
	-rm $(GENERATES)
	-rm -r ru
