
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

// Letter Tiles Analysis software - LetterTilesBoard
// Author: Alan Wilson (alan.w.wilson@gmail.com)
// All rights reserved.

#include "WordTilesBoard.h"

void WordTilesPosition::SetTile(char letter, int score) {
  fLetter = letter;
  fScore = score;
  fHasTile = true;
  if (fBoard) fBoard->RemoveTile(letter);
};
