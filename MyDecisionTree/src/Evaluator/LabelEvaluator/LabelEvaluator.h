#pragma once
#include <vector>

using namespace std;

class LabelEvaluator
{
public:
	static vector<vector<float>> confusionMatrix(vector<float> predictedLabel, vector<float> trueLabel, int labelNum);
};

