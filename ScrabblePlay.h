#ifndef SCRABBLEPLAY_HEADER
#define SCRABBLEPLAY_HEADER

#include "ScrabbleDictionary.h"
#include "ScrabblePosition.h"

#include <ctype.h>

//###############################################################################
// ScrabblePlay class
//###############################################################################

class ScrabblePlay {
public:
  enum DirOfPlay {
    right,
    down
  };

  ScrabblePlay() { fPos = 0; fScore = 0; fDict = 0; fVerbose = false; };
  ScrabblePlay(ScrabblePosition* pos, const char *tiles, DirOfPlay dir, const std::string &player = "", ScrabbleDictionary *dict=0)
                 { ScrabblePlay(); Set(pos, tiles, dir, player, dict); };
  ~ScrabblePlay() { };

  void Set(ScrabblePosition* pos, const char *tiles, DirOfPlay dir, const std::string &player = "", ScrabbleDictionary *dict=0);

  int Play(void);

  inline const ScrabblePosition * GetPosition(void) { return fPos; };
  inline const std::string & GetTiles(void) { return fTiles; };
  inline const std::string & GetWord(void) { return fWord; };
  inline DirOfPlay GetDir(void) { return fDir; };
  inline const std::string & GetPlayer(void) { return fPlayer; };
  inline int GetScore(void) { return fScore; };

  void Print(void);
  bool operator<(const ScrabblePlay &other) const { return fScore < other.fScore; };

  void SetVerbose(bool verb = true) { fVerbose = verb; };

  static void SetDefaultDict(ScrabbleDictionary *dict) { fDefaultDict = dict; };

private:
  ScrabblePosition *fPos;
  std::string fTiles;
  std::string fWord;
  DirOfPlay fDir;
  std::string fPlayer;

  void CalcScore(void);
  int fScore;

  bool fVerbose;

  ScrabbleDictionary *fDict;
  static ScrabbleDictionary *fDefaultDict;

  static const int fPointMap[26];
};

#endif //#ifndef SCRABBLEPLAY_HEADER
