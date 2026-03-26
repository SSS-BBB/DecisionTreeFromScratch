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
	// 1 1 2 3 2 1 3 4
	vector<string> strList = {"Hello", "Hello", "World", "Hi", "World", "Hello", "Hi", "Bye"};
	int n = strList.size();

	DataConverter converter = DataConverter();
	vector<float> convertedList;
	convertedList.reserve(n);

	for (int i = 0; i < n; i++)
	{
		float convertedValue = converter.convert(strList[i]);
		convertedList.push_back(convertedValue);
	}

	for (float value : convertedList)
	{
		cout << value << " ";
	}
	cout << endl;


	return 0;
}