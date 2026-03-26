#pragma once
#include "../Data/Data.h"
#include "../DataConverter/DataConverter.h"
#include <vector>

using namespace std;

class DataList
{
private:
	// number of features(columns) for each data types
	int columnNum;

	// number of all the datas
	int rowNum;

	// index of the last row
	int rearRowIndex;

	// data converter to convert from string to float (null if the column is already int or float)
	vector<DataConverter> dataConverter;

public:
	vector<Data> dataArray;

	DataList(int p_columnNum, int p_rowNum);

	int getColumnNum();
	int getRowNum();

	void addData(Data &data); // Add Data From Data Class
	void printDataList();
	void convertAndPrint();

	void readCSV(string filePath, string columnsVariableType, vector<float> columnsDataType);

	Data& getDataAt(int index);
};