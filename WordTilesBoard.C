
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#include "WordTilesBoard.h"

#include <string.h>
#include <iomanip>
#include <algorithm>

using namespace std;


//###############################################################################
// WordTilesBoard class
//###############################################################################

const int WordTilesBoard::fTileFrequency[27] = {
//A  B  C  D   E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  _
  9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1, 2
};

const int WordTilesBoard::fScoringMap[15][15] = {
  {4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4 },
  {0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0 },
  {0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0 },
  {1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1 },
  {0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 },
  {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0 },
  {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
  {4, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 4 },
  {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
  {0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0 },
  {0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 },
  {1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1 },
  {0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0 },
  {0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0 },
  {4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4 },
};
 
WordTilesBoard::WordTilesBoard(void) {
  for (int iy = 0; iy < 15; ++iy) {
    for (int ix = 0; ix < 15; ++ix) {
      fBoard[ix][iy] = new WordTilesPosition(ix, iy, this);
      fBoard[ix][iy]->SetMultiplier(fScoringMap[ix][iy]);
    }
  }
  for (int iy = 0; iy < 15; ++iy) {
    for (int ix = 0; ix < 15; ++ix) {
      if (ix != 0)  fBoard[ix][iy]->SetLeft( fBoard[ix-1][iy]);
      if (ix != 14) fBoard[ix][iy]->SetRight(fBoard[ix+1][iy]);
      if (iy != 0)  fBoard[ix][iy]->SetUp(   fBoard[ix]  [iy-1]);
      if (iy != 14) fBoard[ix][iy]->SetDown( fBoard[ix]  [iy+1]);
    }
  }
  for (int i=0; i<27; ++i) {
    fTilesLeft[i] = fTileFrequency[i];
  }
}

WordTilesBoard::~WordTilesBoard() {
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) {
      delete fBoard[i][j];
    }
  }
}

void WordTilesBoard::Print(void) {
  cout << "   ";
  for (int ix = 0; ix < 15; ++ix) {
    cout << "  " << setw(2) << ix;
  }
  cout << "\n";
  for (int iy = 0; iy < 15; ++iy) {
    cout << "    -----------------------------------------------------------\n";
    cout << setw(2) << iy << " ";
    for (int ix = 0; ix < 15; ++ix) {
      cout << "|";
      fBoard[ix][iy]->Print();
    }
    cout << "|\n";
  }
  cout << "    -----------------------------------------------------------\n";
}

void WordTilesBoard::PrintPool(void) {
  int tiles[27];
  for (int i=0; i<27; ++i) tiles[i] = fTilesLeft[i];
  bool notdone = true;
  cout << "+---------------------------+\n";
  while (notdone) {
    notdone = false;
    cout << "|";
    for (int i=0; i<27; ++i) {
      if (tiles[i] > 0) {
        cout << (i == 26 ? '*' : (char)('A' + i));
        if (--tiles[i]) notdone = true;
      } else if (tiles[i] == 0) {
        cout << ' ';
      } else {
        cout << '^';
      }
    }
    cout << "|\n";
  }
  cout << "+---------------------------+\n";
}

void WordTilesBoard::Set(int x, int y, char letter, int score) {
  fBoard[x][y]->SetTile(letter, score);
}

void WordTilesBoard::RemoveTile(char letter) {
  if (isupper(letter)) {
    fTilesLeft[letter - 'A']--;
  } else if (islower(letter)) {
    fTilesLeft[26]--;
  }
}

