
#include "ScrabbleDictionary.h"

#include <iostream>

//###############################################################################
// WordTreeNode class
//###############################################################################


void WordTreeNode::Add(const char *str) {
  if (*str == '\0') {
    fEnd = true;
    return;
  }
  int i = toupper(*str) - 'A';
  if (i < 0 || i > 25) {
    std::cerr << "WordTreeNode::Add got invalid i=" << i << std::endl;
    return;
  }
  if (! fL[i]) fL[i] = new WordTreeNode;
  fL[i]->Add(str+1);
}

int WordTreeNode::Count(void) {
  int count = 1;
  for (int i=0; i<26; ++i)
    if (fL[i]) count += fL[i]->Count();
  return count;
}

bool WordTreeNode::Validate(const char *str) {
  char c = *str;
  if (c == '\0') {
    return fEnd;
  } else if (isalpha(c)) {
    int index = toupper(c) - 'A';
    if (fL[index]) return fL[index]->Validate(str+1);
    else return false;
  } else {
    return false;
  }
}

//###############################################################################
// ScrabbleDictionary class
//###############################################################################


void SortString(std::string &str) {
  int length = str.size();
  for (int i=0; i<length-1; ++i) {
    for (int j=i+1; j<length; ++j) {
      if (str[i] > str[j]) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
      }
    }
  }
}

void ScrabbleDictionary::Load(const std::string &str) {
  int length = str.size();
  if (length > MAX_WORD_LENGTH) {
    std::cout << "Can't deal with words longer than " << MAX_WORD_LENGTH << " : " << str << "\n";
    return;
  }
  std::string sorted_str(str);
  SortString(sorted_str);
  //std::cout << "sorted: " << sorted_str << "\n";
  fD.at(str.size()).insert(std::pair<std::string, std::string>(sorted_str, str));

  fTree->Add(str.c_str());
}

bool ScrabbleDictionary::Validate(const std::string &str) {
//   std::string sorted_str(str);
//   SortString(sorted_str);

//   std::multimap<std::string,std::string> &mm = fD.at(str.size());
//   std::multimap<std::string,std::string>::iterator itr = mm.find(sorted_str);
//   if (itr == mm.end()) return false;
//   do {
//     if (itr->second == str) return true;
//     itr++;
//   } while (itr->first == sorted_str);
//   return false;
  return fTree->Validate(str.c_str());
}

void ScrabbleDictionary::PrintStats(void) {
  for (int i=1; i<=MAX_WORD_LENGTH; ++i) {
    printf("%10d words of length %2d\n", fD.at(i).size(), i);
  }

  std::vector<int> hist;
  std::vector<std::multimap<std::string,std::string> >::const_iterator vecitr = fD.begin();
  for (; vecitr != fD.end(); vecitr++) {
    std::multimap<std::string,std::string>::const_iterator itr = (*vecitr).begin();
    int counter = 0;
    std::string previous;
    if (itr != vecitr->end()) previous = itr->first;
    for (; itr != (*vecitr).end(); itr++) {
      //std::cout << "previous=" << previous << " current=" << itr->first << std::endl;
      if (itr->first == previous) {
        counter++;
      } else {
        if (hist.size() <= counter) hist.resize(counter+1, 0);
        hist[counter] += 1;
        previous = itr->first;
        counter = 1;
      }
    }
  }
  for (int i=1; i<hist.size(); ++i) {
    printf("Entries of multiplicity %2d : %6d\n", i, hist.at(i));    
  }
  std::cout << "Nodes in the tree: " << fTree->Count() << std::endl;
}
