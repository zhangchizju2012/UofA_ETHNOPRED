#include "common.hpp"
#include "TreeNode.h"
#include "DecisionTree.h"
//#include <conio.h>
#include <iostream>
using namespace std;

TreeNode::TreeNode()
{
	//set the objects pointers to NULL in default constructor
	m_pYesBranch = NULL;
	m_pNoBranch = NULL;
	m_iNodeID = "0";
}

TreeNode::~TreeNode()
{

}

TreeNode::TreeNode(string nodeID, string newQorA, double nodeValue)
{
	//create a tree node with a specific node id and string
	m_iNodeID = nodeID;
	m_strQuestOrAns = newQorA;
	m_NodeValue = nodeValue;
	//ensure pointers are set to NULL in the new node
	m_pYesBranch = NULL;
	m_pNoBranch = NULL;
}


DecisionTree::DecisionTree()
{
	//set roots node to NULL upon tree creation
	m_pRootNode = NULL;
}

DecisionTree::~DecisionTree()
{
	//recursive call to delete tree nodes and root
	RemoveNode(m_pRootNode);
}

void DecisionTree::CreateRootNode(string nodeID, string newQorA, double nodeValue)
{
	//create the root node with a specific ID and string
	m_pRootNode = new TreeNode(nodeID, newQorA, nodeValue);
}

void DecisionTree::AddYesNode(string existingNodeID, string newNodeID, string newQorA, double newNodeValue)
{
	//if you dont have a root node you cant add another node
	if (m_pRootNode == NULL)
	{
		cout << "Error - no root node in AddYesNode()\n";
		return;
	}

	//otherwise query tree and add node
	if (SearchTreeAndAddYesNode(m_pRootNode, existingNodeID, newNodeID, newQorA, newNodeValue))
	{
		//cout << "Added 'yes' node";
		//cout << newNodeID;
		//cout << " onto 'yes' branch of node ";
		//cout << existingNodeID;
		//cout << endl;
	}
	else
	{
		cout << "Node ";
		cout << existingNodeID;
		cout << " not found \n";
	}
}

