#include "Trie.hpp"

TrieNode* char_in_vertex(vector<TrieNode*>& vertex, char letter)
{
  if(vertex.empty())
    return nullptr;

  auto it = vertex.begin();
  for(; it != vertex.end(); it++)
  {
    if((*it)->letter == letter)
    {
      return *it;
    }

  }
  return nullptr;
}

void add_word(struct TrieNode* node, string word)
{
  if(word.empty() || node == nullptr)
    return;

  TrieNode* searchNode = char_in_vertex(node->vertex, word.at(0));
  DEBUG_PRINT("Find in vertex : " << word.at(0) <<" "<< (searchNode==nullptr));

  if(searchNode == nullptr)
  {
    DEBUG_PRINT("Negative search");
    TrieNode* newNode = new TrieNode();
    newNode->letter = word.at(0);
    word.erase(0,1);

    if(word.empty())
      newNode->isWord = true;

    node->vertex.push_back(newNode);
    add_word(newNode, word);
  }else
  {
    DEBUG_PRINT("Positive search");
    word.erase(0,1);
    add_word(searchNode, word);
  }
}

bool exists(struct TrieNode* node, string word)
{
  if((node == nullptr) || word.empty())
    return false;

  TrieNode* searchNode = char_in_vertex(node->vertex, word.at(0));
  DEBUG_PRINT("Find in vertex : " << word.at(0) <<" "<< (searchNode==nullptr));

  if(searchNode != nullptr)
  {
    word.erase(0,1);

    if(word.empty() ==  true)
      return true;

    return exists(searchNode, word);
  }
}


int find_lowest_barch_index(struct TrieNode* node, string word)
{
  if((node == nullptr) || word.empty())
    return 0;

  TrieNode* searchNode = char_in_vertex(node->vertex, word.at(0));
  DEBUG_PRINT("Find in vertex : " << word.at(0) <<" "<< (searchNode==nullptr));

  if(searchNode != nullptr)
  {
    //if(searchNode->vertex)
    word.erase(0,1);
    return find_lowest_barch_index(searchNode, word);
  }

}

void remove_word(struct TrieNode* node, string word)
{
  if((node == nullptr) || word.empty())
    return;

  TrieNode* searchNode = char_in_vertex(node->vertex, word.at(0));
  DEBUG_PRINT("Find in vertex : " << word.at(0) <<" "<< (searchNode==nullptr));

  if(searchNode != nullptr)
  {
    word.erase(0,1);
    remove_word(searchNode, word);
    DEBUG_PRINT("Size:" << searchNode->vertex.size());

    if((searchNode->vertex.size() == 0) ||
       (searchNode->vertex.size() == 1) &&
       (node->vertex.size() <2))
    {
      DEBUG_PRINT("Removing:" << searchNode->letter);
      delete searchNode;
    }

  }

}
