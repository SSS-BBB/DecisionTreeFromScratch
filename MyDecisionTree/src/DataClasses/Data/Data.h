#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class Data
{
private:
	// number of features
	int featureNum;

	// last index
	int rearIndex;

	// array of the features
	vector<vector<float>> rowData; // first value is the data, and the second value is the type 0 -> categorical, 1 -> numerical

public:
	Data(int p_featureNum);

	// Insert Datas
	void insertData(float data, float type);

	// Show Datas
	void printData();

	// Getter
	int getFeatureNum();

	// Get Data
	float getColumn(int index);
};