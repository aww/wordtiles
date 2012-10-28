
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#ifndef WORDTILESPOSITION_HEADER
#define WORDTILESPOSITION_HEADER

#include <iostream>

class WordTilesBoard;

//###############################################################################
// WordTilesPosition class
//###############################################################################

class WordTilesPosition {
public:
  WordTilesPosition(int x=-1, int y=-1, WordTilesBoard *board = 0) : fX(x), fY(y), fBoard(board)
  { fHasTile = false; fLetter = ' '; fScore = 0; fMultiplier = 0; fUp = 0; fDown = 0; fRight = 0; fLeft = 0; };
  ~WordTilesPosition() {};

  inline int GetX(void) const { return fX; };
  inline int GetY(void) const { return fY; };

  inline char GetLetter(void) const { return fLetter; };
  inline int GetScore(void) const { return fScore; };

  inline void SetMultiplier(int m) { fMultiplier = m; };
  inline int GetMultiplier(void) const { return fMultiplier; };

  inline WordTilesPosition* GetUp(void)    const { return fUp; };
  inline WordTilesPosition* GetDown(void)  const { return fDown; };
  inline WordTilesPosition* GetRight(void) const { return fRight; };
  inline WordTilesPosition* GetLeft(void)  const { return fLeft; };

  void SetTile(char letter, int score);
  inline void SetChar(char letter) { fLetter = letter; };

  inline void SetUp(WordTilesPosition* p)    { fUp = p; };
  inline void SetDown(WordTilesPosition* p)  { fDown = p; };
  inline void SetRight(WordTilesPosition* p) { fRight = p; };
  inline void SetLeft(WordTilesPosition* p)  { fLeft = p; };
  
  inline void Print (void) { std::cout << ' ' << fLetter << ' '; };

  inline bool HasTile(void) { return fHasTile; };

  inline bool Playable(void) {
    return(! HasTile() &&
           ((GetLeft()     && GetLeft()->HasTile())
            || (GetRight() && GetRight()->HasTile())
            || (GetUp()    && GetUp()->HasTile())
            || (GetDown()  && GetDown()->HasTile()))); };
  
  //  void Search(string rack, WordTilesDictionary &dict);
  
private:
  WordTilesPosition *fUp;
  WordTilesPosition *fDown;
  WordTilesPosition *fRight;
  WordTilesPosition *fLeft;
  bool fHasTile;
  char fLetter;
  int fScore;
  int fMultiplier;
  int fX;
  int fY;
  WordTilesBoard *fBoard;
};

#endif //#ifndef WORDTILESPOSITION_HEADER
