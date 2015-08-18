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
		cout << "Added 'yes' node";
		cout << newNodeID;
		cout << " onto 'yes' branch of node ";
		cout << existingNodeID;
		cout << endl;
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
		cout << "Added 'no' node";
		cout << newNodeID;
		cout << " onto 'no' branch of node ";
		cout << existingNodeID;
		cout << endl;
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
	cout << node->m_strQuestOrAns + " (enter yes or no)\n";
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

	cout << "[" + tag + "] node id = ";

	cout << currentNode->m_iNodeID;
	cout << ", question/answer = ";
	cout << currentNode->m_strQuestOrAns;
	cout << endl;

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

		cout << "deleting node " << node->m_iNodeID << endl;
		delete node;
		node = NULL;
	}
}

double DecisionTree::findPosReturnValue(std::vector<vector<string> > inputVector, string a){
	for (int i = 0; i <= (inputVector[0].size()-1); i++){
		if (inputVector[0][i] == a){
			if (inputVector[1][i] == "AA") return 1;
			else if (inputVector[1][i] == "Aa") return 2;
			else if (inputVector[1][i] == "aa") return 3;
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
	std::cout << line1;
	std::cout << line2;
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

	while (breakPos > 4){
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

	return myvector;
}

void calNumReturnResult(vector<string> result){
	int numEUR = 0;
	int numCHN = 0;
	int numAMR = 0;
	int numJPN = 0;
	int numNoValue = 0;
	for (int i = 0; i <= (result.size() - 1); i++){
		if (result[i] == "EUR"){ numEUR++; }
		else if (result[i] == "CHN"){ numCHN++; }
		else if (result[i] == "AMR"){ numAMR++; }
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
	newTree1->CreateRootNode("3", "Q1", 2.5);
	//add subsequent nodes based on problem definition
	newTree1->AddYesNode("3", "2", "Q2", 1.5);
	newTree1->AddNoNode("3", "4", "Q3", 2.5);
	newTree1->AddYesNode("2", "56", "CHN", 2.5);
	newTree1->AddNoNode("2", "67", "JPN", 2.5);
	newTree1->AddYesNode("4", "78", "EUR", 2.5);
	newTree1->AddNoNode("4", "89", "AMR", 2.5);
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
	newTree2->CreateRootNode("54", "Q1", 2.5);
	//add subsequent nodes based on problem definition
	newTree2->AddYesNode("54", "11", "Q2", 1.5);
	newTree2->AddNoNode("54", "9", "Q3", 2.5);
	newTree2->AddYesNode("11", "56", "CHN", 2.5);
	newTree2->AddNoNode("11", "1", "Q4", 1.5);
	newTree2->AddYesNode("9", "78", "EUR", 2.5);
	newTree2->AddNoNode("9", "89", "AMR", 2.5);
	newTree2->AddYesNode("1", "79", "EUR", 2.5);
	newTree2->AddNoNode("1", "86", "JPN", 2.5);
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
	newTree3->CreateRootNode("89", "Q1", 2.5);
	//add subsequent nodes based on problem definition
	newTree3->AddYesNode("89", "11", "Q2", 1.5);
	newTree3->AddNoNode("89", "9", "Q3", 2.5);
	newTree3->AddYesNode("11", "56", "CHN", 2.5);
	newTree3->AddNoNode("11", "5", "Q4", 1.5);
	newTree3->AddYesNode("9", "78", "EUR", 2.5);
	newTree3->AddNoNode("9", "88", "AMR", 2.5);
	newTree3->AddYesNode("5", "79", "EUR", 2.5);
	newTree3->AddNoNode("5", "86", "JPN", 2.5);
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
	newTree4->CreateRootNode("155329", "Q1", 2.5);
	//add subsequent nodes based on problem definition
	newTree4->AddYesNode("155329", "12783", "Q2", 1.5);
	newTree4->AddNoNode("155329", "37720", "Q3", 2.5);
	newTree4->AddYesNode("12783", "392", "CHN", 1.5);
	newTree4->AddNoNode("12783", "243", "Q4", 1.5);
	newTree4->AddYesNode("392", "x", "EUR", 5);
	newTree4->AddNoNode("392", "x", "AMR", 5);
	newTree4->AddYesNode("243", "x", "EUR", 5);
	newTree4->AddNoNode("243", "x", "JPN", 5);
	newTree4->AddYesNode("37720", "x", "JPN", 5);
	newTree4->AddNoNode("37720", "x", "CHN", 5);
	//output the created tree
	newTree4->Output();
	//query the tree
	string result4;
	result4 = newTree4->Query(my);
	cout << result4 << endl;
	delete newTree4;
	myresult.push_back(result4);

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
