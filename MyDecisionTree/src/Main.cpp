#include <iostream>
#include "Data.h"
#include "DataList.h"

using namespace std;

int main()
{
	//Data dummy(1, 2, 1, 3);

	//dummy.InsertInt(20);

	//dummy.InsertFloat(176.2);
	//dummy.InsertFloat(58.7);

	//dummy.InsertChar('O');

	//dummy.InsertString("Suphawit");
	//dummy.InsertString("Buaphan");
	//dummy.InsertString("Kaow");

	//Data someone(1, 2, 1, 3);

	//someone.InsertInt(25);

	//someone.InsertFloat(180.0);
	//someone.InsertFloat(75);

	//someone.InsertChar('A');

	//someone.InsertString("Some");
	//someone.InsertString("One");
	//someone.InsertString("Two");

	//Data errorData(1, 2, 2, 3);

	//errorData.InsertInt(30);

	//errorData.InsertFloat(5);
	//errorData.InsertFloat(79);

	//errorData.InsertChar('B');
	//errorData.InsertChar('C');

	//errorData.InsertString("Error");
	//errorData.InsertString("Data");
	//errorData.InsertString("Test");

	//Data good(1, 2, 1, 3);

	//good.InsertInt(18);

	//good.InsertFloat(175.0);
	//good.InsertFloat(60);

	//good.InsertChar('B');

	//good.InsertString("Good");
	//good.InsertString("Data");
	//good.InsertString("Test");

	//// Data List Test
	//DataList dataList(1, 2, 1, 3, 4);

	//dataList.AddData(dummy);
	//dataList.AddData(someone);
	//dataList.AddData(errorData);
	//dataList.AddData(good);

	// Read CSV Test
	DataList csvData(3, 0, 5, 1, 1000);

	// cisciccic
	clock_t start = clock();
	csvData.ReadCSV("./data/Employee.csv", "cisciccic");
	csvData.PrintDataList();
	clock_t duration = clock() - start;
	cout << "Time: " << (float)duration / CLOCKS_PER_SEC << " seconds" << endl;
	

	return 0;
}