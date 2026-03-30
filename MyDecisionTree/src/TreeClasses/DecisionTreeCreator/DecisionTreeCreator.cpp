#include "DecisionTreeCreator.h"
#include <iostream>

DecisionTreeCreator::DecisionTreeCreator(DataList* p_featureData, vector<float>* p_labels)
{
	featureData = nullptr;
	labels = nullptr;
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

	featureLength = featureData->getColumnNum();
	dataLength = labels->size();
}

Node DecisionTreeCreator::findBestNode(vector<int> rowIndexes)
{
	if (featureData == nullptr || labels == nullptr)
	{
		cerr << "Feature Data and/or Labels are missing, unable to find the best node." << endl;
		return Node(-1, -1);
	}

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
