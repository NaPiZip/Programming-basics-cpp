
#ifndef _HEADER_TRIE_
#define _HEADER_TRIE_

#include <vector>
#include <string>
#include <iostream>

#define DEBUG true
#define DEBUG_PRINT(str) if(DEBUG){cout << str << endl;}

using namespace std;

struct TrieNode{
  char letter;
  bool isWord;
  vector<TrieNode*> vertex;
};

void add_word(struct TrieNode* node, string word);
void remove_word(struct TrieNode* node, string word);
bool exists(struct TrieNode* node, string word);
int count_words(struct TrieNode* node);

// helper function
TrieNode* char_in_vertex(vector<TrieNode*>& vertex, char letter);
int find_lowest_barch_index(struct TrieNode* node, string word);

#endif //_HEADER_TRIE_
