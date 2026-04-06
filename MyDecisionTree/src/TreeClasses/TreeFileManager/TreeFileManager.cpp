#include "TreeFileManager.h"
#include <iostream>

bool TreeFileManager::saveNode(ofstream& file, Node& node, int id)
{
	// save current node
	string line = "";
	line += "(";
	line += to_string(id) + "," + to_string(node.getTreshold()) + "," 
		+ to_string(node.getTargetColumn()) + ",";

	int leftId = getNewId();
	int rightId = getNewId();
	line += to_string(leftId) + "," + to_string(rightId);
	line += ")";
	file << line;
	file << endl;

	// save left and right node

	return true;
}

int TreeFileManager::getNewId()
{
	currentId++;
	return currentId;
}

TreeFileManager::TreeFileManager(string path)
{
	// check invalid filepath
	int dotPos = path.find(".");
	if (dotPos < 0 || path.substr(dotPos + 1) != "tree")
	{
		cerr << "Invalid filepath " + path << endl;
		cerr << "filename must ends with .tree" << endl;
		return;
	}

	// filepath is valid
	this->path = path;
}

void TreeFileManager::saveTree(Node& root)
{
	ofstream file(path);
	file << SAVE_FILE_VERSION << endl;

	// start saving node
	int rootId = getNewId();
	bool saveStatus = saveNode(file, root, rootId);

	if (saveStatus)
	{
		// save successfully
		cout << "Tree File has been saved successfully at " << path << endl;
	}
	else
	{
		cerr << "Something went wrong while saving node." << endl;
	}
}
