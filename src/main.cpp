#include "common.hpp"
#include "TreeNode.h"
#include "DecisionTree.h"
//#include <conio.h>
#include <iostream>
//using namespace std;

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

TreeNode::TreeNode(const std::string & nodeID, const std::string & newQorA, const double & nodeValue)
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

void DecisionTree::CreateRootNode(const std::string & nodeID, const std::string & newQorA, const double & nodeValue)
{
	//create the root node with a specific ID and string
	m_pRootNode = new TreeNode(nodeID, newQorA, nodeValue);
}

void DecisionTree::AddYesNode(const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const	double & newNodeValue)
{
	//if you dont have a root node you cant add another node
	if (m_pRootNode == NULL)
	{
		std::cout << "Error - no root node in AddYesNode()\n";
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
		std::cout << "Node ";
		std::cout << existingNodeID;
		std::cout << " not found \n";
	}
}

bool DecisionTree::SearchTreeAndAddYesNode(TreeNode* currentNode, const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue)
{

	if (currentNode->m_iNodeID == existingNodeID)//for root
	{
		//create node
		if (currentNode->m_pYesBranch == NULL)
		{
			currentNode->m_pYesBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		else//take the place
		{
			currentNode->m_pYesBranch = new TreeNode(newNodeID, newQorA, newNodeValue);
		}
		return true;
	}
	else//for not root
	{
		//try yes branch if it exists
		if (currentNode->m_pYesBranch != NULL)//可以一层一层查进去
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

void DecisionTree::AddNoNode(const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue)
{
	if (m_pRootNode == NULL)
	{
		std::cout << "Error no root node in AddNoNode()\n";
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
		std::cout << "Node ";
		std::cout << existingNodeID;
		std::cout << " not found \n";
	}

}

bool DecisionTree::SearchTreeAndAddNoNode(TreeNode* currentNode, const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue)
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

std::string DecisionTree::QueryBinaryTree(TreeNode* currentNode, std::vector<std::vector<std::string> > inputVector)
{
	if (currentNode->m_pYesBranch == NULL)
	{
		//if both the yes and no branch pointers are NULL
		//the tree is at a decision outcome state so output
		//the string
		if (currentNode->m_pNoBranch == NULL){
			//cout << currentNode->m_strQuestOrAns << endl;
			std::string a = currentNode->m_strQuestOrAns;
			return a;
		}
		else{//useless if the tree I built is right
			std::cout << "Missing yes branch at " + currentNode->m_strQuestOrAns + " question\n";
			return "0";
		}
	}
	if (currentNode->m_pNoBranch == NULL)
	{
		std::cout << "Missing no branch at " + currentNode->m_strQuestOrAns + " question\n";
		return "0";
	}

	//otherwise default to asking the question at the currentNode
	std::string a;
	a = AskQuestion(currentNode, inputVector);
	return a;
}

std::string DecisionTree::Query(std::vector<std::vector<std::string> > inputVector)
{
	std::string result = QueryBinaryTree(m_pRootNode, inputVector);
	return result;
}

std::string DecisionTree::AskQuestion(TreeNode *node, std::vector<std::vector<std::string> > inputVector)
{
	//cout << node->m_strQuestOrAns + " (enter yes or no)\n";
	double answer;
	answer = findPosReturnValue(inputVector, (node->m_iNodeID));
	//string b = "3";
	//cout << inputVector[1][4];
	//cout << findPosReturnValue(inputVector, b);
	if (answer == 0){
		std::string a = "No Value";
		return a;
	}
	else {
		if (answer < (node->m_NodeValue)){
			std::string a = QueryBinaryTree(node->m_pYesBranch, inputVector);
			return a;
		}
		else if (answer >= (node->m_NodeValue)){
			std::string a = QueryBinaryTree(node->m_pNoBranch, inputVector);
			return a;
		}
		//else//看起来好像没用了现在
		//{
		//	std::cout << "Error please answer yes or no\n";
		//	AskQuestion(node, inputVector);
		//}
	}

}
//not use now
void DecisionTree::Output()
{
	OutputBinaryTree("1", m_pRootNode);
}
//not use now
void DecisionTree::OutputBinaryTree(const std::string & tag, TreeNode* currentNode)
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

double DecisionTree::findPosReturnValue(std::vector<std::vector<std::string> > inputVector, const std::string & a){
	for (int i = 0; i <= (inputVector[0].size()-1); i++){
		if (inputVector[0][i] == a){
			if (inputVector[1][i] == "A_A") return 1;
			else if (inputVector[1][i] == "A_B") return 2;
			else if (inputVector[1][i] == "B_B") return 3;
			else if (inputVector[1][i] == "A_C") return 2;
			else if (inputVector[1][i] == "A_G") return 3;
			else if (inputVector[1][i] == "A_T") return 4;
			else if (inputVector[1][i] == "C_A") return 2;
			else if (inputVector[1][i] == "C_C") return 5;
			else if (inputVector[1][i] == "C_G") return 6;
			else if (inputVector[1][i] == "C_T") return 7;
			else if (inputVector[1][i] == "G_A") return 3;
			else if (inputVector[1][i] == "G_C") return 6;
			else if (inputVector[1][i] == "G_G") return 8;
			else if (inputVector[1][i] == "G_T") return 9;
			else if (inputVector[1][i] == "T_A") return 4;
			else if (inputVector[1][i] == "T_C") return 7;
			else if (inputVector[1][i] == "T_G") return 9;
			else if (inputVector[1][i] == "T_T") return 10;
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
template <class Type>
Type stringToNum(const std::string & str)
{
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

bool inTheTreeOrNot(std::vector<std::string> treevector, const std::string & a){
	for (int i = 0; i <= (treevector.size() - 1); i++){
		if (treevector[i] == a){
			return true;
		}
	}
	return false;
}
//string readCSVFile( const char * fileName){
std::vector<std::vector<std::string> > readCSVFile(const char * fileName){
	std::vector<std::vector<std::string> > myvectorinitial;
	myvectorinitial.resize(2);
	std::vector<std::vector<std::string> > myvector;
	myvector.resize(2);
	std::ifstream file;
	std::stringstream ss;
	std::string str;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(fileName);
		ss << file.rdbuf();
		str = ss.str();
		file.close();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Exception opening file\n" << e.what() << std::endl;
		exit(1);
	}
	//std::cout << str;
	std::string delimiter = ",";
	std::string linebreak = "\n";
	std::string line1;
	std::string line2;
	std::string lineID;
	std::string lineInfo;
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
	//East Asian
	std::string treedata = "rs12124819,rs7537756,rs7523549,rs6694632,rs6665000,rs2465126,rs2465136,rs13129,rs11260542,rs9442387,rs12092254,rs9729550,rs1749951,rs17854636,rs182532,rs1887284,rs28414855,rs4648782,rs6699975,rs4074197,rs1107910,rs9970652,rs12403351,rs4648745,rs10910029,rs16824860,rs12034613,rs7512482,rs2645072,rs2840531,rs10910061,rs1998759,rs16823350,rs2651902,rs10797386,rs17398063,rs4648468,rs12073172,rs3765764,rs10910017,rs1885865,rs2275819,rs2298225,rs4654522,rs12023372,rs608210,rs4654468,rs10915307,rs10915396,rs7512133,rs12080410,rs12036857,rs770698,rs11120837,rs6656160,rs11120989,rs178932,rs17389948,rs284243,rs12085319,rs2379143,rs11804222,rs10927559,rs16850259,rs904927,rs2119320,rs7540486,rs3893319,rs4654354,rs12136921,rs4652992,rs3768337,rs6671527,rs4131141,rs1288503,rs2092595,rs12063386,rs10493770,rs10159030,rs914958,rs7547028,rs1074739,rs10494055,rs4244129,rs662353,rs4298709,rs17358956,rs7544659,rs12027396,rs6668819,rs6605005,rs16843306,rs2794860,rs11586974,rs1222144,rs17140182,rs17599139,rs615625,rs12740262,rs10924366,rs4455137,rs342136,rs7563543,rs6732743,rs12615002,rs919688,rs17737466,rs13414393,rs10865278,rs41385746,rs11126130,rs3771848,rs12467106,rs12104625,rs1845017,rs4580387,rs1376444,rs13014047,rs333851,rs6737431,rs4646329,rs10803583,rs10496977,rs10176837,rs11677624,rs6717406,rs41471147,rs10933005,rs6436971,rs11563201,rs13387193,rs13392175,rs717187,rs13085028,rs7640543,rs17029445,rs34136796,rs13322517,rs6779452,rs13064974,rs931250,rs7626152,rs7644875,rs360710,rs191708,rs7640145,rs2133620,rs3930233,rs10804925,rs3889723,rs4490524,rs2390135,rs1498016,rs10017946,rs10013441,rs17040351,rs412763,rs11132199,rs828316,rs31300,rs12697189,rs12658762,rs17783275,rs10060821,rs379717,rs27433,rs7705687,rs7378826,rs17286171,rs17207681,rs17385747,rs2961739,rs6860288,rs17069519,rs4298263,rs6886932,rs17676033,rs3756531,rs2036564,rs9504229,rs9328202,rs17137253,rs7760235,rs9379827,rs2860580,rs2975042,rs3130244,rs3749946,rs2261033,rs9277027,rs3117002,rs3130235,rs6901221,rs2499714,rs4707130,rs313243,rs1407448,rs6926826,rs6927568,rs13203813,rs211605,rs9497981,rs9497982,rs17633478,rs10244477,rs4637726,rs11770368,rs11974206,rs6971267,rs12532805,rs17680606,rs953184,rs10954494,rs12698186,rs1670357,rs17150469,rs4840510,rs17120485,rs1351499,rs7832879,rs13251780,rs2439292,rs1994851,rs1780160,rs4571809,rs12006467,rs7859023,rs1490742,rs3739477,rs10858363,rs2388746,rs12765118,rs11254106,rs11013746,rs2663018,rs2663027,rs4935640,rs17471932,rs7918954,rs1891275,rs12219674,rs10765099,rs2682107,rs12788223,rs11034713,rs7122010,rs1817653,rs4755957,rs4939526,rs7935178,rs11236209,rs770576,rs11224762,rs11224765,rs7928922,rs10895109,rs11224773,rs7935581,rs11224783,rs321125,rs4937070,rs12295314,rs11223548,rs10849181,rs3217805,rs3809250,rs6581191,rs1508594,rs11104947,rs353887,rs9603756,rs9549215,rs1535682,rs9562578,rs9530164,rs9530168,rs6562748,rs11841589,rs9600325,rs7985210,rs982790,rs2209831,rs16947802,rs582322,rs10508158,rs16968045,rs1184774,rs946617,rs1288742,rs17799178,rs2275595,rs1567074,rs16961283,rs7213911,rs9901316,rs3785624,rs7219975,rs3815073,rs16957364,rs7503887,rs3088182,rs16978159,rs667907,rs12480230,rs2224609,rs2072978,rs6018084,rs13042833,rs1569307,rs2838699,rs1883472,rs8135343,rs11703828,\n";
	//origin
	//std::string treedata = "rs987435,rs8091955,rs2040704,rs7921545,rs7677859,rs2324520,rs4242682,rs1450428,rs7215008,rs7974633,rs10187056,rs1588040,rs1932366,rs2204738,rs4847428,rs1909338,rs7676617,rs7158108,rs2578669,rs10758940,rs6679430,rs4835141,rs1099968,rs2214965,rs2506898,rs16953500,rs12511245,rs12921822,rs2035247,rs1679012,rs1726254,rs12681671,rs560767,rs17671597,rs2490385,rs1814538,rs12204275,rs7111521,rs7551132,rs3181372,rs2849372,rs2967391,rs2029623,rs519381,rs2463383,rs11563620,rs6035761,rs27162+F786,rs12446781,rs11098948,rs2546001,rs1854935,rs158512,rs2422098,rs277639,rs6698919,rs4791868,rs9866028,rs9595066,rs1484213,rs4705115,rs4877791,rs9821525,rs2673884,rs9931378,rs6926482,rs2631899,rs4789182,rs1437724,rs6546753,rs1942885,rs11130791,rs4713659,rs10998087,rs1437787,rs13086858,rs864386,rs12120383,rs4615248,rs11170991,rs11903376,rs35389,rs6763648,rs931410,rs12641411,rs590616,rs2605419,rs11649653,rs1320385,rs2433354,rs1117382,rs868622,rs7376483,rs2893312,rs4577845,rs735480,rs10814993,rs2000743,rs702032,rs533571,rs2305858,rs1924381,rs10759290,rs10185826,rs2200402,rs39639,rs6897135,rs4787645,rs10851731,rs12542990,rs12036675,rs6451268,rs260699,rs4722760,rs4749305,rs747094,rs12062528,rs542405,rs6468344,rs1986420,rs11085023,rs260700,rs8097206,rs738276,rs260711,rs2700392,rs282162,rs1478446,rs1805972,rs12677218,rs6977118,rs12895262,rs943773,rs4832501,rs6437783,rs7983489,rs6560084,rs12135904,rs7923368,rs1250253,rs738987,rs7689609,rs2228511,rs11691947,rs7956796,rs6534999,rs2500090,rs2907599,rs4825,rs1419138,rs2675345,rs260705,rs2002739,rs260709,\n";
	//std::cout << line1;
	//std::cout << line2;
	std::vector<size_t>posvector1;
	posvector1.push_back(-1);
	std::vector<size_t>posvector2;
	posvector2.push_back(-1);

	std::vector<std::string> treevector;
	std::vector<size_t>postree;
	postree.push_back(-1);
	std::vector<int>dataposvector;

	for (size_t i = 0; i < treedata.length(); ++i)
	{
		//std::cout << str.at(i);
		if (treedata.at(i) == ','){
			postree.push_back(i);
		}
	}
	postree.push_back(treedata.find(linebreak) - linebreak.length());
	for (int j = 0; j < (postree.size() - 2); j++){
		treevector.push_back(treedata.substr(postree[j] + delimiter.length(), postree[j + 1] - postree[j] - 1));
	}

	for (size_t i = 0; i < line1.length(); ++i)
	{
		//std::cout << str.at(i);
		if (line1.at(i) == ','){
				posvector1.push_back(i);
			}
	}
	posvector1.push_back(line1.find(linebreak)-linebreak.length());
	for (int j = 0; j < (posvector1.size()-2); j++){
		//myvectorinitial[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
		//if (inTheTreeOrNot(treevector, line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1))){
		std::vector<std::string>::iterator it;
	  it = find (treevector.begin(), treevector.end(), (line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1)));
		if (it != treevector.end()){
			dataposvector.push_back(j);
			myvector[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
		}
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
		myvectorinitial[1].push_back(line2.substr(posvector2[j] + delimiter.length(), posvector2[j + 1] - posvector2[j] - 1));
	}
	for (int k = 0; k <= dataposvector.size() - 1; k++){
		//myvector[0].push_back(myvectorinitial[0][dataposvector[k]]);
		myvector[1].push_back(myvectorinitial[1][dataposvector[k]]);
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

void calNumReturnResult(std::vector<std::string> result){
	int numEUR = 0;
	int numCHN = 0;
	int numAMR = 0;
	int numJPN = 0;
	int numNoValue = 0;
	for (int i = 0; i <= (result.size() - 1); i++){
		if (result[i] == "1"){ numEUR++; }
		else if (result[i] == "2"){ numCHN++; }
		else if (result[i] == "3"){ numAMR++; }
		else if (result[i] == "6"){ numJPN++; }
		else if (result[i] == "No Value"){ numNoValue++; }
	}
	std::cout << "EUR: " << numEUR << std::endl;
	std::cout << "CHN: " << numCHN << std::endl;
	std::cout << "AMR: " << numAMR << std::endl;
	std::cout << "JPN: " << numJPN << std::endl;
	std::cout << "NoValue: " << numNoValue << std::endl;
	if ((numEUR >= numCHN) && (numEUR >= numAMR) && (numEUR >= numJPN))
		std::cout << "This is EUR." << std::endl;
	if ((numEUR <= numCHN) && (numCHN >= numAMR) && (numCHN >= numJPN))
		std::cout << "This is CHN." << std::endl;
	if ((numAMR >= numCHN) && (numEUR <= numAMR) && (numAMR >= numJPN))
		std::cout << "This is AMR." << std::endl;
	if ((numJPN >= numCHN) && (numJPN >= numAMR) && (numEUR <= numJPN))
		std::cout << "This is JPN." << std::endl;

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
    std::vector<std::vector<std::string> > my = readCSVFile(inputFile);
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

		std::vector<std::string> myresult;

		std::string treeWordBreak = ",";
	  std::string treeLineBreak = "\n";
	  std::string treeNodeBreak = "_";
		//East Asian
		std::string treeInfo = "Create_rs2860580_Q_5.5,Yes_rs2860580_rs16961283_Q_5.5,No_rs2860580_rs9603756_Q_6,Yes_rs16961283_rs2663018_Q_8.5,No_rs16961283_rs3765764_Q_5.5,Yes_rs9603756_rs4244129_Q_6,No_rs9603756_rs3117002_Q_2,Yes_rs2663018_x_6_5,No_rs2663018_rs6694632_Q_5.5,Yes_rs3765764_x_6_5,No_rs3765764_x_3_5,Yes_rs4244129_rs6671527_Q_2,No_rs4244129_x_6_5,Yes_rs3117002_rs1670357_Q_9.5,No_rs3117002_x_3_5,Yes_rs6694632_x_3_5,No_rs6694632_x_6_5,Yes_rs6671527_rs4654522_Q_7,No_rs6671527_x_6_5,Yes_rs1670357_rs1288503_Q_6,No_rs1670357_x_3_5,Yes_rs4654522_x_3_5,No_rs4654522_x_6_5,Yes_rs1288503_x_3_5,No_rs1288503_x_6_5,\nCreate_rs2975042_Q_9.5,Yes_rs2975042_rs1567074_Q_5.5,No_rs2975042_rs6901221_Q_1.5,Yes_rs1567074_rs1885865_Q_5.5,No_rs1567074_rs2663027_Q_8.5,Yes_rs6901221_rs7705687_Q_8.5,No_rs6901221_x_3_5,Yes_rs1885865_x_6_5,No_rs1885865_x_3_5,Yes_rs2663027_x_6_5,No_rs2663027_rs2465136_Q_6,Yes_rs7705687_rs982790_Q_6,No_rs7705687_rs11236209_Q_5.5,Yes_rs2465136_x_6_5,No_rs2465136_x_3_5,Yes_rs982790_x_6_5,No_rs982790_x_3_5,Yes_rs11236209_x_3_5,No_rs11236209_rs9562578_Q_5.5,Yes_rs9562578_x_3_5,No_rs9562578_rs2036564_Q_6,Yes_rs2036564_x_3_5,No_rs2036564_rs10494055_Q_8.5,Yes_rs10494055_x_3_5,No_rs10494055_x_6_5,\nCreate_rs12698186_Q_2,Yes_rs12698186_rs1184774_Q_5.5,No_rs12698186_rs7503887_Q_8.5,Yes_rs1184774_rs12104625_Q_8.5,No_rs1184774_rs3889723_Q_6,Yes_rs7503887_rs4937070_Q_6,No_rs7503887_rs1074739_Q_3.5,Yes_rs12104625_rs13014047_Q_5.5,No_rs12104625_x_6_5,Yes_rs3889723_x_6_5,No_rs3889723_x_3_5,Yes_rs4937070_x_6_5,No_rs4937070_rs1887284_Q_2,Yes_rs1074739_rs12085319_Q_8.5,No_rs1074739_rs10933005_Q_2,Yes_rs13014047_rs7523549_Q_8.5,No_rs13014047_x_6_5,Yes_rs1887284_x_6_5,No_rs1887284_x_3_5,Yes_rs12085319_x_6_5,No_rs12085319_x_3_5,Yes_rs10933005_x_3_5,No_rs10933005_rs12124819_Q_2,Yes_rs7523549_x_3_5,No_rs7523549_x_6_5,Yes_rs12124819_x_6_5,No_rs12124819_x_3_5,\nCreate_rs4939526_Q_6,Yes_rs4939526_rs17385747_Q_2,No_rs4939526_rs12023372_Q_5.5,Yes_rs17385747_rs931250_Q_8.5,No_rs17385747_rs412763_Q_8.5,Yes_rs12023372_x_3_5,No_rs12023372_x_6_5,Yes_rs931250_rs3771848_Q_9.5,No_rs931250_x_6_5,Yes_rs412763_x_3_5,No_rs412763_x_6_5,Yes_rs3771848_x_6_5,No_rs3771848_rs12295314_Q_2,Yes_rs12295314_rs6927568_Q_5.5,No_rs12295314_x_6_5,Yes_rs6927568_x_6_5,No_rs6927568_rs6860288_Q_6,Yes_rs6860288_rs11804222_Q_2,No_rs6860288_x_6_5,Yes_rs11804222_x_6_5,No_rs11804222_x_3_5,\nCreate_rs11974206_Q_7,Yes_rs11974206_rs16843306_Q_5.5,No_rs11974206_rs2838699_Q_6,Yes_rs16843306_rs178932_Q_5.5,No_rs16843306_rs17040351_Q_2,Yes_rs2838699_rs17207681_Q_2,No_rs2838699_rs13251780_Q_6,Yes_rs178932_x_3_5,No_rs178932_x_6_5,Yes_rs17040351_rs1535682_Q_9.5,No_rs17040351_x_3_5,Yes_rs17207681_rs2072978_Q_5.5,No_rs17207681_rs2275819_Q_5.5,Yes_rs13251780_x_6_5,No_rs13251780_x_3_5,Yes_rs1535682_rs17398063_Q_5.5,No_rs1535682_rs904927_Q_6,Yes_rs2072978_x_6_5,No_rs2072978_rs2682107_Q_2,Yes_rs2275819_x_6_5,No_rs2275819_x_3_5,Yes_rs17398063_x_3_5,No_rs17398063_x_6_5,Yes_rs904927_x_3_5,No_rs904927_x_6_5,Yes_rs2682107_x_6_5,No_rs2682107_x_3_5,\nCreate_rs11104947_Q_5.5,Yes_rs11104947_rs3130244_Q_3.5,No_rs11104947_rs9600325_Q_8.5,Yes_rs3130244_rs1498016_Q_3.5,No_rs3130244_rs9549215_Q_7,Yes_rs9600325_x_6_5,No_rs9600325_rs17029445_Q_6,Yes_rs1498016_rs6699975_Q_1.5,No_rs1498016_x_3_5,Yes_rs9549215_rs11260542_Q_5.5,No_rs9549215_x_6_5,Yes_rs17029445_rs7760235_Q_7,No_rs17029445_x_6_5,Yes_rs6699975_x_3_5,No_rs6699975_x_6_5,Yes_rs11260542_x_3_5,No_rs11260542_x_6_5,Yes_rs7760235_x_6_5,No_rs7760235_rs9901316_Q_5.5,Yes_rs9901316_rs770698_Q_7,No_rs9901316_rs41471147_Q_5.5,Yes_rs770698_x_6_5,No_rs770698_x_3_5,Yes_rs41471147_x_6_5,No_rs41471147_rs3785624_Q_5.5,Yes_rs3785624_x_6_5,No_rs3785624_x_3_5,\nCreate_rs11224783_Q_3.5,Yes_rs11224783_rs9970652_Q_8.5,No_rs11224783_rs10508158_Q_6,Yes_rs9970652_x_6_5,No_rs9970652_x_3_5,Yes_rs10508158_rs9530164_Q_2,No_rs10508158_rs2133620_Q_3.5,Yes_rs9530164_rs17471932_Q_5.5,No_rs9530164_x_6_5,Yes_rs2133620_rs10924366_Q_6,No_rs2133620_rs2439292_Q_5.5,Yes_rs17471932_rs1107910_Q_8.5,No_rs17471932_rs946617_Q_9.5,Yes_rs10924366_x_6_5,No_rs10924366_x_3_5,Yes_rs2439292_x_3_5,No_rs2439292_rs9729550_Q_1.5,Yes_rs1107910_x_6_5,No_rs1107910_x_3_5,Yes_rs946617_x_6_5,No_rs946617_rs6732743_Q_2,Yes_rs9729550_x_3_5,No_rs9729550_x_6_5,Yes_rs6732743_rs17120485_Q_5.5,No_rs6732743_x_6_5,Yes_rs17120485_x_6_5,No_rs17120485_x_3_5,\nCreate_rs3217805_Q_5.5,Yes_rs3217805_rs17633478_Q_2,No_rs3217805_rs3130235_Q_5.5,Yes_rs17633478_rs16947802_Q_3.5,No_rs17633478_x_6_5,Yes_rs3130235_x_3_5,No_rs3130235_rs6886932_Q_5.5,Yes_rs16947802_x_6_5,No_rs16947802_rs7935178_Q_2,Yes_rs6886932_x_3_5,No_rs6886932_x_6_5,Yes_rs7935178_rs17676033_Q_6,No_rs7935178_x_6_5,Yes_rs17676033_rs4840510_Q_5.5,No_rs17676033_x_6_5,Yes_rs4840510_rs662353_Q_5.5,No_rs4840510_x_6_5,Yes_rs662353_rs11677624_Q_2,No_rs662353_x_6_5,Yes_rs11677624_x_6_5,No_rs11677624_x_3_5,\nCreate_rs11224762_Q_2.5,Yes_rs11224762_rs13064974_Q_8.5,No_rs11224762_rs717187_Q_5.5,Yes_rs13064974_rs2465126_Q_2,No_rs13064974_rs12788223_Q_8.5,Yes_rs717187_x_3_5,No_rs717187_rs12063386_Q_8.5,Yes_rs2465126_x_6_5,No_rs2465126_x_3_5,Yes_rs12788223_rs1780160_Q_6,No_rs12788223_rs12080410_Q_7,Yes_rs12063386_rs12034613_Q_5.5,No_rs12063386_x_3_5,Yes_rs1780160_rs2209831_Q_6,No_rs1780160_x_6_5,Yes_rs12080410_x_6_5,No_rs12080410_x_3_5,Yes_rs12034613_x_3_5,No_rs12034613_x_6_5,Yes_rs2209831_rs10244477_Q_8.5,No_rs2209831_x_6_5,Yes_rs10244477_x_6_5,No_rs10244477_rs4654354_Q_6,Yes_rs4654354_rs12740262_Q_5.5,No_rs4654354_x_6_5,Yes_rs12740262_x_3_5,No_rs12740262_x_6_5,\nCreate_rs11224765_Q_6,Yes_rs11224765_rs7626152_Q_8.5,No_rs11224765_rs10765099_Q_2,Yes_rs7626152_rs10910061_Q_2,No_rs7626152_rs11034713_Q_3.5,Yes_rs10765099_x_3_5,No_rs10765099_rs6971267_Q_5.5,Yes_rs10910061_x_3_5,No_rs10910061_x_6_5,Yes_rs11034713_rs10927559_Q_9.5,No_rs11034713_rs3756531_Q_7,Yes_rs6971267_x_3_5,No_rs6971267_x_6_5,Yes_rs10927559_x_6_5,No_rs10927559_x_3_5,Yes_rs3756531_x_6_5,No_rs3756531_rs10496977_Q_8.5,Yes_rs10496977_x_6_5,No_rs10496977_rs12480230_Q_8.5,Yes_rs12480230_rs6926826_Q_2,No_rs12480230_x_6_5,Yes_rs6926826_rs2119320_Q_8.5,No_rs6926826_x_6_5,Yes_rs2119320_x_3_5,No_rs2119320_x_6_5,\nCreate_rs1490742_Q_8.5,Yes_rs1490742_rs1891275_Q_6,No_rs1490742_rs6779452_Q_5.5,Yes_rs1891275_rs10017946_Q_6,No_rs1891275_rs13387193_Q_8.5,Yes_rs6779452_rs7540486_Q_6,No_rs6779452_rs1407448_Q_5.5,Yes_rs10017946_rs6668819_Q_8.5,No_rs10017946_rs13085028_Q_8.5,Yes_rs13387193_rs4490524_Q_8.5,No_rs13387193_x_6_5,Yes_rs7540486_x_3_5,No_rs7540486_x_6_5,Yes_rs1407448_x_6_5,No_rs1407448_rs16850259_Q_8.5,Yes_rs6668819_x_3_5,No_rs6668819_x_6_5,Yes_rs13085028_x_3_5,No_rs13085028_rs7213911_Q_2,Yes_rs4490524_x_3_5,No_rs4490524_x_6_5,Yes_rs16850259_x_6_5,No_rs16850259_x_3_5,Yes_rs7213911_rs4648468_Q_5.5,No_rs7213911_x_3_5,Yes_rs4648468_x_3_5,No_rs4648468_x_6_5,\nCreate_rs2261033_Q_5.5,Yes_rs2261033_rs7122010_Q_6,No_rs2261033_rs1351499_Q_5.5,Yes_rs7122010_rs615625_Q_1.5,No_rs7122010_rs2840531_Q_8.5,Yes_rs1351499_rs10013441_Q_8.5,No_rs1351499_rs2499714_Q_8.5,Yes_rs615625_rs2388746_Q_2,No_rs615625_rs10915307_Q_2,Yes_rs2840531_x_6_5,No_rs2840531_x_3_5,Yes_rs10013441_x_6_5,No_rs10013441_rs2651902_Q_6,Yes_rs2499714_rs7859023_Q_5.5,No_rs2499714_x_3_5,Yes_rs2388746_x_6_5,No_rs2388746_rs9497981_Q_2,Yes_rs10915307_x_3_5,No_rs10915307_x_6_5,Yes_rs2651902_x_3_5,No_rs2651902_x_6_5,Yes_rs7859023_x_6_5,No_rs7859023_x_3_5,Yes_rs9497981_rs10159030_Q_5.5,No_rs9497981_x_6_5,Yes_rs10159030_x_6_5,No_rs10159030_x_3_5,\nCreate_rs10865278_Q_5.5,Yes_rs10865278_rs2961739_Q_8.5,No_rs10865278_rs11223548_Q_8.5,Yes_rs2961739_rs27433_Q_9.5,No_rs2961739_rs6018084_Q_5.5,Yes_rs11223548_rs2275595_Q_5.5,No_rs11223548_rs608210_Q_2,Yes_rs27433_rs13042833_Q_8.5,No_rs27433_rs12073172_Q_5.5,Yes_rs6018084_x_6_5,No_rs6018084_rs12403351_Q_5.5,Yes_rs2275595_x_6_5,No_rs2275595_rs13322517_Q_2,Yes_rs608210_x_3_5,No_rs608210_x_6_5,Yes_rs13042833_rs379717_Q_8.5,No_rs13042833_x_3_5,Yes_rs12073172_x_3_5,No_rs12073172_x_6_5,Yes_rs12403351_x_6_5,No_rs12403351_x_3_5,Yes_rs13322517_rs12467106_Q_5.5,No_rs13322517_x_6_5,Yes_rs379717_x_3_5,No_rs379717_rs6581191_Q_2,Yes_rs12467106_x_6_5,No_rs12467106_x_3_5,Yes_rs6581191_x_3_5,No_rs6581191_x_6_5,\nCreate_rs9530168_Q_5.5,Yes_rs9530168_rs2794860_Q_6,No_rs9530168_rs9497982_Q_2,Yes_rs2794860_x_3_5,No_rs2794860_x_6_5,Yes_rs9497982_rs17137253_Q_2,No_rs9497982_x_6_5,Yes_rs17137253_rs12532805_Q_8.5,No_rs17137253_x_6_5,Yes_rs12532805_rs6717406_Q_9.5,No_rs12532805_rs10954494_Q_2,Yes_rs6717406_x_6_5,No_rs6717406_rs10803583_Q_3.5,Yes_rs10954494_x_3_5,No_rs10954494_x_6_5,Yes_rs10803583_x_6_5,No_rs10803583_rs11563201_Q_6,Yes_rs11563201_rs11586974_Q_8.5,No_rs11563201_x_6_5,Yes_rs11586974_x_3_5,No_rs11586974_x_6_5,\nCreate_rs1508594_Q_8.5,Yes_rs1508594_rs12615002_Q_6,No_rs1508594_rs770576_Q_2,Yes_rs12615002_rs211605_Q_5.5,No_rs12615002_rs3768337_Q_2,Yes_rs770576_rs13203813_Q_6,No_rs770576_rs17069519_Q_3.5,Yes_rs211605_rs11254106_Q_5.5,No_rs211605_x_3_5,Yes_rs3768337_x_3_5,No_rs3768337_x_6_5,Yes_rs13203813_rs16968045_Q_5.5,No_rs13203813_x_6_5,Yes_rs17069519_x_3_5,No_rs17069519_x_6_5,Yes_rs11254106_x_3_5,No_rs11254106_x_6_5,Yes_rs16968045_x_6_5,No_rs16968045_rs12219674_Q_8.5,Yes_rs12219674_x_6_5,No_rs12219674_rs4637726_Q_2,Yes_rs4637726_x_3_5,No_rs4637726_x_6_5,\nCreate_rs10176837_Q_2.5,Yes_rs10176837_rs313243_Q_2,No_rs10176837_rs7985210_Q_9.5,Yes_rs313243_rs11224773_Q_2,No_rs313243_x_6_5,Yes_rs7985210_x_3_5,No_rs7985210_x_6_5,Yes_rs11224773_rs1817653_Q_5.5,No_rs11224773_rs7832879_Q_5.5,Yes_rs1817653_rs4648745_Q_6,No_rs1817653_rs3809250_Q_1.5,Yes_rs7832879_rs4648782_Q_5.5,No_rs7832879_x_3_5,Yes_rs4648745_x_3_5,No_rs4648745_x_6_5,Yes_rs3809250_rs17783275_Q_5.5,No_rs3809250_x_6_5,Yes_rs4648782_x_3_5,No_rs4648782_x_6_5,Yes_rs17783275_x_6_5,No_rs17783275_rs667907_Q_5.5,Yes_rs667907_rs2298225_Q_1.5,No_rs667907_x_6_5,Yes_rs2298225_x_6_5,No_rs2298225_x_3_5,\nCreate_rs7644875_Q_2,Yes_rs7644875_rs17799178_Q_2,No_rs7644875_rs16823350_Q_2,Yes_rs17799178_rs17286171_Q_6,No_rs17799178_rs1994851_Q_5.5,Yes_rs16823350_x_3_5,No_rs16823350_x_6_5,Yes_rs17286171_rs12136921_Q_5.5,No_rs17286171_rs2092595_Q_3.5,Yes_rs1994851_x_3_5,No_rs1994851_rs1749951_Q_2,Yes_rs12136921_rs4074197_Q_2,No_rs12136921_rs17150469_Q_6,Yes_rs2092595_x_6_5,No_rs2092595_x_3_5,Yes_rs1749951_x_3_5,No_rs1749951_x_6_5,Yes_rs4074197_x_6_5,No_rs4074197_x_3_5,Yes_rs17150469_rs11703828_Q_6,No_rs17150469_x_6_5,Yes_rs11703828_rs1222144_Q_2,No_rs11703828_x_6_5,Yes_rs1222144_rs9504229_Q_6,No_rs1222144_x_6_5,Yes_rs9504229_x_3_5,No_rs9504229_x_6_5,\nCreate_rs41385746_Q_6,Yes_rs41385746_rs7928922_Q_6,No_rs41385746_rs9379827_Q_3.5,Yes_rs7928922_rs10849181_Q_8.5,No_rs7928922_rs7544659_Q_2,Yes_rs9379827_rs7640543_Q_5.5,No_rs9379827_rs3088182_Q_6,Yes_rs10849181_rs10493770_Q_6,No_rs10849181_rs6656160_Q_2,Yes_rs7544659_x_3_5,No_rs7544659_x_6_5,Yes_rs7640543_x_6_5,No_rs7640543_x_3_5,Yes_rs3088182_rs7219975_Q_2,No_rs3088182_rs2390135_Q_8.5,Yes_rs10493770_x_6_5,No_rs10493770_rs12092254_Q_2,Yes_rs6656160_x_3_5,No_rs6656160_x_6_5,Yes_rs7219975_x_3_5,No_rs7219975_rs7547028_Q_2,Yes_rs2390135_x_6_5,No_rs2390135_rs13129_Q_6,Yes_rs12092254_x_6_5,No_rs12092254_x_3_5,Yes_rs7547028_rs2645072_Q_1.5,No_rs7547028_x_3_5,Yes_rs13129_x_3_5,No_rs13129_x_6_5,Yes_rs2645072_x_3_5,No_rs2645072_x_6_5,\nCreate_rs12697189_Q_6,Yes_rs12697189_rs7935581_Q_2,No_rs12697189_rs9277027_Q_2,Yes_rs7935581_rs2224609_Q_2,No_rs7935581_rs12027396_Q_8.5,Yes_rs9277027_rs4935640_Q_3.5,No_rs9277027_rs8135343_Q_2,Yes_rs2224609_rs4755957_Q_8.5,No_rs2224609_rs10910017_Q_2,Yes_rs12027396_x_3_5,No_rs12027396_x_6_5,Yes_rs4935640_x_3_5,No_rs4935640_x_6_5,Yes_rs8135343_x_3_5,No_rs8135343_x_6_5,Yes_rs4755957_x_6_5,No_rs4755957_rs13392175_Q_9.5,Yes_rs10910017_x_3_5,No_rs10910017_x_6_5,Yes_rs13392175_rs11120989_Q_2,No_rs13392175_rs11770368_Q_2,Yes_rs11120989_x_6_5,No_rs11120989_x_3_5,Yes_rs11770368_x_3_5,No_rs11770368_x_6_5,\nCreate_rs6436971_Q_8.5,Yes_rs6436971_rs953184_Q_3.5,No_rs6436971_rs12765118_Q_5.5,Yes_rs953184_x_3_5,No_rs953184_rs28414855_Q_1.5,Yes_rs12765118_rs1883472_Q_6,No_rs12765118_rs7378826_Q_9.5,Yes_rs28414855_x_3_5,No_rs28414855_x_6_5,Yes_rs1883472_rs10915396_Q_6,No_rs1883472_rs11132199_Q_6,Yes_rs7378826_rs16824860_Q_8.5,No_rs7378826_rs34136796_Q_3.5,Yes_rs10915396_x_6_5,No_rs10915396_x_3_5,Yes_rs11132199_x_3_5,No_rs11132199_x_6_5,Yes_rs16824860_x_6_5,No_rs16824860_x_3_5,Yes_rs34136796_rs4654468_Q_6,No_rs34136796_rs333851_Q_2,Yes_rs4654468_x_3_5,No_rs4654468_x_6_5,Yes_rs333851_rs17599139_Q_5.5,No_rs333851_x_6_5,Yes_rs17599139_x_6_5,No_rs17599139_rs17389948_Q_8.5,Yes_rs17389948_x_3_5,No_rs17389948_x_6_5,\nCreate_rs360710_Q_5.5,Yes_rs360710_rs12036857_Q_7,No_rs360710_rs12658762_Q_8.5,Yes_rs12036857_x_6_5,No_rs12036857_x_3_5,Yes_rs12658762_rs16957364_Q_8.5,No_rs12658762_rs4298263_Q_2,Yes_rs16957364_rs7512482_Q_6,No_rs16957364_rs3739477_Q_7,Yes_rs4298263_rs1376444_Q_6,No_rs4298263_rs7537756_Q_2,Yes_rs7512482_x_3_5,No_rs7512482_x_6_5,Yes_rs3739477_x_6_5,No_rs3739477_rs1288742_Q_5.5,Yes_rs1376444_rs17358956_Q_1.5,No_rs1376444_x_3_5,Yes_rs7537756_x_3_5,No_rs7537756_x_6_5,Yes_rs1288742_rs17737466_Q_6,No_rs1288742_x_6_5,Yes_rs17358956_x_6_5,No_rs17358956_x_3_5,Yes_rs17737466_rs1845017_Q_5.5,No_rs17737466_x_6_5,Yes_rs1845017_rs11126130_Q_2.5,No_rs1845017_x_6_5,Yes_rs11126130_x_3_5,No_rs11126130_x_6_5,\nCreate_rs3749946_Q_3.5,Yes_rs3749946_rs321125_Q_5.5,No_rs3749946_rs17140182_Q_2,Yes_rs321125_rs7512133_Q_5.5,No_rs321125_rs11120837_Q_8.5,Yes_rs17140182_rs1569307_Q_5.5,No_rs17140182_rs10797386_Q_2,Yes_rs7512133_x_6_5,No_rs7512133_x_3_5,Yes_rs11120837_x_3_5,No_rs11120837_x_6_5,Yes_rs1569307_rs919688_Q_2,No_rs1569307_rs191708_Q_2,Yes_rs10797386_x_3_5,No_rs10797386_x_6_5,Yes_rs919688_x_6_5,No_rs919688_x_3_5,Yes_rs191708_rs12006467_Q_8.5,No_rs191708_x_6_5,Yes_rs12006467_x_6_5,No_rs12006467_rs914958_Q_2,Yes_rs914958_rs828316_Q_2,No_rs914958_x_6_5,Yes_rs828316_x_6_5,No_rs828316_x_3_5,\nCreate_rs13414393_Q_6,Yes_rs13414393_rs10895109_Q_6,No_rs13414393_rs353887_Q_8.5,Yes_rs10895109_rs7918954_Q_6,No_rs10895109_rs4652992_Q_8.5,Yes_rs353887_rs4298709_Q_5.5,No_rs353887_rs1998759_Q_2,Yes_rs7918954_rs7563543_Q_5.5,No_rs7918954_x_6_5,Yes_rs4652992_x_3_5,No_rs4652992_x_6_5,Yes_rs4298709_rs10804925_Q_2,No_rs4298709_rs3815073_Q_8.5,Yes_rs1998759_x_6_5,No_rs1998759_x_3_5,Yes_rs7563543_x_6_5,No_rs7563543_rs17854636_Q_6,Yes_rs10804925_x_6_5,No_rs10804925_rs2379143_Q_6,Yes_rs3815073_rs284243_Q_2,No_rs3815073_rs31300_Q_6,Yes_rs17854636_x_3_5,No_rs17854636_x_6_5,Yes_rs2379143_x_6_5,No_rs2379143_x_3_5,Yes_rs284243_x_3_5,No_rs284243_x_6_5,Yes_rs31300_x_3_5,No_rs31300_x_6_5,\nCreate_rs6562748_Q_1.5,Yes_rs6562748_rs4571809_Q_9.5,No_rs6562748_rs10060821_Q_8.5,Yes_rs4571809_rs6737431_Q_2,No_rs4571809_rs7640145_Q_2,Yes_rs10060821_x_6_5,No_rs10060821_x_3_5,Yes_rs6737431_rs342136_Q_6,No_rs6737431_rs582322_Q_8.5,Yes_rs7640145_rs3930233_Q_8.5,No_rs7640145_x_6_5,Yes_rs342136_rs4131141_Q_6,No_rs342136_rs6665000_Q_1.5,Yes_rs582322_x_6_5,No_rs582322_x_3_5,Yes_rs3930233_rs4455137_Q_5.5,No_rs3930233_rs4646329_Q_6,Yes_rs4131141_x_3_5,No_rs4131141_x_6_5,Yes_rs6665000_x_6_5,No_rs6665000_x_3_5,Yes_rs4455137_x_6_5,No_rs4455137_x_3_5,Yes_rs4646329_rs3893319_Q_2,No_rs4646329_x_6_5,Yes_rs3893319_x_3_5,No_rs3893319_x_6_5,\n";
		//origin
		//std::string treeInfo = "Create_rs6437783_Q_1.5,Yes_rs6437783_rs4835141_Q_1.5,No_rs6437783_rs735480_Q_1.5,Yes_rs4835141_x_2_5,No_rs4835141_x_3_5,Yes_rs735480_x_3_5,No_rs735480_x_1_5,\nCreate_rs35389_Q_2.5,Yes_rs35389_rs4787645_Q_1.5,No_rs35389_rs1726254_Q_2.5,Yes_rs4787645_rs4847428_Q_1.5,No_rs4787645_x_3_5,Yes_rs1726254_x_1_5,No_rs1726254_x_2_5,Yes_rs4847428_x_1_5,No_rs4847428_x_2_5,\nCreate_rs1986420_Q_2.5,Yes_rs1986420_rs12135904_Q_2.5,No_rs1986420_x_1_5,Yes_rs12135904_rs1679012_CHN_1.5,No_rs12135904_x_3_5,Yes_rs1679012_x_2_5,No_rs1679012_x_1_5,\nCreate_rs2675345_Q_1.5,Yes_rs2675345_rs9931378_Q_2.5,No_rs2675345_rs6546753_Q_2.5,Yes_rs9931378_x_1_5,No_rs9931378_x_3_5,Yes_rs6546753_x_3_5,No_rs6546753_x_2_5,\nCreate_rs2700392_Q_1.5,Yes_rs2700392_rs1924381_Q_1.5,No_rs2700392_rs747094_Q_2.5,Yes_rs1924381_x_2_5,No_rs1924381_x_1_5,Yes_rs747094_x_3_5,No_rs747094_rs17671597_Q_1.5,Yes_rs17671597_x_2_5,No_rs17671597_x_1_5,\nCreate_rs260700_Q_2.5,Yes_rs260700_rs6451268_Q_2.5,No_rs260700_rs12204275_Q_1.5,Yes_rs6451268_rs987435_Q_1.5,No_rs6451268_rs16953500_Q_2.5,Yes_rs12204275_x_2_5,No_rs12204275_x_3_5,Yes_rs987435_x_3_5,No_rs987435_rs4242682_Q_2.5,Yes_rs16953500_x_1_5,No_rs16953500_x_2_5,Yes_rs4242682_x_2_5,No_rs4242682_x_1_5,\nCreate_rs260699_Q_1.5,Yes_rs260699_rs11130791_Q_2.5,No_rs260699_rs6897135_Q_1.5,Yes_rs11130791_x_2_5,No_rs11130791_x_3_5,Yes_rs6897135_x_1_5,No_rs6897135_rs1588040_Q_1.5,Yes_rs1588040_x_3_5,No_rs1588040_rs7974633_Q_1.5,Yes_rs7974633_x_1_5,No_rs7974633_x_2_5,\nCreate_rs260705_Q_1.5,Yes_rs260705_rs11649653_Q_1.5,No_rs260705_rs2433354_Q_2.5,Yes_rs11649653_x_2_5,No_rs11649653_x_3_5,Yes_rs2433354_rs2204738_Q_2.5,No_rs2433354_rs4791868_Q_1.5,Yes_rs2204738_x_2_5,No_rs2204738_x_3_5,Yes_rs4791868_x_2_5,No_rs4791868_x_1_5,\nCreate_rs282162_Q_2.5,Yes_rs282162_rs4825_Q_2.5,No_rs282162_rs864386_Q_1.5,Yes_rs4825_rs1814538_Q_1.5,No_rs4825_rs10187056_Q_1.5,Yes_rs864386_x_3_5,No_rs864386_x_1_5,Yes_rs1814538_x_2_5,No_rs1814538_x_1_5,Yes_rs10187056_x_3_5,No_rs10187056_x_2_5,\nCreate_rs2002739_Q_2.5,Yes_rs2002739_rs12120383_Q_1.5,No_rs2002739_rs2000743_Q_2.5,Yes_rs12120383_rs7111521_Q_1.5,No_rs12120383_rs12921822_Q_1.5,Yes_rs2000743_x_3_5,No_rs2000743_x_1_5,Yes_rs7111521_x_2_5,No_rs7111521_x_1_5,Yes_rs12921822_x_3_5,No_rs12921822_x_2_5,\nCreate_rs4722760_Q_1.5,Yes_rs4722760_rs13086858_Q_2.5,No_rs4722760_rs1320385_Q_2.5,Yes_rs13086858_rs7676617_Q_1.5,No_rs13086858_x_3_5,Yes_rs1320385_rs7215008_Q_1.5,No_rs1320385_rs6698919_Q_2.5,Yes_rs7676617_x_1_5,No_rs7676617_x_2_5,Yes_rs7215008_x_3_5,No_rs7215008_x_2_5,Yes_rs6698919_x_1_5,No_rs6698919_x_2_5,\nCreate_rs2907599_Q_1.5,Yes_rs2907599_rs12036675_Q_2.5,No_rs2907599_rs10814993_Q_1.5,Yes_rs12036675_x_2_5,No_rs12036675_x_1_5,Yes_rs10814993_rs2463383_Q_1.5,No_rs10814993_rs1484213_Q_2.5,Yes_rs2463383_x_2_5,No_rs2463383_x_3_5,Yes_rs1484213_x_2_5,No_rs1484213_x_1_5,\nCreate_rs2893312_Q_1.5,Yes_rs2893312_rs868622_Q_1.5,No_rs2893312_rs12062528_Q_2.5,Yes_rs868622_x_3_5,No_rs868622_rs2578669_Q_2.5,Yes_rs12062528_rs519381_Q_1.5,No_rs12062528_rs9595066_Q_2.5,Yes_rs2578669_x_2_5,No_rs2578669_x_1_5,Yes_rs519381_x_3_5,No_rs519381_x_2_5,Yes_rs9595066_x_1_5,No_rs9595066_x_2_5,\nCreate_rs590616_Q_1.5,Yes_rs590616_rs2605419_Q_2.5,No_rs590616_rs12895262_Q_1.5,Yes_rs2605419_x_3_5,No_rs2605419_x_1_5,Yes_rs12895262_x_1_5,No_rs12895262_rs1909338_Q_2.5,Yes_rs1909338_rs10758940_Q_1.5,No_rs1909338_x_3_5,Yes_rs10758940_x_1_5,No_rs10758940_x_2_5,\nCreate_rs533571_Q_2.5,Yes_rs533571_rs6468344_Q_2.5,No_rs533571_rs4577845_Q_2.5,Yes_rs6468344_rs11098948_Q_1.5,No_rs6468344_rs2029623_Q_1.5,Yes_rs4577845_x_3_5,No_rs4577845_x_1_5,Yes_rs11098948_x_3_5,No_rs11098948_x_2_5,Yes_rs2029623_x_2_5,No_rs2029623_x_1_5,\nCreate_rs260709_Q_2.5,Yes_rs260709_rs11691947_Q_2.5,No_rs260709_rs1437724_Q_1.5,Yes_rs11691947_rs7158108_3_2.5,No_rs11691947_rs4705115_1_1.5,Yes_rs1437724_x_2_5,No_rs1437724_x_3_5,Yes_rs7158108_x_1_5,No_rs7158108_x_2_5,Yes_rs4705115_x_3_5,No_rs4705115_rs2214965_Q_1.5,Yes_rs2214965_x_1_5,No_rs2214965_x_2_5,\nCreate_rs6534999_Q_2.5,Yes_rs6534999_rs7689609_Q_2.5,No_rs6534999_rs12542990_Q_2.5,Yes_rs7689609_x_1_5,No_rs7689609_rs1450428_Q_1.5,Yes_rs12542990_rs7551132_Q_1.5,No_rs12542990_x_3_5,Yes_rs1450428_x_3_5,No_rs1450428_x_2_5,Yes_rs7551132_x_1_5,No_rs7551132_x_2_5,\nCreate_rs4832501_Q_1.5,Yes_rs4832501_rs2200402_Q_2.5,No_rs4832501_rs931410_Q_1.5,Yes_rs2200402_rs2546001_Q_1.5,No_rs2200402_rs8091955_Q_2.5,Yes_rs931410_rs1099968_Q_2.5,No_rs931410_x_1_5,Yes_rs2546001_x_2_5,No_rs2546001_x_1_5,Yes_rs8091955_x_3_5,No_rs8091955_x_2_5,Yes_rs1099968_rs7921545_Q_2.5,No_rs1099968_x_1_5,Yes_rs7921545_x_2_5,No_rs7921545_x_3_5,\nCreate_rs1437787_Q_1.5,Yes_rs1437787_rs11170991_Q_2.5,No_rs1437787_rs1805972_Q_1.5,Yes_rs11170991_x_3_5,No_rs11170991_x_1_1.5,Yes_rs1805972_rs2422098_Q_1.5,No_rs1805972_rs9821525_Q_1.5,Yes_rs2422098_x_2_5,No_rs2422098_x_1_5,Yes_rs9821525_x_3_5,No_rs9821525_rs12511245_Q_2.5,Yes_rs12511245_x_2_5,No_rs12511245_x_1_5,\nCreate_rs4749305_Q_1.5,Yes_rs4749305_rs2631899_Q_2.5,No_rs4749305_rs7956796_Q_2.5,Yes_rs2631899_x_3_5,No_rs2631899_x_2_5,Yes_rs7956796_x_1_5,No_rs7956796_rs4877791_Q_2.5,Yes_rs4877791_rs1932366_Q_1.5,No_rs4877791_x_3_5,Yes_rs1932366_x_1_5,No_rs1932366_x_2_5,\nCreate_rs542405_Q_2.5,Yes_rs542405_rs6977118_Q_1.5,No_rs542405_rs2305858_Q_2.5,Yes_rs6977118_rs11563620_Q_1.5,No_rs6977118_x_3_5,Yes_rs2305858_rs2040704_Q_1.5,No_rs2305858_x_1_5,Yes_rs11563620_x_2_5,No_rs11563620_x_1_5,Yes_rs2040704_x_3_5,No_rs2040704_x_2_5,\nCreate_rs738276_Q_1.5,Yes_rs738276_rs4615248_Q_2.5,No_rs738276_rs7983489_Q_1.5,Yes_rs4615248_rs12681671_Q_1.5,No_rs4615248_x_3_5,Yes_rs7983489_rs6035761_Q_1.5,No_rs7983489_rs2324520_Q_2.5,Yes_rs12681671_x_2_5,No_rs12681671_x_1_5,Yes_rs6035761_x_2_5,No_rs6035761_x_1_5,Yes_rs2324520_rs3181372_Q_2.5,No_rs2324520_x_3_5,Yes_rs3181372_x_2_5,No_rs3181372_x_1_5,\nCreate_rs943773_Q_1.5,Yes_rs943773_rs4789182_Q_1.5,No_rs943773_rs702032_Q_2.5,Yes_rs4789182_x_2_5,No_rs4789182_x_3_5,Yes_rs702032_rs6926482_Q_1.5,No_rs702032_x_1_5,Yes_rs6926482_x_3_5,No_rs6926482_rs2490385_Q_1.5,Yes_rs2490385_x_1_5,No_rs2490385_x_2_5,\nCreate_rs8097206_Q_2.5,Yes_rs8097206_rs39639_Q_1.5,No_rs8097206_rs12641411_Q_2.5,Yes_rs39639_rs9866028_Q_1.5,No_rs39639_rs4713659_Q_2.5,Yes_rs12641411_x_1_5,No_rs12641411_x_3_5,Yes_rs9866028_x_2_5,No_rs9866028_x_1_5,Yes_rs4713659_rs27162_Q_2.5,No_rs4713659_x_3_5,Yes_rs27162_x_2_5,No_rs27162_x_1_5,\nCreate_rs10851731_Q_1.5,Yes_rs10851731_rs6560084_Q_2.5,No_rs10851731_rs11085023_Q_2.5,Yes_rs6560084_x_1_5,No_rs6560084_x_2_5,Yes_rs11085023_rs277639_Q_1.5,No_rs11085023_x_3_5,Yes_rs277639_x_1_5,No_rs277639_rs7677859_Q_1.5,Yes_rs7677859_x_3_5,No_rs7677859_x_2_5,\nCreate_rs2228511_Q_2.5,Yes_rs2228511_rs738987_Q_1.5,No_rs2228511_rs2500090_Q_2.5,Yes_rs738987_rs560767_2_2.5,No_rs738987_rs2967391_3_2.5,Yes_rs2500090_x_1_5,No_rs2500090_x_2_5,Yes_rs560767_x_3_5,No_rs560767_x_2_5,Yes_rs2967391_x_2_5,No_rs2967391_x_1_5,\nCreate_rs1942885_Q_2.5,Yes_rs1942885_rs11903376_Q_1.5,No_rs1942885_rs12677218_Q_2.5,Yes_rs11903376_x_1_5,No_rs11903376_rs2035247_Q_1.5,Yes_rs12677218_rs2849372_Q_2.5,No_rs12677218_x_3_5,Yes_rs2035247_x_1_5,No_rs2035247_rs6679430_Q_2.5,Yes_rs2849372_x_2_5,No_rs2849372_x_1_5,Yes_rs6679430_x_2_5,No_rs6679430_x_3_5,\nCreate_rs260711_Q_1.5,Yes_rs260711_rs10998087_Q_2.5,No_rs260711_rs1117382_Q_2.5,Yes_rs10998087_x_3_5,No_rs10998087_x_2_5,Yes_rs1117382_x_1_5,No_rs1117382_rs7376483_Q_2.5,Yes_rs7376483_rs12446781_Q_1.5,No_rs7376483_x_3_5,Yes_rs12446781_x_1_5,No_rs12446781_x_2_5,\nCreate_rs1250253_Q_2.5,Yes_rs1250253_rs1478446_Q_2.5,No_rs1250253_rs6763648_Q_1.5,Yes_rs1478446_rs2673884_Q_2.5,No_rs1478446_rs2506898_Q_2.5,Yes_rs6763648_x_3_5,No_rs6763648_x_2_5,Yes_rs2673884_rs158512_Q_1.5,No_rs2673884_x_3_5,Yes_rs2506898_x_1_5,No_rs2506898_x_2_5,Yes_rs158512_x_1_5,No_rs158512_x_2_5,\nCreate_rs7923368_Q_2.5,Yes_rs7923368_rs1419138_Q_2.5,No_rs7923368_rs10759290_Q_1.5,Yes_rs1419138_rs10185826_Q_2.5,No_rs1419138_x_1_5,Yes_rs10759290_x_1_5,No_rs10759290_x_3_5,Yes_rs10185826_rs1854935_Q_1.5,No_rs10185826_x_3_5,Yes_rs1854935_x_1_5,No_rs1854935_x_2_5,\n";
		//string treeInfo = "Create_rs198642_Q_2.5,Yes_rs198642_rs1213594_Q_2.5,No_rs198642_x_1_5,Yes_rs1213594_rs167912_CHN_1.5,No_rs1213594_x_3_5,Yes_rs167912_x_2_5,No_rs167912_x_1_5,\n";
		std::string treeLineInfo;
	  std::string treeWordInfo;
	  std::vector<std::string> treeNodeInfo;
	  size_t treeNodePos;
	  size_t treeWordPos;
	  size_t treeLinePos;
	  treeLinePos = treeInfo.find(treeLineBreak);
	  while(treeLinePos < 1000000){//应该为while循环
	    treeLineInfo = treeInfo.substr(0, treeLinePos + treeLineBreak.length());

			DecisionTree* newTree = new DecisionTree();

	    treeWordPos = treeLineInfo.find(treeWordBreak);
	    while(treeWordPos < 1000000){
	      treeWordInfo = treeLineInfo.substr(0, treeWordPos + treeWordBreak.length());

	      treeNodePos = treeWordInfo.find(treeNodeBreak);
	      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	      //cout << treeNodeInfo[0] << endl;
	      treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	      treeNodePos = treeWordInfo.find(treeNodeBreak);
	      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	      //cout << treeNodeInfo[1] << endl;
	      treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	      treeNodePos = treeWordInfo.find(treeNodeBreak);
	      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	      //cout << treeNodeInfo[2] << endl;
	      if(treeNodeInfo[0] == "Create"){
	        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	        treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	        double a = stringToNum<double>(treeNodeInfo[3]);
	        newTree->CreateRootNode(treeNodeInfo[1], treeNodeInfo[2], a);
	        treeNodeInfo.clear();
	      }
	      else if (treeNodeInfo[0] == "Yes"){
	        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	        treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

	        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	        treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	        double a = stringToNum<double>(treeNodeInfo[4]);
	        newTree->AddYesNode(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
	        treeNodeInfo.clear();
	      }
	      else if (treeNodeInfo[0] == "No"){
	        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	        treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

	        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	        treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	        double a = stringToNum<double>(treeNodeInfo[4]);
	        newTree->AddNoNode(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
	        treeNodeInfo.clear();
	      }

	      treeLineInfo.erase(0, treeWordPos + treeWordBreak.length());
	      treeWordPos = treeLineInfo.find(treeWordBreak);
	    }
	    //newTree->Output();
			std::string result;
			result = newTree->Query(my);
			std::cout << result << std::endl;
			delete newTree;
			myresult.push_back(result);

			treeInfo.erase(0, treeLinePos + treeLineBreak.length());
	    treeLinePos = treeInfo.find(treeLineBreak);
	  }
/*
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
*/
	calNumReturnResult(myresult);
//took about 15 seconds
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
