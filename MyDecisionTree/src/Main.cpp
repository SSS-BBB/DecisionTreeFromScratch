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
	vector<float> dataType = {0, 1, 0, 0, 1, 0, 0, 1, 0};
	DataList dataList(9, 2026);
	dataList.readCSV("data/Employee.csv", "sisiissii", dataType);
	
	DataList slicedDataList = dataList.sliceColumn(2, 5);
	dataList.printDataList(0, 9);
	cout << "-----------------" << endl;
	slicedDataList.printDataList(0, 9);


	return 0;
}