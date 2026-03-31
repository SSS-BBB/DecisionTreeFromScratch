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

	// function to predict the labels from the data
	void predict(vector<int> rowIndexes, DataList& data, vector<float>& labels);

	// function to split data to left and right array
	void split(vector<int> rowIndexes, DataList& data, vector<int>& leftIndexes, vector<int>& rightIndexes);

	void setLeftNode(Node* node);
	void setRightNode(Node* node);

	bool isLeafNode();
};