#pragma once
#include <string>

using namespace std;

class Data
{
private:
	// last index of each datatypes
	int rearIndexInt;
	int rearIndexFloat;
	int rearIndexChar;
	int rearIndexString;

public:
	// number of features for each data types
	int iFeatureNum;
	int fFeatureNum;
	int cFeatureNum;
	int sFeatureNum;

	int* iFeatureArray;
	float* fFeatureArray;
	char* cFeatureArray;
	string* sFeatureArray;

	Data(int p_iFeatureNum, int p_fFeatureNum, int p_cFeatureNum, int p_sFeatureNum);
	Data();

	// Insert Datas
	void InsertInt(int data);
	void InsertFloat(float data);
	void InsertChar(char data);
	void InsertString(string data);

	// Show Datas
	void PrintData();
};