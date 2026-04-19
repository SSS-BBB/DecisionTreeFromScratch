#pragma once
#include "../Node/Node.h"
#include <fstream>

using namespace std;

struct FileNodeInfo
{
	// id for the node is index position from the vector
	int targetColumnIndex = -1;
	int leftId, rightId = -1;
	float treshold = 0.0f;
};

class TreeFileManager
{
private:
	const string SAVE_FILE_VERSION = "TREE TEST";
	const string LOAD_FILE_VERSION = "TREE TEST";

	string path = "";

	int currentId = -1;

	bool saveNode(ofstream& file, Node& node, int id);

	int getNewId();

	unique_ptr<Node> setNode(const vector<FileNodeInfo>& fileNodeInfoList, int id);

	void printNodeInfo(const vector<FileNodeInfo>& fileNodeInfoList);

public:
	TreeFileManager(string path);

	void saveTree(Node& root);

	unique_ptr<Node> loadTree();
};