bool DecisionTree::SearchTreeAndAddYesNode(TreeNode* currentNode, string existingNodeID, string newNodeID, string newQorA, double newNodeValue)
{

	if (currentNode->m_iNodeID == existingNodeID)
	{
		//create node
		if (currentNode->m_pYesBranch == NULL)
		{
			currentNode->m_pYesBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		else
		{
			currentNode->m_pYesBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		return true;
	}
	else
	{
		//try yes branch if it exists
		if (currentNode->m_pYesBranch != NULL)
		{
			if (SearchTreeAndAddYesNode(currentNode->m_pYesBranch, existingNodeID, newNodeID, newQorA, newNodeValue))
			{
				return true;
			}
			else
			{
				//try no branch if it exists
				if (currentNode->m_pNoBranch != NULL)
				{
					return(SearchTreeAndAddYesNode(currentNode->m_pNoBranch, existingNodeID, newNodeID, newQorA, newNodeValue));
				}
				else
					return false;
			}
		}
		return false;
	}
}

void DecisionTree::AddNoNode(string existingNodeID, string newNodeID, string newQorA, double newNodeValue)
{
	if (m_pRootNode == NULL)
	{
		cout << "Error no root node in AddNoNode()\n";
		return;
	}
	if (SearchTreeAndAddNoNode(m_pRootNode, existingNodeID, newNodeID, newQorA, newNodeValue))
	{
		//cout << "Added 'no' node";
		//cout << newNodeID;
		//cout << " onto 'no' branch of node ";
		//cout << existingNodeID;
		//cout << endl;
	}
	else
	{
		cout << "Node ";
		cout << existingNodeID;
		cout << " not found \n";
	}

}

bool DecisionTree::SearchTreeAndAddNoNode(TreeNode* currentNode, string existingNodeID, string newNodeID, string newQorA, double newNodeValue)
{
	if (currentNode->m_iNodeID == existingNodeID)
	{
		if (currentNode->m_pNoBranch == NULL)
		{
			currentNode->m_pNoBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		else
		{
			currentNode->m_pNoBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		return true;
	}
	else
	{
		if (currentNode->m_pYesBranch != NULL)
		{
			if (SearchTreeAndAddNoNode(currentNode->m_pYesBranch, existingNodeID, newNodeID, newQorA, newNodeValue))
			{
				return true;
			}
			else
			{
				if (currentNode->m_pNoBranch != NULL)
				{
					return(SearchTreeAndAddNoNode(currentNode->m_pNoBranch, existingNodeID, newNodeID, newQorA, newNodeValue));
				}
				else
					return false;

			}
		}
		else
			return false;
	}
}

string DecisionTree::QueryBinaryTree(TreeNode* currentNode, std::vector<vector<string> > inputVector)
{
	if (currentNode->m_pYesBranch == NULL)
	{
		//if both the yes and no branch pointers are NULL
		//the tree is at a decision outcome state so output
		//the string
		if (currentNode->m_pNoBranch == NULL){
			//cout << currentNode->m_strQuestOrAns << endl;
			string a = currentNode->m_strQuestOrAns;
			return a;
		}
		else{
			cout << "Missing yes branch at " + currentNode->m_strQuestOrAns + " question\n";
			return "0";
		}
	}
	if (currentNode->m_pNoBranch == NULL)
	{
		cout << "Missing no branch at " + currentNode->m_strQuestOrAns + " question\n";
		return "0";
	}

	//otherwise default to asking the question at the currentNode
	string d;
	d = AskQuestion(currentNode, inputVector);
	return d;
}

string DecisionTree::Query(std::vector<vector<string> > inputVector)
{
	string result = QueryBinaryTree(m_pRootNode, inputVector);
	return result;
}

string DecisionTree::AskQuestion(TreeNode *node, std::vector<vector<string> > inputVector)
{
	//cout << node->m_strQuestOrAns + " (enter yes or no)\n";
	double answer;
	answer = findPosReturnValue(inputVector, (node->m_iNodeID));
	//string b = "3";
	//cout << inputVector[1][4];
	//cout << findPosReturnValue(inputVector, b);
	if (answer == 0){
		string e = "No Value";
		return e;
	}
	else {
		if (answer < (node->m_NodeValue)){
			string c = QueryBinaryTree(node->m_pYesBranch, inputVector);
			return c;
		}
		else if (answer >(node->m_NodeValue)){
			string b = QueryBinaryTree(node->m_pNoBranch, inputVector);
			return b;
		}
		else//看起来好像没用了现在
		{
			cout << "Error please answer yes or no\n";
			AskQuestion(node, inputVector);
		}
	}

}

void DecisionTree::Output()
{
	OutputBinaryTree("1", m_pRootNode);
}

void DecisionTree::OutputBinaryTree(string tag, TreeNode* currentNode)
{
	if (currentNode == NULL)
		return;

	//cout << "[" + tag + "] node id = ";

	//cout << currentNode->m_iNodeID;
	//cout << ", question/answer = ";
	//cout << currentNode->m_strQuestOrAns;
	//cout << endl;

	// Go down yes branch
	OutputBinaryTree(tag + ".1", currentNode->m_pYesBranch);
	// Go down no branch
	OutputBinaryTree(tag + ".2", currentNode->m_pNoBranch);

}

void DecisionTree::RemoveNode(TreeNode *node)
{
	if (node != NULL)
	{
		if (node->m_pYesBranch != NULL)
			RemoveNode(node->m_pYesBranch);

		if (node->m_pNoBranch != NULL)
			RemoveNode(node->m_pNoBranch);

		//cout << "deleting node " << node->m_iNodeID << endl;
		delete node;
		node = NULL;
	}
}

double DecisionTree::findPosReturnValue(std::vector<vector<string> > inputVector, string a){
	for (int i = 0; i <= (inputVector[0].size()-1); i++){
		if (inputVector[0][i] == a){
			if (inputVector[1][i] == "A_A") return 1;
			else if (inputVector[1][i] == "A_B") return 2;
			else if (inputVector[1][i] == "B_B") return 3;
			else return 0;
		}

	}
	return 0;
}

/* test vector
std::vector<vector<int> > newVector(){
  std::vector<vector<int> > myvector;
  myvector.resize(2);
  for(int i=1;i<=10;i++) myvector[0].push_back(i);
  for(int j=3;j<=12;j++) myvector[0].push_back(j);
  return myvector;
}*/
/*
int findPosReturnValue(std::vector<vector<string> > inputVector, string a){
  for(int i=0; i<=(inputVector[0].size()); i++){
    if(inputVector[0][i] == a){
      if(inputVector[1][i] == "AA") return 111;
      else if(inputVector[1][i] == "Aa") return 222;
      else if(inputVector[1][i] == "aa") return 333;
    }

  }
  //return 20;
}
*/

//string readCSVFile( const char * fileName){
std::vector<vector<string> > readCSVFile(const char * fileName){
	std::vector<vector<string> > myvector;
	myvector.resize(2);
	ifstream file;
	stringstream ss;
	string str;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		file.open(fileName);
		ss << file.rdbuf();
		str = ss.str();
		file.close();
	}
	catch (ifstream::failure e) {
		std::cerr << "Exception opening file\n" << e.what() << endl;
		exit(1);
	}
	//std::cout << str;
	string delimiter = ",";
	string linebreak = "\n";
	string line1;
	string line2;
	string lineID;
	string lineInfo;
	/*
	size_t breakPos = str.find(linebreak);
	lineID = str.substr(0, breakPos);
	lineInfo = str.erase(0, breakPos + linebreak.length());
	std::cout << (breakPos == std::string::npos) << endl;
	cout << breakPos << endl;
	cout << std::string::npos << endl;
	cout << str;
	str.erase(0, breakPos + linebreak.length());
	cout << str;
	breakPos = str.find(linebreak);
	cout << breakPos << endl;
	cout << std::string::npos << endl;
	return lineID;
	*/

	size_t breakPos = str.find(linebreak);
	line1 = str.substr(0, breakPos + linebreak.length());
	str = str.erase(0, breakPos + linebreak.length());
	breakPos = str.find(linebreak);
	line2 = str.substr(0, breakPos + linebreak.length());
	//std::cout << line1;
	//std::cout << line2;
	std::vector<size_t>posvector1;
	posvector1.push_back(-1);
	std::vector<size_t>posvector2;
	posvector2.push_back(-1);
	for (size_t i = 0; i < line1.length(); ++i)
	{
		//std::cout << str.at(i);
		if (line1.at(i) == ','){
				posvector1.push_back(i);
			}
	}
	posvector1.push_back(line1.find(linebreak)-linebreak.length());
	for (int j = 0; j < (posvector1.size()-2); j++){
		myvector[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] -1));
	}

	for (size_t i = 0; i < line2.length(); ++i)
	{
		//std::cout << str.at(i);
		if (line2.at(i) == ','){
			posvector2.push_back(i);
		}
	}
	posvector2.push_back(line2.find(linebreak) - linebreak.length());
	for (int j = 0; j < (posvector2.size() - 2); j++){
		myvector[1].push_back(line2.substr(posvector2[j] + delimiter.length(), posvector2[j + 1] - posvector2[j] - 1));
	}
	/*
	breakPos = line1.find(linebreak);
	//cout << breakPos << endl;
	//cout << std::string::npos << endl;

	size_t commaPos;

	commaPos = line1.find(delimiter);
	lineID = line1.substr(0, commaPos);
	//cout << lineID << endl;
	myvector[0].push_back(lineID);

	while (breakPos > 11){
		line1 = line1.erase(0, commaPos + delimiter.length());
		breakPos = line1.find(linebreak);
		//cout << breakPos << endl;
		//cout << std::string::npos << endl;
		commaPos = line1.find(delimiter);
		if (commaPos > 100000)
			commaPos = breakPos;
		lineID = line1.substr(0, commaPos);
		//cout << lineID << endl;
		myvector[0].push_back(lineID);
	}

	breakPos = line2.find(linebreak);
	commaPos = line2.find(delimiter);
	lineID = line2.substr(0, commaPos);
	//cout << lineID << endl;
	myvector[1].push_back(lineID);

	while (breakPos > 5){
		line2 = line2.erase(0, commaPos + delimiter.length());
		breakPos = line2.find(linebreak);
		//cout << breakPos << endl;
		//cout << std::string::npos << endl;
		commaPos = line2.find(delimiter);
		if (commaPos > 100000)
			commaPos = breakPos;
		lineID = line2.substr(0, commaPos);
		//cout << lineID << endl;
		myvector[1].push_back(lineID);
	}
*/
	return myvector;
}

void calNumReturnResult(vector<string> result){
	int numEUR = 0;
	int numCHN = 0;
	int numAMR = 0;
	int numJPN = 0;
	int numNoValue = 0;
	for (int i = 0; i <= (result.size() - 1); i++){
		if (result[i] == "1"){ numEUR++; }
		else if (result[i] == "2"){ numCHN++; }
		else if (result[i] == "3"){ numAMR++; }
		else if (result[i] == "JPN"){ numJPN++; }
		else if (result[i] == "No Value"){ numNoValue++; }
	}
	cout << "EUR: " << numEUR << endl;
	cout << "CHN: " << numCHN << endl;
	cout << "AMR: " << numAMR << endl;
	cout << "JPN: " << numJPN << endl;
	cout << "NoValue: " << numNoValue << endl;
	if ((numEUR >= numCHN) && (numEUR >= numAMR) && (numEUR >= numJPN))
		cout << "This is EUR." << endl;
	if ((numEUR <= numCHN) && (numCHN >= numAMR) && (numCHN >= numJPN))
		cout << "This is CHN." << endl;
	if ((numAMR >= numCHN) && (numEUR <= numAMR) && (numAMR >= numJPN))
		cout << "This is AMR." << endl;
	if ((numJPN >= numCHN) && (numJPN >= numAMR) && (numEUR <= numJPN))
		cout << "This is JPN." << endl;

}

int main(int argc, char *argv[]) {
  int c;
  char * inputFile = NULL;
  char * output_file = NULL;
  while ((c = getopt (argc, argv, "i:o:")) != -1){
    switch (c)
      {

      case 'i':
    //          fprintf(stderr,"[%s]-> ",optarg);
        if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
            fprintf (stderr,
               "Found illegal or NULL parameter for the option -i.\n");
            return 1;
        }

        inputFile = optarg;

        break;

      case 'o':
    //          fprintf(stderr,"[%s]-> ",optarg);
        if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
            fprintf (stderr,
               "Found illegal or NULL parameter for the option -o.\n");
            return 1;
        }

        output_file = optarg;

        break;

    case '?':
      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      return 1;
    }
  }
  if (inputFile != NULL){
    std::cout << inputFile << std::endl;
  }

    // insert code here...
