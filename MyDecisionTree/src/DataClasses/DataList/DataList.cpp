#include "DataList.h"
#include <iostream>
#include <fstream>
#include "../../Utils/Utils.h"

DataList::DataList(int p_rowNum, vector<int> p_columnDataTypes)
{
	// Initialize column numbers
	columnNum = p_columnDataTypes.size();

	// Initialize rows number and index
	rowNum = p_rowNum;
	rearRowIndex = -1;

	// Initialize data array with size
	dataArray = make_unique<vector<vector<float>>>();
	dataArray->reserve(rowNum);

	// initialize data converter with size
	dataConverter.reserve(columnNum);

	// initialize column data types
	columnDataTypes.reserve(columnNum);
	columnDataTypes = p_columnDataTypes;

	// initialize unique value columns with size
	uniqueValueColumns.reserve(columnNum);

	// create data converter and unique values set for each columns
	for (int i = 0; i < columnNum; i++)
	{
		// create data converter
		dataConverter.emplace_back(DataConverter());
		// create unique value set
		set<float> emptyset = {};
		uniqueValueColumns.push_back(emptyset);
	}
}

DataList::DataList() : DataList(0, {})
{

}

int DataList::getColumnNum()
{
	return columnNum;
}

int DataList::getRowNum()
{
	return rowNum;
}

int DataList::getRearRowIndex()
{
	return rearRowIndex;
}

void DataList::addRow(vector<float> rowData)
{
	// check if data array is nullptr
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to add a row." << endl;
		return;
	}

	// check if datas are full
	if (rearRowIndex >= rowNum - 1)
	{
		cerr << "Data List is full, unable to add more data." << endl;
		cerr << "Unable to add this data" << endl;
		cerr << "-------------------------" << endl;
		return;
	}
	// check if columns don't match
	if (rowData.size() != columnNum)
	{
		cerr << "Columns from this data don't match column number given for this DataList Class." << endl;
		cerr << "Unable to add this data" << endl;
		cerr << "-------------------------" << endl;
		return;
	}

	rearRowIndex++;

	// add unique values
	for (int i = 0; i < columnNum; i++)
	{
		uniqueValueColumns[i].insert(rowData[i]);
	}

	// add rows
	dataArray->emplace_back(rowData);
}

void DataList::printColumnDataTypes()
{
	cout << "Column Data Type:" << endl;
	for (int j = 0; j < columnNum; j++)
	{
		cout << columnDataTypes[j] << " ";
	}
	cout << endl;
}

void DataList::printDataList()
{
	/*if (dataArray == nullptr)
	{
		cout << "Data Array is nullptr, unable to print data list." << endl;
		return;
	}*/

	printDataList(0, rearRowIndex);
}

void DataList::printDataList(int startIndex, int endIndex)
{
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to print data list." << endl;
		return;
	}

	int n = endIndex - startIndex + 1;
	if (n > rowNum || n <= 0 || startIndex >= rowNum || endIndex >= rowNum)
	{
		cerr << "index out of bounds, unable to print data list." << endl;
		return;
	}

	for (int i = startIndex; i <= endIndex; i++)
	{
		for (int j = 0; j < columnNum; j++)
		{
			cout << (*dataArray)[i][j] << " ";
		}
		cout << endl;
		if (i == rearRowIndex)
		{
			printColumnDataTypes();
		}
	}

	cout << "Data Size = " << rowNum << endl;
}

void DataList::printUniqueData()
{
	for (set<float> uniqueValues : uniqueValueColumns)
	{
		for (float unique : uniqueValues)
		{
			cout << unique << " ";
		}
		cout << endl;
	}

	cout << "Midpoints" << endl;
	for (set<float> midpointSet : midpointColumns)
	{
		for (float midvalue : midpointSet)
		{
			cout << midvalue << " ";
		}
		cout << endl;
	}
}

void DataList::convertAndPrint()
{
	convertAndPrint(0, rearRowIndex);
}

