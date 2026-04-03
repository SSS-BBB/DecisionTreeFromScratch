#pragma once
#include "../DataList/DataList.h";
class DataManager
{

public:
	static void trainTestSplit(DataList& data, float testSize,
		DataList& xTrain, DataList& xTest,
		vector<float>& yTrain, vector<float>& yTest);

};

