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
		entropy += -(pLabels[i] * log2(pLabels[i]));
	}

	return entropy;
}

Node DecisionTreeCreator::findBestNode(vector<int> rowIndexes)
{
	if (featureData == nullptr || labels == nullptr)
	{
		cerr << "Feature Data and/or Labels are missing, unable to find the best node." << endl;
		return Node(-1, -1);
	}

	float currentEntropy = calculateEntropy(rowIndexes);
	cout << "Current Entropy: " << currentEntropy << endl;

	// iterate through each features
	for (int featureIndex = 0; featureIndex < featureLength; featureIndex++)
	{
		Node bestFeatureNode = findBestFeatureNode(rowIndexes, featureIndex);
	}

	return Node(-1, 1);
}

Node DecisionTreeCreator::createTree()
{
	// row indexes from first to last
	vector<int> allIndexes;
	for (int i = 0; i <= featureData->getRearRowIndex(); i++)
	{
		allIndexes.push_back(i);
	}

	return findBestNode(allIndexes);
}

Node DecisionTreeCreator::findBestFeatureNode(vector<int> rowIndexes, int featureIndex)
{
	// find best node for specific feature
	if (featureIndex < 0 || featureIndex >= featureLength)
	{
		cerr << "feature index out of bounds, unable to find best node for feature " << featureIndex << endl;
		return Node(-1, -1);
	}

	// iterate through every unique values of this feature to find the best value node for this feature
	// the best value node is the node with the most information gain
	set<float> featureUniqueValues = featureData->getUniqueAtColumn(featureIndex);
	for (float unique : featureUniqueValues)
	{
		cout << unique << " ";
	}
	cout << endl;

	return Node(-1, 1);
}
