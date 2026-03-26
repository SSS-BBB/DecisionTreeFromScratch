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

public:
	vector<Data> dataArray;

	// data converter to convert from string to float (null if the column is already int or float)
	vector<DataConverter> dataConverter;

	DataList(int p_columnNum, int p_rowNum);

	int getColumnNum();
	int getRowNum();

	void addData(Data &data); // Add Data From Data Class
	void printDataList();
	void printDataList(int startIndex, int endIndex); // Print Data From start to End
	void convertAndPrint();
	void convertAndPrint(int startIndex, int endIndex);

	void readCSV(string filePath, string columnsVariableType, vector<float> columnsDataType);

	Data& getDataAt(int index);
	DataList sliceColumn(int startIndex, int endIndex);
};