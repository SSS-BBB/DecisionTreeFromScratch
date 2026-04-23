#include "DecisionTreeCreator.h"
#include <iostream>
#include <cmath>

DecisionTreeCreator::DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels, int p_uniqueValueLength, 
	int p_maximumDepth, int p_minSamplesSplit, int p_minSamplesLeaf)
{
	featureData = nullptr;
	labels = nullptr;
	uniqueValueLength = 0;
	featureLength = 0;
	dataLength = 0;
	maximumDepth = 0;
	minSamplesSplit = 0;
	minSamplesLeaf = 0;

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

	if (p_maximumDepth <= 0)
	{
		maximumDepth = dataLength + 1;
	}
	else
	{
		maximumDepth = p_maximumDepth;
	}

	if (p_minSamplesSplit <= 0)
	{
		minSamplesSplit = 2;
	}
	else
	{
		minSamplesSplit = p_minSamplesSplit;
	}

	if (p_minSamplesLeaf <= 0)
	{
		minSamplesLeaf = 1;
	}
	else
	{
		minSamplesLeaf = p_minSamplesLeaf;
	}
}

DecisionTreeCreator::DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels, int p_uniqueValueLength) : 
	DecisionTreeCreator(p_featureData, p_labels, p_uniqueValueLength, -1, -1, -1)
{
	
}

