//============================================================================
// Name        : BabyNames_Q17_7.cpp
// Author      : Yael Cohen
// Version     : 0
// Description : Solution for Question 17.7 from Cracking the Coding interviewm vesion 6
//============================================================================
/*
 * Question description:
 * Each year, the government releases a list of the 10000 most common baby names and their frequencies.
 * the only problem with this is that some names have multiple spellings, For example "John" and "Jon" are essentially
 * the same name but would be listed separately in the list.
 * Given two lists, one of names/frequencies and the other of pairs of equivalent names,
 * write an algorithm to print a new list of the true frequency of each name. in the final list, any name can be used as the 'real' name.
 *
 */


#include <iostream>
#include "NamesFreqSpellNonSeneitive.h"
#include <map>
using namespace std;

/*
 * test1 - basic
 * expected result: Chris (36) John (27)
 */
void test1()
{

		cout <<"\n      Baby Names TEST1" <<endl;
		NamesFreqSpellNonSeneitive babyNames;
		map<string,int> namesF;
		namesF.insert(pair<string,int>("John",15));
		namesF.insert(pair<string,int>("Jon",12));
		namesF.insert(pair<string,int>("Chris",13));
		namesF.insert(pair<string,int>("Kris",4));
		namesF.insert(pair<string,int>("Christopher",19));

		babyNames.populateNodes(namesF);

		vector<vector<string>* > synonymsList;
		vector<string> jon;
		jon.push_back("Jon");
		jon.push_back("John");
		synonymsList.push_back(&jon);

		vector<string> John;
		John.push_back("John");
		John.push_back("Johnny");
		synonymsList.push_back(&John);

		vector<string> Chris;
		Chris.push_back("Chris");
		Chris.push_back("Kris");
		synonymsList.push_back(&Chris);

		vector<string> Christopher;
		Christopher.push_back("Chris");
		Christopher.push_back("Christopher");
		synonymsList.push_back(&Christopher);

		babyNames.populateEdges(synonymsList);
		babyNames.countComponentFrequency_BFS();

}

/*
 * test2 - no edges
 * expected result: John (15)
 */
void test2()
{

	cout <<"\n      Baby Names TEST2" <<endl;
	NamesFreqSpellNonSeneitive babyNames;
	map<string,int> namesF;
	namesF.insert(pair<string,int>("John",15));
	babyNames.populateNodes(namesF);
	vector<vector<string>* > synonymsList;
	vector<string> jon;
	synonymsList.push_back(&jon);
	babyNames.populateEdges(synonymsList);
	babyNames.countComponentFrequency_BFS();

}

/*
 * test3
 * 1 component of multiple synonyms and 1 with 1 name  + edge for nodes not in the graph
 * expected result: John (63)  Kris (2)
 */
void test3()
{

		cout <<"\n      Baby Names TEST1" <<endl;
		NamesFreqSpellNonSeneitive babyNames;
		map<string,int> namesF;
		namesF.insert(pair<string,int>("John",15));
		namesF.insert(pair<string,int>("Jon",12));
		namesF.insert(pair<string,int>("Johnny",13));
		namesF.insert(pair<string,int>("Johnathan",4));
		namesF.insert(pair<string,int>("Jonathan",19));
		namesF.insert(pair<string,int>("Kris",2));

		babyNames.populateNodes(namesF);

		vector<vector<string>* > synonymsList;
		vector<string> jon;
		jon.push_back("Jon");
		jon.push_back("John");
		jon.push_back("Jonathan");
		jon.push_back("Johnny");
		jon.push_back("Johnathan");

		synonymsList.push_back(&jon);


		vector<string> Christopher;
		Christopher.push_back("Chris");
		Christopher.push_back("Christopher");
		synonymsList.push_back(&Christopher);

		babyNames.populateEdges(synonymsList);
		babyNames.countComponentFrequency_BFS();

}

int main() {

	test1();
	test2();
	test3();

	return 0;
}
