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
	newTree5->AddNoNode("rs747094", "x", "rs17671597", 1.5);
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
	newTree14->CreateRootNode("rs2675345", "Q", 1.5);
	//add subsequent nodes based on problem definition
	newTree14->AddYesNode("rs2675345", "rs9931378", "Q", 2.5);
	newTree14->AddNoNode("rs2675345", "rs6546753", "Q", 2.5);
	newTree14->AddYesNode("rs9931378", "x", "1", 5);
	newTree14->AddNoNode("rs9931378", "x", "3", 5);
	newTree14->AddYesNode("rs6546753", "x", "3", 5);
	newTree14->AddNoNode("rs6546753", "x", "2", 5);
	//output the created tree
	newTree14->Output();
	//query the tree
	string result14;
	result14 = newTree14->Query(my);
	cout << result14 << endl;
	delete newTree14;
	myresult.push_back(result14);

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
