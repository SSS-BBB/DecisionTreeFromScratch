#include "DecisionTreeCreator.h"
#include <iostream>
#include <cmath>

DecisionTreeCreator::DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels, int p_uniqueValueLength)
{
	featureData = nullptr;
	labels = nullptr;
	uniqueValueLength = 0;
	featureLength = 0;
	dataLength = 0;

	nodeMemory = {};

	// data length doesn't match labels length
	if ((p_featureData->getRearRowIndex() + 1) != p_labels->size())
	{
		cerr << "given feature data length doesn't match given labels length, unable to create the decision tree" << endl;
		return;
	}

	featureData = p_featureData;
	labels = p_labels;
	uniqueValueLength = p_uniqueValueLength;

	featureLength = featureData->getColumnNum();
	dataLength = labels->size();
}

float DecisionTreeCreator::calculateEntropy(vector<int> rowIndexes)
{
	if (rowIndexes.size() == 0)
	{
		return 0.0f;
	}

	if (uniqueValueLength == 0)
	{
		cerr << "Unique Value Length is 0, unable to calculate the entropy." << endl;
		return 0.0f;
	}

	vector<float> pLabels; // probability for each labels
	pLabels.reserve(uniqueValueLength);

	// initialize every labels to 0: O(n) where n = uniqueValueLength
	for (int i = 0; i < uniqueValueLength; i++)
	{
		pLabels.push_back(0);
	}

	// calculate p: O(n) where n = size of row indexes
	float p = 1.0f / rowIndexes.size();
	for (int currentRow : rowIndexes)
	{
		if (currentRow < 0 || currentRow >= dataLength)
		{
			cerr << "Index out of bounds, unable to include entropy for row " << currentRow << endl;
			continue;
		}

		int currentLabel = (*labels)[currentRow];
		if (currentLabel < 0 || currentLabel >= uniqueValueLength)
		{
			cerr << "Label column is not converted, unable to include entropy for label " << currentLabel << endl;
			continue;
		}

		pLabels[currentLabel] += p;
	}

	// calculate entropy: O(n) where n = uniqueValueLength
	float entropy = 0.0f;
	for (int i = 0; i < uniqueValueLength; i++)
	{
		if (pLabels[i] == 0)
		{
			continue;
		}

		entropy += -(pLabels[i] * log2(pLabels[i]));
	}

	return entropy;
}

float DecisionTreeCreator::findMajorityLabel(vector<int> rowIndexes)
{
	if (rowIndexes.size() == 0)
	{
		cerr << "Row indexes are empty, unable to find the majority label." << endl;
		return -1.0f;
	}

	if (uniqueValueLength == 0)
	{
		cerr << "Unique Value Length is 0, unable to find the majority label." << endl;
		return -1.0f;
	}

	int maxLabelCount = 0;
	int majorityLabel = 0;
	vector<int> labelCount; // amount of each labels
	labelCount.reserve(uniqueValueLength);

	// initialize every labels to 0: O(n) where n = uniqueValueLength
	for (int i = 0; i < uniqueValueLength; i++)
	{
		labelCount.push_back(0);
	}

	// calculate p: O(n) where n = size of row indexes
	for (int currentRow : rowIndexes)
	{
		if (currentRow < 0 || currentRow >= dataLength)
		{
			cerr << "Index out of bounds, unable to include label for row " << currentRow << endl;
			continue;
		}

		int currentLabel = (*labels)[currentRow];
		if (currentLabel < 0 || currentLabel >= uniqueValueLength)
		{
			cerr << "Label column is not converted, unable to include label " << currentLabel << endl;
			continue;
		}

		labelCount[currentLabel] += 1;

		if (labelCount[currentLabel] > maxLabelCount)
		{
			maxLabelCount = labelCount[currentLabel];
			majorityLabel = currentLabel;
		}
	}

	return majorityLabel;
}

