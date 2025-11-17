#pragma once
#include "Data.h"
#include <list>

using namespace std;

class DataList
{
private:
	// number of features(columns) for each data types
	int iColumnNum;
	int fColumnNum;
	int cColumnNum;
	int sColumnNum;

	// number of all the datas
	int rowNum;

	// index of the last row
	int rearRowIndex;

public:
	Data* dataArray;

	DataList(int p_iFeatureNum, int p_fFeatureNum, int p_cFeatureNum, int p_sFeatureNum, int p_rowNum);

	int GetColumnNum();
	int GetRowNum();

	void AddData(list<int> &iData, list<float> &fData, list<char> &cData, list<string> &sData); // Add Data From List
	void AddData(Data &data); // Add Data From Data Class
	void PrintDataList();

	void ReadCSV(string filePath, string columnsType);
};