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

void Node::predictAll(DataList& data, vector<float>& labels)
{
	vector<int> allIndexes;
	for (int i = 0; i <= data.getRearRowIndex(); i++)
	{
		allIndexes.push_back(i);
	}
	predict(allIndexes, data, labels);
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

void Node::setLeftNode(unique_ptr<Node> node)
{
	leftNode = move(node);
}

void Node::setRightNode(unique_ptr<Node> node)
{
	rightNode = move(node);
}

unique_ptr<Node>& Node::getLeftNode()
{
	if (leftNode == nullptr)
	{
		cerr << "No left node in this node." << endl;
		unique_ptr<Node> empty;
		return empty;
	}

	return leftNode;
}

unique_ptr<Node>& Node::getRightNode()
{
	if (rightNode == nullptr)
	{
		cerr << "No right node in this node." << endl;
		unique_ptr<Node> empty;
		return empty;
	}

	return rightNode;
}

bool Node::isLeafNode()
{
	return (leftNode == nullptr && rightNode == nullptr) || targetColumnIndex < 0;
}

bool Node::isInvalidNode()
{
	return !isLeafNode() && leftNode == nullptr || rightNode == nullptr;
}

float Node::getTreshold()
{
	return treshold;
}

int Node::getTargetColumn()
{
	return targetColumnIndex;
}

void Node::printInfo()
{
	cout << "Target Column Index: " << targetColumnIndex << endl;
	cout << "Treshold: " << treshold << endl;
}

void Node::printAllChildren(int level)
{
	// print current level
	cout << "Level " << level << endl;
	printInfo();

	// leaf node
	if (isLeafNode() || isInvalidNode())
	{
		return;
	}

	
	// inner node
	cout << "Left: " << endl;
	leftNode->printInfo();

	cout << "Right: " << endl;
	rightNode->printInfo();

	cout << "-------------------" << endl;
	cout << endl;

	// print next level
	leftNode->printAllChildren(level + 1);
	rightNode->printAllChildren(level + 1);
}
