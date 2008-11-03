
#include <iomanip>

#include <string.h>
#include <iostream>
#include <fstream>

#include "ScrabbleBoard.h"

using namespace std;


void BothTurns(int &total1, ScrabblePosition* pos1, char *tiles1, ScrabblePlay::DirOfPlay dir1,
               int &total2, ScrabblePosition* pos2, char *tiles2, ScrabblePlay::DirOfPlay dir2) {
  ScrabblePlay play;
  play.Set(pos1, tiles1, dir1);
  int score1 = play.Play();
  total1 += score1;
  play.Set(pos2, tiles2, dir2);
  int score2 = play.Play();
  total2 += score2;
  cout << setw(12) << tiles1 << setw(4) << score1 << setw(4) << total1
       << setw(12) << tiles2 << setw(4) << score2 << setw(4) << total2 << "\n";
}

int main (int argc, const char *argv[]) {

  if (argc < 2 || argc > 3) {
    cout << "Usage: " << argv[0] << " <gamefile> [rack]" << endl;
    return 1;
  }

  ScrabbleBoard *board = new ScrabbleBoard;


  // Load the dictionary
  ScrabbleDictionary *dict = new ScrabbleDictionary;
  ifstream wordlist_file("TWL06.txt", ifstream::in);
  string word;
  int word_count = 0;
  while (wordlist_file.good()) {
    wordlist_file >> word;
    if (word == "") continue;
    dict->Load(word);
    word_count++;
  }
  cout << "Read in " << word_count << " words.\n";
  //dict->PrintStats();

  ScrabblePlay::SetDefaultDict(dict);


  std::vector<ScrabblePlay> plays;

  ifstream input(argv[1], ifstream::in);

  string name, tiles;
  int x, y;
  char dir;
  ScrabblePlay play;
  int i=0;
  while (input.good()) {
    input >> name >> x >> y >> dir >> tiles;
    if (! input.good()) break;
    play.Set(board->GetXY(x,y), tiles.c_str(), dir == '>' ? ScrabblePlay::right : ScrabblePlay::down, name);
    play.SetVerbose();
    play.Play();
    plays.push_back(play);
    i++;
  }

  cout << "\n";

  int total[2] = {0,0};
  i=0;
  for (std::vector<ScrabblePlay>::iterator itr = plays.begin(); itr != plays.end(); ++itr) {
    total[i%2] += itr->GetScore();
    cout << setw(10) << itr->GetPlayer() << " plays " << setw(12) << itr->GetTiles()
         << " for " << setw(3) << itr->GetScore() << " points (total " << setw(3) << total[i%2] << ")"
         << " at (" << setw(2) << itr->GetPosition()->GetX() << ", " << setw(2) << itr->GetPosition()->GetY() << ") "
         << (itr->GetDir() == ScrabblePlay::right ? '>' : 'v')  << endl;
    i++;
  }

  board->Print();

  if (argc == 3) {

    std::string rack(argv[2]);
    
    // Normalize the rack, all letter go to uppercase and everything else to '*'
    // Also, remove these tiles from the pool.
    for (std::string::iterator itr = rack.begin(); itr != rack.end(); ++itr) {
      if (isalpha(*itr)) *itr = toupper(*itr);
      else               *itr = '*';
      board->RemoveTile(*itr);
    }

    cout << "\nPool of tiles is\n";
    board->PrintPool();

    cout << "\nRack is " << rack << "\n";

    // Search for plays
    cout << "\nSearch results\n";
    board->Search(rack.c_str(), dict);

  } else {

    cout << "\nPool of tiles is\n";
    board->PrintPool();

  }
  
  delete dict;
  delete board;
  
  return 0;
}
