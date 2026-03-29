#include <iostream>
#include <ctime>
#include <string>
#include "DataClasses/Data/Data.h"
#include "DataClasses/DataList/DataList.h"
#include "TreeClasses/Node/Node.h"
#include "DataClasses/DataConverter/DataConverter.h"

using namespace std;

int main()
{
	
	vector<int> dummyDataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	DataList dummyData(20, dummyDataType);

	// add datas
	vector<float> row1 = { 1, 2017, 1, 3, 34, 1, 2, 0, 0 };
	vector<float> row2 = { 2, 2013, 2, 3, 34, 2, 2, 3, 1 };
	vector<float> row3 = { 2, 2015, 3, 3, 34, 1, 1, 2, 1 };
	vector<float> row4 = { 3, 2020, 1, 3, 34, 2, 1, 5, 0 };
	vector<float> row5 = { 1, 2024, 2, 3, 34, 1, 2, 2, 0 };
	dummyData.addRow(row1);
	dummyData.addRow(row2);
	dummyData.addRow(row3);
	dummyData.addRow(row4);
	dummyData.addRow(row5);

	dummyData.convertAndPrint();
	cout << "---------------" << endl;

	// load converters
	DataConverter loadedConverter0;
	loadedConverter0.load("saved file/data converters/converter0.cvtr");
	dummyData.setDataConverter(0, loadedConverter0);

	DataConverter loadedConverter1;
	loadedConverter1.load("saved file/data converters/converter1.cvtr");
	dummyData.setDataConverter(1, loadedConverter1);

	dummyData.convertAndPrint();
	dummyData.printUniqueData();

	
	
	/*
	vector<int> dataType = {0, 1, 0, 0, 1, 0, 0, 1, 0};
	DataList dataList(1000, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissii");
	// dataList.convertAndPrint();
	
	DataList slicedDataList = dataList.sliceColumn(2, 5).sliceRow(500, 600);

	// save data converter
	// dataList.saveConverterAt(1, "saved file/data converters/converter1.cvtr");
	*/


	return 0;
}