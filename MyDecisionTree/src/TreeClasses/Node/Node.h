#pragma once
#include <string>
#include "../../DataClasses/Data/Data.h"

using namespace std;

class Node
{
private:
	// value to compare
	int iTreshold;
	float fTreshold;
	char cTreshold;
	string sTreshold;

	char dataType;
	int targetColumnIndex;

	// next node
	Node* leftNode;
	Node* rightNode;

	// function to split data
	// return true -> go to left node
	bool ISplit(int data);
	bool FSplit(float data);
	bool CSplit(char data);
	bool SSplit(string data);

public:
	Node(char p_dataType, int p_targetColumnIndex); // Internal Node
	Node(); // Leaf Node

	void SetITreshold(int tresholdValue);
	void SetFTreshold(float tresholdValue);
	void SetCTreshold(char tresholdValue);
	void SetSTreshold(string tresholdValue);

	int GetITreshold();
	float GetFTreshold();
	char GetCTreshold();
	string GetSTreshold();

	void SetLeftNode(Node& node);
	void SetRightNode(Node& node);

	Node& NextNode(Data& data);

	void PrintNode();

	bool IsLeafNode();
};