#include "Utils.h"
#include <iostream>

int Utils::CountChar(string s, char targetCount)
{
    int count = 0;
    for (char c : s)
    {
        if (c == targetCount)
            count++;
    }

    return count;
}

vector<float> Utils::createFilledArray(int size, float value)
{
    if (size < 0)
    {
        cerr << "Unable to create an array with negative size." << endl;
        vector<float> empty = {};
        return empty;
    }

    // create n size array filled with value
    vector<float> filledArray;
    filledArray.reserve(size);
    for (int i = 0; i < size; i++)
    {
        filledArray.push_back(value);
    }

    return filledArray;
}

void Utils::printArrayWithIndex(vector<float> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << i << ": " << array[i] << endl;
    }
}