void WordTilesBoard::SearchHelper(WordTreeNode *node, const char *pattern, const char *rack, string tiles) {
  //cout << "SearchHelper(" << pattern << ", " << rack << ", " << tiles << ")\n";
  if (*pattern == '\0') {
    if (node->fEnd == true) { // Found a word!
      WordTilesPlay play;
      play.Set(fSearchPos, tiles.c_str(), fSearchDir);
      if (play.GetScore() > 0) {
        fPlays.push_back(play);
      }
    }
  } else if (*pattern == ' ') {
    int charbitmap = 0; // so we only try a character once.
    char subrack[8];
    int len = strlen(rack);
    for (int i=0; i<len; ++i) {
      char curchar = rack[i];
      if (isalpha(curchar)) {
        int index = toupper(curchar) - 'A';
        if (((charbitmap >> index) & 0x1) == 0) {
          charbitmap |= 0x1 << index;
          if (node->fL[index]) {
            string newtiles(tiles);
            newtiles.push_back(curchar);
            strcpy(subrack+i, rack+i+1);
            SearchHelper(node->fL[index], pattern+1, subrack, newtiles);
          }
        }
      } else if (curchar == '*') { // blank tile
        if (((charbitmap >> 26) & 0x1) == 0) {
          charbitmap |= 0x1 << 26;
          strcpy(subrack+i, rack+i+1);
          for (int l=0; l<26; l++) {
            if (node->fL[l]) {
              string newtiles(tiles);
              newtiles.push_back((char)l+'a');
              SearchHelper(node->fL[l], pattern+1, subrack, newtiles);
            }
          }
        }
      }
      subrack[i] = curchar;
    }
  } else if (isalpha(*pattern)) {
    int index = toupper(*pattern) - 'A';
    tiles.push_back('.');
    if (node->fL[index]) SearchHelper(node->fL[index], pattern+1, rack, tiles); 
  }
  
}

int WordTilesBoard::Search(string rack, WordTilesDictionary *dict) {

  fPlays.clear();

  fSearchDir = WordTilesPlay::right;
  for (int j = 0; j < 15; ++j) {
    for (int i = 0; i < 15; ++i) {
      WordTilesPosition *pos = fBoard[i][j];
      WordTilesPosition *end = pos;
      if (! pos->GetLeft() || ! pos->GetLeft()->HasTile()) {
        string pattern;
        bool playable = false;
        int len = 1;
        int free = 0;
        while (end) {
          if (end->Playable()) playable = true;
          if (end->HasTile()) {
            pattern.push_back(end->GetLetter());
          } else {
            pattern.push_back(' ');
            if (++free > 7) break;
          }
          end = end->GetRight();
          if (len > 1 && ( ! end || ! end->HasTile()) && playable) {
            //cout << setw(2) << len << " Pattern: '" << pattern << "'\n";
            fSearchPos = pos;
            SearchHelper(dict->fTree, pattern.c_str(), rack.c_str(), "");
          }
          len++;
        }
      }    
    }
  }

  fSearchDir = WordTilesPlay::down;
  for (int j = 0; j < 15; ++j) {
    for (int i = 0; i < 15; ++i) {
      WordTilesPosition *pos = fBoard[i][j];
      WordTilesPosition *end = pos;
      if (! pos->GetUp() || ! pos->GetUp()->HasTile()) {
        string pattern;
        bool playable = false;
        int len = 1;
        int free = 0;
        while (end) {
          if (end->Playable()) playable = true;
          if (end->HasTile()) {
            pattern.push_back(end->GetLetter());
          } else {
            pattern.push_back(' ');
            if (++free > 7) break;
          }
          end = end->GetDown();
          if (len > 1 && ( ! end || ! end->HasTile()) && playable) {
            //cout << setw(2) << len << " Pattern: '" << pattern << "'\n";
            fSearchPos = pos;
            SearchHelper(dict->fTree, pattern.c_str(), rack.c_str(), "");
          }
          len++;
        }
      }
    }
  }


  std::sort(fPlays.begin(), fPlays.end());
  std::reverse(fPlays.begin(), fPlays.end());

  vector<WordTilesPlay>::iterator play_itr=fPlays.begin();
  int i=0;
  for (; play_itr != fPlays.end() && i < 25; ++play_itr, ++i) {
    play_itr->Print();
  }

  return 0;
}


