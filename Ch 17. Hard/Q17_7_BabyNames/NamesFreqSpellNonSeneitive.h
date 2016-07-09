/*
 * NamesFreqSpellNonSeneitive.h
 *
 *  Created on: 7 αιεμ 2016
 *      Author: Yael
 */

#ifndef NamesFreqSpellNonSeneitive_H_
#define NamesFreqSpellNonSeneitive_H_

#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string>
using namespace std;

class NamesFreqSpellNonSeneitive {
public:
	NamesFreqSpellNonSeneitive();
	virtual ~NamesFreqSpellNonSeneitive();

	struct Node
	{
		string name;
		int frequency =0;
		set<Node*> directConnections; //edges
		bool visited=false;
	};

	vector<Node*> graph;
	map<string, Node*> mapNameToNode;

	//assuming map - no repeated names (keys)
	void populateNodes(map<string, int>& namesFrequencyMap);

	/*
	 * @populateEdges
	 * input: reference to vector of synonyms' pointers
	 * for each list of synonyms in the given vector, The method adds an edge to graph for every 2 names in the group (symmetric and transitive)
	 * Runtime: O(L*G) where G is the number of synonyms groups and L is the number of the synonyms in the largset group
	 */
	void populateEdges(vector<vector<string>* > &synonyms  );

	/*
	 * @countComponentFrequency_BFS
	 * for each connected component in graph, the method picks an arbitrary name and prints the summation of the frequencies for all it's synonyms
	 * output form: GroupName1 (group1 frequency) GroupName1 (group2 frequency)... GroupNameN (group N frequency)
	 * Runtime: O(V+E)
	 */
	void countComponentFrequency_BFS();

};

#endif /* NamesFreqSpellNonSeneitive_H_ */
