

#include "ScrabbleBoard.h"

void ScrabblePosition::SetTile(char letter, int score) {
  fLetter = letter;
  fScore = score;
  fHasTile = true;
  if (fBoard) fBoard->RemoveTile(letter);
};
