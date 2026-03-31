#pragma once
#include <string>
#include <vector>

using namespace std;

class Utils
{
public:
	static int CountChar(string s, char targetCount);
	static vector<float>  createFilledArray(int size, float value);
	static void printArrayWithIndex(vector<float> array);
};