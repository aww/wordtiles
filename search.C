
#include <iostream>
#include <fstream>


int main (int argc, char **argv) {

  int climit = 100;
  switch (argc) {
  case 2:
    break;
  case 3:
    climit = atoi(argv[2]);
    break;
  default:
    std::cout << "Usage: " << argv[0] << " <characters> [char limit]\n";
    return(1);
  }

  std::ifstream wordlist_file("TWL06.txt", std::ifstream::in);
  std::string word;
  while (wordlist_file.good()) {
    wordlist_file >> word;
    if (word == "") continue;
    if (word.size() > climit) continue;
    //std::cout << word << "\n";
    std::string word_mod(word);
    char *c = argv[1];
    for (; *c != '\0'; ++c) {
      //std::cout << " " << *c << "\n";
      bool found = false;
      std::string::iterator w;
      for (w = word_mod.begin(); w != word_mod.end(); ++w) {
        if (*w == *c) {
          word_mod.erase(w);
          found = true;
          break;
        }
      }
      //std::cout << "  " << word_mod << "\n";
      if (!found) {
        break;
      }
    }
    if (*c == '\0') {
      std::cout << word << "\n";
    }
  }

}
