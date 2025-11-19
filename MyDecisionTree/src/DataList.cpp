#include "DataList.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

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

	// Initialize data array with size
	dataArray.reserve(rowNum);
	
	//for (int i = 0; i < rowNum; i++)
	//{
	//	Data element(iColumnNum, fColumnNum, cColumnNum, sColumnNum);
	//	dataArray.emplace_back(element);

	//	dataArray[i] = Data();
	//	// Note: be careful of stack overflow
	//}
}

int DataList::GetColumnNum()
{
	return iColumnNum + fColumnNum + cColumnNum + sColumnNum;
}

int DataList::GetRowNum()
{
	return rowNum;
}

void DataList::AddData(Data& data)
{
	/*if (dataArray == nullptr)
	{
		cout << "Data Array is nullptr, unable to add this data." << endl;
		data.PrintData();
		return;
	}*/

	if (rearRowIndex >= rowNum - 1)
	{
		cout << "Data List is full, unable to add more data." << endl;
		data.PrintData();
		cout << "Unable to add this data" << endl;
		cout << "-------------------------" << endl;
		return;
	}

	// check if passed data is valid -> size of the data is equal to the given size
	if (data.GetIFeatureNum() != iColumnNum || data.GetFFeatureNum() != fColumnNum ||
		data.GetCFeatureNum() != cColumnNum || data.GetSFeatureNum() != sColumnNum)
	{
		cout << "Size of the data is not equal to the given size of the columns." << endl;
		data.PrintData();
		cout << "Unable to add this data" << endl;
		cout << "-------------------------" << endl;
		return;
	}

	rearRowIndex++;
	dataArray.emplace_back(data);
}

void DataList::PrintDataList()
{
	/*if (dataArray == nullptr)
	{
		cout << "Data Array is nullptr, unable to print data list." << endl;
		return;
	}*/

	for (int i = 0; i <= rearRowIndex; i++)
	{
		dataArray[i].PrintData();
	}
}

void DataList::ReadCSV(string filePath, string columnsType)
{
	// Columns Type to let the program knows which type is this column
	// Ex. ifcs -> first column is integer, second is float, third is char, last is string

	// check if number of each type is equal to the column number
	int iCount = 0;
	int fCount = 0;
	int cCount = 0;
	int sCount = 0;

	for (char type : columnsType)
	{
		switch (type)
		{
		case 'i':
			iCount++;
			break;
		case 'f':
			fCount++;
			break;
		case 'c':
			cCount++;
			break;
		case 's':
			sCount++;
			break;

		default:
			break;
		}
	}

	if (iCount != iColumnNum || fCount != fColumnNum || cCount != cColumnNum || sCount != sColumnNum)
	{
		cout << "Some/All column type is not equal to the given size of the columns." << endl;
		return;
	}

	ifstream dataFile;
	string line = "";
	dataFile.open(filePath);
	getline(dataFile, line);

	// check if counted columns is equal to data list column num
	if (Utils::CountChar(line, ',') + 1 != GetColumnNum())
	{
		cout << "Number of columns from the file is not equal to number of columns from this data list." << endl;
		return;
	}

	// add data
	for (int row = 0; row < rowNum; row++)
	{
		getline(dataFile, line);

		if (line.empty())
		{
			cout << "Got all the data." << endl;
			return;
		}

		// add a row
		Data data(iColumnNum, fColumnNum, cColumnNum, sColumnNum);
		for (int i = 0; i < GetColumnNum(); i++)
		{
			// get cell
			int delimiterLocation = line.find(',');

			string currentCell = line.substr(0, delimiterLocation);
			line = line.substr(delimiterLocation + 1, line.length());

			// add data to a row
			char currentType = columnsType[i];

			switch (currentType)
			{
			case 'i':
				data.InsertInt(stoi(currentCell));
				break;
			case 'f':
				data.InsertFloat(stof(currentCell));
				break;
			case 'c':
				data.InsertChar(currentCell[0]);
				break;
			case 's':
				data.InsertString(currentCell);
				break;

			default:
				cout << "The program doesn't know data type" + currentType << endl;
				break;
			}
		}
		AddData(data);
		cout << row + 1 << "/" << rowNum << endl;
	}
	
}
