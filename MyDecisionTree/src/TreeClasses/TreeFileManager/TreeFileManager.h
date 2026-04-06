#pragma once
#include "../Node/Node.h"
#include <fstream>

using namespace std;

class TreeFileManager
{
private:
	const string SAVE_FILE_VERSION = "TREE TEST";

	string path = "";

	int currentId = -1;

	bool saveNode(ofstream& file, Node& node, int id);

	int getNewId();

public:
	TreeFileManager(string path);

	void saveTree(Node& root);
	// unique_ptr<Node> loadTree();
};

