#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
#include <iostream>

using namespace std;

list<char> telephoneMappings(char c, unordered_map<char, list<char> >& telephoneMapper) {
  auto itr = telephoneMapper.find(c);
  return itr->second;
}



void generateListToTry(unordered_set<string>& dict, list<list<string> > & result, vector<string>& soFar, string& test, int min, int current, int depthCount) {
  if (test.size() < min + current) {
    return;
  }

  for (int i = 0; i < test.size() - current - min - 1; ++i) {
    string s = test.substr(current, i);
    auto itr = dict.find(s);
    if (itr == dict.end()) { 
      return;
    }
    s = test.substr(i + 1, test.size() - 1);
    //auto
    itr = dict.find(s);
    if (itr != dict.end()) {
      list<string> oneSuccess;
      for (int j = 0; j < depthCount + 1; ++j) {
        oneSuccess.push_back(soFar[j]);
      }
      oneSuccess.push_back(s);
    }

    generateListToTry(dict, result, soFar, test, min, current + i, depthCount + 1);
  } 
}

void findAllCombinations(unordered_set<string>& dict, string& test, list<list<string> >& result, int min) {
  auto itr = dict.find(test);
  if (itr != dict.end()) {
    list<string> l;
    l.push_back(test);
    result.push_back(l);
  }

  vector<string> helperVec(test.size(), "");
  generateListToTry(dict, result, helperVec, test, min, 0, 0);
}

void generateCombinations(unordered_set<string>& dict, string& input, string& test, int current, list<list<string> >& result, unordered_map<char, list<char> >& telephoneMapper) {
  if (current == test.size()) {
    std::cout << "panda says: " << current << " and " << test << '\n';

    findAllCombinations(dict, test, result, 3);
    return;
  }

  for (auto c : telephoneMappings(input[current], telephoneMapper)) {
    test[current] = c;
    generateCombinations(dict, input, test, current + 1, result, telephoneMapper);
  }
}



int main() {
  unordered_set<string> dict = {
    "it",
    "your",
    "reality",
    "real",
    "our"
  };
  string input = "7325189087";
  string test(input.size(), ' ');


  list<list<string> > result;
  unordered_map<char, list<char> > telephoneMapper = {
      { '1', { 'i', 'j' } },
      { '2', { 'a', 'b', 'c' } },
      { '3', { 'd', 'e', 'f' } },
      { '4', { 'g', 'h' } },
      { '5', { 'k', 'l' } },
      { '6', { 'm', 'n' } },
      { '7', { 'p', 'r', 's' } },
      { '8', { 't', 'u', 'v' } },
      { '9', { 'w', 'x', 'y' } },
      { '0', { 'o', 'q', 'z' } },
  };
  generateCombinations(dict, input, test, 0, result, telephoneMapper);

  for (auto lists : result) {
    for (auto s : lists) {
      std::cout << s << ' ';
    }
    std::cout << '\n';
  }


  return 0;
}