Node DecisionTreeCreator::findBestNode(vector<int> rowIndexes, int level)
{
	if (rowIndexes.size() == 0)
	{
		cerr << "Level: " << level << " No data to find the best node." << endl;
		return Node(-1, -1);
	}

	if (featureData == nullptr || labels == nullptr)
	{
		cerr << "Feature Data and/or Labels are missing, unable to find the best node." << endl;
		return Node(-1, -1);
	}

	float currentEntropy = calculateEntropy(rowIndexes);
	cout << "Level " << level << ": Entropy = " << currentEntropy << endl;

	// leaf node
	// entropy = 0
	if (currentEntropy == 0)
	{
		// only 1 label
		float nodeLabel = (*labels)[rowIndexes[0]];
		cout << "Reached Entropy = 0" << endl;
		cout << "Node Label = " << nodeLabel << endl;
		return Node(-1, nodeLabel);
	}

	// reach maximum height

	// inner node
	vector<int> empty = {};
	NodeInfo currentBestNodeInfo = { -1, -1, -INFINITY, empty, empty };

	// iterate through each features
	for (int featureIndex = 0; featureIndex < featureLength; featureIndex++)
	{
		NodeInfo bestFeatureNodeInfo = findBestFeatureNode(rowIndexes, featureIndex, currentEntropy);
		// cout << "Feature: " << featureIndex << " Information Gain: " << bestFeatureNodeInfo.informationGain << endl;
		if (bestFeatureNodeInfo.informationGain > currentBestNodeInfo.informationGain 
			&& !bestFeatureNodeInfo.leftIndexes.empty() && !bestFeatureNodeInfo.rightIndexes.empty())
		{
			// update best node info
			currentBestNodeInfo.featureIndex = bestFeatureNodeInfo.featureIndex;
			currentBestNodeInfo.value = bestFeatureNodeInfo.value;
			currentBestNodeInfo.informationGain = bestFeatureNodeInfo.informationGain;
			currentBestNodeInfo.leftIndexes = bestFeatureNodeInfo.leftIndexes;
			currentBestNodeInfo.rightIndexes = bestFeatureNodeInfo.rightIndexes;
		}
	}

	if (currentBestNodeInfo.featureIndex == -1)
	{
		// cannot find the best node with left and right array not empty
		// make this node a leaf node
		// find majority label
		cout << "Cannot split more node" << endl;
		float nodeLabel = findMajorityLabel(rowIndexes);
		cout << "Node Label = " << nodeLabel << endl;
		return Node(-1, nodeLabel);
	}

	Node bestNode(currentBestNodeInfo.featureIndex, currentBestNodeInfo.value);
	Node bestLeftNode = findBestNode(currentBestNodeInfo.leftIndexes, level + 1);
	Node bestRightNode = findBestNode(currentBestNodeInfo.rightIndexes, level + 1);

	nodeMemory.push_back(bestLeftNode);
	nodeMemory.push_back(bestRightNode);

	bestNode.setLeftNode(&(nodeMemory[nodeMemory.size() - 2]));
	bestNode.setRightNode(&(nodeMemory[nodeMemory.size() - 1]));

	/*
	cout << "--------------------" << endl;
	cout << "Level " << level << " Completed" << endl;
	cout << "Left Feature Index = " << bestLeftNode.getTargetColumn() << endl;
	cout << "Left Value = " << bestLeftNode.getTreshold() << endl;
	cout << "--------------------" << endl;
	*/

	return bestNode;
}

Node DecisionTreeCreator::createTree()
{
	// row indexes from first to last
	vector<int> allIndexes;
	for (int i = 0; i <= featureData->getRearRowIndex(); i++)
	{
		allIndexes.push_back(i);
	}

	Node bestRoot = findBestNode(allIndexes, 0);

	cout << "Node Memory Size = " << nodeMemory.size() << endl;

	return bestRoot;
}

NodeInfo DecisionTreeCreator::findBestFeatureNode(vector<int> rowIndexes, int featureIndex, float currentEntropy)
{
	if (rowIndexes.size() == 0)
	{
		cerr << "No data to find the best feature node." << endl;
		vector<int> empty = {};
		NodeInfo nullNode = {-1, -1, -INFINITY, empty, empty};
		return nullNode;
	}

	if (featureIndex < 0 || featureIndex >= featureLength)
	{
		cerr << "feature index out of bounds, unable to find best node for feature " << featureIndex << endl;
		vector<int> empty = {};
		NodeInfo nullNode = { -1, -1, -INFINITY, empty, empty };
		return nullNode;
	}

	// find best node for specific feature
	// iterate through every unique values of this feature to find the best value node for this feature
	// the best value node is the node with the most information gain
	set<float> featureUniqueValues = featureData->getUniqueAtColumn(featureIndex);
	
	vector<int> empty = {};
	NodeInfo bestNodeInfo = { featureIndex, -1, -INFINITY, empty, empty };

	for (float unique : featureUniqueValues)
	{
		// create node for this unique value
		Node currentNode(featureIndex, unique);

		// data split from this node
		vector<int> leftIndexes = {};
		vector<int> rightIndexes = {};
		currentNode.split(rowIndexes, *featureData, leftIndexes, rightIndexes);

		// calculate information gain
		float wLeft = ((float) leftIndexes.size()) / rowIndexes.size();
		float entropyLeft = calculateEntropy(leftIndexes);

		float wRight = ((float) rightIndexes.size()) / rowIndexes.size();
		float entropyRight = calculateEntropy(rightIndexes);

		float entropySum = wLeft*entropyLeft + wRight*entropyRight;

		float currentInformationGain = currentEntropy - entropySum;

		// check max information gain
		if (currentInformationGain > bestNodeInfo.informationGain && !leftIndexes.empty() && !rightIndexes.empty())
		{
			bestNodeInfo.informationGain = currentInformationGain;
			bestNodeInfo.value = unique;
			bestNodeInfo.leftIndexes = leftIndexes;
			bestNodeInfo.rightIndexes = rightIndexes;
		}

		// cout << "Value: " << unique << " Information Gain: " << currentInformationGain << endl;
	}

	return bestNodeInfo;
}

void DecisionTreeCreator::printNodeMemory()
{
	for (Node node : nodeMemory)
	{
		node.printInfo();
		cout << "-----------------------" << endl;
	}
}
