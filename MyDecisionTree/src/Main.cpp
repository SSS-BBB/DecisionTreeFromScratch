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
	vector<int> dummyDataType = { 0, 1, 0, 0, 1 };
	DataList dummyData(20, dummyDataType);

	// add datas
	vector<float> row1 = { 1, 2, 3, 4, 5 };
	vector<float> row2 = { 1, 3, 5, 7, 9 };
	vector<float> row3 = { 5, 7, 11, 8, 8 };
	vector<float> row4 = { 4, 11, 0, 5, 1 };
	vector<float> row5 = { 8, 9, 7, 2, 5 };
	dummyData.addRow(row1);
	dummyData.addRow(row2);
	dummyData.addRow(row3);
	dummyData.addRow(row4);
	dummyData.addRow(row5);

	dummyData.printDataList();
	*/

	
	vector<int> dataType = {0, 1, 0, 0, 1, 0, 0, 1, 0};
	DataList dataList(2026, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissii");
	// dataList.convertAndPrint();
	
	DataList slicedDataList = dataList.sliceColumn(2, 5).sliceRow(500, 1000);
	dataList.convertAndPrint(0, 9);
	cout << "-----------------" << endl;
	slicedDataList.convertAndPrint(0, 9);


	return 0;
}