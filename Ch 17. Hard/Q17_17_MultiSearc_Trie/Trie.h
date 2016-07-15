/*
 * Trie.h
 *
 *  Created on: 14 αιεμ 2016
 *      Author: Yael
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <set>
using namespace std;
#define LETTERS_IN_LANGUAGE 26
#define FIRST_LETTER_IN_LANGUAGE = 'a';
typedef unsigned int uint;

class Trie {

	struct TrieNode
	{
		char letter;
		bool isEndOfWord;
		int prefixCount;

		TrieNode* childrens[LETTERS_IN_LANGUAGE];
		TrieNode* parent;  // for future use, e.g- delete word
		TrieNode()
		{
			letter='\0';
			isEndOfWord = false;
			prefixCount =0 ;
			for (int i =0; i < LETTERS_IN_LANGUAGE; i ++)
			{
				childrens[i] =0;
			}
			parent=0;
		}
	};

public:
	Trie();
	virtual ~Trie();

	/*
	 * returns false if there's any error (e.g non alphabetic characters)
	 * runtime: O(W) - W length of word
	 */
	bool insert(string &word);
	/*
	 * method Trie::search
	 * search for word in the trie, returns true if exist, false if not.
	 * @Runtime: O(W) where W is the length of word
	 */
	bool search(string &word);
	/*
	 * method Trie::findSubWords
	 * @input:  word - a string and a reference to the output set of sub words
	 * the method populates o_subWords with all the words in the trie that starts with word[0] and are substring of word
	 * @output: false in case of error, true otherwise.
	 * @Runtime: O(W*H) where W is the length of word and H is the height of the trie that starts with the letter word[i] (the length of the longest word)
	 */
	bool findSubWords(string &word, set<string>& o_subWords);

private:
	TrieNode* root;

	int getIndexByLetter(char letter);
	void deleteTrieRec(TrieNode *node);
};

#endif /* TRIE_H_ */
