
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#ifndef WORDTILESPLAY_HEADER
#define WORDTILESPLAY_HEADER

#include "WordTilesDictionary.h"
#include "WordTilesPosition.h"

#include <ctype.h>

//###############################################################################
// WordTilesPlay class
//###############################################################################

class WordTilesPlay {
public:
  enum DirOfPlay {
    right,
    down
  };

  WordTilesPlay() { fPos = 0; fScore = 0; fDict = 0; fVerbose = false; };
  WordTilesPlay(WordTilesPosition* pos, const char *tiles, DirOfPlay dir, const std::string &player = "", WordTilesDictionary *dict=0)
                 { WordTilesPlay(); Set(pos, tiles, dir, player, dict); };
  ~WordTilesPlay() { };

  void Set(WordTilesPosition* pos, const char *tiles, DirOfPlay dir, const std::string &player = "", WordTilesDictionary *dict=0);

  int Play(void);

  inline const WordTilesPosition * GetPosition(void) { return fPos; };
  inline const std::string & GetTiles(void) { return fTiles; };
  inline const std::string & GetWord(void) { return fWord; };
  inline DirOfPlay GetDir(void) { return fDir; };
  inline const std::string & GetPlayer(void) { return fPlayer; };
  inline int GetScore(void) { return fScore; };

  void Print(void);
  bool operator<(const WordTilesPlay &other) const { return fScore < other.fScore; };

  void SetVerbose(bool verb = true) { fVerbose = verb; };

  static void SetDefaultDict(WordTilesDictionary *dict) { fDefaultDict = dict; };

private:
  WordTilesPosition *fPos;
  std::string fTiles;
  std::string fWord;
  DirOfPlay fDir;
  std::string fPlayer;

  void CalcScore(void);
  int fScore;

  bool fVerbose;

  WordTilesDictionary *fDict;
  static WordTilesDictionary *fDefaultDict;

  static const int fPointMap[26];
};

#endif //#ifndef WORDTILESPLAY_HEADER
