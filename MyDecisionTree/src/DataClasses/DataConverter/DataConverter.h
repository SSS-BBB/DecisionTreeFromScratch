#pragma once
#include <map>
#include <string>

using namespace std;

class DataConverter
{
private:
	map<string, float> convertedDict;
	float currentValue;
public:
	DataConverter();
	float convert(string data);
	string convertBack(float value);
};

