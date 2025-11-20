#pragma once
#include <string>
#include <vector>

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

	// array of the features
	vector<int> iFeatureArray;
	vector<float> fFeatureArray;
	vector<char> cFeatureArray;
	vector<string> sFeatureArray;

public:
	Data(int p_iFeatureNum = 0, int p_fFeatureNum = 0, int p_cFeatureNum = 0, int p_sFeatureNum = 0);

	// Insert Datas
	void InsertInt(int data);
	void InsertFloat(float data);
	void InsertChar(char data);
	void InsertString(string data);

	// Show Datas
	void PrintData();

	// Getter
	int GetIFeatureNum();
	int GetFFeatureNum();
	int GetCFeatureNum();
	int GetSFeatureNum();

	// Get Data
	int GetIData(int index);
	float GetFData(int index);
	char GetCData(int index);
	string GetSData(int index);
};