float DecisionTreeCreator::calculateGini(vector<int> rowIndexes)
{
	if (labels == nullptr)
	{
		cerr << "Label Array is missing, unable to calculate entropy." << endl;
		return INFINITY;
	}

	if (rowIndexes.size() == 0)
	{
		return INFINITY;
	}

	if (uniqueValueLength == 0)
	{
		cerr << "Unique Value Length is 0, unable to calculate the entropy." << endl;
		return INFINITY;
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

	// calculate gini: O(n) where n = uniqueValueLength
	float gini = 1.0f;
	for (int i = 0; i < uniqueValueLength; i++)
	{
		gini -= pLabels[i] * pLabels[i];
	}

	return gini;
}

float DecisionTreeCreator::findMajorityLabel(vector<int> rowIndexes)
{
	if (labels == nullptr)
	{
		cerr << "Label Array is missing, unable to find majority label." << endl;
		return 0.0f;
	}

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

unique_ptr<Node> DecisionTreeCreator::findBestNode(vector<int> rowIndexes, int level)
{
	if (rowIndexes.size() == 0)
	{
		cerr << "Level: " << level << " No data to find the best node." << endl;
		unique_ptr<Node> errorNode = make_unique<Node>(-1, -1);
		return errorNode;
	}

	if (featureData == nullptr || labels == nullptr)
	{
		cerr << "Feature Data and/or Labels are missing, unable to find the best node." << endl;
		unique_ptr<Node> errorNode = make_unique<Node>(-1, -1);
		return errorNode;
	}

	DataList currentFeatureData = featureData->selectRow(rowIndexes);

	float currentGini = calculateGini(rowIndexes);
	cout << "Level " << level << ": Gini = " << currentGini << endl;

	// leaf node
	// gini = 0
	if (currentGini == 0)
	{
		// only 1 label
		float nodeLabel = (*labels)[rowIndexes[0]];
		cout << "Reached Gini = 0" << endl;
		cout << "Node Label = " << nodeLabel << endl;

		unique_ptr<Node> leafNode = make_unique<Node>(-1, nodeLabel);
		return leafNode;
	}

	// reach maximum depth
	if (level + 1 > maximumDepth)
	{
		float nodeLabel = findMajorityLabel(rowIndexes);
		cout << "Reached Maximum Depth" << endl;
		cout << "Node Label = " << nodeLabel << endl;

		unique_ptr<Node> leafNode = make_unique<Node>(-1, nodeLabel);
		return leafNode;
	}

	// not enough samples
	if (rowIndexes.size() < minSamplesSplit)
	{
		float nodeLabel = findMajorityLabel(rowIndexes);
		cout << "Not enough samples to split" << endl;
		cout << "Node Label = " << nodeLabel << endl;

		unique_ptr<Node> leafNode = make_unique<Node>(-1, nodeLabel);
		return leafNode;
	}

	// inner node
	vector<int> empty = {};
	NodeInfo currentBestNodeInfo = { -1, -1, INFINITY, empty, empty };

	// iterate through each features
	for (int featureIndex = 0; featureIndex < featureLength; featureIndex++)
	{
		NodeInfo bestFeatureNodeInfo = findBestFeatureNode(currentFeatureData, rowIndexes, featureIndex);
		// cout << "Feature: " << featureIndex << " Information Gain: " << bestFeatureNodeInfo.informationGain << endl;
		if (bestFeatureNodeInfo.gini < currentBestNodeInfo.gini 
			&& bestFeatureNodeInfo.leftIndexes.size() >= minSamplesLeaf 
			&& bestFeatureNodeInfo.rightIndexes.size() >= minSamplesLeaf)
		{
			// update best node info
			currentBestNodeInfo.featureIndex = bestFeatureNodeInfo.featureIndex;
			currentBestNodeInfo.value = bestFeatureNodeInfo.value;
			currentBestNodeInfo.gini = bestFeatureNodeInfo.gini;
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
		unique_ptr<Node> leafNode = make_unique<Node>(-1, nodeLabel);
		return leafNode;
	}

	unique_ptr<Node> bestNode = make_unique<Node>(currentBestNodeInfo.featureIndex, currentBestNodeInfo.value);
	bestNode->setLeftNode(findBestNode(currentBestNodeInfo.leftIndexes, level + 1));
	bestNode->setRightNode(findBestNode(currentBestNodeInfo.rightIndexes, level + 1));

	return bestNode;
}

unique_ptr<Node> DecisionTreeCreator::createTree()
{
	// row indexes from first to last
	vector<int> allIndexes;
	for (int i = 0; i <= featureData->getRearRowIndex(); i++)
	{
		allIndexes.push_back(i);
	}

	unique_ptr<Node> bestRoot = findBestNode(allIndexes, 0);

	return bestRoot;
}

NodeInfo DecisionTreeCreator::findBestFeatureNode(DataList& currentFeatureData, vector<int> rowIndexes, int featureIndex)
{
	vector<int> empty = {};
	NodeInfo nullNode = { -1, -1, INFINITY, empty, empty };

	if (rowIndexes.size() == 0)
	{
		cerr << "No data to find the best feature node." << endl;
		return nullNode;
	}

	if (featureIndex < 0 || featureIndex >= featureLength)
	{
		cerr << "feature index out of bounds, unable to find best node for feature " << featureIndex << endl;
		return nullNode;
	}


	// find best node for specific feature
	// iterate through every unique values of this feature to find the best value node for this feature
	// the best value node is the node with the most information gain
	set<float> featureTresholdSet = currentFeatureData.getTresholdsAtColumn(featureIndex);

	NodeInfo bestNodeInfo = { featureIndex, -1, INFINITY, empty, empty };

	for (float treshold : featureTresholdSet)
	{
		// create node for this unique value
		Node currentNode(featureIndex, treshold);

		// data split from this node
		vector<int> leftIndexes = {};
		vector<int> rightIndexes = {};
		currentNode.split(rowIndexes, *featureData, leftIndexes, rightIndexes);

		// calculate information gain
		float wLeft = ((float) leftIndexes.size()) / rowIndexes.size();
		float giniLeft = calculateGini(leftIndexes);

		float wRight = ((float) rightIndexes.size()) / rowIndexes.size();
		float giniRight = calculateGini(rightIndexes);

		float giniWeightedSum = wLeft*giniLeft + wRight*giniRight;

		// check max information gain
		if (giniWeightedSum < bestNodeInfo.gini && !leftIndexes.empty() && !rightIndexes.empty())
		{
			bestNodeInfo.gini = giniWeightedSum;
			bestNodeInfo.value = treshold;
			bestNodeInfo.leftIndexes = leftIndexes;
			bestNodeInfo.rightIndexes = rightIndexes;
		}
	}

	return bestNodeInfo;
}
