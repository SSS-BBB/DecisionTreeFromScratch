#include "LabelEvaluator.h"
#include <iostream>

vector<vector<float>> LabelEvaluator::confusionMatrix(vector<float> predictedLabel, vector<float> trueLabel, int labelNum)
{
    if (predictedLabel.size() != trueLabel.size())
    {
        cerr << "Predicted Label and True Label do not have the same length, unable to create a confusion matrix" << endl;
        vector<vector<float>> empty = {};
        return empty;
    }

    // create a 2d array with rows represent true label, and columns represent predicted label
    vector<vector<float>> confusionMatrix;
    confusionMatrix.reserve(labelNum);
    for (int i = 0; i < labelNum; i++)
    {
        vector<float> newRow;
        newRow.reserve(labelNum);
        for (int j = 0; j < labelNum; j++)
        {
            newRow.push_back(0);
        }
        confusionMatrix.push_back(newRow);
    }

    // analyze data
    float p = 1.0f / trueLabel.size();
    for (int i = 0; i < trueLabel.size(); i++)
    {
        int trueValue = trueLabel[i];
        if (trueValue < 0 || trueValue >= labelNum)
        {
            cerr << "This true label is not converted, unable to include " << trueValue << 
                " in confusion matrix." << endl;
            continue;
        }

        int predictedValue = predictedLabel[i];
        if (predictedValue < 0 || predictedValue >= labelNum)
        {
            cerr << "This predicted label is not converted, unable to include " << predictedValue <<
                    " in confusion matrix." << endl;
            continue;
        }

        confusionMatrix[trueValue][predictedValue] += p;
        
    }

    // print confusion Matrix
    for (int i = 0; i < labelNum; i++)
    {
        for (int j = 0; j < labelNum; j++)
        {
            cout << confusionMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // print info from the confusion matrix
    // Accuracy
    float accuracy = 0.0f;
    for (int i = 0; i < labelNum; i++)
    {
        // diagonal
        accuracy += confusionMatrix[i][i];
    }
    cout << "Accuracy = " << accuracy << endl;

    // Precision
    vector<float> precision;
    precision.reserve(labelNum);
    for (int i = 0; i < labelNum; i++)
    {
        // nominator
        precision.push_back(confusionMatrix[i][i]);
        // denominator
        float denominator = 0.0f;
        for (int j = 0; j < labelNum; j++)
        {
            denominator += confusionMatrix[j][i];
        }
        precision[i] /= denominator;
    }

    // Recall
    vector<float> recall;
    recall.reserve(labelNum);
    for (int i = 0; i < labelNum; i++)
    {
        // nominator
        recall.push_back(confusionMatrix[i][i]);
        // denominator
        float denominator = 0.0f;
        for (int j = 0; j < labelNum; j++)
        {
            denominator += confusionMatrix[i][j];
        }
        recall[i] /= denominator;
    }

    // print precision and recall
    for (int i = 0; i < labelNum; i++)
    {
        // print precision
        cout << i << ": " << "precision = " << precision[i] << ", " <<
            "recall = " << recall[i] << endl;
    }

    return confusionMatrix;
}
