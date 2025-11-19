#include "Utils.h"

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
