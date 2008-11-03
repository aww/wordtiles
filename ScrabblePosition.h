#ifndef SCRABBLEPOSITION_HEADER
#define SCRABBLEPOSITION_HEADER

#include <iostream>

class ScrabbleBoard;

//###############################################################################
// ScrabblePosition class
//###############################################################################

class ScrabblePosition {
public:
  ScrabblePosition(int x=-1, int y=-1, ScrabbleBoard *board = 0) : fX(x), fY(y), fBoard(board)
  { fHasTile = false; fLetter = ' '; fScore = 0; fMultiplier = 0; fUp = 0; fDown = 0; fRight = 0; fLeft = 0; };
  ~ScrabblePosition() {};

  inline int GetX(void) const { return fX; };
  inline int GetY(void) const { return fY; };

  inline char GetLetter(void) const { return fLetter; };
  inline int GetScore(void) const { return fScore; };

  inline void SetMultiplier(int m) { fMultiplier = m; };
  inline int GetMultiplier(void) const { return fMultiplier; };

  inline ScrabblePosition* GetUp(void)    const { return fUp; };
  inline ScrabblePosition* GetDown(void)  const { return fDown; };
  inline ScrabblePosition* GetRight(void) const { return fRight; };
  inline ScrabblePosition* GetLeft(void)  const { return fLeft; };

  void SetTile(char letter, int score);
  inline void SetChar(char letter) { fLetter = letter; };

  inline void SetUp(ScrabblePosition* p)    { fUp = p; };
  inline void SetDown(ScrabblePosition* p)  { fDown = p; };
  inline void SetRight(ScrabblePosition* p) { fRight = p; };
  inline void SetLeft(ScrabblePosition* p)  { fLeft = p; };
  
  inline void Print (void) { std::cout << ' ' << fLetter << ' '; };

  inline bool HasTile(void) { return fHasTile; };

  inline bool Playable(void) {
    return(! HasTile() &&
           ((GetLeft()     && GetLeft()->HasTile())
            || (GetRight() && GetRight()->HasTile())
            || (GetUp()    && GetUp()->HasTile())
            || (GetDown()  && GetDown()->HasTile()))); };
  
  //  void Search(string rack, ScrabbleDictionary &dict);
  
private:
  ScrabblePosition *fUp;
  ScrabblePosition *fDown;
  ScrabblePosition *fRight;
  ScrabblePosition *fLeft;
  bool fHasTile;
  char fLetter;
  int fScore;
  int fMultiplier;
  int fX;
  int fY;
  ScrabbleBoard *fBoard;
};

#endif //#ifndef SCRABBLEPOSITION_HEADER
