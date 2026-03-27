#pragma once
#include <map>
#include <string>

using namespace std;

class DataConverter
{
private:
	map<string, float> convertedDict;
	float currentValue;
	string CURRENT_FILE_VERSION = "CVTR 0.2";
public:
	DataConverter();
	DataConverter(map<string, float> p_convertedDict, float p_currentValue); // initialize with values

	float convert(string data);
	string convertBack(float value);

	float getCurrentValue();

	void save(string filepath);
	void load(string filepath);
};

