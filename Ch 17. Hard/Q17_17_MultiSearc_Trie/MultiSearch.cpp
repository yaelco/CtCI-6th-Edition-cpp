/*
 * MultiSearch.cpp
 *
 *  Created on: July 14  2016
 *  Author: Yael Cohen
 *  Description:
 *  Given a string b and an array of smaller strings T, design a method to search b for each small string in T
 *
 *  Assumptions: -Print the substring words to the standard output
 *  		 -if a word in T appears more than once in b, it will be printed once
 */

#include "Trie.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;
/*
 * method printSubStringsOfB
 * @input: T - vector of small strings.
 * 	   b -  longer string
 * @Description: the method prints all the words in T that are substrings of b
 * @Runtime: O(V*M + B*M)    where V is the size of T, M is the longest word in T and B is the length of B
 */
void printSubStringsOfB(vector<string> &T, string& b)
{
	if(b.empty() || T.empty())
	{
		cerr<< "invalid input" <<endl;
		return;
	}
	Trie trie;
	for (uint i =0; i < T.size(); i++)   //O(V*M)
		trie.insert(T[i]);

	string subs;
	set<string> res;
	for (uint i =0; i < b.size(); i++)  //O(B * M)
	{
		subs = b.substr(i);
		trie.findSubWords(subs, res) ;
	}
	cout <<"Following are the substrings of " <<b.c_str() <<" from the given list:" <<endl;
	set<string>::iterator it;
	for ( it = res.begin(); it != res.end(); it++)
		cout <<*it<<" " ;
	cout <<endl;

}
//basic test
void test1_multisearch()
{
	string str = "mississippi";
	string T[] = {"is", "ppi", "hi", "sis", "i", "ssippi"};
	vector<string> vec(T, T+6);
	printSubStringsOfB(vec,str);
}
//no substrings, empty result
void test2_multisearch()
{
	string str = "mississippi";
	string T[] = {"os", "ppp", "hi", "sos", "o", "ssoppi"};
	vector<string> vec(T, T+6);
	printSubStringsOfB(vec,str);
}
//empty list
void test3_multisearch()
{
	string str = "mississippi";
	vector<string> vec;
	printSubStringsOfB(vec,str);
}
int main()
{
	test1_multisearch();
	test2_multisearch();  // empty result
	test3_multisearch();  // error
	return 0;
}
