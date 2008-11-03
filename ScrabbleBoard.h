#ifndef SCRABBLEBOARD_HEADER
#define SCRABBLEBOARD_HEADER

#include "ScrabblePosition.h"
#include "ScrabbleDictionary.h"
#include "ScrabblePlay.h"

#include <ctype.h>
#include <vector>

//###############################################################################
// ScrabbleBoard class
//###############################################################################

class ScrabbleBoard {
public:
  ScrabbleBoard();
  ~ScrabbleBoard();

  void Print(void);
  void PrintPool(void);

  void Set(int x, int y, char letter, int score);

  int Search(std::string rack, ScrabbleDictionary *dict);

  void RemoveTile(char letter);

  ScrabblePosition* GetXY(int x, int y) { return fBoard[x][y]; };

private:
  ScrabblePosition* fBoard[15][15];
  static const int fScoringMap[15][15];

  void SearchHelper(WordTreeNode *node, const char *pattern, const char *rack, std::string tiles);
  std::vector<ScrabblePlay> fPlays;
  ScrabblePosition *fSearchPos;
  ScrabblePlay::DirOfPlay fSearchDir;

  int fTilesLeft[27];
  static const int fTileFrequency[27];
};

#endif //#ifndef SCRABBLEBOARD_HEADER
