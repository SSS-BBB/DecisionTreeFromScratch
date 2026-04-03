#include "DataManager.h"
#include <iostream>

void DataManager::trainTestSplit(DataList& data, float testSize, DataList& xTrain, DataList& xTest, vector<float>& yTrain, vector<float>& yTest)
{
	if (testSize <= 0 || testSize >= 1)
	{
		cerr << "Test Size needs to be between 0 and 1." << endl;
		return;
	}

	// train test split - split data to training set and testing set
	float trainSize = 1 - testSize;
	int splitIndex = data.getRowNum() * trainSize - 1;
	DataList train = data.sliceRow(0, splitIndex);
	DataList test = data.sliceRow(splitIndex + 1, data.getRowNum() - 1);

	// x y split
	xTrain = train.sliceColumn(0, train.getColumnNum() - 2);
	yTrain = train.getColumn(train.getColumnNum() - 1);

	xTest = test.sliceColumn(0, test.getColumnNum() - 2);
	yTest = test.getColumn(test.getColumnNum() - 1);

}
