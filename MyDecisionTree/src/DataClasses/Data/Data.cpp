#include "Data.h"
#include <iostream>

Data::Data(int p_featureNum)
{
	// Initialize feature numbers
	featureNum = p_featureNum;

	// Initialize features array
	rowData = vector<vector<float>>();
	rowData.reserve(featureNum);

	// Initialize rear indexes
	rearIndex = -1;
}

void Data::insertData(float data, float type)
{
	if (rearIndex >= featureNum - 1)
	{
		cerr << "This row is full, unable to insert " << data << endl;
		return;
	}
	rearIndex++;
	vector<float> newData = {data, type};
	rowData.push_back(newData);
}

void Data::printData()
{
	for (int i = 0; i < rowData.size(); i++)
	{
		cout << rowData[i][0] << " ";
	}
	cout << endl;
}

int Data::getFeatureNum()
{
	return featureNum;
}

float Data::getColumn(int index)
{
	if (index >= featureNum)
	{
		cerr << "Index out of bounds" << endl;
		return -1.0f;
	}

	return rowData[index][0];
}

float Data::getColumnType(int index)
{
	if (index >= featureNum)
	{
		cerr << "Index out of bounds" << endl;
		return -1.0f;
	}

	return rowData[index][1];
}

Data Data::slice(int startIndex, int endIndex)
{
	int n = endIndex - startIndex + 1; // array length after sliced
	if (n > featureNum || n <= 0 || startIndex >= featureNum || endIndex >= featureNum)
	{
		cerr << "Index out of bounds, unable to slice the data." << endl;
		return *this;
	}

	Data dropedData(n);
	for (int i = startIndex; i <= endIndex; i++)
	{
		dropedData.insertData(rowData[i][0], rowData[i][1]);
	}

	return dropedData;
}
