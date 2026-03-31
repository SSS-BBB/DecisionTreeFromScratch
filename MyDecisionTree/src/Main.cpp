#include <iostream>
#include <ctime>
#include <string>
#include "DataClasses/Data/Data.h"
#include "DataClasses/DataList/DataList.h"
#include "TreeClasses/Node/Node.h"
#include "DataClasses/DataConverter/DataConverter.h"
#include "TreeClasses/DecisionTreeCreator/DecisionTreeCreator.h"

using namespace std;

void dummyDataTest();
void readCSVTest();
void nodeTest();
void treeCreatorTest();

int main()
{
	// treeCreatorTest();
	nodeTest();
	return 0;
}

void dummyDataTest()
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

	dummyData.printUniqueData();

	// load converters
	/*
	DataConverter loadedConverter0;
	loadedConverter0.load("saved file/data converters/converter0.cvtr");
	dummyData.setDataConverter(0, loadedConverter0);

	DataConverter loadedConverter1;
	loadedConverter1.load("saved file/data converters/converter1.cvtr");
	dummyData.setDataConverter(1, loadedConverter1);

	dummyData.convertAndPrint();
	dummyData.printUniqueData();
	*/
}

void readCSVTest()
{
	const int N = 1000;
	vector<int> dataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	DataList dataList(N, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissii");

	DataList slicedDataList = dataList.sliceColumn(2, 5).sliceRow(500, 600);

	dataList.convertAndPrint(0, 4);
	dataList.printUniqueData();
	cout << "--------------" << endl;
	slicedDataList.convertAndPrint(0, 4);
	cout << "--------------" << endl;
	slicedDataList.printUniqueData();

	// save data converter
	// dataList.saveConverterAt(1, "saved file/data converters/converter1.cvtr");
}

void nodeTest()
{
	const int N = 1000;
	vector<int> dataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	DataList dataList(N, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissii");
	// node test
	// create data
	DataList featureData = dataList.sliceColumn(0, 7);
	featureData.printDataList(0, 9);
	featureData.printUniqueData();

	vector<float> labelsData;
	labelsData.reserve(N);
	for (int i = 0; i < N; i++)
	{
		labelsData.push_back(-1);
	}

	vector<int> dataIndexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// create node
	Node rootNode(2, 2);
	Node node11(1, 2015);
	Node node12(3, 1);
	Node leafNode0(-1, 0);
	Node leafNode1(-1, 1);

	// connect node
	rootNode.setLeftNode(&node11);
	rootNode.setRightNode(&node12);

	node11.setLeftNode(&leafNode0);
	node11.setRightNode(&leafNode1);

	node12.setLeftNode(&leafNode0);
	node12.setRightNode(&leafNode1);

	// test node
	rootNode.predict(dataIndexes, featureData, labelsData);

	cout << "---------------" << endl;
	// print labels
	for (int index : dataIndexes)
	{
		cout << index << " " << labelsData[index] << endl;
	}
}

void treeCreatorTest()
{
	// Data
	const int N = 5;
	vector<int> dataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	DataList dataList(N, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissic"); // make labels column c to convert labels data to 0-n

	DataList featureData = dataList.sliceColumn(0, 7);
	vector<float> labels = dataList.getColumn(8);
	set<float> labelUniqueValues = dataList.getUniqueAtColumn(8);

	dataList.convertAndPrint();

	// Tree
	DecisionTreeCreator tree(&featureData, &labels, labelUniqueValues.size());
	tree.createTree();
}