void DataList::convertAndPrint(int startIndex, int endIndex)
{
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to convert and print data list." << endl;
		return;
	}

	int n = endIndex - startIndex + 1;
	if (n > rowNum || n <= 0 || startIndex >= rowNum || endIndex >= rowNum)
	{
		cerr << "index out of bounds, unable to convert and print data list." << endl;
		return;
	}
	for (int i = startIndex; i <= endIndex; i++)
	{
		for (int j = 0; j < columnNum; j++)
		{
			// only convert the column that has been converted
			if (dataConverter[j].getConvertedSize() > 0)
			{
				cout << dataConverter[j].convertBack((*dataArray)[i][j]) << " ";
			}
			else
			{
				cout << (*dataArray)[i][j] << " ";
			}
		}
		cout << endl;
		// print data type after the last row
		if (i == rearRowIndex)
		{
			printColumnDataTypes();
		}
	}
}



void DataList::readCSV(string filePath, string columnsVariableType)
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
		vector<float> currentRow;
		currentRow.reserve(columnNum);
		for (int i = 0; i < columnNum; i++)
		{
			// get cell
			int delimiterLocation = line.find(',');

			string currentCell = line.substr(0, delimiterLocation);
			line = line.substr(delimiterLocation + 1, line.length());

			// add data to a row
			char currentVariableType = columnsVariableType[i];
			float currentDataType = columnDataTypes[i];
			DataConverter& currentConverter = dataConverter[i];

			// int or float data
			if (currentVariableType == 'i' || currentVariableType == 'f')
			{
				// add data to the cell
				float addedValue = stof(currentCell);
				currentRow.push_back(addedValue);
			}
			// char or string data
			else if (currentVariableType == 'c' || currentVariableType == 's')
			{
				// add data to the cell
				float convertedValue = currentConverter.convert(currentCell);
				currentRow.push_back(convertedValue);
			}
			else
			{
				cerr << "The program doesn't know data type " + currentVariableType << endl;
			}
		}
		addRow(currentRow);
		cout << row + 1 << "/" << rowNum << endl;
	}
	
	// finished adding data
	setMidpoint();
}

float DataList::getDataAt(int rowIndex, int columnIndex)
{
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to get data at index " 
			<< "(" << rowIndex << "," << columnIndex << ")" << endl;
		return 404;
	}

	if (rowIndex >= rowNum || columnIndex >= columnNum || rowIndex < 0 || columnIndex < 0)
	{
		cerr << "index out of bounds, unable to get data at index."
		     << "(" << rowIndex << "," << columnIndex << ")" << endl;
		return (*dataArray)[0][0];
	}

	return (*dataArray)[rowIndex][columnIndex];
}

DataList DataList::sliceColumn(int startIndex, int endIndex)
{
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to slice the columns." << endl;
		return move(*this);
	}

	int n = endIndex - startIndex + 1; // column length after sliced
	if (n > columnNum || n <= 0 || startIndex >= columnNum || endIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to slice the columns." << endl;
		return move(*this);
	}
	// create column data types
	vector<int> droppedColumnDataTypes;
	droppedColumnDataTypes.reserve(n);
	for (int i = startIndex; i <= endIndex; i++)
	{
		droppedColumnDataTypes.push_back(columnDataTypes[i]);
	}

	DataList dropedDataList(rowNum, droppedColumnDataTypes);

	// add converter
	for (int i = startIndex; i <= endIndex; i++)
	{
		//                              0 -> n-1       startIndex -> endIndex
		dropedDataList.setDataConverter(i - startIndex, dataConverter[i]);
	}

	// add data
	for (int i = 0; i < rowNum; i++)
	{
		vector<float> currentSlicedColumn;
		currentSlicedColumn.reserve(n);
		for (int j = startIndex; j <= endIndex; j++)
		{
			currentSlicedColumn.push_back((*dataArray)[i][j]);
		}
		dropedDataList.addRow(currentSlicedColumn);
	}

	dropedDataList.setMidpoint();

	return dropedDataList;
}

