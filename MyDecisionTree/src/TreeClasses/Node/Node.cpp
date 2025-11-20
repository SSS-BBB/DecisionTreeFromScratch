#include "Node.h"
#include <iostream>

bool Node::ISplit(int data)
{
	if (data <= iTreshold)
		return true;

	return false;
}

bool Node::FSplit(float data)
{
	if (data <= fTreshold)
		return true;

	return false;
}

bool Node::CSplit(char data)
{
	if (data == cTreshold)
		return true;

	return false;
}

bool Node::SSplit(string data)
{
	if (data == sTreshold)
		return true;

	return false;
}

Node::Node(char p_dataType, int p_targetColumnIndex)
{
	dataType = p_dataType;
	targetColumnIndex = p_targetColumnIndex;

	// Initialize treshold
	iTreshold = 0;
	fTreshold = 0.0f;
	cTreshold = 'o';
	sTreshold = "o";

	leftNode = nullptr;
	rightNode = nullptr;
}

Node::Node()
{
	dataType = 'c';
	targetColumnIndex = -1;

	// Initialize treshold
	iTreshold = 0;
	fTreshold = 0.0f;
	cTreshold = 'o';
	sTreshold = "o";

	leftNode = nullptr;
	rightNode = nullptr;
}

void Node::SetITreshold(int tresholdValue)
{
	if (dataType != 'i')
	{
		cerr << "Warning: Setting Integer but Data Type is not integer" << endl;
	}
	iTreshold = tresholdValue;
}

void Node::SetFTreshold(float tresholdValue)
{
	if (dataType != 'f')
	{
		cerr << "Warning: Setting Float but Data Type is not float" << endl;
	}
	fTreshold = tresholdValue;
}

void Node::SetCTreshold(char tresholdValue)
{
	if (dataType != 'c')
	{
		cerr << "Warning: Setting Char but Data Type is not char" << endl;
	}
	cTreshold = tresholdValue;
}

void Node::SetSTreshold(string tresholdValue)
{
	if (dataType != 's')
	{
		cerr << "Warning: Setting String but Data Type is not string" << endl;
	}
	sTreshold = tresholdValue;
}

int Node::GetITreshold()
{
	return iTreshold;
}

float Node::GetFTreshold()
{
	return fTreshold;
}

char Node::GetCTreshold()
{
	return cTreshold;
}

string Node::GetSTreshold()
{
	return sTreshold;
}

void Node::SetLeftNode(Node& node)
{
	leftNode = &node;
}

void Node::SetRightNode(Node& node)
{
	rightNode = &node;
}

Node& Node::NextNode(Data& data)
{
	if (leftNode == nullptr || rightNode == nullptr)
	{
		cerr << "Left Node/Right Node is nullptr" << endl;
		cerr << "Unable to process this data:" << endl;
		data.PrintData();
		Node nullNode('N', -1);
		return nullNode;
	}

	switch (dataType)
	{
	case 'i':
		if (ISplit(data.GetIData(targetColumnIndex)))
			return *leftNode;
		return *rightNode;
		break;
	case 'f':
		if (FSplit(data.GetFData(targetColumnIndex)))
			return *leftNode;
		return *rightNode;
		break;
	case 'c':
		if (CSplit(data.GetCData(targetColumnIndex)))
			return *leftNode;
		return *rightNode;
		break;
	case 's':
		if (SSplit(data.GetSData(targetColumnIndex)))
			return *leftNode;
		return *rightNode;
		break;
	default:
		cerr << "Unknown dataype: " << dataType << endl;
		break;
	}

	Node nullNode('N', -1);
	return nullNode;
}

void Node::PrintNode()
{
	switch (dataType)
	{
	case 'i':
		cout << dataType << ", " << targetColumnIndex << ", " << iTreshold << endl;
		break;
	case 'f':
		cout << dataType << ", " << targetColumnIndex << ", " << fTreshold << endl;
		break;
	case 'c':
		cout << dataType << ", " << targetColumnIndex << ", " << cTreshold << endl;
		break;
	case 's':
		cout << dataType << ", " << targetColumnIndex << ", " << sTreshold << endl;
		break;

	default:
		cerr << "Unknown dataype: " << dataType << endl;
		break;
	}
}

bool Node::IsLeafNode()
{
	return leftNode == nullptr && rightNode == nullptr;
}
