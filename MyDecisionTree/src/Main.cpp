#include <iostream>
#include <ctime>
#include <string>
#include <memory>
#include "DataClasses/Data/Data.h"
#include "DataClasses/DataList/DataList.h"
#include "TreeClasses/Node/Node.h"
#include "DataClasses/DataConverter/DataConverter.h"
#include "TreeClasses/DecisionTreeCreator/DecisionTreeCreator.h"
#include "Utils/Utils.h"

using namespace std;

void dummyDataTest();
void readCSVTest();
void nodeTest();
void treeCreatorTest();

int main()
{
	// readCSVTest();
	treeCreatorTest();
	// nodeTest();
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
	dataList.readCSV("data/Employee.csv", "sisiissic");
	
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
	dataList.readCSV("data/Employee.csv", "sisiissic");
	// node test
	// create data
	DataList featureData = dataList.sliceColumn(0, 7);
	featureData.printDataList(0, 9);
	featureData.printUniqueData();

	vector<float> labelsData = Utils::createFilledArray(N, -1);

	vector<int> dataIndexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// create node
	unique_ptr<Node> rootNode = make_unique<Node>(2, 2);
	unique_ptr<Node> node11 = make_unique<Node>(1, 2015);
	unique_ptr<Node> node12 = make_unique<Node>(3, 1);
	unique_ptr<Node> leafNode21 = make_unique<Node>(-1, 0);
	unique_ptr<Node> leafNode22 = make_unique<Node>(-1, 1);
	unique_ptr<Node> leafNode23 = make_unique<Node>(-1, 0);
	unique_ptr<Node> leafNode24 = make_unique<Node>(-1, 1);

	// connect node
	rootNode->setLeftNode(make_unique<Node>(1, 2015));
	rootNode->setRightNode(make_unique<Node>(3, 1));

	rootNode->getLeftNode()->setLeftNode(make_unique<Node>(-1, 0));
	rootNode->getLeftNode()->setRightNode(make_unique<Node>(-1, 1));

	rootNode->getRightNode()->setLeftNode(make_unique<Node>(-1, 0));
	rootNode->getRightNode()->setRightNode(make_unique<Node>(-1, 1));

	// test node
	rootNode->predictAll(featureData, labelsData);

	cout << "---------------" << endl;
	// print labels
	Utils::printArrayWithIndex(labelsData);
}

void treeCreatorTest()
{
	// Data
	const int N = 100;
	vector<int> dataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
	DataList dataList(N, dataType);
	dataList.readCSV("data/Employee.csv", "sisiissic"); // make labels column c to convert labels data to 0-n

	DataList featureData = dataList.sliceColumn(0, 7);
	vector<float> labels = dataList.getColumn(8);
	set<float> labelUniqueValues = dataList.getUniqueAtColumn(8);

	dataList.convertAndPrint();

	// Tree
	DecisionTreeCreator tree(&featureData, &labels, labelUniqueValues.size());
	unique_ptr<Node> root = move(tree.createTree());
	// tree.printNodeMemory();
	// root.printAllChildren(0);

	// Test Tree
	vector<float> labelTest = Utils::createFilledArray(featureData.getRowNum(), -1);
	root->predictAll(featureData, labelTest);
	Utils::printArrayWithIndex(labelTest);
}
