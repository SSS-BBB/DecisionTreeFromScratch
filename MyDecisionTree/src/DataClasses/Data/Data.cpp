#include "Data.h"
#include <iostream>

Data::Data(int p_iFeatureNum, int p_fFeatureNum, int p_cFeatureNum, int p_sFeatureNum)
{
	// Initialize feature numbers
	iFeatureNum = p_iFeatureNum;
	fFeatureNum = p_fFeatureNum;
	cFeatureNum = p_cFeatureNum;
	sFeatureNum = p_sFeatureNum;

	// Initialize features array
	iFeatureArray.reserve(iFeatureNum);
	fFeatureArray.reserve(fFeatureNum);
	cFeatureArray.reserve(cFeatureNum);
	sFeatureArray.reserve(sFeatureNum);

	// Initialize rear indexes
	rearIndexInt = -1;
	rearIndexFloat = -1;
	rearIndexChar = -1;
	rearIndexString = -1;
}

void Data::InsertInt(int data)
{

	if (rearIndexInt >= iFeatureNum - 1)
	{
		cerr << "Integer array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexInt++;
	iFeatureArray.push_back(data);
}

void Data::InsertFloat(float data)
{

	if (rearIndexFloat >= fFeatureNum - 1)
	{
		cerr << "Float array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexFloat++;
	fFeatureArray.push_back(data);
}

void Data::InsertChar(char data)
{

	if (rearIndexChar >= cFeatureNum - 1)
	{
		cerr << "Char array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexChar++;
	cFeatureArray.push_back(data);
}

void Data::InsertString(string data)
{

	if (rearIndexString >= sFeatureNum - 1)
	{
		cerr << "String array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexString++;
	sFeatureArray.push_back(data);
}

void Data::PrintData()
{

	// cout << "Integer Data:" << endl;
	for (int i = 0; i <= rearIndexInt; i++)
	{
		cout << iFeatureArray[i] << ", ";
	}
	// cout << "\n----------------\n";

	// cout << "Float Data:" << endl;
	for (int i = 0; i <= rearIndexFloat; i++)
	{
		cout << fFeatureArray[i] << ", ";
	}
	// cout << "\n----------------\n";

	// cout << "Character Data:" << endl;
	for (int i = 0; i <= rearIndexChar; i++)
	{
		cout << cFeatureArray[i] << ", ";
	}
	// cout << "\n----------------\n";

	// cout << "String Data:" << endl;
	for (int i = 0; i <= rearIndexString; i++)
	{
		cout << sFeatureArray[i] << ", ";
	}
	// cout << "\n----------------\n";
	cout << "\n";
}

int Data::GetIFeatureNum()
{
	return iFeatureNum;
}

int Data::GetFFeatureNum()
{
	return fFeatureNum;
}

int Data::GetCFeatureNum()
{
	return cFeatureNum;
}

int Data::GetSFeatureNum()
{
	return sFeatureNum;
}

int Data::GetIData(int index)
{
	if (index >= iFeatureNum)
	{
		cerr << "index out of bounds" << endl;
		return 0;
	}

	return iFeatureArray[index];
}

float Data::GetFData(int index)
{
	if (index >= fFeatureNum)
	{
		cerr << "index out of bounds" << endl;
		return 0.0f;
	}

	return fFeatureArray[index];
}

char Data::GetCData(int index)
{
	if (index >= cFeatureNum)
	{
		cerr << "index out of bounds" << endl;
		return 0;
	}
	return cFeatureArray[index];
}

string Data::GetSData(int index)
{
	if (index >= sFeatureNum)
	{
		cerr << "index out of bounds" << endl;
		return "";
	}

	return sFeatureArray[index];
}
