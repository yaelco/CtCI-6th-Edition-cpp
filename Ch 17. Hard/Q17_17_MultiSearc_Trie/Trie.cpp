/*
 * Trie.cpp
 *
 *  Created on: 14 αιεμ 2016
 *      Author: Yael
 */

#include "Trie.h"
#include <iostream>

Trie::Trie() {
	// TODO Auto-generated constructor stub
	root = new TrieNode();
}
void Trie::deleteTrieRec(TrieNode *node)
{
	if (0 == node)
		return;
	for (uint i =0; i < LETTERS_IN_LANGUAGE; i++)
	{
		if(0 != node->childrens[i])
		{
			deleteTrieRec(node->childrens[i]);
		}
	}
	delete node;
	node =0;
}

Trie::~Trie() {
	deleteTrieRec(root);
}

/*
 * returns false if there's any error (e.g non alphabetic characters)
 * runtime: O(W) - W length of word
 */
bool Trie::insert(string &word)
{
/*	if( word.empty() )
	{
		root->isEndOfWord = true;
		root->prefixCount++;
		return true;
	} */ // redundant, will happen anyway

	TrieNode* current = root;
	for (uint i =0; i < word.size(); i++)
	{
		int letterIndex = getIndexByLetter(word[i]);
		if(-1 == letterIndex)
		{
			cerr <<"invalid letter: '" << word[i] <<"' is not alphabetic." <<endl;
			return false;
		}
		if (0 == current->childrens[letterIndex] )
		{
			current->childrens[letterIndex] = new TrieNode();
			current->childrens[letterIndex]->letter = word[i];
			current->childrens[letterIndex]->parent = current;
		}
		current->prefixCount++;
		current = current->childrens[letterIndex];
	}

	current->isEndOfWord = true;
	current->prefixCount++;
	return true;

}

/*
 * method Trie::search
 * search for word in the trie, returns true if exist, false if not.
 * @Runtime: O(W) where W is the length of word
 */
bool Trie::search(string &word)
{
	TrieNode* current = root;

		for (uint i =0; i < word.size(); i++)
		{
			int letterIndex = getIndexByLetter(word[i]);
			if(-1 == letterIndex)
			{
				cerr <<"invalid letter: '" << word[i] <<"' is not alphabetic." <<endl;
				return false;
			}
			if (0 == current->childrens[letterIndex] || 0 == current->prefixCount)
			{
				return false;
			}

			current = current->childrens[letterIndex];
		}

		return current->isEndOfWord;
}


/*
 * method Trie::findSubWords
 * @input:  word - a string and a reference to the output set of sub words
 * the method populates o_subWords with all the words in the trie that starts with word[0] and are substring of word
 * @output: false in case of error, true otherwise.
 * @Runtime: O(W) where W is the min of the length of word and the height of the trie that starts with the letter word[i] (the length of the longest word)
 */
bool Trie::findSubWords(string &word, set<string>& o_subWords)
{
	TrieNode* current = root;

		for (uint i =0; i < word.size(); i++)
		{
			if(0 == current->prefixCount)
					break;
			if (current->isEndOfWord)
			{
				o_subWords.insert(word.substr(0, i));
			}
			int letterIndex = getIndexByLetter(word[i]);
			if(-1 == letterIndex)
			{
				cerr <<"invalid letter: '" << word[i] <<"' is not alphabetic." <<endl;
				return false;
			}
			if (0 == current->childrens[letterIndex] )
				return true;
			current = current->childrens[letterIndex];
		}
		if (current->isEndOfWord)
			{
				o_subWords.insert(word);
			}
		return true;
}



// Private helper methods
/*
 *  returns the index of the letter (offset from a for lower case or offset from A for upper case)
 *  e.g: input a and A both return 0
 *  for invalid letter, who is not in the range 'a'-'z' / 'A'-'Z', -1 will be returned to indicae error
 */
int Trie::getIndexByLetter(char letter)
{
	int ans =-1;
	if (letter >= 'a' && letter <='z')
		ans = letter - 'a';
	else if (letter >= 'A' && letter <='Z')
		ans = letter - 'A';
	return ans;
}

