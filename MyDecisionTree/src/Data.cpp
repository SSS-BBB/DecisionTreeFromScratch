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
	iFeatureArray = new int[iFeatureNum];
	fFeatureArray = new float[fFeatureNum];
	cFeatureArray = new char[cFeatureNum];
	sFeatureArray = new string[sFeatureNum];

	// Initialize rear indexes
	rearIndexInt = -1;
	rearIndexFloat = -1;
	rearIndexChar = -1;
	rearIndexString = -1;
}

Data::Data()
{
	Data::Data(0, 0, 0, 0);
}

void Data::InsertInt(int data)
{
	if (rearIndexInt >= iFeatureNum - 1)
	{
		cout << "Integer array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexInt++;
	iFeatureArray[rearIndexInt] = data;
}

void Data::InsertFloat(float data)
{
	if (rearIndexFloat >= fFeatureNum - 1)
	{
		cout << "Float array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexFloat++;
	fFeatureArray[rearIndexFloat] = data;
}

void Data::InsertChar(char data)
{
	if (rearIndexChar >= cFeatureNum - 1)
	{
		cout << "Char array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexChar++;
	cFeatureArray[rearIndexChar] = data;
}

void Data::InsertString(string data)
{
	if (rearIndexString >= sFeatureNum - 1)
	{
		cout << "String array is full, unable to insert " << data << endl;
		return;
	}

	rearIndexString++;
	sFeatureArray[rearIndexString] = data;
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
