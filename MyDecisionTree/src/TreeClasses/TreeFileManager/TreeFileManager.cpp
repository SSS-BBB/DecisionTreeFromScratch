#include "TreeFileManager.h"
#include <iostream>

bool TreeFileManager::saveNode(ofstream& file, Node& node, int id)
{
	// check invalid node
	if (node.isInvalidNode())
	{
		cerr << "Node is invalid, unable to save this node." << endl;
		return false;
	}

	// save current node
	string line = "";
	line += "(";
	line += to_string(id) + "," + to_string(node.getTreshold()) + "," 
		+ to_string(node.getTargetColumn()) + ",";

	// check leaf node
	if (node.isLeafNode())
	{
		line += "-1,-1";
		line += ")";
		file << line << endl;
		return true;
	}

	// save left and right node
	int leftId = getNewId();
	int rightId = getNewId();
	line += to_string(leftId) + "," + to_string(rightId);
	line += ")";
	file << line << endl;

	bool leftStatus = saveNode(file, *node.getLeftNode(), leftId);
	bool rightStatus = saveNode(file, *node.getRightNode(), rightId);

	return leftStatus && rightStatus;
}

int TreeFileManager::getNewId()
{
	currentId++;
	return currentId;
}

unique_ptr<Node> TreeFileManager::setNode(const vector<FileNodeInfo>& fileNodeInfoList, int id)
{
	unique_ptr<Node> empty = make_unique<Node>(-1, -1);

	if (id < 0 || id >= fileNodeInfoList.size())
	{
		cerr << "Unable to set node with id " << id << endl;
		return empty;
	}

	// set node from node info using recursion
	cout << "Setting " << id << endl;
	
	FileNodeInfo currentNodeInfo = fileNodeInfoList[id];
	unique_ptr<Node> currentNode = make_unique<Node>(currentNodeInfo.targetColumnIndex, currentNodeInfo.treshold);
	if (currentNode->isInvalidNode())
	{
		cerr << "Invalid Node. Unable to set node with id " << id << endl;
		return empty;
	}
	else if (currentNodeInfo.targetColumnIndex < 0)
	{
		cout << "Leaf Node Reached at id " << id << endl;
		return currentNode;
	}

	// inner node
	currentNode->setLeftNode(setNode(fileNodeInfoList, currentNodeInfo.leftId));
	currentNode->setRightNode(setNode(fileNodeInfoList, currentNodeInfo.rightId));
	
	return currentNode;
}

void TreeFileManager::printNodeInfo(const vector<FileNodeInfo>& fileNodeInfoList)
{
	int id = 0;
	for (FileNodeInfo nodeInfo : fileNodeInfoList)
	{
		cout << id << "," << nodeInfo.treshold << "," << nodeInfo.targetColumnIndex << ","
			 << nodeInfo.leftId << "," << nodeInfo.rightId << endl;
		id++;
	}
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

	// save node count
	file << "Node Count" << endl;
	file << root.getChildrenCount() << endl;

	// start saving node
	file << "Node Info" << endl;
	int rootId = getNewId();
	bool saveStatus = saveNode(file, root, rootId);

	if (saveStatus)
	{
		// save successfully
		file << "END";
		cout << "Tree File has been saved successfully at " << path << endl;
	}
	else
	{
		cerr << "Something went wrong while saving node." << endl;
	}

	// reset id
	currentId = -1;
}

unique_ptr<Node> TreeFileManager::loadTree()
{
	unique_ptr<Node> empty = make_unique<Node>(-1, -1);

	// load node information from file
	ifstream file(path);
	string line = "";

	// check valid version
	getline(file, line);
	if (line != LOAD_FILE_VERSION)
	{
		cerr << "Invalid Load File Version." << endl;
		cerr << "Unable to load tree from " << path << endl;
		return empty;
	}

	// node count
	getline(file, line);
	if (line != "Node Count")
	{
		cerr << "Invalid Tree File. No Node Count Line." << endl;
		cerr << "Unable to load tree from " << path << endl;
		return empty;
	}
	getline(file, line);
	int nodeCount = stoi(line);

	if (nodeCount <= 0)
	{
		cerr << "Node Count <= 0. Unable to load tree from " << path << endl;
		return empty;
	}

	// start loading node information into a vector
	vector<FileNodeInfo> fileNodeInfoList;
	fileNodeInfoList.reserve(nodeCount);
	for (int i = 0; i < nodeCount; i++)
	{
		FileNodeInfo currentNodeInfo;
		fileNodeInfoList.emplace_back(currentNodeInfo);
	}

	getline(file, line);
	if (line != "Node Info")
	{
		cerr << "Invalid Tree File. No Node Info Line." << endl;
		cerr << "Unable to load tree from " << path << endl;
		return empty;
	}

	getline(file, line);
	while (line != "END" && !line.empty())
	{
		// (id,treshold,targetColumnIndex,leftID,rightID)

		// id
		int delimiterLocation = line.find(',');
		int nodeId = stoi(line.substr(1, delimiterLocation - 1)); // exclude (
		line = line.substr(delimiterLocation + 1);
		cout << "Reading " << nodeId << endl;

		// treshold
		delimiterLocation = line.find(',');
		float treshold = stof(line.substr(0, delimiterLocation));
		line = line.substr(delimiterLocation + 1);

		// targetColumnIndex
		delimiterLocation = line.find(',');
		int targetColumnIndex = stoi(line.substr(0, delimiterLocation));
		line = line.substr(delimiterLocation + 1);

		// leftID
		delimiterLocation = line.find(',');
		int leftId = stoi(line.substr(0, delimiterLocation));
		line = line.substr(delimiterLocation + 1);

		// rightID
		int rightId = stoi(line.substr(0, line.length() - 1));

		// edit information from the vector
		if (nodeId < 0 || nodeId >= nodeCount)
		{
			cerr << "Invalid Node Id. Unable to read node with the id " << nodeId << endl;
			getline(file, line);
			continue;
		}

		fileNodeInfoList[nodeId].treshold = treshold;
		fileNodeInfoList[nodeId].targetColumnIndex = targetColumnIndex;
		fileNodeInfoList[nodeId].leftId = leftId;
		fileNodeInfoList[nodeId].rightId = rightId;

		// next line
		getline(file, line);
	}

	// this is where real stuff happen
	return setNode(fileNodeInfoList, 0);
}
