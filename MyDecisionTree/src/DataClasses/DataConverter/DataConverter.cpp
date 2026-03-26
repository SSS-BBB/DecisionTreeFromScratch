#include "DataConverter.h"

DataConverter::DataConverter()
{
	convertedDict = {};
	currentValue = 0;
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

float DataConverter::getCurrentValue()
{
	return currentValue;
}
