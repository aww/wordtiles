WordTiles
=========

WordTiles parses .wordtiles files to reconstruct a game of placing letters on tiles down on a grid to form words. (Compare to Scrabble (TM))
It verifies that the plays are valid, totals the score, and keeps track of how many of each tile remains hidden.
Given your current set of tiles it will also provide a list of the highest scoring plays.
It reads TWL06.txt to form the dictionary of valid words.

Building
--------

You should be able to build by just doing

    make

or

    scons


Running
-------

To run you give it a path to the game file (my files use the suffix .wordtiles) and optionally the letters you have on your rack (if you want to compute highest scoring moves). There are example files which you can try, for example

    ./wordtiles example_games/2008-12-24-Tiffany-Mom.wordtiles |less


Game files
----------

The most important lines in the game files are of the form

    play <name> <x-index> <y-index> <direction> <play>

where the fields are separated by spaces.  These specify what each player played.  The name is the player name and can be anything without spaces, but should be consistent for totals to make sense. The x-index and y-index are integers starting from 0 at the bottom left. The direction is the character '>' for horizontal words and 'v' for vertical words. The play is a string using uppercase letters for regular lettered tiles, lowercase letters for blank tiles that have been given a letter value, and '.' for existing letters that are part of the primary word.

The file can also have

    has <name> <rack>

where <rack> is a string of letters and . or _ for blank tiles.  Wherever this is given the top plays for this player at this point in the game will be computed and displayed (even if out-of-turn).

There are also a couple possibly entries that are not yet implemented such as 'contests' and 'pass'.
