/*
 * LongestWord.cpp
 *
 *  Created on: July 13 2016
 *  Author: Yael Cohen
 *  Description: Solution to question 17.15: Given a list of words, write a program to find the longest word made of other words in the list
 */

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm> //sort
using namespace std;


/*
 * method isBuiltFromDictionaryWords
 * @input:
 * dictionary - in the first call the unordered_map contains all the words in the input list with value "true". during the processing it is enhanced to
 *  	hold all the strings that are examined so far as keys, with value "true" if the key is a word or made of words or false otherwise or false otherwize
 * str - string to check if built from dictionary words
 * @output: true if str can be split to words from the given dictionary, false otherwise
 */
bool isBuiltFromDictionaryWords(string& str, unordered_map<string, bool>& dictionary)
{
  if(dictionary.find(str) != dictionary.end())   // memoization is used to save examining the same strings in different calls
  {
    return  dictionary.at(str);
  }
  string prefix ="";
  for (unsigned int i = 0 ; i < str.size(); i++)
  {
    prefix+=str[i];
    if (dictionary.find(prefix) != dictionary.end() && dictionary.at(prefix) == true)
    {
      string cont = str.substr(i+1);
      if(isBuiltFromDictionaryWords(cont, dictionary) )
    	  return true;
    }
  }
  dictionary.insert(pair<string, bool>(str, false));
  return  false;
}

// return true if first > second
bool pairCompare(const std::pair<int, string*>& firstElem, const std::pair<int, string*>& secondElem) {
	return firstElem.first > secondElem.first;
}

/*
 * method longestWord
 * @input: listOfWords- reference to vector of strings
 * @output: o_longestW - the longest string that is made of other strings in listOfWords
 * The method returns true if there is such string that is composed of at least 2 other words in the given list or false otherwise
 */

bool longestWord( vector<string> &listOfWords, string &o_longestW)
{
	bool ans = false;
	vector<pair<int, string*> > sizeStrVec;  // constructed to sort the words by length
	sizeStrVec.reserve(listOfWords.size());

	unordered_map<string,bool> dictionary;		// will hold all the strings that are examined as keys, with value "true" if the key is a word or made of words
	for (unsigned int i =0; i < listOfWords.size(); i++ )
	{
		sizeStrVec.push_back( pair<int,string*>(listOfWords[i].size(), &listOfWords[i]) );
		dictionary.insert(pair<string,bool>(listOfWords[i], true));
	}
	std::sort(sizeStrVec.begin(), sizeStrVec.end(), pairCompare);

	for (unsigned int i =0; i < sizeStrVec.size(); i++)
	{
		string* s = sizeStrVec[i].second;
		dictionary.erase(*s);
		bool res = isBuiltFromDictionaryWords(*s, dictionary);
		dictionary.insert(pair<string,bool>(*s, true));
		if (res)
		{
			o_longestW = *s;
			ans = true;
			break;
		}
	}
	return ans;

}

int main() {

	string array [] = {"cat", "banana", "dog", "nana", "walk", "walker", "dogwalker"};
	vector<string> words(array, array+7);
	string res;
	if ( longestWord( words, res))
		cout <<"The longest word that is made of at least 2 other words is: "<< res <<endl;
	else
		cout <<"In the given list none of the words is made of other words"<< res <<endl;
  return 0;
}
