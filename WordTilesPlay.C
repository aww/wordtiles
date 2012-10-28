
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#include "WordTilesPlay.h"

#include <iomanip>

using namespace std;

//###############################################################################
// WordTilesPlay class
//###############################################################################

WordTilesDictionary *WordTilesPlay::fDefaultDict = 0;

const int WordTilesPlay::fPointMap[26] = {
//A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P   Q  R  S  T  U  V  W  X  Y   Z
  1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

void WordTilesPlay::Set(WordTilesPosition* pos, const char *tiles, DirOfPlay dir, const std::string &player, WordTilesDictionary *dict) {
  fTiles = tiles;
  fPos = pos;
  fDir = dir;
  fPlayer = player;
  if (dict) fDict = dict;
  else      fDict = fDefaultDict;
  CalcScore();
}

void WordTilesPlay::Print(void) {
  cout << "Scoring " << setw(3) << fScore
       << " with " << setw(15) << fWord
       << " using play " << setw(15) << fTiles
       << " going " << (fDir == right ? "right" : "down ")
       << " from " << setw(2) << fPos->GetX() << "," << setw(2) << fPos->GetY()
       << "\n";
}

int WordTilesPlay::Play(void) {
  WordTilesPosition *pos = fPos;
  const char *tilepos = fTiles.c_str();
  char tile = *tilepos;
  while (tile != '\0' && pos) {
    if (isupper(tile)) pos->SetTile(tile, fPointMap[tile-'A']);
    if (islower(tile)) pos->SetTile(tile, 0);

    if (fDir == down) pos = pos->GetDown();
    else              pos = pos->GetRight();
    tilepos++;
    tile = *tilepos;
  }
  return fScore;
}


void WordTilesPlay::CalcScore(void) {

  int count_from_rack = 0;
  int totaux_score = 0;
  int pri_score = 0;
  int pri_multiplier = 1;
  string pri_word("");
  bool valid = true;

  WordTilesPosition *pos = fPos;
  const char *tilepos = fTiles.c_str();
  char tile = *tilepos;

  if (fDir == down && pos->GetUp() && pos->GetUp()->HasTile()
      || fDir == right && pos->GetLeft() && pos->GetLeft()->HasTile()) {
    fScore = 0;
    if (fVerbose) cout << "Invalid start of " << fTiles << endl;
    return;
  }

  while (pos && tile != '\0') {
    //cout << "in CalcScore(): tile = " << tile << "\n";
    if (isalpha(tile)) count_from_rack++;

    // Calculate the score from this tile
    int score = 0;
    int aux_score = 0;
    string aux_word("");
    aux_word.push_back(tile);
    if (isalpha(tile)) { // New tile played on board
      pri_word.push_back(toupper(tile));

      if (isupper(tile)) { // Regular tile
        score = fPointMap[tile-'A'];
        if      (pos->GetMultiplier() == 1) score *= 2;
        else if (pos->GetMultiplier() == 2) score *= 3;
      }

      WordTilesPosition *auxpos;
      if (fDir == down) {
        auxpos = pos;
        while (auxpos->GetLeft() && auxpos->GetLeft()->HasTile()) {
          auxpos = auxpos->GetLeft();
          aux_score += auxpos->GetScore();
          aux_word.insert(aux_word.begin(), toupper(auxpos->GetLetter()));
        }
        auxpos = pos;
        while (auxpos->GetRight() && auxpos->GetRight()->HasTile()) {
          auxpos = auxpos->GetRight();
          aux_score += auxpos->GetScore();
          aux_word.push_back(toupper(auxpos->GetLetter()));
        }
      } else {
        auxpos = pos;
        while (auxpos->GetUp() && auxpos->GetUp()->HasTile()) {
          auxpos = auxpos->GetUp();
          aux_score += auxpos->GetScore();
          aux_word.insert(aux_word.begin(), toupper(auxpos->GetLetter()));
        }
        auxpos = pos;
        while (auxpos->GetDown() && auxpos->GetDown()->HasTile()) {
          auxpos = auxpos->GetDown();
          aux_score += auxpos->GetScore();
          aux_word.push_back(toupper(auxpos->GetLetter()));
        }
      }
      // If we found anything then don't forget to add the tile in the primary word.
      if (aux_word.size() > 1) aux_score += score;

      // Apply word multipliers
      if      (pos->GetMultiplier() == 3) {
        aux_score *= 2;
        pri_multiplier *= 2;
      }
      else if (pos->GetMultiplier() == 4) {
        aux_score *= 3;
        pri_multiplier *= 3;
      }

    } else { // Tile was already on the board
      score = pos->GetScore();
      pri_word.push_back(toupper(pos->GetLetter()));
    }

    totaux_score += aux_score;    
    pri_score += score;

    if (aux_score) {
      if (fVerbose) cout << "Auxiallary word '" << aux_word << "' ";
      if (fDict) {
        if (fDict->Validate(aux_word)) {
          if (fVerbose) cout << "scoring " << aux_score << " is valid." << endl;
        } else {
          if (fVerbose) cout << "is INVALID." << endl;
          fScore = 0;
          return;
        }
      } else {
        if (fVerbose) cout << "was not validated." << endl;
      }
    }
 
    if (fDir == down) pos = pos->GetDown();
    else              pos = pos->GetRight();
    tilepos++;
    tile = *tilepos;
  }

  if (pos && pos->HasTile()) {
    fScore = 0;
    if (fVerbose) cout << "Invalid end of " << fTiles << endl;
    return;
  }
  
  pri_score *= pri_multiplier;

  if (fVerbose) cout << "Primary word '" << pri_word << "' ";
  if (fDict) {
    if (fDict->Validate(pri_word)) {
      if (fVerbose) cout << "scoring " << pri_score << " is valid." << endl;
    } else {
      if (fVerbose) cout << "is INVALID." << endl;
      fScore = 0;
      return;
    }
  } else {
    if (fVerbose) cout << "was not validated." << endl;
  }

  //cout << "in CalcScore(): totaux_score = " << totaux_score << ", pri_score = " << pri_score << ", count_from_rack = " << count_from_rack << "\n";
  fWord = pri_word;
  fScore = totaux_score + pri_score;
  if (count_from_rack >= 7) fScore += 50; // Bingo
}


