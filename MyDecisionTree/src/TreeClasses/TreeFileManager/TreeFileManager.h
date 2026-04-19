#pragma once
#include "../Node/Node.h"
#include <fstream>

using namespace std;

struct FileNodeInfo
{
	int id = -1;
	int columnTargetIndex = -1;
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

	bool loadNode(vector<FileNodeInfo>& fileNodeInfoList, int id);

public:
	TreeFileManager(string path);

	void saveTree(Node& root);

	Node loadTree();
};

