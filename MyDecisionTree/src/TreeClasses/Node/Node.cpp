#include "Node.h"
#include <iostream>

bool Node::isValueLeft(float value, int columnDataType)
{
	// 0 -> categorical
	if (columnDataType == 0)
	{
		return value == treshold;
	}

	// 1 -> numerical
	if (columnDataType == 1)
	{
		return value <= treshold;
	}

	return false;
}

Node::Node(int p_targetColumnIndex, float p_treshold)
{
	targetColumnIndex = p_targetColumnIndex;
	treshold = p_treshold;
	leftNode = nullptr;
	rightNode = nullptr;
}

void Node::split(vector<int> rowIndexes, DataList& data, vector<float>& labels)
{
	// leaf node
	if (isLeafNode())
	{
		// set labels
		for (int index : rowIndexes)
		{
			labels[index] = treshold;
		}
		return;
	}

	// not leaf node
	// to make sure to not dereferrence nullptr
	if (leftNode == nullptr || rightNode == nullptr)
	{
		cerr << "Left or Right Node is null ptr, unable to proceed." << endl;
		return;
	}

	vector<int> leftIndexArray;
	vector<int> rightIndexArray;

	for (int index : rowIndexes)
	{
		int columnDataType = data.getColumnDataTypeAt(targetColumnIndex);
		float dataValue = data.getDataAt(index, targetColumnIndex);
		if (isValueLeft(dataValue, columnDataType))
		{
			leftIndexArray.push_back(index);
		}
		else
		{
			rightIndexArray.push_back(index);
		}
	}

	// go to the next node
	leftNode->split(leftIndexArray, data, labels);
	rightNode->split(rightIndexArray, data, labels);
}

void Node::setLeftNode(Node* node)
{
	leftNode = node;
}

void Node::setRightNode(Node* node)
{
	rightNode = node;
}

bool Node::isLeafNode()
{
	return (leftNode == nullptr && rightNode == nullptr) || targetColumnIndex < 0;
}
