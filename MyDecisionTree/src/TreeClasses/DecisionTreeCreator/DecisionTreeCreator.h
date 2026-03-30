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
public:
	DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels);

	Node findBestNode(vector<int> rowIndexes);
	Node createTree();

	Node findBestFeatureNode(vector<int> rowIndexes, int featureIndex);
};