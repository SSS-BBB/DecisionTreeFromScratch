#pragma once
#include <map>
#include <string>
#include <set>

using namespace std;

class DataConverter
{
private:
	map<string, float> convertedDict;
	float currentValue;

	// set<float> uniqueValues;

	string CURRENT_SAVE_FILE_VERSION = "CVTR 0.3.5";
	string CURRENT_LOAD_FILE_VERSION = "CVTR 0.3.5";
public:
	DataConverter();
	DataConverter(map<string, float> p_convertedDict, float p_currentValue); // initialize with values

	float convert(string data);
	string convertBack(float value);

	float getCurrentValue();

	// void addUniqueValue(float value);
	// void printUniqueValues();

	void save(string filepath);
	void load(string filepath);
};

