
#include "gtest/gtest.h"
#include "Trie.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(TrieNode, char_in_vertex_test){
  TrieNode a, b, c;
  b.letter = 'a';
  c.letter = 'b';
  a.vertex.push_back(&b);
  a.vertex.push_back(&c);

  TrieNode* element = char_in_vertex(a.vertex,'n');
  EXPECT_EQ((element==nullptr),true);

  element = char_in_vertex(a.vertex, b.letter);
  EXPECT_EQ((element!=nullptr), true);
  EXPECT_EQ(element->letter, b.letter);

  element = char_in_vertex(a.vertex, c.letter );
  EXPECT_EQ((element!=nullptr), true);
  EXPECT_EQ(element->letter, c.letter);
}

TEST(TrieNode, add_word)
{
  TrieNode root;
  string word = "was";

  TrieNode* element = char_in_vertex(root.vertex, 'w');
  add_word(&root, word);

  element = char_in_vertex(root.vertex, 'x');
  EXPECT_EQ((element == nullptr), true);

  element = char_in_vertex(root.vertex, word.at(0));
  EXPECT_EQ((element == nullptr), false);
  EXPECT_EQ(element->letter, word.at(0));

  element = char_in_vertex(element->vertex, word.at(1));
  EXPECT_EQ((element == nullptr), false);
  EXPECT_EQ(element->letter, word.at(1));

  element = char_in_vertex(element->vertex, word.at(2));
  EXPECT_EQ((element == nullptr), false);
  EXPECT_EQ(element->letter, word.at(2));
  }

  TEST(TrieNode, does_word_exist_in_trie_tree)
  {
    TrieNode* root = new TrieNode();
    string word = "Nawin";

    EXPECT_EQ(exists(root, word), false);
    add_word(root, word);
    EXPECT_EQ(exists(root, "Other"), false);
    EXPECT_EQ(exists(root, word), true);
  }

  TEST(TrieNode, adding_multipe_words)
  {
    TrieNode* root = new TrieNode();
    string firstWord  = "Nawin",
           secondWord = "Belen",
           thirdWord  = "Tim";

    EXPECT_EQ(exists(root, "anything"), false);

    add_word(root, firstWord);
    EXPECT_EQ(exists(root, firstWord), true);
    EXPECT_EQ(exists(root, secondWord), false);
    EXPECT_EQ(exists(root, thirdWord), false);

    add_word(root, secondWord);
    EXPECT_EQ(exists(root, firstWord), true);
    EXPECT_EQ(exists(root, secondWord), true);
    EXPECT_EQ(exists(root, thirdWord), false);

    add_word(root, thirdWord);
    EXPECT_EQ(exists(root, firstWord), true);
    EXPECT_EQ(exists(root, secondWord), true);
    EXPECT_EQ(exists(root, thirdWord), true);
  }

/*
TEST(TrieNode, remove_word)
{
  TrieNode* root = new TrieNode();
  string firstWord  = "Nawin",
         secondWord = "Belen",
         thirdWord  = "Bellabs";

  add_word(root, firstWord);
  add_word(root, secondWord);
  add_word(root, thirdWord);

  cout << "Index " << find_lowest_barch_index(root,thirdWord) << endl;
}
*/
TEST(TrieNode, remove_word)
{
  TrieNode* root = new TrieNode();
  string firstWord  = "Nawin",
         secondWord = "Belen",
         thirdWord  = "Nature";

  add_word(root, firstWord);
  add_word(root, secondWord);
  add_word(root, thirdWord);

  remove_word(root,thirdWord);
  EXPECT_EQ(exists(root, firstWord), true);
  EXPECT_EQ(exists(root, secondWord), true);
  EXPECT_EQ(exists(root, thirdWord), false);
}
