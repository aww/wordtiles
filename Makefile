
GCCOPT  = -g -O0
SOURCES = Scrabble.C ScrabblePlay.C ScrabbleDictionary.C ScrabbleBoard.C ScrabblePosition.C
OBJECTS = $(SOURCES:.C=.o)

scrabble: $(OBJECTS)
	c++ -o scrabble $(GCCOPT) $(OBJECTS)

depend:
	makedepend $(SOURCES)

clean:
	rm $(OBJECTS)


search: search.C
	c++ search.C -o search

curses_example:
	gcc -o curses_example curses_example.c -lncurses

.C.o:
	c++ -c $(GCCOPT) $<

.PHONY: depend clean


# DO NOT DELETE THIS LINE -- make depend depends on it.

Scrabble.o: /usr/include/string.h /usr/include/features.h
Scrabble.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
Scrabble.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h
Scrabble.o: ScrabbleBoard.h ScrabblePosition.h ScrabbleDictionary.h
Scrabble.o: /usr/include/ctype.h /usr/include/bits/types.h
Scrabble.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
Scrabble.o: /usr/include/endian.h /usr/include/bits/endian.h ScrabblePlay.h
ScrabblePlay.o: ScrabblePlay.h ScrabbleDictionary.h /usr/include/ctype.h
ScrabblePlay.o: /usr/include/features.h /usr/include/sys/cdefs.h
ScrabblePlay.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
ScrabblePlay.o: /usr/include/bits/wordsize.h
ScrabblePlay.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h
ScrabblePlay.o: /usr/include/bits/typesizes.h /usr/include/endian.h
ScrabblePlay.o: /usr/include/bits/endian.h ScrabblePosition.h
ScrabbleDictionary.o: ScrabbleDictionary.h /usr/include/ctype.h
ScrabbleDictionary.o: /usr/include/features.h /usr/include/sys/cdefs.h
ScrabbleDictionary.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
ScrabbleDictionary.o: /usr/include/bits/wordsize.h
ScrabbleDictionary.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h
ScrabbleDictionary.o: /usr/include/bits/typesizes.h /usr/include/endian.h
ScrabbleDictionary.o: /usr/include/bits/endian.h
ScrabbleBoard.o: ScrabbleBoard.h ScrabblePosition.h ScrabbleDictionary.h
ScrabbleBoard.o: /usr/include/ctype.h /usr/include/features.h
ScrabbleBoard.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
ScrabbleBoard.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
ScrabbleBoard.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h
ScrabbleBoard.o: /usr/include/bits/typesizes.h /usr/include/endian.h
ScrabbleBoard.o: /usr/include/bits/endian.h ScrabblePlay.h
ScrabblePosition.o: ScrabbleBoard.h ScrabblePosition.h ScrabbleDictionary.h
ScrabblePosition.o: /usr/include/ctype.h /usr/include/features.h
ScrabblePosition.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
ScrabblePosition.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
ScrabblePosition.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stddef.h
ScrabblePosition.o: /usr/include/bits/typesizes.h /usr/include/endian.h
ScrabblePosition.o: /usr/include/bits/endian.h ScrabblePlay.h
