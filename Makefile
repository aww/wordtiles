
# Depend scheme came from http://c2.com/cgi/wiki?MakeDepend

GCCOPT  = -g -O0
SOURCES = WordTiles.C WordTilesPlay.C WordTilesDictionary.C WordTilesBoard.C WordTilesPosition.C
OBJECTS = $(SOURCES:.C=.o)
DEPFILE = .depend
DEPTOKEN = '\# MAKEDEPENDS'
DEPFLAGS = -Y -f $(DEPFILE) -s $(DEPTOKEN)

wordtiles: $(OBJECTS)
	c++ -o wordtiles $(GCCOPT) $(OBJECTS)

depend:
	rm -f $(DEPFILE)
	make $(DEPFILE)

clean:
	rm -f $(OBJECTS) $(DEPFILE) $(DEPFILE).bak

cleanexe:
	rm -f wordtiles search curses_example

search: search.C
	c++ search.C -o search

.C.o:
	c++ -c $(GCCOPT) $<

.PHONY: depend clean

$(DEPFILE):
	echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(GCCOPT) -- $(SOURCES) >&/dev/null

sinclude $(DEPFILE)
