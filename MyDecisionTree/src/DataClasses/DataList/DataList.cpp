#include "DataList.h"
#include <iostream>
#include <fstream>
#include "../../Utils/Utils.h"

DataList::DataList(int p_columnNum, int p_rowNum)
{
	// Initialize column numbers
	columnNum = p_columnNum;

	// Initialize rows number and index
	rowNum = p_rowNum;
	rearRowIndex = -1;

	// Initialize data array with size
	dataArray.reserve(rowNum);

	// initialize data converter with size
	dataConverter.reserve(columnNum);
}

int DataList::getColumnNum()
{
	return columnNum;
}

int DataList::getRowNum()
{
	return rowNum;
}

void DataList::addData(Data& data)
{
	if (rearRowIndex >= rowNum - 1)
	{
		cerr << "Data List is full, unable to add more data." << endl;
		// data.PrintData();
		cerr << "Unable to add this data" << endl;
		cerr << "-------------------------" << endl;
		return;
	}

	rearRowIndex++;
	dataArray.emplace_back(data);
}

void DataList::printDataList()
{
	/*if (dataArray == nullptr)
	{
		cout << "Data Array is nullptr, unable to print data list." << endl;
		return;
	}*/

	for (int i = 0; i <= rearRowIndex; i++)
	{
		dataArray[i].printData();
	}
}

void DataList::printDataList(int startIndex, int endIndex)
{
	int n = endIndex - startIndex + 1;
	if (n > rowNum || n <= 0 || startIndex >= rowNum || endIndex >= rowNum)
	{
		cerr << "index out of bounds, unable to print data list." << endl;
		return;
	}

	for (int i = startIndex; i <= endIndex; i++)
	{
		dataArray[i].printData();
	}
}

void DataList::convertAndPrint()
{
	// convert Data back and print the data
	for (int i = 0; i <= rearRowIndex; i++)
	{
		Data& currentRow = dataArray[i];
		for (int j = 0; j < columnNum; j++)
		{
			// only convert the column that has been converted
			if (dataConverter[j].getCurrentValue() > 0)
			{
				cout << dataConverter[j].convertBack(currentRow.getColumn(j)) << " ";
			}
			else
			{
				cout << currentRow.getColumn(j) << " ";
			}
		}
		cout << endl;
		// print data type after the last row
		if (i == rearRowIndex)
		{
			for (int j = 0; j < columnNum; j++)
			{
				cout << currentRow.getColumnType(j) << " ";
			}
			cout << endl;
		}
	}
}

void DataList::convertAndPrint(int startIndex, int endIndex)
{
	int n = endIndex - startIndex + 1;
	if (n > rowNum || n <= 0 || startIndex >= rowNum || endIndex >= rowNum)
	{
		cerr << "index out of bounds, unable to convert and print data list." << endl;
		return;
	}
	for (int i = startIndex; i <= endIndex; i++)
	{
		Data& currentRow = dataArray[i];
		for (int j = 0; j < columnNum; j++)
		{
			// only convert the column that has been converted
			if (dataConverter[j].getCurrentValue() > 0)
			{
				cout << dataConverter[j].convertBack(currentRow.getColumn(j)) << " ";
			}
			else
			{
				cout << currentRow.getColumn(j) << " ";
			}
		}
		cout << endl;
		// print data type after the last row
		if (i == rearRowIndex)
		{
			for (int j = 0; j < columnNum; j++)
			{
				cout << currentRow.getColumnType(j) << " ";
			}
			cout << endl;
		}
	}
}

void DataList::readCSV(string filePath, string columnsVariableType, vector<float> columnsDataType)
{
	// Columns Variable Type to let the program knows which type is this column
	// Ex. ifcs -> first column is integer, second is float, third is char, last is string

	// Columns Data Type to let the program knows if the column is categorical(0) or numerical(1)

	// check if number of each type is equal to the column number
	if (columnsVariableType.size() != columnNum)
	{
		cerr << "Columns Variable Type does not equal to the given size of the columns." << endl;
		return;
	}
	if (columnsDataType.size() != columnNum)
	{
		cerr << "Columns Data Type does not equal to the given size of the columns." << endl;
		return;
	}

	ifstream dataFile;
	string line = "";
	dataFile.open(filePath);
	getline(dataFile, line);

	// check if counted columns is equal to data list column num
	if (Utils::CountChar(line, ',') + 1 != columnNum)
	{
		cerr << "Number of columns from the file does not equal to number of columns from this data list." << endl;
		return;
	}

	// create Converter for each column
	for (int i = 0; i < columnNum; i++)
	{
		dataConverter.emplace_back(DataConverter());
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
		Data data(columnNum);
		for (int i = 0; i < columnNum; i++)
		{
			// get cell
			int delimiterLocation = line.find(',');

			string currentCell = line.substr(0, delimiterLocation);
			line = line.substr(delimiterLocation + 1, line.length());

			// add data to a row
			char currentVariableType = columnsVariableType[i];
			float currentDataType = columnsDataType[i];
			DataConverter& currentConverter = dataConverter[i];

			if (currentVariableType == 'i' || currentVariableType == 'f')
				data.insertData(stof(currentCell), currentDataType);
			else if (currentVariableType == 'c' || currentVariableType == 's')
			{
				float convertedValue = currentConverter.convert(currentCell);
				data.insertData(convertedValue, currentDataType);
			}
			else
			{
				cerr << "The program doesn't know data type " + currentVariableType << endl;
			}
		}
		addData(data);
		cout << row + 1 << "/" << rowNum << endl;
	}
	
}

Data& DataList::getDataAt(int index)
{
	if (index >= rowNum)
	{
		cerr << "index out of bounds" << endl;
		return dataArray[0];
	}

	return dataArray[index];
}

DataList DataList::sliceColumn(int startIndex, int endIndex)
{
	int n = endIndex - startIndex + 1; // column length after sliced
	if (n > columnNum || n <= 0 || startIndex >= columnNum || endIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to slice the columns." << endl;
		return *this;
	}

	DataList dropedDataList(n, rowNum);

	// add converter
	for (int i = startIndex; i <= endIndex; i++)
	{
		dropedDataList.dataConverter.emplace_back(dataConverter[i]);
	}

	// add data
	for (int i = 0; i < rowNum; i++)
	{
		Data slicedData = dataArray[i].slice(startIndex, endIndex);
		dropedDataList.addData(slicedData);
	}

	return dropedDataList;
}
