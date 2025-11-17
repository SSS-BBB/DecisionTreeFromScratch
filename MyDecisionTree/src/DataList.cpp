#include "DataList.h"
#include <iostream>

DataList::DataList(int p_iFeatureNum, int p_fFeatureNum, int p_cFeatureNum, int p_sFeatureNum, int p_rowNum)
{
	// Initialize column numbers
	iColumnNum = p_iFeatureNum;
	fColumnNum = p_fFeatureNum;
	cColumnNum = p_cFeatureNum;
	sColumnNum = p_sFeatureNum;

	// Initialize rows number and index
	rowNum = p_rowNum;
	rearRowIndex = -1;

	// Initialize data array
	dataArray = new Data[rowNum];
	for (int i = 0; i < rowNum; i++)
	{
		dataArray[i].iFeatureNum = iColumnNum;
		dataArray[i].fFeatureNum = fColumnNum;
		dataArray[i].cFeatureNum = cColumnNum;
		dataArray[i].sFeatureNum = sColumnNum;
	}
}

int DataList::GetColumnNum()
{
	return iColumnNum + fColumnNum + cColumnNum + sColumnNum;
}

int DataList::GetRowNum()
{
	return rowNum;
}

void DataList::AddData(list<int>& iData, list<float>& fData, list<char>& cData, list<string>& sData)
{
	if (rearRowIndex >= rowNum - 1)
	{
		cout << "Data List is full, unable to add more data." << endl;
		return;
	}

	// check if passed data is valid -> size of the list is equal to the given size
	if (iData.size() != iColumnNum || fData.size() != fColumnNum ||
		cData.size() != cColumnNum || sData.size() != sColumnNum)
	{
		cout << "Size of the list is not equal to the given size of the columns." << endl;
		return;
	}
		
	rearRowIndex++;

	// add int data
	for (int x : iData)
	{
		dataArray[rearRowIndex].InsertInt(x);
	}

	// add float data
	for (float x : fData)
	{
		dataArray[rearRowIndex].InsertFloat(x);
	}

	// add char data
	for (char x : cData)
	{
		dataArray[rearRowIndex].InsertChar(x);
	}

	// add string data
	for (string x : sData)
	{
		dataArray[rearRowIndex].InsertString(x);
	}
}

void DataList::AddData(Data& data)
{
	if (rearRowIndex >= rowNum - 1)
	{
		cout << "Data List is full, unable to add more data." << endl;
		data.PrintData();
		cout << "Unable to add this data" << endl;
		cout << "-------------------------" << endl;
		return;
	}

	// check if passed data is valid -> size of the data is equal to the given size
	if (data.iFeatureNum != iColumnNum || data.fFeatureNum != fColumnNum ||
		data.cFeatureNum != cColumnNum || data.sFeatureNum != sColumnNum)
	{
		cout << "Size of the data is not equal to the given size of the columns." << endl;
		data.PrintData();
		cout << "Unable to add this data" << endl;
		cout << "-------------------------" << endl;
		return;
	}

	rearRowIndex++;
	dataArray[rearRowIndex] = data;
}

void DataList::PrintDataList()
{
	for (int i = 0; i <= rearRowIndex; i++)
	{
		dataArray[i].PrintData();
	}
}