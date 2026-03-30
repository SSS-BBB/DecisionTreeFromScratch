#pragma once
#include "../../DataClasses/DataList/DataList.h"
#include "../Node/Node.h"
#include <vector>

using namespace std;

class DecisionTreeCreator
{
private:
	DataList* featureData; // no need to manipulate the data so I'll store it as a pointer.
	vector<float>* labels;
	
	int featureLength; // lengh of feature from feature data
	int dataLength; // number of rows from feature and labels data
	int uniqueValueLength; // how much unique values are in the label
public:
	DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels, int p_uniqueValueLength);

	float calculateEntropy(vector<int> rowIndexes);

	Node findBestNode(vector<int> rowIndexes);
	Node createTree();

	Node findBestFeatureNode(vector<int> rowIndexes, int featureIndex);
};