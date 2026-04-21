# Decision Tree From Scratch

## Read Data
Create a DataList object to store the data
```cpp
// DataList data(number of data, dataType)
vector<int> dataType = { 0, 1, 0, 0, 1, 0, 0, 1, 0 };
DataList data(3000, dataType);
```
dataType is a vector of int containing 0 or 1. each index position represents the type of data of each column. 0 represents categorical data (Ex. Gender, City) and 1 represents numerical data (Ex. Income, Price). In this case the first column is categorical, the second is numerical, the third is categorical, and so on.

***Note:*** the size of dataType array must match the size of column

Read CSV File
```cpp
// data.readCSV(filepath, variable type)
data.readCSV("data/Employee.csv", "sisiissic");
```
variable type is a string containing 'i', 'f', 's', 'c' which represents variable type of each column (each position represents each column). 'i' is integer, 'f' is float, 's' is string, 'c' is char. In this case the first column is string, the second is integer, the third is string, and so on.

***Note:*** the length of variableType string must match the size of column
```cpp
class DataList
{
    .
    .
    .
    unique_ptr<vector<vector<float>>> dataArray;
    .
    .
    .
}
```

Since DataList class only stores float data that means non-numerical columns have to be converted to numerical using ***DataConverter***.

Therefore after you've read the data you should save the converter file, so that when you have new data you want to predict. You can convert the data before predicting.
```cpp
// save converter
// dataList.saveConverterAt(indexColumn, filepath);
data.saveConverterAt(0, "saved file/data converters/converter0.cvtr");
// save all columns

// load converter
DataConverter loadedConverter0;
// loadedConverter0.load(filepath);
loadedConverter0.load("saved file/data converters/converter0.cvtr");
// newData.setDataConverter(indexColumn, DataConverter object);
newData.setDataConverter(0, loadedConverter0);
// load all columns
```

## Train Test Split
Create DataList Object xTrain xTest for feature data, and create vector of float for yTrain yTest for label data
```cpp
DataList xTrain;
DataList xTest;
vector<float> yTrain;
vector<float> yTest;
```
Now call train test split function from DataManager class.
```cpp
// trainTestSplit(data, test size, xTrain, xTest, yTrain, yTest)
DataManager::trainTestSplit(data, 0.2, xTrain, xTest, yTrain, yTest);
```
Split data will be store on variables you pass to the function.

***Note*** This function assumes your label is at the last column.

### Train Model (Create Tree)
If you don't know how many unique values are in your label. You can get it using this function.
```cpp
// getUniqueAtColumn(column of your label).size()
int labelNum = data.getUniqueAtColumn(8).size();
```

Create DecisionTreeCreator object
```cpp
// DecisionTreeCreator Constructor (address of feature data, address of label data, unique label length, maximum height (optional))
DecisionTreeCreator tree(&xTrain, &yTrain, labelNum);
```
***Note*** By default maximum height will be data size (number of rows) + 1

Call training function from the object.
```cpp
unique_ptr<Node> root = tree.createTree();
```
You'll get unique pointer of the root node as a return.

## Test Model
Create vector of float to store prediction results.
```cpp
// create array with the same size as xTest and fill all values with -1
// createFilledArray(size, filled value)
vector<float> yPred = Utils::createFilledArray(xTest.getRowNum(), -1);
```
Predict Data from root node.
```cpp
// predictAll(featureData, array to store results)
root->predictAll(xTest, yPred);
```
Prediction results will be stored in yPred.

Evaluate results with Confusion Matrix.
```cpp
// confusionMatrix(predicted values, true values, unique values length)
LabelEvaluator::confusionMatrix(yPred, yTest, labelNum);
```

![Confusion Matrix Table](/confusion%20matrix%20table.png)
This table will be shown (In the command prompt) as well as accuracy, precision, and recall.

## Save and Load Model
Create Tree File Manager class for saving and loading model and pass filepath.
```cpp
TreeFileManager treeFileManager("saved file/trees/employeeTree.tree");
```
Call saveTree function and pass the root node of the tree.
```cpp
treeFileManager.saveTree(*root);
```
Load tree by simply calling loadTree function.
```cpp
unique_ptr<Node> loadedRootNode = treeFileManager.loadTree();
```
you'll get unique pointer of the root node of the tree as a return.

***Note*** filepath has already been passed wehn creating TreeFileManager object, no need to pass filepath into loadTree function.