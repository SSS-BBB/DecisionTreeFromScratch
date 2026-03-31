#pragma once
#include "../../DataClasses/DataList/DataList.h"
#include "../Node/Node.h"
#include <vector>

using namespace std;

// store information to consider for best possible node
struct NodeInfo
{
	int featureIndex;
	float value;
	float informationGain;
	vector<int> leftIndexes, rightIndexes;
};

class DecisionTreeCreator
{
private:
	DataList* featureData; // no need to manipulate the data so I'll store it as a pointer.
	vector<float>* labels;
	vector<Node> nodeMemory; // store all nodes in the tree here to make the program remembers all the nodes.
	
	int featureLength; // lengh of feature from feature data
	int dataLength; // number of rows from feature and labels data
	int uniqueValueLength; // how much unique values are in the label
	int possibleNodeNumber; // number of all possible nodes that can be created with this data
	int maximumHeight;
public:
	DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels, int p_uniqueValueLength);

	float calculateEntropy(vector<int> rowIndexes);

	float findMajorityLabel(vector<int> rowIndexes);

	Node findBestNode(vector<int> rowIndexes, int level);
	Node createTree();
	NodeInfo findBestFeatureNode(vector<int> rowIndexes, int featureIndex, float currentEntropy);

	void printNodeMemory();
};