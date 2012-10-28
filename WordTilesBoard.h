
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#ifndef WORDTILESBOARD_HEADER
#define WORDTILESBOARD_HEADER

#include "WordTilesPosition.h"
#include "WordTilesDictionary.h"
#include "WordTilesPlay.h"

#include <ctype.h>
#include <vector>

//###############################################################################
// WordTilesBoard class
//###############################################################################

class WordTilesBoard {
public:
  WordTilesBoard();
  ~WordTilesBoard();

  void Print(void);
  void PrintPool(void);

  void Set(int x, int y, char letter, int score);

  int Search(std::string rack, WordTilesDictionary *dict);

  void RemoveTile(char letter);

  WordTilesPosition* GetXY(int x, int y) { return fBoard[x][y]; };

private:
  WordTilesPosition* fBoard[15][15];
  static const int fScoringMap[15][15];

  void SearchHelper(WordTreeNode *node, const char *pattern, const char *rack, std::string tiles);
  std::vector<WordTilesPlay> fPlays;
  WordTilesPosition *fSearchPos;
  WordTilesPlay::DirOfPlay fSearchDir;

  int fTilesLeft[27];
  static const int fTileFrequency[27];
};

#endif //#ifndef WORDTILESBOARD_HEADER
