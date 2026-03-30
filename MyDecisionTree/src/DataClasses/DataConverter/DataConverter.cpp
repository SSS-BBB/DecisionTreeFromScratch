#include "DataConverter.h"
#include <iostream>
#include <fstream>

DataConverter::DataConverter()
{
	convertedDict = {};
	currentValue = -1;
}

DataConverter::DataConverter(map<string, float> p_convertedDict, float p_currentValue)
{
	convertedDict = p_convertedDict;
	currentValue = p_currentValue;
}

float DataConverter::convert(string data)
{
	// x.first is the key we are trying to convert, x.second is the value that the key will converts to
	for (auto x : convertedDict)
	{
		if (x.first == data) return x.second;
	}
	// creates new pair
	currentValue++;
	convertedDict.insert({data, currentValue});
	// add unique value
	// addUniqueValue(currentValue);

	return currentValue;
}

string DataConverter::convertBack(float value)
{
	for (auto x : convertedDict)
	{
		if (x.second == value) return x.first;
	}
	// unable to find the value to convert back to
	return "No Value!";
}

int DataConverter::getConvertedSize()
{
	return currentValue + 1;
}

/*
float DataConverter::getCurrentValue()
{
	return currentValue;
}
*/
/*
void DataConverter::addUniqueValue(float value)
{
	uniqueValues.insert(value);
}

void DataConverter::printUniqueValues()
{
	for (float unique : uniqueValues)
	{
		cout << unique << " ";
	}
	cout << endl;
}
*/

void DataConverter::save(string filepath)
{
	// file surname must be .cvtr (converter)
	int dotPos = filepath.find(".");
	if (dotPos < 0 || filepath.substr(dotPos + 1) != "cvtr")
	{
		cerr << "Invalid filepath " + filepath << endl;
		cerr << "filename must ends with .cvtr" << endl;
		return;
	}

	ofstream file(filepath);

	// version
	file << CURRENT_SAVE_FILE_VERSION << endl;

	// save current value
	file << "currentValue" << endl;
	file << currentValue << endl;

	// save unique values
	/*
	file << "uniqueValues" << endl;
	for (float unique : uniqueValues)
	{
		file << unique << ",";
	}
	file << endl;
	*/

	// save converted dictionary (map)
	file << "convertedDict" << endl;
	for (auto x : convertedDict)
	{
		file << x.first << "," << x.second << endl;
	}
	file << "end";

	file.close();
	cout << "Data Converter saved successfully at " << filepath << endl;
}

void DataConverter::load(string filepath)
{
	// file surname must be .cvtr (converter)
	int dotPos = filepath.find(".");
	if (dotPos < 0 || filepath.substr(dotPos + 1) != "cvtr")
	{
		cerr << "Invalid filepath " + filepath << endl;
		cerr << "filename must ends with .cvtr" << endl;
		return;
	}

	ifstream file(filepath);
	convertedDict.clear();

	string line = "";
	getline(file, line);

	// check version
	if (line != CURRENT_LOAD_FILE_VERSION)
	{
		cerr << "Invalid File Version" << endl;
		cerr << "Needs " << CURRENT_LOAD_FILE_VERSION << " to load." << endl;
		return;
	}
	getline(file, line);
	
	// get current value
	if (line == "currentValue")
	{
		getline(file, line);
		currentValue = stof(line);
	}
	getline(file, line);

	/*
	// get unique values
	if (line == "uniqueValues")
	{
		getline(file, line);
		while (!line.empty())
		{
			int delimiterLocation = line.find(',');
			float unique = stof(line.substr(0, delimiterLocation));
			addUniqueValue(unique);
			line = line.substr(delimiterLocation + 1);
		}
	}
	getline(file, line);
	*/

	// get converted dictionary
	if (line == "convertedDict")
	{
		getline(file, line);
		while (line != "end" and !line.empty())
		{
			int delimiterLocation = line.find(',');
			string toConvertData = line.substr(0, delimiterLocation);
			float convertedValue = stof(line.substr(delimiterLocation + 1));
			convertedDict.insert({toConvertData, convertedValue});
			getline(file, line);
		}
	}

	file.close();
	cout << "Data Converter loaded successfully from " << filepath << endl;

}
