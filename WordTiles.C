
//
// Part of Alan Wilson's (alan.w.wilson@gmail.com) program
// for analyzing that game where you make words with tiles.
//

#include <iomanip>

#include <string.h>
#include <iostream>
#include <fstream>

#include <sstream>
#include <algorithm>
#include <iterator>

#include <ncurses.h>

#include "WordTilesBoard.h"

using namespace std;


void BothTurns(int &total1, WordTilesPosition* pos1, char *tiles1, WordTilesPlay::DirOfPlay dir1,
               int &total2, WordTilesPosition* pos2, char *tiles2, WordTilesPlay::DirOfPlay dir2) {
  WordTilesPlay play;
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

  WordTilesBoard *board = new WordTilesBoard;


  // Load the dictionary
  WordTilesDictionary *dict = new WordTilesDictionary;
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
  dict->PrintStats();

  WordTilesPlay::SetDefaultDict(dict);


  std::vector<WordTilesPlay> plays;

  ifstream input(argv[1], ifstream::in);

  string line;
  string command, name, tiles;
  int x, y;
  char dir;
  WordTilesPlay play;
  int move_count=0;
  while (input.good()) {
    // This gets a line and splits it into tokens via spaces
    getline(input, line);
    istringstream iss(line);
    std::vector<std::string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<std::vector<std::string> >(tokens));

    for (int i=0; i<tokens.size(); i++) {
      std::cout << tokens[i] << " ";
    }
    std::cout << "\n";

    if (tokens.size() == 0 || tokens[0].size() == 0) continue;

    if (tokens[0][0] == '#') continue;

    command = tokens[0];
    if (command == "add") {
      if (tokens.size() < 2) {
        std::cout << "ERROR: insufficient tokens after 'add': " << line << "\n";
      } else {
        word = tokens[1];
        cout << "\n";
        cout << "Adding " << word << " to the dictionary.\n";
        dict->Load(word);
      }

    } else if (command == "has") {
      if (tokens.size() < 3) {
        std::cout << "ERROR: insufficient tokens after 'has': " << line << "\n";
      } else {
        name = tokens[1];
        tiles = tokens[2];
        cout << "\n";
        cout << name << " has " << tiles << ".\n";
        for (std::string::iterator itr = tiles.begin(); itr != tiles.end(); ++itr) {
          if (isalpha(*itr)) *itr = toupper(*itr);
          else               *itr = '*';
        }
        board->Search(tiles.c_str(), dict);
      }

    } else if (command == "play") {
      if (tokens.size() < 6) {
        std::cout << "ERROR: insufficient tokens after 'play': " << line << "\n";
      } else {
        name = tokens[1];
        x = atoi(tokens[2].c_str());
        y = atoi(tokens[3].c_str());
        dir = tokens[4][0];
        tiles = tokens[5];
        cout << "\n";
        cout << name << " plays " << tiles << (dir == '>' ? " right" : " down")
             << " from (" << x << "," << y << ").\n";
        play.SetVerbose();
        play.Set(board->GetXY(x,y), tiles.c_str(), dir == '>' ? WordTilesPlay::right : WordTilesPlay::down, name);
        play.Play();
        plays.push_back(play);
        move_count++;
      }

    } else if (command == "pass") {
      if (tokens.size() < 2) {
        std::cout << "ERROR: insufficient tokens after 'pass': " << line << "\n";
      } else {
        name = tokens[1];
        cout << "\n";
        cout << name << " passes (NOT IMPLEMENTED!).\n";
        //
        // FILL IN
        //
      }

    } else if (command == "contests") {
      if (tokens.size() < 3) {
        std::cout << "ERROR: insufficient tokens after 'contests': " << line << "\n";
      } else {
        name = tokens[1];
        std::string status(tokens[2]);
        if (status != "succeeded" && status != "failed") {
          std::cout << "ERROR: result of contests must be 'succeeded' or 'failed': " << line << "\n";
        } else {
          cout << "\n";
          cout << name << " contests (NOT IMPLEMENTED!).\n";
          //
          // FILL IN
          //
        }
      }

    } else {
      cout << "ERROR: " << command << " is an unrecognized command.\n";
    }
  }

  cout << "\n";

  //initscr();

  std::map<string, int> total_score;
  for (std::vector<WordTilesPlay>::iterator itr = plays.begin(); itr != plays.end(); ++itr) {
    total_score[itr->GetPlayer()] += itr->GetScore();
    cout << setw(10) << itr->GetPlayer() << " plays " << setw(12) << itr->GetTiles()
         << " for " << setw(3) << itr->GetScore()
         << " points (total " << setw(3) << total_score[itr->GetPlayer()] << ")"
         << " at (" << setw(2) << itr->GetPosition()->GetX() << ", " << setw(2) << itr->GetPosition()->GetY() << ") "
         << (itr->GetDir() == WordTilesPlay::right ? '>' : 'v')  << endl;
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

  //getch();
  //endwin();
  
  return 0;
}