DataList DataList::sliceRow(int startIndex, int endIndex)
{
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to slice rows." << endl;
		return move(*this);
	}

	int n = endIndex - startIndex + 1; // row length after sliced
	if (n > rowNum || n <= 0 || startIndex >= rowNum || endIndex >= rowNum)
	{
		cerr << "index out of bounds, unable to slice rows." << endl;
		return move(*this);
	}

	DataList slicedDataList(n, columnDataTypes);

	// add converter
	for (int i = 0; i < columnNum; i++)
	{
		slicedDataList.setDataConverter(i, dataConverter[i]);
	}

	// add data
	for (int i = startIndex; i <= endIndex; i++)
	{
		slicedDataList.addRow((*dataArray)[i]);
	}

	slicedDataList.setMidpoint();

	return slicedDataList;
}

DataList DataList::selectRow(vector<int> selectRowIndex)
{
	// get data for some indexes
	if (dataArray == nullptr)
	{
		cerr << "Data Array is missing, unable to select rows." << endl;
		return move(*this);
	}

	DataList selectedData(selectRowIndex.size(), columnDataTypes);

	// add converter
	for (int i = 0; i < columnNum; i++)
	{
		selectedData.setDataConverter(i, dataConverter[i]);
	}

	// add data
	for (int i : selectRowIndex)
	{
		selectedData.addRow((*dataArray)[i]);
	}

	selectedData.setMidpoint();

	return selectedData;
}

void DataList::saveConverterAt(int index, string filepath)
{
	if (index < 0 || index >= columnNum)
	{
		cerr << "index out of bounds, unable to save data converter at " << index << endl;
		return;
	}

	dataConverter[index].save(filepath);
}

void DataList::setDataConverter(int index, DataConverter &newDataConverter)
{
	if (index < 0 || index >= columnNum)
	{
		cerr << "index out of bounds, unable to set data converter at " << index << endl;
		return;
	}

	dataConverter[index] = newDataConverter;
}

int DataList::getColumnDataTypeAt(int columnIndex)
{
	if (columnIndex < 0 || columnIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to get column data type at " << columnIndex << endl;
		return -1;
	}

	return columnDataTypes[columnIndex];
}

set<float> DataList::getUniqueAtColumn(int columnIndex)
{
	if (columnIndex < 0 || columnIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to get unique values at column " << columnIndex << endl;
		set<float> emptyset = {};
		return emptyset;
	}

	return uniqueValueColumns[columnIndex];
}

set<float> DataList::getMidpointsAtColumn(int columnIndex)
{
	if (columnIndex < 0 || columnIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to get midpoints at column " << columnIndex << endl;
		set<float> emptyset = {};
		return emptyset;
	}

	if (columnDataTypes[columnIndex] != 1)
	{
		cout << "Warning: getting midpoints at non-numerical columns. set will be empty." << endl;
	}

	return midpointColumns[columnIndex];
}

set<float> DataList::getTresholdsAtColumn(int columnIndex)
{
	// return uniques if column is categorical, and return midpoints if column is numerical
	if (columnIndex < 0 || columnIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to get treshold at column " << columnIndex << endl;
		set<float> emptyset = {};
		return emptyset;
	}

	if (columnDataTypes[columnIndex] == 1)
	{
		return getMidpointsAtColumn(columnIndex);
	}

	return getUniqueAtColumn(columnIndex);
}

vector<float> DataList::getColumn(int columnIndex)
{
	// get specific column as a vector
	if (columnIndex < 0 || columnIndex >= columnNum)
	{
		cerr << "index out of bounds, unable to get the column " << columnIndex << endl;
		vector<float> emptyvector = {};
		return emptyvector;
	}

	vector<float> columnData;
	columnData.reserve(rowNum);

	for (int i = 0; i < rowNum; i++)
	{
		columnData.push_back(getDataAt(i, columnIndex));
	}

	return columnData;
}

void DataList::setMidpoint()
{
	// set midpoint value from unique values for numerical columns
	for (int i = 0; i < columnDataTypes.size(); i++)
	{
		set<float> midpoints;
		if (columnDataTypes[i] == 1)
		{
			// convert unique values set to vector
			vector<float> uniqueNums(uniqueValueColumns[i].begin(), uniqueValueColumns[i].end());

			for (int j = 0; j < uniqueNums.size() - 1; j++)
			{
				float midvalue = (uniqueNums[j] + uniqueNums[j + 1]) / 2.0f;
				midpoints.insert(midvalue);
			}
		}
		midpointColumns.emplace_back(midpoints);
	}
}

