/*
 * NamesFreqSpellNonSensitive.cpp
 *      Author: Yael Cohen
 */

#include "NamesFreqSpellNonSensitive.h"
#include <iostream>

NamesFreqSpellNonSensitive::NamesFreqSpellNonSensitive() {}

NamesFreqSpellNonSensitive::~NamesFreqSpellNonSensitive()
	{
		for (unsigned int i =0; i < graph.size(); i++)
		{
			if (0 != graph[i])
			{
				delete graph[i];
				graph[i] = 0;
			}
		}
	}

void NamesFreqSpellNonSensitive::populateNodes(map<string, int>& namesFrequencyMap)
{
	map<string, int>::iterator it;
	for (it = namesFrequencyMap.begin(); it != namesFrequencyMap.end(); it++ )
	{
		Node * newNode= new Node();
		graph.push_back(newNode);
		newNode->name = it->first;
		newNode->frequency = it->second;
		mapNameToNode.insert(pair<string,Node*>(newNode->name, newNode));
	}
}

void NamesFreqSpellNonSensitive::populateEdges(vector<vector<string>* > &synonyms  )
{
	for (unsigned int g =0; g < synonyms.size(); g++)  // for each group of synonyms
	{
		for (unsigned int i = 0; i < synonyms[g]->size(); i++)
		{
			for (unsigned int j =i+1; j < synonyms[g]->size(); j++)
			{  // for every two synonym words words (non repeating), add an edge in the graph
				try
				{
					Node * a = mapNameToNode.at(synonyms[g]->at(i));
					Node * b = mapNameToNode.at(synonyms[g]->at(j));
					a->directConnections.insert(b);
					b->directConnections.insert(a);
				}
				// if one of the nodes doesn't exist (meaning it was in the synonym list but not in the frequencies list), no need to add an edge, this doesn't impact the counting as the missing node's frequency is 0
				catch (...) {}
			}

		}
	}
}

void NamesFreqSpellNonSensitive::countComponentFrequency_BFS()
{
	if (graph.empty())
		return;

	queue<Node*> queue;
	string groupName;
	int countF;
	Node * curr;

	for (unsigned int i =0; i < graph.size(); i++)
	{
		if (graph[i]->visited)
			continue;
		countF = 0;
		groupName = graph[i]->name;
		queue.push(graph[i]);

		while (! queue.empty())
		{
			curr = queue.front();
			queue.pop();
			if (! curr->visited)
			{
				countF += curr->frequency;
				set<Node*>::iterator it;
				for (it =curr->directConnections.begin(); it != curr->directConnections.end(); it++)
				{
					queue.push(*it);
				}
				curr->visited = true;
			}
		}
		cout <<groupName <<" ("<< countF<<") ";
	}
	cout <<endl;
}


