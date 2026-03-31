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

void Node::predict(vector<int> rowIndexes, DataList& data, vector<float>& labels)
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

	split(rowIndexes, data, leftIndexArray, rightIndexArray);

	// go to the next node
	leftNode->predict(leftIndexArray, data, labels);
	rightNode->predict(rightIndexArray, data, labels);
}

void Node::split(vector<int> rowIndexes, DataList& data, vector<int>& leftIndexes, vector<int>& rightIndexes)
{
	for (int index : rowIndexes)
	{
		if (index < 0 || index > data.getRearRowIndex())
		{
			cerr << "Index out of bounds, unable to split data at index " << index << endl;
			continue;
		}

		int columnDataType = data.getColumnDataTypeAt(targetColumnIndex);
		float dataValue = data.getDataAt(index, targetColumnIndex);
		if (isValueLeft(dataValue, columnDataType))
		{
			leftIndexes.push_back(index);
		}
		else
		{
			rightIndexes.push_back(index);
		}
	}
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
