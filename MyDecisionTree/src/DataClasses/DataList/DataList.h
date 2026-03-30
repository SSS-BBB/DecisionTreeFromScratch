#pragma once
// #include "../Data/Data.h"
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

	// store The Actual Datas
	vector<vector<float>> dataArray;

	// data converter for each columns to convert from string to float (null if the column is already int or float)
	vector<DataConverter> dataConverter;

	// 0 or 1 data type (o for categorical data and 1 for numerical data)
	vector<int> columnDataTypes;

	// unique values for each columns
	vector<set<float>> uniqueValueColumns;

public:
	DataList(int p_rowNum, vector<int> p_columnDataTypes);

	int getColumnNum();
	int getRowNum();
	int getRearRowIndex();

	void addRow(vector<float> rowData); // Add a row

	void printColumnDataTypes();
	void printDataList();
	void printDataList(int startIndex, int endIndex); // Print Data From start to End
	void printUniqueData();

	void convertAndPrint();
	void convertAndPrint(int startIndex, int endIndex);

	void readCSV(string filePath, string columnsVariableType);

	float getDataAt(int rowIndex, int columnIndex);
	DataList sliceColumn(int startIndex, int endIndex);
	DataList sliceRow(int startIndex, int endIndex);

	void saveConverterAt(int index, string filepath);
	void setDataConverter(int index, DataConverter &newDataConverter);

	int getColumnDataTypeAt(int columnIndex);

	set<float> getUniqueAtColumn(int columnIndex);

	vector<float> getColumn(int columnIndex);
};