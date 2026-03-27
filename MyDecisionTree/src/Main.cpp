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
	/*
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

	DataConverter loadedConverter;
	loadedConverter.load("saved file/data converters/converter0.cvtr");
	dummyData.setDataConverter(0, loadedConverter);
	dummyData.convertAndPrint();

	*/
	

	vector<int> dataType = {0, 1, 0, 0, 1, 0, 0, 1, 0};
	DataList dataList(1000, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissii");
	// dataList.convertAndPrint();
	
	DataList slicedDataList = dataList.sliceColumn(2, 5).sliceRow(500, 600);
	// dataList.convertAndPrint(0, 9);
	// cout << "-----------------" << endl;
	// slicedDataList.convertAndPrint(0, 9);


	return 0;
}