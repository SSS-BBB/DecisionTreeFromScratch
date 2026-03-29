#pragma once
#include <string>
#include "../../DataClasses/DataList/DataList.h"

using namespace std;

class Node
{
private:
	// value to compare
	float treshold;

	int targetColumnIndex;

	// next node
	Node* leftNode;
	Node* rightNode;

	bool isValueLeft(float value, int columnDataType); // check if the value should go to the left node

public:

	Node(int p_targetColumnIndex, float p_treshold);

	// function to split data to left and right node (if not leaf node)
	void split(vector<int> rowIndexes, DataList& data, vector<float>& labels);

	void setLeftNode(Node* node);
	void setRightNode(Node* node);

	bool isLeafNode();
};