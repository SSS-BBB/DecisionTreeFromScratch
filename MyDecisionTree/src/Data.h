#pragma once
#include <string>

using namespace std;

class Data
{
private:
	// number of features for each data types
	int iFeatureNum;
	int fFeatureNum;
	int cFeatureNum;
	int sFeatureNum;

	// last index of each datatypes
	int rearIndexInt;
	int rearIndexFloat;
	int rearIndexChar;
	int rearIndexString;

public:
	int* iFeatureArray;
	float* fFeatureArray;
	char* cFeatureArray;
	string* sFeatureArray;

	Data(int p_iFeatureNum, int p_fFeatureNum, int p_cFeatureNum, int p_sFeatureNum);

	// Insert Datas
	void InsertInt(int data);
	void InsertFloat(float data);
	void InsertChar(char data);
	void InsertString(string data);

	// Show Datas
	void PrintData();
};