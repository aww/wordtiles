#ifndef SCRABBLEDICTIONARY_HEADER
#define SCRABBLEDICTIONARY_HEADER

#include <ctype.h>
#include <vector>
#include <map>

//###############################################################################
// WordTreeNode class
//###############################################################################

class WordTreeNode {
public:
  WordTreeNode() { for (int i=0; i<26; ++i) fL[i] = 0; fEnd = false; };
  ~WordTreeNode() { for (int i=0; i<26; ++i) delete fL[i]; };
  void Add(const char *str);

  bool Validate(const char *str);

  int Count(void);

  WordTreeNode * fL[26];
  bool fEnd;
};


//###############################################################################
// ScrabbleDictionary class
//###############################################################################

#define MAX_WORD_LENGTH 15

class ScrabbleDictionary {
public:
  ScrabbleDictionary() { fD.resize(MAX_WORD_LENGTH+1); fTree = new WordTreeNode; };
  ~ScrabbleDictionary() { delete fTree; };

  void Load(const std::string &str);
  void PrintStats(void);
  bool Validate(const std::string &str);

  // Sorted by number of characters, then sorted character set
  std::vector<std::multimap<std::string,std::string> > fD;
  WordTreeNode *fTree;
  
};

#endif //#ifndef SCRABBLEDICTIONARY_HEADER