/*
    std::ifstream theFile(inputFile);
    int id;
    std::string name;
    double money;
    while (theFile >> id >> name >> money) {
        cout << id << ", " << name << ", " << money << endl;
    }
    std::cout << "Hello, World!\n";*/

    //std::vector<vector<int> > my = newVector();
    std::vector<vector<string> > my = readCSVFile(inputFile);
    //for(int i=1;i<=5;i++) myvector.push_back(i);
		/*
    for(std::vector<string>::iterator it = my[0].begin();it != my[0].end();it++){std::cout << " " << *it;}
    for(std::vector<string>::iterator it = my[1].begin();it != my[1].end();it++){std::cout << " " << *it;}
    std::cout << endl;
    cout << my[1][1];
    cout << endl;
    cout << (my[1][1] == "8");
    cout << endl;
    cout << my[0].size();
    cout << endl;
    string b = "4";
    //cout << findPosReturnValue(my,b);
    cout << endl;
    //std::cout << readCSVFile(inputFile);
    //std::cout << name;
		*/

		std::vector<string> myresult;
	//create he new decision tree object
	DecisionTree* newTree1 = new DecisionTree();
	//add the required root node
	newTree1->CreateRootNode("rs6437783", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree1->AddYesNode("rs6437783", "rs4835141", "Q", 1.5);
	newTree1->AddNoNode("rs6437783", "rs735480", "Q", 1.5);
	newTree1->AddYesNode("rs4835141", "x", "2", 5);
	newTree1->AddNoNode("rs4835141", "x", "3", 5);
	newTree1->AddYesNode("rs735480", "x", "3", 5);
	newTree1->AddNoNode("rs735480", "x", "1", 5);
	//output the created tree
	newTree1->Output();
	//query the tree
	string result1;
	result1 = newTree1->Query(my);
	cout << result1 << endl;
	delete newTree1;
	myresult.push_back(result1);

	DecisionTree* newTree2 = new DecisionTree();
	//add the required root node
	newTree2->CreateRootNode("rs35389", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree2->AddYesNode("rs35389", "rs4787645", "Q", 1.5);
	newTree2->AddNoNode("rs35389", "rs1726254", "Q", 2.5);
	newTree2->AddYesNode("rs4787645", "rs4847428", "Q", 1.5);
	newTree2->AddNoNode("rs4787645", "x", "3", 5);
	newTree2->AddYesNode("rs1726254", "x", "1", 5);
	newTree2->AddNoNode("rs1726254", "x", "2", 5);
	newTree2->AddYesNode("rs4847428", "x", "1", 5);
	newTree2->AddNoNode("rs4847428", "x", "2", 5);
	//output the created tree
	newTree2->Output();
	//query the tree
	string result2;
	result2 = newTree2->Query(my);
	cout << result2 << endl;
	delete newTree2;
	myresult.push_back(result2);

	DecisionTree* newTree3 = new DecisionTree();
	//add the required root node
	newTree3->CreateRootNode("rs1986420", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree3->AddYesNode("rs1986420", "rs12135904", "Q", 2.5);
	newTree3->AddNoNode("rs1986420", "x", "1", 5);
	newTree3->AddYesNode("rs12135904", "rs1679012", "CHN", 1.5);
	newTree3->AddNoNode("rs12135904", "x", "3", 5);
	newTree3->AddYesNode("rs1679012", "x", "2", 5);
	newTree3->AddNoNode("rs1679012", "x", "1", 5);
	//output the created tree
	newTree3->Output();
	//query the tree
	string result3;
	result3 = newTree3->Query(my);
	cout << result3 << endl;
	delete newTree3;
	myresult.push_back(result3);

	DecisionTree* newTree4 = new DecisionTree();
	//add the required root node
	newTree4->CreateRootNode("rs2675345", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree4->AddYesNode("rs2675345", "rs9931378", "Q", 2.5);
	newTree4->AddNoNode("rs2675345", "rs6546753", "Q", 2.5);
	newTree4->AddYesNode("rs9931378", "x", "1", 5);
	newTree4->AddNoNode("rs9931378", "x", "3", 5);
	newTree4->AddYesNode("rs6546753", "x", "3", 5);
	newTree4->AddNoNode("rs6546753", "x", "2", 5);
	//output the created tree
	newTree4->Output();
	//query the tree
	string result4;
	result4 = newTree4->Query(my);
	cout << result4 << endl;
	delete newTree4;
	myresult.push_back(result4);

	DecisionTree* newTree5 = new DecisionTree();
	//add the required root node
	newTree5->CreateRootNode("rs2700392", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree5->AddYesNode("rs2700392", "rs1924381", "Q", 1.5);
	newTree5->AddNoNode("rs2700392", "rs747094", "Q", 2.5);
	newTree5->AddYesNode("rs1924381", "x", "2", 5);
	newTree5->AddNoNode("rs1924381", "x", "1", 5);
	newTree5->AddYesNode("rs747094", "x", "3", 5);
	newTree5->AddNoNode("rs747094", "rs17671597", "Q", 1.5);
	newTree5->AddYesNode("rs17671597", "x", "2", 5);
	newTree5->AddNoNode("rs17671597", "x", "1", 5);
	//output the created tree
	newTree5->Output();
	//query the tree
	string result5;
	result5 = newTree5->Query(my);
	cout << result5 << endl;
	delete newTree5;
	myresult.push_back(result5);

	DecisionTree* newTree6 = new DecisionTree();
	//add the required root node
	newTree6->CreateRootNode("rs260700", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree6->AddYesNode("rs260700", "rs6451268", "Q", 2.5);
	newTree6->AddNoNode("rs260700", "rs12204275", "Q", 1.5);
	newTree6->AddYesNode("rs6451268", "rs987435", "Q", 1.5);
	newTree6->AddNoNode("rs6451268", "rs16953500", "Q", 2.5);
	newTree6->AddYesNode("rs12204275", "x", "2", 5);
	newTree6->AddNoNode("rs12204275", "x", "3", 5);
	newTree6->AddYesNode("rs987435", "x", "3", 5);
	newTree6->AddNoNode("rs987435", "rs4242682", "Q", 2.5);
	newTree6->AddYesNode("rs16953500", "x", "1", 5);
	newTree6->AddNoNode("rs16953500", "x", "2", 5);
	newTree6->AddYesNode("rs4242682", "x", "2", 5);
	newTree6->AddNoNode("rs4242682", "x", "1", 5);
	//output the created tree
	newTree6->Output();
	//query the tree
	string result6;
	result6 = newTree6->Query(my);
	cout << result6 << endl;
	delete newTree6;
	myresult.push_back(result6);

	DecisionTree* newTree7 = new DecisionTree();
	//add the required root node
	newTree7->CreateRootNode("rs260699", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree7->AddYesNode("rs260699", "rs11130791", "Q", 2.5);
	newTree7->AddNoNode("rs260699", "rs6897135", "Q", 1.5);
	newTree7->AddYesNode("rs11130791", "x", "2", 5);
	newTree7->AddNoNode("rs11130791", "x", "3", 5);
	newTree7->AddYesNode("rs6897135", "x", "1", 5);
	newTree7->AddNoNode("rs6897135", "rs1588040", "Q", 1.5);
	newTree7->AddYesNode("rs1588040", "x", "3", 5);
	newTree7->AddNoNode("rs1588040", "rs7974633", "Q", 1.5);
	newTree7->AddYesNode("rs7974633", "x", "1", 5);
	newTree7->AddNoNode("rs7974633", "x", "2", 5);
	//output the created tree
	newTree7->Output();
	//query the tree
	string result7;
	result7 = newTree7->Query(my);
	cout << result7 << endl;
	delete newTree7;
	myresult.push_back(result7);

	DecisionTree* newTree8 = new DecisionTree();
	//add the required root node
	newTree8->CreateRootNode("rs260705", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree8->AddYesNode("rs260705", "rs11649653", "Q", 1.5);
	newTree8->AddNoNode("rs260705", "rs2433354", "Q", 2.5);
	newTree8->AddYesNode("rs11649653", "x", "2", 5);
	newTree8->AddNoNode("rs11649653", "x", "3", 5);
	newTree8->AddYesNode("rs2433354", "rs2204738", "Q", 2.5);
	newTree8->AddNoNode("rs2433354", "rs4791868", "Q", 1.5);
	newTree8->AddYesNode("rs2204738", "x", "2", 5);
	newTree8->AddNoNode("rs2204738", "x", "3", 5);
	newTree8->AddYesNode("rs4791868", "x", "2", 5);
	newTree8->AddNoNode("rs4791868", "x", "1", 5);
	//output the created tree
	newTree8->Output();
	//query the tree
	string result8;
	result8 = newTree8->Query(my);
	cout << result8 << endl;
	delete newTree8;
	myresult.push_back(result8);

	DecisionTree* newTree9 = new DecisionTree();
	//add the required root node
	newTree9->CreateRootNode("rs282162", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree9->AddYesNode("rs282162", "rs4825", "Q", 2.5);
	newTree9->AddNoNode("rs282162", "rs864386", "Q", 1.5);
	newTree9->AddYesNode("rs4825", "rs1814538", "Q", 1.5);
	newTree9->AddNoNode("rs4825", "rs10187056", "Q", 1.5);
	newTree9->AddYesNode("rs864386", "x", "3", 5);
	newTree9->AddNoNode("rs864386", "x", "1", 5);
	newTree9->AddYesNode("rs1814538", "x", "2", 5);
	newTree9->AddNoNode("rs1814538", "x", "1", 5);
	newTree9->AddYesNode("rs10187056", "x", "3", 5);
	newTree9->AddNoNode("rs10187056", "x", "2", 5);
	//output the created tree
	newTree9->Output();
	//query the tree
	string result9;
	result9 = newTree9->Query(my);
	cout << result9 << endl;
	delete newTree9;
	myresult.push_back(result9);

	DecisionTree* newTree10 = new DecisionTree();
	//add the required root node
	newTree10->CreateRootNode("rs2002739", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree10->AddYesNode("rs2002739", "rs12120383", "Q", 1.5);
	newTree10->AddNoNode("rs2002739", "rs2000743", "Q", 2.5);
	newTree10->AddYesNode("rs12120383", "rs7111521", "Q", 1.5);
	newTree10->AddNoNode("rs12120383", "rs12921822", "Q", 1.5);
	newTree10->AddYesNode("rs2000743", "x", "3", 5);
	newTree10->AddNoNode("rs2000743", "x", "1", 5);
	newTree10->AddYesNode("rs7111521", "x", "2", 5);
	newTree10->AddNoNode("rs7111521", "x", "1", 5);
	newTree10->AddYesNode("rs12921822", "x", "3", 5);
	newTree10->AddNoNode("rs12921822", "x", "2", 5);
	//output the created tree
	newTree10->Output();
	//query the tree
	string result10;
	result10 = newTree10->Query(my);
	cout << result10 << endl;
	delete newTree10;
	myresult.push_back(result10);

	DecisionTree* newTree11 = new DecisionTree();
	//add the required root node
	newTree11->CreateRootNode("rs4722760", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree11->AddYesNode("rs4722760", "rs13086858", "Q", 2.5);
	newTree11->AddNoNode("rs4722760", "rs1320385", "Q", 2.5);
	newTree11->AddYesNode("rs13086858", "rs7676617", "Q", 1.5);
	newTree11->AddNoNode("rs13086858", "x", "3", 5);
	newTree11->AddYesNode("rs1320385", "rs7215008", "Q", 1.5);
	newTree11->AddNoNode("rs1320385", "rs6698919", "Q", 2.5);
	newTree11->AddYesNode("rs7676617", "x", "1", 5);
	newTree11->AddNoNode("rs7676617", "x", "2", 5);
	newTree11->AddYesNode("rs7215008", "x", "3", 5);
	newTree11->AddNoNode("rs7215008", "x", "2", 5);
	newTree11->AddYesNode("rs6698919", "x", "1", 5);
	newTree11->AddNoNode("rs6698919", "x", "2", 5);
	//output the created tree
	newTree11->Output();
	//query the tree
	string result11;
	result11 = newTree11->Query(my);
	cout << result11 << endl;
	delete newTree11;
	myresult.push_back(result11);

	DecisionTree* newTree12 = new DecisionTree();
	//add the required root node
	newTree12->CreateRootNode("rs2907599", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree12->AddYesNode("rs2907599", "rs12036675", "Q", 2.5);
	newTree12->AddNoNode("rs2907599", "rs10814993", "Q", 1.5);
	newTree12->AddYesNode("rs12036675", "x", "2", 5);
	newTree12->AddNoNode("rs12036675", "x", "1", 5);
	newTree12->AddYesNode("rs10814993", "rs2463383", "Q", 1.5);
	newTree12->AddNoNode("rs10814993", "rs1484213", "Q", 2.5);
	newTree12->AddYesNode("rs2463383", "x", "2", 5);
	newTree12->AddNoNode("rs2463383", "x", "3", 5);
	newTree12->AddYesNode("rs1484213", "x", "2", 5);
	newTree12->AddNoNode("rs1484213", "x", "1", 5);
	//output the created tree
	newTree12->Output();
	//query the tree
	string result12;
	result12 = newTree12->Query(my);
	cout << result12 << endl;
	delete newTree12;
	myresult.push_back(result12);

	DecisionTree* newTree13 = new DecisionTree();
	//add the required root node
	newTree13->CreateRootNode("rs2893312", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree13->AddYesNode("rs2893312", "rs868622", "Q", 1.5);
	newTree13->AddNoNode("rs2893312", "rs12062528", "Q", 2.5);
	newTree13->AddYesNode("rs868622", "x", "3", 5);
	newTree13->AddNoNode("rs868622", "rs2578669", "Q", 2.5);
	newTree13->AddYesNode("rs12062528", "rs519381", "Q", 1.5);
	newTree13->AddNoNode("rs12062528", "rs9595066", "Q", 2.5);
	newTree13->AddYesNode("rs2578669", "x", "2", 5);
	newTree13->AddNoNode("rs2578669", "x", "1", 5);
	newTree13->AddYesNode("rs519381", "x", "3", 5);
	newTree13->AddNoNode("rs519381", "x", "2", 5);
	newTree13->AddYesNode("rs9595066", "x", "1", 5);
	newTree13->AddNoNode("rs9595066", "x", "2", 5);
	//output the created tree
	newTree13->Output();
	//query the tree
	string result13;
	result13 = newTree13->Query(my);
	cout << result13 << endl;
	delete newTree13;
	myresult.push_back(result13);

	DecisionTree* newTree14 = new DecisionTree();
	//add the required root node
	newTree14->CreateRootNode("rs590616", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree14->AddYesNode("rs590616", "rs2605419", "Q", 2.5);
	newTree14->AddNoNode("rs590616", "rs12895262", "Q", 1.5);
	newTree14->AddYesNode("rs2605419", "x", "3", 5);
	newTree14->AddNoNode("rs2605419", "x", "1", 5);
	newTree14->AddYesNode("rs12895262", "x", "1", 5);
	newTree14->AddNoNode("rs12895262", "rs1909338", "Q", 2.5);
	newTree14->AddYesNode("rs1909338", "rs10758940", "Q", 1.5);
	newTree14->AddNoNode("rs1909338", "x", "3", 5);
	newTree14->AddYesNode("rs10758940", "x", "1", 5);
	newTree14->AddNoNode("rs10758940", "x", "2", 5);
	//output the created tree
	newTree14->Output();
	//query the tree
	string result14;
	result14 = newTree14->Query(my);
	cout << result14 << endl;
	delete newTree14;
	myresult.push_back(result14);

	DecisionTree* newTree15 = new DecisionTree();
	//add the required root node
	newTree15->CreateRootNode("rs533571", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree15->AddYesNode("rs533571", "rs6468344", "Q", 2.5);
	newTree15->AddNoNode("rs533571", "rs4577845", "Q", 2.5);
	newTree15->AddYesNode("rs6468344", "rs11098948", "Q", 1.5);
	newTree15->AddNoNode("rs6468344", "rs2029623", "Q", 1.5);
	newTree15->AddYesNode("rs4577845", "x", "3", 5);
	newTree15->AddNoNode("rs4577845", "x", "1", 5);
	newTree15->AddYesNode("rs11098948", "x", "3", 5);
	newTree15->AddNoNode("rs11098948", "x", "2", 5);
	newTree15->AddYesNode("rs2029623", "x", "2", 5);
	newTree15->AddNoNode("rs2029623", "x", "1", 5);
	//output the created tree
	newTree15->Output();
	//query the tree
	string result15;
	result15 = newTree15->Query(my);
	cout << result15 << endl;
	delete newTree15;
	myresult.push_back(result15);

	DecisionTree* newTree16 = new DecisionTree();
	//add the required root node
	newTree16->CreateRootNode("rs260709", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree16->AddYesNode("rs260709", "rs11691947", "Q", 2.5);
	newTree16->AddNoNode("rs260709", "rs1437724", "Q", 1.5);
	newTree16->AddYesNode("rs11691947", "rs7158108", "3", 2.5);
	newTree16->AddNoNode("rs11691947", "rs4705115", "1", 1.5);
	newTree16->AddYesNode("rs1437724", "x", "2", 5);
	newTree16->AddNoNode("rs1437724", "x", "3", 5);
	newTree16->AddYesNode("rs7158108", "x", "1", 5);
	newTree16->AddNoNode("rs7158108", "x", "2", 5);
	newTree16->AddYesNode("rs4705115", "x", "3", 5);
	newTree16->AddNoNode("rs4705115", "rs2214965", "Q", 1.5);
	newTree16->AddYesNode("rs2214965", "x", "1", 5);
	newTree16->AddNoNode("rs2214965", "x", "2", 5);
	//output the created tree
	newTree16->Output();
	//query the tree
	string result16;
	result16 = newTree16->Query(my);
	cout << result16 << endl;
	delete newTree16;
	myresult.push_back(result16);

	DecisionTree* newTree17 = new DecisionTree();
	//add the required root node
	newTree17->CreateRootNode("rs6534999", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree17->AddYesNode("rs6534999", "rs7689609", "Q", 2.5);
	newTree17->AddNoNode("rs6534999", "rs12542990", "Q", 2.5);
	newTree17->AddYesNode("rs7689609", "x", "1", 5);
	newTree17->AddNoNode("rs7689609", "rs1450428", "Q", 1.5);
	newTree17->AddYesNode("rs12542990", "rs7551132", "Q", 1.5);
	newTree17->AddNoNode("rs12542990", "x", "3", 5);
	newTree17->AddYesNode("rs1450428", "x", "3", 5);
	newTree17->AddNoNode("rs1450428", "x", "2", 5);
	newTree17->AddYesNode("rs7551132", "x", "1", 5);
	newTree17->AddNoNode("rs7551132", "x", "2", 5);
	//output the created tree
	newTree17->Output();
	//query the tree
	string result17;
	result17 = newTree17->Query(my);
	cout << result17 << endl;
	delete newTree17;
	myresult.push_back(result17);

	DecisionTree* newTree18 = new DecisionTree();
	//add the required root node
	newTree18->CreateRootNode("rs4832501", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree18->AddYesNode("rs4832501", "rs2200402", "Q", 2.5);
	newTree18->AddNoNode("rs4832501", "rs931410", "Q", 1.5);
	newTree18->AddYesNode("rs2200402", "rs2546001", "Q", 1.5);
	newTree18->AddNoNode("rs2200402", "rs8091955", "Q", 2.5);
	newTree18->AddYesNode("rs931410", "rs1099968", "Q", 2.5);
	newTree18->AddNoNode("rs931410", "x", "1", 5);
	newTree18->AddYesNode("rs2546001", "x", "2", 5);
	newTree18->AddNoNode("rs2546001", "x", "1", 5);
	newTree18->AddYesNode("rs8091955", "x", "3", 5);
	newTree18->AddNoNode("rs8091955", "x", "2", 5);
	newTree18->AddYesNode("rs1099968", "rs7921545", "Q", 2.5);
	newTree18->AddNoNode("rs1099968", "x", "1", 5);
	newTree18->AddYesNode("rs7921545", "x", "2", 5);
	newTree18->AddNoNode("rs7921545", "x", "3", 5);
	//output the created tree
	newTree18->Output();
	//query the tree
	string result18;
	result18 = newTree18->Query(my);
	cout << result18 << endl;
	delete newTree18;
	myresult.push_back(result18);

	DecisionTree* newTree19 = new DecisionTree();
	//add the required root node
	newTree19->CreateRootNode("rs1437787", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree19->AddYesNode("rs1437787", "rs11170991", "Q", 2.5);
	newTree19->AddNoNode("rs1437787", "rs1805972", "Q", 1.5);
	newTree19->AddYesNode("rs11170991", "x", "3", 5);
	newTree19->AddNoNode("rs11170991", "x", "1", 1.5);
	newTree19->AddYesNode("rs1805972", "rs2422098", "Q", 1.5);
	newTree19->AddNoNode("rs1805972", "rs9821525", "Q", 1.5);
	newTree19->AddYesNode("rs2422098", "x", "2", 5);
	newTree19->AddNoNode("rs2422098", "x", "1", 5);
	newTree19->AddYesNode("rs9821525", "x", "3", 5);
	newTree19->AddNoNode("rs9821525", "rs12511245", "Q", 2.5);
	newTree19->AddYesNode("rs12511245", "x", "2", 5);
	newTree19->AddNoNode("rs12511245", "x", "1", 5);
	//output the created tree
	newTree19->Output();
	//query the tree
	string result19;
	result19 = newTree19->Query(my);
	cout << result19 << endl;
	delete newTree19;
	myresult.push_back(result19);

	DecisionTree* newTree20 = new DecisionTree();
	//add the required root node
	newTree20->CreateRootNode("rs4749305", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree20->AddYesNode("rs4749305", "rs2631899", "Q", 2.5);
	newTree20->AddNoNode("rs4749305", "rs7956796", "Q", 2.5);
	newTree20->AddYesNode("rs2631899", "x", "3", 5);
	newTree20->AddNoNode("rs2631899", "x", "2", 5);
	newTree20->AddYesNode("rs7956796", "x", "1", 5);
	newTree20->AddNoNode("rs7956796", "rs4877791", "Q", 2.5);
	newTree20->AddYesNode("rs4877791", "rs1932366", "Q", 1.5);
	newTree20->AddNoNode("rs4877791", "x", "3", 5);
	newTree20->AddYesNode("rs1932366", "x", "1", 5);
	newTree20->AddNoNode("rs1932366", "x", "2", 5);
	//output the created tree
	newTree20->Output();
	//query the tree
	string result20;
	result20 = newTree20->Query(my);
	cout << result20 << endl;
	delete newTree20;
	myresult.push_back(result20);

	DecisionTree* newTree21 = new DecisionTree();
	//add the required root node
	newTree21->CreateRootNode("rs542405", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree21->AddYesNode("rs542405", "rs6977118", "Q", 1.5);
	newTree21->AddNoNode("rs542405", "rs2305858", "Q", 2.5);
	newTree21->AddYesNode("rs6977118", "rs11563620", "Q", 1.5);
	newTree21->AddNoNode("rs6977118", "x", "3", 5);
	newTree21->AddYesNode("rs2305858", "rs2040704", "Q", 1.5);
	newTree21->AddNoNode("rs2305858", "x", "1", 5);
	newTree21->AddYesNode("rs11563620", "x", "2", 5);
	newTree21->AddNoNode("rs11563620", "x", "1", 5);
	newTree21->AddYesNode("rs2040704", "x", "3", 5);
	newTree21->AddNoNode("rs2040704", "x", "2", 5);
	//output the created tree
	newTree21->Output();
	//query the tree
	string result21;
	result21 = newTree21->Query(my);
	cout << result21 << endl;
	delete newTree21;
	myresult.push_back(result21);

	DecisionTree* newTree22 = new DecisionTree();
	//add the required root node
	newTree22->CreateRootNode("rs738276", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree22->AddYesNode("rs738276", "rs4615248", "Q", 2.5);
	newTree22->AddNoNode("rs738276", "rs7983489", "Q", 1.5);
	newTree22->AddYesNode("rs4615248", "rs12681671", "Q", 1.5);
	newTree22->AddNoNode("rs4615248", "x", "3", 5);
	newTree22->AddYesNode("rs7983489", "rs6035761", "Q", 1.5);
	newTree22->AddNoNode("rs7983489", "rs2324520", "Q", 2.5);
	newTree22->AddYesNode("rs12681671", "x", "2", 5);
	newTree22->AddNoNode("rs12681671", "x", "1", 5);
	newTree22->AddYesNode("rs6035761", "x", "2", 5);
	newTree22->AddNoNode("rs6035761", "x", "1", 5);
	newTree22->AddYesNode("rs2324520", "rs3181372", "Q", 2.5);
	newTree22->AddNoNode("rs2324520", "x", "3", 5);
	newTree22->AddYesNode("rs3181372", "x", "2", 5);
	newTree22->AddNoNode("rs3181372", "x", "1", 5);
	//output the created tree
	newTree22->Output();
	//query the tree
	string result22;
	result22 = newTree22->Query(my);
	cout << result22 << endl;
	delete newTree22;
	myresult.push_back(result22);

	DecisionTree* newTree23 = new DecisionTree();
	//add the required root node
	newTree23->CreateRootNode("rs943773", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree23->AddYesNode("rs943773", "rs4789182", "Q", 1.5);
	newTree23->AddNoNode("rs943773", "rs702032", "Q", 2.5);
	newTree23->AddYesNode("rs4789182", "x", "2", 5);
	newTree23->AddNoNode("rs4789182", "x", "3", 5);
	newTree23->AddYesNode("rs702032", "rs6926482", "Q", 1.5);
	newTree23->AddNoNode("rs702032", "x", "1", 5);
	newTree23->AddYesNode("rs6926482", "x", "3", 5);
	newTree23->AddNoNode("rs6926482", "rs2490385", "Q", 1.5);
	newTree23->AddYesNode("rs2490385", "x", "1", 5);
	newTree23->AddNoNode("rs2490385", "x", "2", 5);
	//output the created tree
	newTree23->Output();
	//query the tree
	string result23;
	result23 = newTree23->Query(my);
	cout << result23 << endl;
	delete newTree23;
	myresult.push_back(result23);

	DecisionTree* newTree24 = new DecisionTree();
	//add the required root node
	newTree24->CreateRootNode("rs8097206", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree24->AddYesNode("rs8097206", "rs39639", "Q", 1.5);
	newTree24->AddNoNode("rs8097206", "rs12641411", "Q", 2.5);
	newTree24->AddYesNode("rs39639", "rs9866028", "Q", 1.5);
	newTree24->AddNoNode("rs39639", "rs4713659", "Q", 2.5);
	newTree24->AddYesNode("rs12641411", "x", "1", 5);
	newTree24->AddNoNode("rs12641411", "x", "3", 5);
	newTree24->AddYesNode("rs9866028", "x", "2", 5);
	newTree24->AddNoNode("rs9866028", "x", "1", 5);
	newTree24->AddYesNode("rs4713659", "rs27162", "Q", 2.5);
	newTree24->AddNoNode("rs4713659", "x", "3", 5);
	newTree24->AddYesNode("rs27162", "x", "2", 5);
	newTree24->AddNoNode("rs27162", "x", "1", 5);
	//output the created tree
	newTree24->Output();
	//query the tree
	string result24;
	result24 = newTree24->Query(my);
	cout << result24 << endl;
	delete newTree24;
	myresult.push_back(result24);

	DecisionTree* newTree25 = new DecisionTree();
	//add the required root node
	newTree25->CreateRootNode("rs10851731", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree25->AddYesNode("rs10851731", "rs6560084", "Q", 2.5);
	newTree25->AddNoNode("rs10851731", "rs11085023", "Q", 2.5);
	newTree25->AddYesNode("rs6560084", "x", "1", 5);
	newTree25->AddNoNode("rs6560084", "x", "2", 5);
	newTree25->AddYesNode("rs11085023", "rs277639", "Q", 1.5);
	newTree25->AddNoNode("rs11085023", "x", "3", 5);
	newTree25->AddYesNode("rs277639", "x", "1", 5);
	newTree25->AddNoNode("rs277639", "rs7677859", "Q", 1.5);
	newTree25->AddYesNode("rs7677859", "x", "3", 5);
	newTree25->AddNoNode("rs7677859", "x", "2", 5);
	//output the created tree
	newTree25->Output();
	//query the tree
	string result25;
	result25 = newTree25->Query(my);
	cout << result25 << endl;
	delete newTree25;
	myresult.push_back(result25);

	DecisionTree* newTree26 = new DecisionTree();
	//add the required root node
	newTree26->CreateRootNode("rs2228511", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree26->AddYesNode("rs2228511", "rs738987", "Q", 1.5);
	newTree26->AddNoNode("rs2228511", "rs2500090", "Q", 2.5);
	newTree26->AddYesNode("rs738987", "rs560767", "2", 2.5);
	newTree26->AddNoNode("rs738987", "rs2967391", "3", 2.5);
	newTree26->AddYesNode("rs2500090", "x", "1", 5);
	newTree26->AddNoNode("rs2500090", "x", "2", 5);
	newTree26->AddYesNode("rs560767", "x", "3", 5);
	newTree26->AddNoNode("rs560767", "x", "2", 5);
	newTree26->AddYesNode("rs2967391", "x", "2", 5);
	newTree26->AddNoNode("rs2967391", "x", "1", 5);
	//output the created tree
	newTree26->Output();
	//query the tree
	string result26;
	result26 = newTree26->Query(my);
	cout << result26 << endl;
	delete newTree26;
	myresult.push_back(result26);

	DecisionTree* newTree27 = new DecisionTree();
	//add the required root node
	newTree27->CreateRootNode("rs1942885", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree27->AddYesNode("rs1942885", "rs11903376", "Q", 1.5);
	newTree27->AddNoNode("rs1942885", "rs12677218", "Q", 2.5);
	newTree27->AddYesNode("rs11903376", "x", "1", 5);
	newTree27->AddNoNode("rs11903376", "rs2035247", "Q", 1.5);
	newTree27->AddYesNode("rs12677218", "rs2849372", "Q", 2.5);
	newTree27->AddNoNode("rs12677218", "x", "3", 5);
	newTree27->AddYesNode("rs2035247", "x", "1", 5);
	newTree27->AddNoNode("rs2035247", "rs6679430", "Q", 2.5);
	newTree27->AddYesNode("rs2849372", "x", "2", 5);
	newTree27->AddNoNode("rs2849372", "x", "1", 5);
	newTree27->AddYesNode("rs6679430", "x", "2", 5);
	newTree27->AddNoNode("rs6679430", "x", "3", 5);
	//output the created tree
	newTree27->Output();
	//query the tree
	string result27;
	result27 = newTree27->Query(my);
	cout << result27 << endl;
	delete newTree27;
	myresult.push_back(result27);

	DecisionTree* newTree28 = new DecisionTree();
	//add the required root node
	newTree28->CreateRootNode("rs260711", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree28->AddYesNode("rs260711", "rs10998087", "Q", 2.5);
	newTree28->AddNoNode("rs260711", "rs1117382", "Q", 2.5);
	newTree28->AddYesNode("rs10998087", "x", "3", 5);
	newTree28->AddNoNode("rs10998087", "x", "2", 5);
	newTree28->AddYesNode("rs1117382", "x", "1", 5);
	newTree28->AddNoNode("rs1117382", "rs7376483", "Q", 2.5);
	newTree28->AddYesNode("rs7376483", "rs12446781", "Q", 1.5);
	newTree28->AddNoNode("rs7376483", "x", "3", 5);
	newTree28->AddYesNode("rs12446781", "x", "1", 5);
	newTree28->AddNoNode("rs12446781", "x", "2", 5);
	//output the created tree
	newTree28->Output();
	//query the tree
	string result28;
	result28 = newTree28->Query(my);
	cout << result28 << endl;
	delete newTree28;
	myresult.push_back(result28);

	DecisionTree* newTree29 = new DecisionTree();
	//add the required root node
	newTree29->CreateRootNode("rs1250253", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree29->AddYesNode("rs1250253", "rs1478446", "Q", 2.5);
	newTree29->AddNoNode("rs1250253", "rs6763648", "Q", 1.5);
	newTree29->AddYesNode("rs1478446", "rs2673884", "Q", 2.5);
	newTree29->AddNoNode("rs1478446", "rs2506898", "Q", 2.5);
	newTree29->AddYesNode("rs6763648", "x", "3", 5);
	newTree29->AddNoNode("rs6763648", "x", "2", 5);
	newTree29->AddYesNode("rs2673884", "rs158512", "Q", 1.5);
	newTree29->AddNoNode("rs2673884", "x", "3", 5);
	newTree29->AddYesNode("rs2506898", "x", "1", 5);
	newTree29->AddNoNode("rs2506898", "x", "2", 5);
	newTree29->AddYesNode("rs158512", "x", "1", 5);
	newTree29->AddNoNode("rs158512", "x", "2", 5);
	//output the created tree
	newTree29->Output();
	//query the tree
	string result29;
	result29 = newTree29->Query(my);
	cout << result29 << endl;
	delete newTree29;
	myresult.push_back(result29);

	DecisionTree* newTree30 = new DecisionTree();
	//add the required root node
	newTree30->CreateRootNode("rs7923368", "Q", 2.5);
	//add subsequent nodes based on problem definition
	newTree30->AddYesNode("rs7923368", "rs1419138", "Q", 2.5);
	newTree30->AddNoNode("rs7923368", "rs10759290", "Q", 1.5);
	newTree30->AddYesNode("rs1419138", "rs10185826", "Q", 2.5);
	newTree30->AddNoNode("rs1419138", "x", "1", 5);
	newTree30->AddYesNode("rs10759290", "x", "1", 5);
	newTree30->AddNoNode("rs10759290", "x", "3", 5);
	newTree30->AddYesNode("rs10185826", "rs1854935", "Q", 1.5);
	newTree30->AddNoNode("rs10185826", "x", "3", 5);
	newTree30->AddYesNode("rs1854935", "x", "1", 5);
	newTree30->AddNoNode("rs1854935", "x", "2", 5);
	//output the created tree
	newTree30->Output();
	//query the tree
	string result30;
	result30 = newTree30->Query(my);
	cout << result30 << endl;
	delete newTree30;
	myresult.push_back(result30);

	calNumReturnResult(myresult);

	system("pause");
	return 0;

}

///Users/zhangchi/Desktop/Machine learning_1/Test_data_270_50000_markers.csv
/*
#include "common.hpp"
int main(int argc, char *argv[]){

  int c;
  char * inputFile = NULL;
  char * output_file = NULL;
  while ((c = getopt (argc, argv, "i:o:")) != -1){
        switch (c)
  	{

  	case 'i':
  //          fprintf(stderr,"[%s]-> ",optarg);
  	  if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
  	      fprintf (stderr,
  		       "Found illegal or NULL parameter for the option -i.\n");
  	      return 1;
  	  }

  	  inputFile = optarg;

  	  break;

    case 'o':
  //          fprintf(stderr,"[%s]-> ",optarg);
      if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
          fprintf (stderr,
             "Found illegal or NULL parameter for the option -o.\n");
          return 1;
      }

      output_file = optarg;

      break;

  case '?':
    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
    return 1;
  }
}
if (inputFile != NULL){
  std::cout << inputFile << std::endl;
}

if (output_file != NULL){
  std::cout << output_file << std::endl;
}
  auto str = "Hello World!!";

  return 0;
}
*/
