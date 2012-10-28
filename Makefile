
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

curses_example:
	gcc -o Curses_Examples/curses_example  Curses_Examples/curses_example.c -lncurses
	gcc -o Curses_Examples/curses_example2 Curses_Examples/curses_example2.c -lncurses
	gcc -o Curses_Examples/curses_example3 Curses_Examples/curses_example3.c -lncurses

.C.o:
	c++ -c $(GCCOPT) $<

.PHONY: depend clean

$(DEPFILE):
	echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(GCCOPT) -- $(SOURCES) >&/dev/null

sinclude $(DEPFILE)
