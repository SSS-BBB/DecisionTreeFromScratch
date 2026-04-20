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