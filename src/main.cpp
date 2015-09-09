
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
	//Euro 15 trees
	//std::string treedata = "rs3131972,rs3748592,rs13303010,rs9697457,rs35940137,rs2710875,rs9442380,rs10907175,rs11721,rs35134975,rs873927,rs28456011,rs752965,rs6663158,rs1878752,rs4648843,rs11590198,rs4648451,rs16824089,rs12756705,rs12411035,rs4654598,rs11591221,rs7537345,rs10915671,rs2649071,rs12061902,rs12084067,rs7540503,rs4243830,rs12754538,rs11121374,rs4129341,rs2924863,rs16853148,rs1737352,rs11582182,rs1192579,rs2744705,rs9426362,rs6425820,rs2492301,rs2788031,rs17123422,rs1772618,rs11208566,rs9729825,rs17099679,rs1333717,rs41453452,rs10494252,rs1027423,rs164151,rs2015330,rs16865298,rs1496092,rs1772145,rs17048875,rs3890758,rs2671264,rs7419176,rs4853793,rs4952541,rs13396777,rs12466764,rs11694681,rs1031466,rs3791298,rs1942055,rs7599054,rs6430545,rs1446523,rs1530559,rs4954218,rs7570971,rs12988076,rs6719488,rs4988235,rs309180,rs218174,rs309160,rs309164,rs12615624,rs687670,rs309134,rs309137,rs4954557,rs11693502,rs749873,rs932206,rs4954573,rs7568884,rs11692725,rs10204606,rs11687599,rs10803574,rs2890917,rs13005337,rs1485973,rs1453406,rs10172873,rs12053389,rs17255817,rs3828267,rs4666782,rs13431857,rs1016569,rs16827500,rs10510366,rs1126098,rs615861,rs4292253,rs3773540,rs17404744,rs16849564,rs1356359,rs17786823,rs35936034,rs17018796,rs17040162,rs17040164,rs6846249,rs13143297,rs1565469,rs13150320,rs6552970,rs154160,rs17602783,rs12109110,rs12654448,rs1419644,rs439812,rs1318631,rs2395634,rs6904956,rs7740421,rs10245230,rs12690925,rs10096219,rs10113325,rs10888101,rs1481742,rs1401817,rs6998565,rs272613,rs1355640,rs2418249,rs4880987,rs11252318,rs12259741,rs1249402,rs11008809,rs760336,rs7911308,rs11602585,rs2595448,rs7395373,rs659944,rs721346,rs2283293,rs11831618,rs1871549,rs265638,rs7966178,rs7981968,rs540497,rs17091427,rs9788522,rs7168653,rs1002007,rs12905660,rs16973728,rs299955,rs4799085,rs6052070,rs6029050,rs16980843,rs233253,rs461436,rs5754554,\n";
	//NorthAmerican 12 trees
	//std::string treedata = "rs3131972,rs2905036,rs4245756,rs4970383,rs4475691,rs13302982,rs4040604,rs3748592,rs3748593,rs28570376,rs6696281,rs35940137,rs9331225,rs9803031,rs6667248,rs4314833,rs9729550,rs11466691,rs6603781,rs6685064,rs3737721,rs3737718,rs2274264,rs12142199,rs3855955,rs17160669,rs35242196,rs1240708,rs873927,rs35958305,rs7290,rs3766178,rs3128342,rs1926883,rs7407,rs2281173,rs2235536,rs2254669,rs4648808,rs425277,rs9442619,rs2292857,rs262680,rs10910034,rs2643885,rs2055204,rs2840530,rs4310388,rs10752748,rs2606411,rs6681741,rs2817185,rs1798246,rs2651927,rs2651912,rs2500283,rs12043519,rs2483275,rs2244013,rs6669870,rs2298225,rs12039666,rs10492944,rs7541544,rs351619,rs17348860,rs3947662,rs367673,rs13376100,rs9329417,rs973978,rs6577401,rs7517585,rs11120943,rs17031150,rs9919220,rs679563,rs11582339,rs3860318,rs11121722,rs1881559,rs1569635,rs9442235,rs638425,rs41388954,rs10737480,rs10917234,rs12410046,rs12075715,rs3767908,rs1335762,rs2183746,rs12097368,rs1498111,rs522821,rs3795501,rs274751,rs11264025,rs1861,rs11211329,rs12028663,rs12038297,rs7552342,rs3737829,rs2793661,rs10889634,rs12059795,rs12411125,rs6694203,rs11204853,rs16841094,rs2814778,rs7552141,rs4644548,rs6663420,rs1246828,rs488612,rs2802774,rs12568035,rs11119881,rs1439464,rs17742354,rs6541124,rs16846854,rs12467317,rs672463,rs4669937,rs1524007,rs10165208,rs7588439,rs1396795,rs1396797,rs6732285,rs4851370,rs2123694,rs13397666,rs260698,rs7582192,rs164736,rs2059696,rs10173594,rs6717424,rs1858104,rs6731591,rs4668272,rs1865164,rs17027638,rs5004864,rs6445254,rs2083838,rs11707443,rs1374821,rs4678073,rs6439472,rs6804194,rs16870076,rs210780,rs12108234,rs10008032,rs5743567,rs4833103,rs4624679,rs17007466,rs10025344,rs11748410,rs609096,rs2303170,rs35389,rs35391,rs28117,rs35411,rs1363845,rs331728,rs2270068,rs3776337,rs3776334,rs3776329,rs4958560,rs6932667,rs2051548,rs2691483,rs9442996,rs7759248,rs1016101,rs1338839,rs4870227,rs17084501,rs11965097,rs7782345,rs1465221,rs10245220,rs2904664,rs310373,rs1384182,rs4871389,rs10969597,rs10961635,rs7860104,rs10962599,rs2891125,rs12685829,rs715846,rs1888913,rs2377982,rs10749549,rs3814226,rs11192637,rs11198214,rs3213221,rs10835271,rs12294859,rs4930431,rs7134749,rs2519,rs12423495,rs10777469,rs1007916,rs16941717,rs692902,rs2292051,rs13378757,rs11147417,rs17640978,rs12875618,rs9573246,rs9557355,rs17128262,rs7154864,rs8007618,rs12590812,rs926144,rs4906743,rs1800414,rs11636232,rs916977,rs12595731,rs1704348,rs3848147,rs11637114,rs4436808,rs8053650,rs1133238,rs2032915,rs6500380,rs4790359,rs7214357,rs220486,rs8081204,rs9907225,rs4968239,rs9893667,rs9896466,rs8078633,rs911445,rs6053122,rs6038071,rs2039242,rs2829003,rs4819094,rs917408,rs738989,rs17425081,rs12484869,rs1960182,rs5751131,rs5758402,\n";
	//African 22 trees
	std::string treedata = "rs12124819,rs2905036,rs4245756,rs6694982,rs17160698,rs28499371,rs6696281,rs28391282,rs3128117,rs9697358,rs9331225,rs9803031,rs6667248,rs11807848,rs12757754,rs2298217,rs9660710,rs10907175,rs1815606,rs11466673,rs3813199,rs11260562,rs11260568,rs1739855,rs3737718,rs12142199,rs3845293,rs17160975,rs36044796,rs9782908,rs11807706,rs3128342,rs2377417,rs7520934,rs4648764,rs7531583,rs9970652,rs752965,rs2459994,rs3107145,rs427811,rs9442619,rs1713712,rs10910061,rs12033324,rs903903,rs1123571,rs2494640,rs11581548,rs7512269,rs2477703,rs2477707,rs2147905,rs2234167,rs10910097,rs897620,rs880724,rs2842909,rs2817178,rs1798246,rs10492940,rs2500297,rs12086132,rs6687835,rs1333190,rs870171,rs4648501,rs2493314,rs4648524,rs2821059,rs2794320,rs7514979,rs2298223,rs12079672,rs12090228,rs17404600,rs12093951,rs10915424,rs10915430,rs4130091,rs12071761,rs1353341,rs589870,rs6660514,rs616317,rs242058,rs242050,rs12408533,rs4654607,rs12124406,rs11584727,rs6426370,rs3128689,rs6690311,rs16840287,rs11808981,rs2071958,rs9659669,rs11805412,rs2153900,rs17027039,rs4845820,rs12122894,rs9434795,rs2693958,rs17376559,rs11121090,rs11584036,rs6684149,rs935073,rs2982364,rs10864504,rs7534387,rs6419478,rs11807931,rs816060,rs12405691,rs17038427,rs10754901,rs16853407,rs3817958,rs12409852,rs6691985,rs619345,rs1031567,rs542634,rs525448,rs881247,rs11573205,rs10916790,rs8064,rs3795845,rs641347,rs12067378,rs12040683,rs3935892,rs10799032,rs28495286,rs16824722,rs967094,rs6671001,rs2057969,rs10890311,rs1258010,rs2758735,rs17104047,rs212989,rs6668399,rs7515087,rs4926853,rs7536376,rs542727,rs11808336,rs552006,rs12025026,rs6657290,rs6700924,rs316671,rs615739,rs12097782,rs925192,rs4847372,rs2064662,rs12074249,rs12039907,rs3017627,rs11102559,rs6665912,rs4845735,rs6427184,rs11265070,rs2808651,rs485618,rs12135523,rs12136407,rs16853992,rs1417592,rs9650996,rs7534913,rs7536226,rs12758773,rs3789052,rs12058761,rs3795521,rs6659655,rs10864120,rs1776037,rs7538397,rs12141832,rs6682184,rs6685066,rs12463789,rs1389583,rs771307,rs10204491,rs16866638,rs13414905,rs16862376,rs6734731,rs7590763,rs10198116,rs41513050,rs1067344,rs9789429,rs12478385,rs7596776,rs1534110,rs7600669,rs6731365,rs11125815,rs17030159,rs6547187,rs2309582,rs4851391,rs13389290,rs17030353,rs2034357,rs12620050,rs404499,rs17044602,rs4142753,rs17007536,rs2082331,rs7589010,rs12614459,rs1446750,rs842361,rs16855615,rs4954207,rs6742013,rs7605229,rs1042712,rs309172,rs309161,rs7573555,rs309143,rs6430594,rs309154,rs10205050,rs6755409,rs13403738,rs6759948,rs4894197,rs2562831,rs1427150,rs6734110,rs1607345,rs16849099,rs10932521,rs1443670,rs6436964,rs11688448,rs1995209,rs13087319,rs12630974,rs17729838,rs6785796,rs11718932,rs422584,rs385521,rs9851767,rs6807580,rs12487340,rs11711134,rs3749388,rs1995236,rs6446241,rs4928007,rs4683973,rs2325037,rs16838604,rs349558,rs7649861,rs6770324,rs1546260,rs10513545,rs6778401,rs16848617,rs6779590,rs13081915,rs10428090,rs16855847,rs1039027,rs9290610,rs6800015,rs1374808,rs10937252,rs16862821,rs9290877,rs2378559,rs2185886,rs1000647,rs968365,rs6854453,rs7686272,rs13137543,rs7674434,rs11544855,rs1901747,rs7669018,rs17089059,rs10028900,rs10022017,rs11735775,rs6854417,rs388401,rs6848616,rs12502827,rs4235448,rs4699030,rs17042596,rs17532826,rs17048953,rs6854489,rs345981,rs544870,rs1459157,rs10461322,rs11943281,rs316598,rs1393117,rs2658083,rs852619,rs7730689,rs2388044,rs17595719,rs16901558,rs6882064,rs2913276,rs17301591,rs4513668,rs7700264,rs6595775,rs2624459,rs7446054,rs2227282,rs2237059,rs803137,rs17646556,rs17171218,rs7728894,rs309331,rs17108678,rs17450822,rs7739132,rs2753922,rs6456890,rs1233320,rs2535340,rs1793891,rs12191877,rs367645,rs12191891,rs6932992,rs11963526,rs12204275,rs7741503,rs9486141,rs4245542,rs12191383,rs1204826,rs4946158,rs9400909,rs7753502,rs10872503,rs9376452,rs11155161,rs16900601,rs12701555,rs699486,rs1409968,rs10237182,rs17144015,rs4732511,rs11980955,rs6466823,rs6967965,rs11975980,rs7783639,rs6944302,rs1404315,rs10487094,rs10487999,rs17139871,rs1523794,rs11769723,rs4987672,rs13236792,rs1364519,rs4909055,rs532885,rs4841471,rs1356946,rs748596,rs1077052,rs7010861,rs6558059,rs7017705,rs17786140,rs1404756,rs218892,rs3039743,rs7010482,rs34065840,rs2272634,rs6477310,rs10429529,rs2025319,rs10971164,rs17210010,rs10867230,rs4878051,rs4242609,rs10992623,rs10818338,rs12005198,rs10819101,rs11564096,rs7039873,rs7390989,rs11257434,rs2815617,rs950220,rs1416801,rs9988744,rs10828213,rs824602,rs2839657,rs2370791,rs1935648,rs9421731,rs9415758,rs10825916,rs1536084,rs2182160,rs7923866,rs2476949,rs714816,rs2672609,rs11018181,rs10764918,rs7914354,rs10832430,rs10836370,rs7946936,rs11828501,rs11823218,rs8191431,rs12276848,rs11603486,rs10895512,rs6591090,rs1942518,rs542650,rs10501858,rs4366501,rs7316060,rs16910077,rs10492377,rs1601745,rs10785426,rs4344559,rs11836193,rs12305915,rs10748260,rs7295341,rs10847881,rs11060955,rs9575364,rs2951787,rs12561320,rs9597104,rs9583470,rs1407893,rs1956593,rs10140504,rs7155859,rs1051388,rs12897140,rs12885391,rs10137272,rs10498587,rs2373262,rs10873649,rs1679012,rs10454039,rs199138,rs1834640,rs7169337,rs7177754,rs1037041,rs8035628,rs8027920,rs8028686,rs8041403,rs4887382,rs9788651,rs8042942,rs2191430,rs4787040,rs2287198,rs1420676,rs1982394,rs7206635,rs16972211,rs8052388,rs8051251,rs17796342,rs7185017,rs17741623,rs11654128,rs2240099,rs34052864,rs8075137,rs8892,rs1241988,rs9953932,rs28464695,rs2230233,rs16949551,rs4605270,rs9958746,rs3106146,rs6422427,rs1725501,rs123187,rs11084467,rs4815694,rs3790221,rs6119337,rs6067491,rs6099216,rs2180698,rs354742,rs218336,rs11702338,rs3761364,rs965494,rs9975332,rs2839509,rs875060,rs417252,rs2023637,rs4819836,rs2270013,rs2040435,rs2267270,rs7284910,rs5999984,rs9619574,rs2227914,rs6007462,rs5770567,\n";
	//Kenyan 31 trees
	//std::string treedata = "rs3131972,rs7537756,rs6694982,rs1110052,rs17160698,rs13303106,rs13303010,rs3935066,rs6696281,rs28504611,rs13303118,rs2341362,rs9697358,rs6667248,rs3766191,rs11260595,rs2298217,rs1320565,rs4314833,rs3813199,rs11260568,rs6685064,rs3737721,rs2274264,rs9782908,rs11552172,rs28635343,rs28707307,rs4648764,rs12069909,rs12742323,rs16824500,rs28625223,rs2803310,rs262656,rs2503701,rs7553178,rs4648819,rs12404555,rs1998759,rs10910099,rs12117343,rs12752801,rs6681741,rs2376821,rs2651906,rs3002685,rs6673393,rs11808276,rs947347,rs4431782,rs2181484,rs7523732,rs1175549,rs12031557,rs10915360,rs10753376,rs16838922,rs349400,rs3820250,rs392630,rs11799924,rs6671889,rs648378,rs12095221,rs7554078,rs11805516,rs4908925,rs11120876,rs12119558,rs6676442,rs2493214,rs67746,rs12022654,rs2744677,rs6429800,rs495937,rs7548984,rs16851168,rs9943244,rs7539166,rs4661748,rs1925704,rs4912106,rs897469,rs2776822,rs672138,rs4631721,rs17263039,rs7523842,rs477882,rs10890041,rs11210640,rs12145658,rs12085768,rs6697095,rs7527194,rs11208579,rs6424639,rs7415927,rs17369470,rs11583332,rs11166028,rs12064015,rs1772890,rs1844959,rs1597178,rs3125677,rs12059640,rs10908849,rs8177963,rs12739022,rs12069196,rs12135523,rs11586404,rs12722820,rs2284767,rs16863858,rs9660718,rs6424976,rs4651330,rs2488479,rs6428392,rs1125954,rs2359377,rs875044,rs12239056,rs1891231,rs445633,rs4658560,rs6677662,rs2551320,rs11884415,rs1534110,rs12994558,rs2061517,rs6731365,rs1005608,rs11125815,rs17030159,rs4233931,rs6760326,rs2861641,rs9309464,rs2190355,rs17754897,rs1595422,rs1545223,rs2241883,rs17048353,rs17044602,rs17047458,rs2315523,rs6735149,rs7586145,rs16855615,rs6742013,rs7605229,rs3806502,rs1050115,rs6724569,rs2015532,rs3769012,rs7581814,rs12472293,rs309172,rs7573555,rs309143,rs6430594,rs309154,rs10497029,rs4972277,rs6737636,rs7565410,rs6736379,rs6730036,rs1440463,rs5001924,rs985365,rs13404079,rs7561423,rs17202778,rs4142221,rs4674632,rs2058061,rs9832923,rs13319626,rs17298420,rs11916051,rs17226259,rs6794557,rs201729,rs936663,rs11915247,rs9874060,rs7653308,rs4269034,rs3935821,rs10001947,rs5743612,rs992133,rs17082523,rs9992661,rs17028457,rs12645079,rs1567049,rs13142580,rs1379602,rs316598,rs2188301,rs770308,rs9292857,rs2028723,rs10520997,rs16870510,rs6880683,rs10072084,rs973332,rs10474381,rs12188101,rs7710375,rs6862681,rs10075371,rs1366457,rs2227282,rs2237059,rs30534,rs17286578,rs312557,rs10075720,rs6556382,rs13162048,rs6458997,rs683966,rs6927023,rs364950,rs404557,rs9470872,rs7770679,rs11759220,rs1206088,rs12204275,rs6938518,rs7741503,rs7760662,rs9485572,rs7745739,rs17055737,rs4721216,rs699486,rs595541,rs6968676,rs2054788,rs6975220,rs1005032,rs1990796,rs10242455,rs4646457,rs776746,rs2740566,rs800672,rs6963345,rs4725499,rs17685410,rs4875671,rs2515542,rs532885,rs11203815,rs2237835,rs16937924,rs28399555,rs16886536,rs12541188,rs17775439,rs2720710,rs2944776,rs2721202,rs869939,rs16934647,rs10965215,rs7874475,rs1411088,rs13288508,rs4310281,rs1330684,rs4750058,rs17095806,rs7094900,rs7358097,rs1347957,rs11190458,rs809825,rs6584646,rs790660,rs2067022,rs704737,rs11547493,rs1792959,rs10792608,rs1399357,rs10897976,rs16923264,rs16905958,rs3103736,rs7136627,rs11176729,rs11842930,rs9576822,rs9516890,rs11618950,rs1956593,rs2415306,rs6572913,rs10137272,rs12885270,rs2373262,rs2430341,rs8027732,rs12438284,rs9745005,rs4402506,rs7168199,rs17241648,rs8057684,rs12601516,rs7216396,rs12943500,rs35487582,rs8070885,rs17823777,rs11660396,rs9953932,rs9948548,rs17086113,rs350130,rs2423334,rs1206810,rs6096853,rs6015825,rs8140370,rs5770567,\n";
	//East Asian 47 trees
	//std::string treedata = "rs12124819,rs7537756,rs4040604,rs7523549,rs3935066,rs6694632,rs6665000,rs2465126,rs2465136,rs13129,rs7526076,rs9442372,rs3737728,rs2298217,rs4970421,rs11260542,rs9442387,rs12092254,rs1320565,rs9729550,rs11466691,rs6603781,rs6662635,rs1749951,rs17854636,rs182532,rs2765015,rs2291889,rs11488462,rs1571149,rs1887284,rs1926883,rs28414855,rs4648782,rs12748433,rs6699975,rs4074197,rs760925,rs1107910,rs7534617,rs9970652,rs12403351,rs28710181,rs4648745,rs10910029,rs10752741,rs4648805,rs4648807,rs16824860,rs12034613,rs7512482,rs16824948,rs2645072,rs2840531,rs10910061,rs1123571,rs4233033,rs1998759,rs11573979,rs11573970,rs10909872,rs1869972,rs2606414,rs16823350,rs6695131,rs926244,rs2651902,rs2651929,rs10797386,rs17398063,rs2455107,rs4648468,rs12073172,rs12119711,rs3765764,rs10910017,rs1885865,rs2275819,rs2298225,rs4131373,rs34835780,rs4654522,rs12023372,rs16840755,rs608210,rs10799255,rs16839450,rs4654468,rs1841241,rs10915307,rs2199215,rs2611423,rs10915396,rs7512133,rs12080410,rs12036857,rs770698,rs17028725,rs6698924,rs6577582,rs11120837,rs6656160,rs11120989,rs707457,rs178932,rs428180,rs12738365,rs17389948,rs7530465,rs284243,rs710139,rs12085319,rs17036706,rs2379143,rs11804222,rs12755560,rs10927559,rs164868,rs16850259,rs6685406,rs4920386,rs620950,rs1317209,rs3820330,rs11585587,rs904927,rs2119320,rs7540486,rs3893319,rs12090967,rs4654354,rs10914477,rs12136921,rs4652992,rs3768337,rs2660563,rs2209477,rs11538784,rs11580074,rs6671527,rs11211612,rs4131141,rs6694834,rs1288503,rs797913,rs4926684,rs2092595,rs2272052,rs686543,rs12561942,rs12063386,rs12760071,rs10493770,rs4101233,rs10159030,rs914958,rs7547028,rs662009,rs1074739,rs10494055,rs4244129,rs7542677,rs662353,rs17033865,rs4656248,rs2295615,rs2275603,rs4298709,rs17358956,rs863454,rs10913136,rs873525,rs7544659,rs12027396,rs6668819,rs6605005,rs16843306,rs2794860,rs11586974,rs10863308,rs2000319,rs1222144,rs2273939,rs487113,rs17140182,rs4846908,rs17599139,rs615625,rs12740262,rs7520258,rs10924366,rs4455137,rs953599,rs9287778,rs342136,rs7563543,rs17018699,rs6732743,rs12615002,rs919688,rs10460504,rs17737466,rs1914778,rs1421617,rs13414393,rs10865278,rs41385746,rs11126130,rs13432159,rs41374247,rs3771848,rs1517782,rs12467106,rs12104625,rs1845017,rs11127018,rs4580387,rs1376444,rs10168169,rs13014047,rs333859,rs333851,rs333846,rs4662834,rs6737431,rs12104489,rs4646329,rs10803583,rs10496977,rs374722,rs4662280,rs7587849,rs10176837,rs4530328,rs11677624,rs16826345,rs6717406,rs6732937,rs41471147,rs10932401,rs17325821,rs10933005,rs6436971,rs11563201,rs13387193,rs13392175,rs13030338,rs2320378,rs717187,rs1369407,rs1687331,rs4525889,rs1349283,rs13085028,rs7640543,rs17029445,rs34136796,rs13084153,rs11707193,rs13322517,rs7642488,rs1011609,rs6779452,rs12490963,rs16827628,rs1355781,rs13064974,rs931250,rs7626152,rs7644875,rs360710,rs191708,rs1511412,rs2348394,rs7640145,rs2133620,rs4680238,rs603638,rs3930233,rs1868150,rs751396,rs2713721,rs16864358,rs10804925,rs3889723,rs10517011,rs4371605,rs6833864,rs7658552,rs2173201,rs243996,rs4490524,rs6844821,rs2390135,rs1498016,rs10017946,rs1113111,rs17033938,rs10013441,rs17040351,rs412763,rs7687912,rs11132199,rs828316,rs6420051,rs31300,rs12697189,rs12658762,rs17783275,rs702552,rs10060821,rs379717,rs27433,rs13160949,rs10073882,rs7705687,rs7378826,rs17286171,rs17207681,rs17385747,rs2961739,rs6860288,rs6879391,rs17069519,rs11959012,rs1960425,rs4298263,rs315808,rs6886932,rs17676033,rs3756531,rs17075791,rs2036564,rs9504229,rs9328202,rs9328204,rs17137253,rs7760235,rs9502295,rs2432785,rs2503823,rs9379827,rs6940237,rs3757181,rs16895223,rs2860580,rs2975042,rs3130244,rs3749946,rs2261033,rs9277027,rs2567274,rs3117002,rs3130235,rs3130237,rs3116996,rs6901221,rs6901830,rs2499714,rs1398572,rs689391,rs4707130,rs485276,rs313243,rs1407448,rs6926826,rs6927568,rs10046248,rs13203813,rs3777997,rs211605,rs478611,rs9497981,rs9497982,rs17633478,rs742636,rs7767039,rs946236,rs372440,rs10244477,rs4637726,rs11770368,rs11974206,rs6971267,rs1035582,rs12532805,rs17680606,rs12534948,rs4617036,rs10240570,rs319870,rs2237551,rs953184,rs10500071,rs12532116,rs10954494,rs12698186,rs1670357,rs1900102,rs17150469,rs4840510,rs17120485,rs7016943,rs1351499,rs7832879,rs13251780,rs2439292,rs1994851,rs6472787,rs1869609,rs2513850,rs2622637,rs7461808,rs871952,rs12547611,rs2976392,rs2920297,rs2382019,rs1780160,rs4571809,rs1017783,rs12006467,rs10512019,rs12551119,rs1999462,rs3824405,rs6560612,rs7859023,rs4255200,rs2418268,rs2418269,rs1490742,rs3739477,rs10858363,rs17135476,rs11251966,rs2388746,rs17151786,rs7921121,rs12765118,rs11254106,rs10904962,rs11013746,rs3762084,rs1148214,rs2663018,rs2663027,rs1317894,rs4935397,rs4935640,rs17471932,rs12250707,rs12266901,rs16933163,rs7918954,rs1250544,rs12254574,rs2000177,rs1891275,rs12219674,rs12412736,rs10765099,rs11016442,rs8181588,rs2682107,rs443592,rs3741026,rs7944342,rs2268063,rs649640,rs10836933,rs12788223,rs11034713,rs7938730,rs1369323,rs7122010,rs1817653,rs4755957,rs4939526,rs7935178,rs640655,rs642490,rs11236209,rs4753962,rs770576,rs11224762,rs11224765,rs7928922,rs10895109,rs10444351,rs11224773,rs7935581,rs11224783,rs4141989,rs2046685,rs1791466,rs321125,rs1877351,rs2298464,rs4937070,rs4937384,rs12295314,rs2105606,rs11223548,rs10849181,rs3217805,rs3809250,rs10843585,rs1874799,rs2277317,rs6581191,rs1275569,rs11104775,rs1508594,rs11104947,rs11611632,rs353887,rs701100,rs7995074,rs9603756,rs9549215,rs1535682,rs4942308,rs9562578,rs566105,rs1504418,rs9530164,rs9543281,rs9530168,rs6562748,rs11841589,rs9600325,rs7985210,rs982790,rs2209831,rs16947802,rs9518309,rs582322,rs10508158,rs16968045,rs9559436,rs1184774,rs17764769,rs946617,rs17093760,rs217656,rs10134028,rs4904385,rs174519,rs174511,rs174510,rs174504,rs1288742,rs17799178,rs3742672,rs8016966,rs1955614,rs2275595,rs2958272,rs17649182,rs1567074,rs16961283,rs8041381,rs12922641,rs7203853,rs9930735,rs4785322,rs6564809,rs41526051,rs8050818,rs7213911,rs9901316,rs3785624,rs7219975,rs3815073,rs16957364,rs17821703,rs17221329,rs4969058,rs7503887,rs10853282,rs3088182,rs17561133,rs16978159,rs7244157,rs7235487,rs8093745,rs10408164,rs4416143,rs667907,rs202481,rs12480230,rs2224609,rs2423402,rs2072978,rs6030932,rs6018084,rs13042833,rs375980,rs1569307,rs2838699,rs1883472,rs11913594,rs8135343,rs11703828,rs133503,\n";
	//Hapmap 2
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
		if (result[i] == "7"){ numEUR++; }
		else if (result[i] == "9"){ numCHN++; }
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
		//Euro 15 trees (remain 14 trees, delete the 9th)
		//std::string treeInfo = "Create_rs7570971_Q_1.5,Yes_rs7570971_rs10494252_Q_3.5,No_rs7570971_rs10096219_Q_8.5,Yes_rs10494252_rs28456011_Q_6,No_rs10494252_rs12754538_Q_8.5,Yes_rs10096219_rs1878752_Q_2,No_rs10096219_rs10172873_Q_2,Yes_rs28456011_x_2_5,No_rs28456011_x_10_5,Yes_rs12754538_rs12756705_Q_8.5,No_rs12754538_x_2_5,Yes_rs1878752_x_10_5,No_rs1878752_x_2_5,Yes_rs10172873_rs13396777_Q_5.5,No_rs10172873_x_10_5,Yes_rs12756705_x_10_5,No_rs12756705_x_2_5,Yes_rs13396777_x_10_5,No_rs13396777_rs12061902_Q_8.5,Yes_rs12061902_x_10_5,No_rs12061902_x_2_5,\nCreate_rs4988235_Q_5.5,Yes_rs4988235_rs10888101_Q_8.5,No_rs4988235_rs272613_Q_2,Yes_rs10888101_x_10_5,No_rs10888101_rs7966178_Q_6,Yes_rs272613_rs16853148_Q_6,No_rs272613_rs13303010_Q_2,Yes_rs7966178_rs721346_Q_8.5,No_rs7966178_x_10_5,Yes_rs16853148_rs16849564_Q_6,No_rs16853148_x_2_5,Yes_rs13303010_x_2_5,No_rs13303010_x_10_5,Yes_rs721346_x_10_5,No_rs721346_rs17404744_Q_8.5,Yes_rs16849564_x_2_5,No_rs16849564_x_10_5,Yes_rs17404744_x_2_5,No_rs17404744_x_10_5,\nCreate_rs932206_Q_6,Yes_rs932206_rs4954218_Q_9.5,No_rs932206_rs2283293_Q_2,Yes_rs4954218_rs9426362_Q_2,No_rs4954218_rs4292253_Q_6,Yes_rs2283293_rs265638_Q_6,No_rs2283293_rs10907175_Q_1.5,Yes_rs9426362_x_2_5,No_rs9426362_x_10_5,Yes_rs4292253_x_2_5,No_rs4292253_rs1355640_Q_5.5,Yes_rs265638_x_10_5,No_rs265638_rs11008809_Q_2,Yes_rs10907175_x_10_5,No_rs10907175_x_2_5,Yes_rs1355640_x_2_5,No_rs1355640_rs11590198_Q_2,Yes_rs11008809_x_10_5,No_rs11008809_rs1485973_Q_2,Yes_rs11590198_x_2_5,No_rs11590198_x_10_5,Yes_rs1485973_rs35134975_Q_5.5,No_rs1485973_x_10_5,Yes_rs35134975_x_10_5,No_rs35134975_x_2_5,\nCreate_rs1942055_Q_5.5,Yes_rs1942055_rs309164_Q_8.5,No_rs1942055_rs6052070_Q_2,Yes_rs309164_rs1027423_Q_7,No_rs309164_rs9788522_Q_3.5,Yes_rs6052070_rs16980843_Q_3.5,No_rs6052070_rs13150320_Q_2,Yes_rs1027423_rs3131972_Q_2,No_rs1027423_rs11692725_Q_2,Yes_rs9788522_x_10_5,No_rs9788522_x_2_5,Yes_rs16980843_x_10_5,No_rs16980843_rs11121374_Q_5.5,Yes_rs13150320_x_2_5,No_rs13150320_x_10_5,Yes_rs3131972_x_10_5,No_rs3131972_x_2_5,Yes_rs11692725_x_2_5,No_rs11692725_rs1453406_Q_6,Yes_rs11121374_x_2_5,No_rs11121374_x_10_5,Yes_rs1453406_x_2_5,No_rs1453406_rs11208566_Q_5.5,Yes_rs11208566_x_2_5,No_rs11208566_x_10_5,\nCreate_rs749873_Q_6,Yes_rs749873_rs1401817_Q_2,No_rs749873_rs6430545_Q_2.5,Yes_rs1401817_rs154160_Q_7,No_rs1401817_x_2_5,Yes_rs6430545_rs12259741_Q_5.5,No_rs6430545_rs540497_Q_6,Yes_rs154160_x_2_5,No_rs154160_rs16973728_Q_8.5,Yes_rs12259741_rs16824089_Q_8.5,No_rs12259741_rs6425820_Q_8.5,Yes_rs540497_rs1126098_Q_5.5,No_rs540497_x_10_5,Yes_rs16973728_x_2_5,No_rs16973728_x_10_5,Yes_rs16824089_x_2_5,No_rs16824089_x_10_5,Yes_rs6425820_x_2_5,No_rs6425820_x_10_5,Yes_rs1126098_rs17602783_Q_2,No_rs1126098_x_10_5,Yes_rs17602783_x_10_5,No_rs17602783_rs13005337_Q_2,Yes_rs13005337_x_10_5,No_rs13005337_x_2_5,\nCreate_rs1530559_Q_5.5,Yes_rs1530559_rs10245230_Q_6,No_rs1530559_rs7911308_Q_3.5,Yes_rs10245230_rs9729825_Q_2,No_rs10245230_rs1419644_Q_2.5,Yes_rs7911308_rs10113325_Q_5.5,No_rs7911308_x_2_5,Yes_rs9729825_rs10915671_Q_5.5,No_rs9729825_rs11721_Q_3.5,Yes_rs1419644_rs6846249_Q_1.5,No_rs1419644_x_10_5,Yes_rs10113325_rs2744705_Q_8.5,No_rs10113325_rs1737352_Q_5.5,Yes_rs10915671_x_10_5,No_rs10915671_x_2_5,Yes_rs11721_x_2_5,No_rs11721_x_10_5,Yes_rs6846249_x_10_5,No_rs6846249_x_2_5,Yes_rs2744705_rs9697457_Q_5.5,No_rs2744705_x_2_5,Yes_rs1737352_x_2_5,No_rs1737352_x_10_5,Yes_rs9697457_x_2_5,No_rs9697457_x_10_5,\nCreate_rs309180_Q_5.5,Yes_rs309180_rs11252318_Q_6,No_rs309180_rs7740421_Q_2,Yes_rs11252318_rs4954557_Q_6,No_rs11252318_rs2595448_Q_6,Yes_rs7740421_rs439812_Q_6,No_rs7740421_x_2_5,Yes_rs4954557_rs1772618_Q_2,No_rs4954557_rs299955_Q_2,Yes_rs2595448_x_10_5,No_rs2595448_rs1016569_Q_8.5,Yes_rs439812_x_2_5,No_rs439812_x_10_5,Yes_rs1772618_x_10_5,No_rs1772618_x_2_5,Yes_rs299955_rs752965_Q_8.5,No_rs299955_x_2_5,Yes_rs1016569_x_10_5,No_rs1016569_rs3773540_Q_5.5,Yes_rs752965_x_10_5,No_rs752965_x_2_5,Yes_rs3773540_x_10_5,No_rs3773540_rs4243830_Q_6,Yes_rs4243830_x_10_5,No_rs4243830_x_2_5,\nCreate_rs218174_Q_5.5,Yes_rs218174_rs687670_Q_8.5,No_rs218174_rs6904956_Q_8.5,Yes_rs687670_rs2890917_Q_2.5,No_rs687670_rs164151_Q_6,Yes_rs6904956_x_2_5,No_rs6904956_rs1318631_Q_2,Yes_rs2890917_rs7395373_Q_8.5,No_rs2890917_rs1356359_Q_5.5,Yes_rs164151_x_10_5,No_rs164151_rs6552970_Q_8.5,Yes_rs1318631_x_2_5,No_rs1318631_x_10_5,Yes_rs7395373_rs873927_Q_5.5,No_rs7395373_rs6663158_Q_5.5,Yes_rs1356359_x_10_5,No_rs1356359_rs11602585_Q_8.5,Yes_rs6552970_rs12411035_Q_5.5,No_rs6552970_x_10_5,Yes_rs873927_x_10_5,No_rs873927_x_2_5,Yes_rs6663158_x_10_5,No_rs6663158_x_2_5,Yes_rs11602585_x_2_5,No_rs11602585_x_10_5,Yes_rs12411035_x_2_5,No_rs12411035_x_10_5,\nCreate_rs309137_Q_6,Yes_rs309137_rs10803574_Q_2,No_rs309137_rs1446523_Q_2,Yes_rs10803574_x_2_5,No_rs10803574_rs3890758_Q_5.5,Yes_rs1446523_rs12690925_Q_8.5,No_rs1446523_rs2418249_Q_6,Yes_rs3890758_rs9442380_Q_8.5,No_rs3890758_x_2_5,Yes_rs12690925_rs4648843_Q_8.5,No_rs12690925_rs1871549_Q_8.5,Yes_rs2418249_rs2924863_Q_9.5,No_rs2418249_rs4880987_Q_8.5,Yes_rs9442380_x_10_5,No_rs9442380_x_2_5,Yes_rs4648843_x_10_5,No_rs4648843_x_2_5,Yes_rs1871549_x_2_5,No_rs1871549_x_10_5,Yes_rs2924863_x_10_5,No_rs2924863_rs13431857_Q_6,Yes_rs4880987_x_10_5,No_rs4880987_x_2_5,Yes_rs13431857_x_10_5,No_rs13431857_rs11582182_Q_7,Yes_rs11582182_x_10_5,No_rs11582182_x_2_5,\nCreate_rs12615624_Q_2,Yes_rs12615624_rs17040162_Q_8.5,No_rs12615624_rs35936034_Q_6,Yes_rs17040162_x_10_5,No_rs17040162_rs10510366_Q_2,Yes_rs35936034_rs2492301_Q_8.5,No_rs35936034_rs12466764_Q_7,Yes_rs10510366_x_10_5,No_rs10510366_rs17255817_Q_5.5,Yes_rs2492301_rs12654448_Q_6,No_rs2492301_rs11694681_Q_5.5,Yes_rs12466764_rs3748592_Q_5.5,No_rs12466764_rs1772145_Q_8.5,Yes_rs17255817_x_2_5,No_rs17255817_x_10_5,Yes_rs12654448_rs1002007_Q_2,No_rs12654448_x_2_5,Yes_rs11694681_x_10_5,No_rs11694681_x_2_5,Yes_rs3748592_x_2_5,No_rs3748592_x_10_5,Yes_rs1772145_x_10_5,No_rs1772145_x_2_5,Yes_rs1002007_x_2_5,No_rs1002007_x_10_5,\nCreate_rs309134_Q_5.5,Yes_rs309134_rs3791298_Q_8.5,No_rs309134_rs17040164_Q_6,Yes_rs3791298_rs17018796_Q_7,No_rs3791298_rs16827500_Q_3.5,Yes_rs17040164_rs4853793_Q_8.5,No_rs17040164_x_10_5,Yes_rs17018796_x_10_5,No_rs17018796_rs7419176_Q_8.5,Yes_rs16827500_rs1565469_Q_8.5,No_rs16827500_rs2671264_Q_9.5,Yes_rs4853793_rs1249402_Q_7,No_rs4853793_x_10_5,Yes_rs7419176_x_10_5,No_rs7419176_x_2_5,Yes_rs1565469_x_2_5,No_rs1565469_x_10_5,Yes_rs2671264_x_2_5,No_rs2671264_rs12109110_Q_2.5,Yes_rs1249402_x_10_5,No_rs1249402_x_2_5,Yes_rs12109110_x_2_5,No_rs12109110_rs12084067_Q_6,Yes_rs12084067_x_10_5,No_rs12084067_x_2_5,\nCreate_rs11693502_Q_6,Yes_rs11693502_rs7168653_Q_6,No_rs11693502_rs7599054_Q_5.5,Yes_rs7168653_rs11831618_Q_1.5,No_rs7168653_rs2015330_Q_2.5,Yes_rs7599054_rs6029050_Q_6,No_rs7599054_rs1481742_Q_8.5,Yes_rs11831618_x_10_5,No_rs11831618_x_2_5,Yes_rs2015330_x_10_5,No_rs2015330_x_2_5,Yes_rs6029050_rs17048875_Q_3.5,No_rs6029050_x_10_5,Yes_rs1481742_rs35940137_Q_5.5,No_rs1481742_rs16865298_Q_2,Yes_rs17048875_x_10_5,No_rs17048875_rs7981968_Q_8.5,Yes_rs35940137_x_2_5,No_rs35940137_x_10_5,Yes_rs16865298_x_2_5,No_rs16865298_x_10_5,Yes_rs7981968_rs17123422_Q_6,No_rs7981968_x_10_5,Yes_rs17123422_rs7540503_Q_6,No_rs17123422_x_10_5,Yes_rs7540503_x_2_5,No_rs7540503_x_10_5,\nCreate_rs12988076_Q_3.5,Yes_rs12988076_rs11687599_Q_5.5,No_rs12988076_rs233253_Q_2,Yes_rs11687599_rs7568884_Q_8.5,No_rs11687599_rs12053389_Q_1.5,Yes_rs233253_rs3828267_Q_8.5,No_rs233253_x_2_5,Yes_rs7568884_rs4799085_Q_6,No_rs7568884_rs1333717_Q_2,Yes_rs12053389_x_2_5,No_rs12053389_x_10_5,Yes_rs3828267_x_2_5,No_rs3828267_rs4654598_Q_2,Yes_rs4799085_rs2395634_Q_2,No_rs4799085_rs1192579_Q_8.5,Yes_rs1333717_x_10_5,No_rs1333717_x_2_5,Yes_rs4654598_x_2_5,No_rs4654598_x_10_5,Yes_rs2395634_rs2649071_Q_2,No_rs2395634_rs17099679_Q_5.5,Yes_rs1192579_x_2_5,No_rs1192579_x_10_5,Yes_rs2649071_x_10_5,No_rs2649071_x_2_5,Yes_rs17099679_rs11591221_Q_6,No_rs17099679_x_10_5,Yes_rs11591221_x_2_5,No_rs11591221_x_10_5,\nCreate_rs6719488_Q_8.5,Yes_rs6719488_rs461436_Q_6,No_rs6719488_rs10204606_Q_2,Yes_rs461436_rs4666782_Q_2,No_rs461436_x_2_5,Yes_rs10204606_rs615861_Q_6,No_rs10204606_rs4954573_Q_8.5,Yes_rs4666782_rs7537345_Q_2,No_rs4666782_x_2_5,Yes_rs615861_x_2_5,No_rs615861_x_10_5,Yes_rs4954573_rs4952541_Q_1.5,No_rs4954573_rs17091427_Q_8.5,Yes_rs7537345_x_2_5,No_rs7537345_x_10_5,Yes_rs4952541_x_2_5,No_rs4952541_x_10_5,Yes_rs17091427_x_10_5,No_rs17091427_rs13143297_Q_6,Yes_rs13143297_rs12905660_Q_6,No_rs13143297_x_10_5,Yes_rs12905660_x_10_5,No_rs12905660_rs1031466_Q_8.5,Yes_rs1031466_x_10_5,No_rs1031466_x_2_5,\n";
		//North American 12 trees
		//std::string treeInfo = "Create_rs35389_Q_2,Yes_rs35389_rs11147417_Q_8.5,No_rs35389_rs2814778_Q_8.5,Yes_rs11147417_rs12038297_Q_1.5,No_rs11147417_rs8081204_Q_2,Yes_rs2814778_rs1335762_Q_6,No_rs2814778_rs1800414_Q_8.5,Yes_rs12038297_x_8_5,No_rs12038297_x_1_5,Yes_rs8081204_rs10969597_Q_9.5,No_rs8081204_x_5_5,Yes_rs1335762_x_8_5,No_rs1335762_x_1_5,Yes_rs1800414_rs6603781_Q_5.5,No_rs1800414_rs4870227_Q_7,Yes_rs10969597_x_1_5,No_rs10969597_rs17031150_Q_8.5,Yes_rs6603781_x_5_5,No_rs6603781_x_4_5,Yes_rs4870227_rs10961635_Q_8.5,No_rs4870227_rs3776334_Q_5.5,Yes_rs17031150_x_2_5,No_rs17031150_x_8_5,Yes_rs10961635_x_5_5,No_rs10961635_rs2292857_Q_5.5,Yes_rs3776334_rs1798246_Q_1.5,No_rs3776334_rs16846854_Q_8.5,Yes_rs2292857_x_4_5,No_rs2292857_x_8_5,Yes_rs1798246_x_8_5,No_rs1798246_x_4_5,Yes_rs16846854_rs4310388_Q_8.5,No_rs16846854_rs1384182_Q_7,Yes_rs4310388_x_2_5,No_rs4310388_x_8_5,Yes_rs1384182_x_2_5,No_rs1384182_rs12568035_Q_6,Yes_rs12568035_x_5_5,No_rs12568035_x_8_5,\nCreate_rs5751131_Q_2,Yes_rs5751131_rs2829003_Q_1.5,No_rs5751131_rs873927_Q_5.5,Yes_rs2829003_rs35391_Q_6,No_rs2829003_rs6577401_Q_8.5,Yes_rs873927_x_8_5,No_rs873927_x_4_5,Yes_rs35391_rs7154864_Q_5.5,No_rs35391_rs1133238_Q_5.5,Yes_rs6577401_x_1_5,No_rs6577401_x_8_5,Yes_rs7154864_rs4906743_Q_5.5,No_rs7154864_rs17027638_Q_2,Yes_rs1133238_rs2303170_Q_2,No_rs1133238_rs4930431_Q_6,Yes_rs4906743_rs9729550_Q_3.5,No_rs4906743_rs2254669_Q_5.5,Yes_rs17027638_rs2519_Q_6,No_rs17027638_rs2793661_Q_6,Yes_rs2303170_x_5_5,No_rs2303170_x_4_5,Yes_rs4930431_rs672463_Q_6,No_rs4930431_rs12685829_Q_5.5,Yes_rs9729550_x_5_5,No_rs9729550_x_4_5,Yes_rs2254669_x_8_5,No_rs2254669_x_4_5,Yes_rs2519_rs3737718_Q_5.5,No_rs2519_x_8_5,Yes_rs2793661_x_8_5,No_rs2793661_x_5_5,Yes_rs672463_x_4_5,No_rs672463_rs488612_Q_8.5,Yes_rs12685829_x_5_5,No_rs12685829_rs13376100_Q_8.5,Yes_rs3737718_x_4_5,No_rs3737718_x_2_5,Yes_rs488612_x_1_5,No_rs488612_x_5_5,Yes_rs13376100_x_8_5,No_rs13376100_x_2_5,\nCreate_rs5758402_Q_6,Yes_rs5758402_rs9893667_Q_8.5,No_rs5758402_rs3128342_Q_1.5,Yes_rs9893667_rs3947662_Q_9.5,No_rs9893667_rs28117_Q_2,Yes_rs3128342_x_4_5,No_rs3128342_x_8_5,Yes_rs3947662_x_1_5,No_rs3947662_x_8_5,Yes_rs28117_rs10245220_Q_5.5,No_rs28117_rs17084501_Q_8.5,Yes_rs10245220_rs12590812_Q_5.5,No_rs10245220_rs1396795_Q_5.5,Yes_rs17084501_rs2039242_Q_5.5,No_rs17084501_rs2032915_Q_8.5,Yes_rs12590812_rs3748592_Q_2,No_rs12590812_rs17742354_Q_3.5,Yes_rs1396795_rs1569635_Q_8.5,No_rs1396795_rs2183746_Q_8.5,Yes_rs2039242_x_5_5,No_rs2039242_rs6667248_Q_2,Yes_rs2032915_rs4871389_Q_8.5,No_rs2032915_rs973978_Q_5.5,Yes_rs3748592_x_5_5,No_rs3748592_x_8_5,Yes_rs17742354_x_2_5,No_rs17742354_rs2123694_Q_2,Yes_rs1569635_x_8_5,No_rs1569635_x_5_5,Yes_rs2183746_x_8_5,No_rs2183746_rs12043519_Q_6,Yes_rs6667248_x_8_5,No_rs6667248_x_1_5,Yes_rs4871389_x_8_5,No_rs4871389_rs9919220_Q_5.5,Yes_rs973978_x_8_5,No_rs973978_x_4_5,Yes_rs2123694_x_5_5,No_rs2123694_rs2643885_Q_1.5,Yes_rs12043519_x_2_5,No_rs12043519_x_5_5,Yes_rs9919220_x_5_5,No_rs9919220_x_4_5,Yes_rs2643885_x_1_5,No_rs2643885_x_4_5,\nCreate_rs1960182_Q_2,Yes_rs1960182_rs8078633_Q_5.5,No_rs1960182_rs2817185_Q_2,Yes_rs8078633_rs3848147_Q_2,No_rs8078633_rs11264025_Q_6,Yes_rs2817185_x_4_5,No_rs2817185_x_8_5,Yes_rs3848147_rs7134749_Q_8.5,No_rs3848147_rs10165208_Q_7,Yes_rs11264025_x_1_5,No_rs11264025_x_8_5,Yes_rs7134749_rs9573246_Q_6,No_rs7134749_rs11192637_Q_5.5,Yes_rs10165208_x_5_5,No_rs10165208_x_8_5,Yes_rs9573246_rs9442996_Q_5.5,No_rs9573246_rs12142199_Q_5.5,Yes_rs11192637_rs12075715_Q_3.5,No_rs11192637_rs11204853_Q_8.5,Yes_rs9442996_rs6685064_Q_6,No_rs9442996_rs6731591_Q_8.5,Yes_rs12142199_x_5_5,No_rs12142199_x_4_5,Yes_rs12075715_x_1_5,No_rs12075715_rs3795501_Q_6,Yes_rs11204853_rs4314833_Q_6,No_rs11204853_rs2904664_Q_6,Yes_rs6685064_x_2_5,No_rs6685064_x_5_5,Yes_rs6731591_x_5_5,No_rs6731591_rs6694203_Q_8.5,Yes_rs3795501_x_5_5,No_rs3795501_x_8_5,Yes_rs4314833_x_4_5,No_rs4314833_x_5_5,Yes_rs2904664_rs12411125_Q_6,No_rs2904664_x_5_5,Yes_rs6694203_x_2_5,No_rs6694203_x_8_5,Yes_rs12411125_x_2_5,No_rs12411125_x_8_5,\nCreate_rs2270068_Q_8.5,Yes_rs2270068_rs4790359_Q_6,No_rs2270068_rs9442235_Q_9.5,Yes_rs4790359_rs4833103_Q_3.5,No_rs4790359_rs11121722_Q_5.5,Yes_rs9442235_x_8_5,No_rs9442235_x_4_5,Yes_rs4833103_rs12467317_Q_5.5,No_rs4833103_rs12423495_Q_8.5,Yes_rs11121722_x_1_5,No_rs11121722_x_8_5,Yes_rs12467317_rs4970383_Q_1.5,No_rs12467317_rs4968239_Q_6,Yes_rs12423495_rs17640978_Q_8.5,No_rs12423495_rs917408_Q_8.5,Yes_rs4970383_x_1_5,No_rs4970383_x_8_5,Yes_rs4968239_rs6541124_Q_6,No_rs4968239_rs10737480_Q_9.5,Yes_rs17640978_rs9442619_Q_6,No_rs17640978_rs1338839_Q_9.5,Yes_rs917408_rs260698_Q_2,No_rs917408_x_8_5,Yes_rs6541124_x_2_5,No_rs6541124_x_5_5,Yes_rs10737480_x_8_5,No_rs10737480_x_2_5,Yes_rs9442619_x_8_5,No_rs9442619_x_4_5,Yes_rs1338839_x_2_5,No_rs1338839_x_5_5,Yes_rs260698_rs9803031_Q_8.5,No_rs260698_rs12097368_Q_8.5,Yes_rs9803031_x_1_5,No_rs9803031_x_4_5,Yes_rs12097368_rs7541544_Q_8.5,No_rs12097368_rs522821_Q_5.5,Yes_rs7541544_x_5_5,No_rs7541544_x_8_5,Yes_rs522821_rs262680_Q_6,No_rs522821_rs6696281_Q_6,Yes_rs262680_x_1_5,No_rs262680_x_8_5,Yes_rs6696281_x_2_5,No_rs6696281_x_4_5,\nCreate_rs6500380_Q_2,Yes_rs6500380_rs738989_Q_1.5,No_rs6500380_rs17007466_Q_9.5,Yes_rs738989_x_4_5,No_rs738989_rs4644548_Q_6,Yes_rs17007466_rs2606411_Q_8.5,No_rs17007466_rs12484869_Q_5.5,Yes_rs4644548_x_8_5,No_rs4644548_x_5_5,Yes_rs2606411_x_1_5,No_rs2606411_x_2_5,Yes_rs12484869_rs2281173_Q_2,No_rs12484869_rs911445_Q_9.5,Yes_rs2281173_x_4_5,No_rs2281173_x_8_5,Yes_rs911445_rs11636232_Q_6,No_rs911445_rs35411_Q_2,Yes_rs11636232_rs926144_Q_2,No_rs11636232_rs11748410_Q_6,Yes_rs35411_rs3767908_Q_2,No_rs35411_rs2059696_Q_2,Yes_rs926144_rs12875618_Q_2,No_rs926144_rs3213221_Q_7,Yes_rs11748410_x_2_5,No_rs11748410_x_8_5,Yes_rs3767908_rs12039666_Q_6,No_rs3767908_x_1_5,Yes_rs2059696_rs3737721_Q_2,No_rs2059696_x_8_5,Yes_rs12875618_x_5_5,No_rs12875618_x_2_5,Yes_rs3213221_rs12410046_Q_5.5,No_rs3213221_x_8_5,Yes_rs12039666_x_2_5,No_rs12039666_x_5_5,Yes_rs3737721_x_1_5,No_rs3737721_x_4_5,Yes_rs12410046_x_4_5,No_rs12410046_rs17160669_Q_6,Yes_rs17160669_x_2_5,No_rs17160669_x_5_5,\nCreate_rs7552141_Q_2,Yes_rs7552141_rs1374821_Q_6,No_rs7552141_rs41388954_Q_7,Yes_rs1374821_rs6717424_Q_2,No_rs1374821_rs11637114_Q_6,Yes_rs41388954_x_8_5,No_rs41388954_x_1_5,Yes_rs6717424_rs2500283_Q_5.5,No_rs6717424_rs1498111_Q_2,Yes_rs11637114_rs4436808_Q_5.5,No_rs11637114_rs1865164_Q_2,Yes_rs2500283_x_4_5,No_rs2500283_x_8_5,Yes_rs1498111_rs1240708_Q_2,No_rs1498111_x_8_5,Yes_rs4436808_rs10835271_Q_2,No_rs4436808_rs1524007_Q_8.5,Yes_rs1865164_rs9329417_Q_6,No_rs1865164_x_1_5,Yes_rs1240708_x_2_5,No_rs1240708_x_5_5,Yes_rs10835271_rs11120943_Q_5.5,No_rs10835271_rs2483275_Q_6,Yes_rs1524007_rs11119881_Q_3.5,No_rs1524007_rs5743567_Q_5.5,Yes_rs9329417_x_2_5,No_rs9329417_x_5_5,Yes_rs11120943_x_2_5,No_rs11120943_x_8_5,Yes_rs2483275_x_4_5,No_rs2483275_x_5_5,Yes_rs11119881_x_5_5,No_rs11119881_rs7759248_Q_6,Yes_rs5743567_rs3766178_Q_6,No_rs5743567_rs6732285_Q_1.5,Yes_rs7759248_rs4958560_Q_8.5,No_rs7759248_x_8_5,Yes_rs3766178_x_5_5,No_rs3766178_x_8_5,Yes_rs6732285_rs11965097_Q_6,No_rs6732285_x_5_5,Yes_rs4958560_x_2_5,No_rs4958560_rs2651927_Q_1.5,Yes_rs11965097_rs4245756_Q_6,No_rs11965097_x_8_5,Yes_rs2651927_x_5_5,No_rs2651927_x_1_5,Yes_rs4245756_x_2_5,No_rs4245756_x_1_5,\nCreate_rs7588439_Q_2,Yes_rs7588439_rs3776329_Q_5.5,No_rs7588439_rs7517585_Q_6,Yes_rs3776329_rs6053122_Q_2,No_rs3776329_rs210780_Q_6,Yes_rs7517585_x_8_5,No_rs7517585_x_1_5,Yes_rs6053122_rs10777469_Q_2,No_rs6053122_rs4819094_Q_9.5,Yes_rs210780_x_4_5,No_rs210780_rs4648808_Q_6,Yes_rs10777469_rs4678073_Q_1.5,No_rs10777469_rs1246828_Q_5.5,Yes_rs4819094_rs10749549_Q_2,No_rs4819094_rs13378757_Q_2,Yes_rs4648808_x_8_5,No_rs4648808_x_1_5,Yes_rs4678073_rs8007618_Q_8.5,No_rs4678073_rs4851370_Q_6,Yes_rs1246828_x_5_5,No_rs1246828_rs6663420_Q_6,Yes_rs10749549_x_4_5,No_rs10749549_rs12294859_Q_8.5,Yes_rs13378757_rs638425_Q_8.5,No_rs13378757_x_2_5,Yes_rs8007618_rs1363845_Q_2,No_rs8007618_rs3748593_Q_3.5,Yes_rs4851370_x_5_5,No_rs4851370_x_8_5,Yes_rs6663420_x_4_5,No_rs6663420_x_8_5,Yes_rs12294859_x_8_5,No_rs12294859_rs1465221_Q_5.5,Yes_rs638425_x_5_5,No_rs638425_x_2_5,Yes_rs1363845_rs6932667_Q_2,No_rs1363845_x_5_5,Yes_rs3748593_x_8_5,No_rs3748593_x_5_5,Yes_rs1465221_x_2_5,No_rs1465221_rs13302982_Q_2,Yes_rs6932667_x_8_5,No_rs6932667_x_2_5,Yes_rs13302982_x_1_5,No_rs13302982_x_5_5,\nCreate_rs16941717_Q_1.5,Yes_rs16941717_rs7214357_Q_5.5,No_rs16941717_rs6804194_Q_8.5,Yes_rs7214357_rs2651912_Q_8.5,No_rs7214357_rs10962599_Q_6,Yes_rs6804194_rs28570376_Q_5.5,No_rs6804194_rs11466691_Q_8.5,Yes_rs2651912_x_1_5,No_rs2651912_x_8_5,Yes_rs10962599_rs12595731_Q_5.5,No_rs10962599_rs4669937_Q_5.5,Yes_rs28570376_x_1_5,No_rs28570376_x_8_5,Yes_rs11466691_x_5_5,No_rs11466691_x_4_5,Yes_rs12595731_rs1439464_Q_5.5,No_rs12595731_rs3814226_Q_5.5,Yes_rs4669937_rs2377982_Q_8.5,No_rs4669937_rs1396797_Q_5.5,Yes_rs1439464_x_4_5,No_rs1439464_x_5_5,Yes_rs3814226_rs10910034_Q_8.5,No_rs3814226_rs2891125_Q_5.5,Yes_rs2377982_rs331728_Q_5.5,No_rs2377982_rs10917234_Q_2,Yes_rs1396797_rs2083838_Q_5.5,No_rs1396797_rs17348860_Q_6,Yes_rs10910034_x_4_5,No_rs10910034_x_5_5,Yes_rs2891125_rs10889634_Q_2,No_rs2891125_rs3737829_Q_2,Yes_rs331728_x_2_5,No_rs331728_rs3131972_Q_2,Yes_rs10917234_x_2_5,No_rs10917234_x_8_5,Yes_rs2083838_rs2051548_Q_6,No_rs2083838_x_5_5,Yes_rs17348860_x_8_5,No_rs17348860_x_2_5,Yes_rs10889634_rs4040604_Q_8.5,No_rs10889634_rs2244013_Q_5.5,Yes_rs3737829_x_8_5,No_rs3737829_x_1_5,Yes_rs3131972_x_1_5,No_rs3131972_x_5_5,Yes_rs2051548_x_2_5,No_rs2051548_x_8_5,Yes_rs4040604_x_4_5,No_rs4040604_x_5_5,Yes_rs2244013_x_1_5,No_rs2244013_x_2_5,\nCreate_rs609096_Q_5.5,Yes_rs609096_rs9907225_Q_6,No_rs609096_rs13397666_Q_5.5,Yes_rs9907225_rs8053650_Q_6,No_rs9907225_rs7782345_Q_9.5,Yes_rs13397666_rs6445254_Q_2,No_rs13397666_rs12059795_Q_8.5,Yes_rs8053650_rs7860104_Q_2,No_rs8053650_rs1016101_Q_5.5,Yes_rs7782345_x_1_5,No_rs7782345_x_8_5,Yes_rs6445254_rs7552342_Q_8.5,No_rs6445254_rs10752748_Q_5.5,Yes_rs12059795_x_8_5,No_rs12059795_x_4_5,Yes_rs7860104_rs164736_Q_3.5,No_rs7860104_rs16841094_Q_2,Yes_rs1016101_rs2235536_Q_8.5,No_rs1016101_rs274751_Q_8.5,Yes_rs7552342_x_5_5,No_rs7552342_x_1_5,Yes_rs10752748_x_4_5,No_rs10752748_x_8_5,Yes_rs164736_x_8_5,No_rs164736_rs2274264_Q_5.5,Yes_rs16841094_rs4624679_Q_1.5,No_rs16841094_rs1861_Q_3.5,Yes_rs2235536_x_8_5,No_rs2235536_x_5_5,Yes_rs274751_rs2840530_Q_2,No_rs274751_rs6681741_Q_6,Yes_rs2274264_x_5_5,No_rs2274264_rs11211329_Q_2,Yes_rs4624679_x_8_5,No_rs4624679_rs35242196_Q_3.5,Yes_rs1861_x_2_5,No_rs1861_x_5_5,Yes_rs2840530_x_1_5,No_rs2840530_x_8_5,Yes_rs6681741_x_5_5,No_rs6681741_x_8_5,Yes_rs11211329_rs10492944_Q_8.5,No_rs11211329_x_8_5,Yes_rs35242196_x_5_5,No_rs35242196_x_2_5,Yes_rs10492944_x_2_5,No_rs10492944_x_5_5,\nCreate_rs9896466_Q_5.5,Yes_rs9896466_rs2802774_Q_3.5,No_rs9896466_rs4668272_Q_5.5,Yes_rs2802774_x_1_5,No_rs2802774_x_8_5,Yes_rs4668272_rs1007916_Q_8.5,No_rs4668272_rs10008032_Q_6,Yes_rs1007916_rs1881559_Q_3.5,No_rs1007916_rs3855955_Q_5.5,Yes_rs10008032_rs17425081_Q_5.5,No_rs10008032_rs310373_Q_6,Yes_rs1881559_x_8_5,No_rs1881559_x_5_5,Yes_rs3855955_x_8_5,No_rs3855955_x_4_5,Yes_rs17425081_rs16870076_Q_8.5,No_rs17425081_rs7582192_Q_5.5,Yes_rs310373_rs11198214_Q_7,No_rs310373_rs6439472_Q_8.5,Yes_rs16870076_x_8_5,No_rs16870076_x_2_5,Yes_rs7582192_rs425277_Q_8.5,No_rs7582192_rs12108234_Q_2,Yes_rs11198214_x_8_5,No_rs11198214_rs3860318_Q_2.5,Yes_rs6439472_rs7407_Q_6,No_rs6439472_x_5_5,Yes_rs425277_x_2_5,No_rs425277_x_8_5,Yes_rs12108234_rs9557355_Q_8.5,No_rs12108234_rs10173594_Q_2,Yes_rs3860318_x_2_5,No_rs3860318_x_5_5,Yes_rs7407_x_2_5,No_rs7407_x_8_5,Yes_rs9557355_rs11582339_Q_9.5,No_rs9557355_x_2_5,Yes_rs10173594_rs367673_Q_7,No_rs10173594_rs4475691_Q_8.5,Yes_rs11582339_rs6669870_Q_8.5,No_rs11582339_x_2_5,Yes_rs367673_rs351619_Q_2,No_rs367673_x_4_5,Yes_rs4475691_x_8_5,No_rs4475691_x_5_5,Yes_rs6669870_x_5_5,No_rs6669870_x_4_5,Yes_rs351619_x_1_5,No_rs351619_rs7290_Q_8.5,Yes_rs7290_x_5_5,No_rs7290_x_2_5,\nCreate_rs220486_Q_5.5,Yes_rs220486_rs2298225_Q_3.5,No_rs220486_rs3776337_Q_7,Yes_rs2298225_x_8_5,No_rs2298225_x_1_5,Yes_rs3776337_rs1888913_Q_9.5,No_rs3776337_rs6038071_Q_6,Yes_rs1888913_x_1_5,No_rs1888913_rs35940137_Q_5.5,Yes_rs6038071_rs715846_Q_2,No_rs6038071_rs2292051_Q_2,Yes_rs35940137_x_5_5,No_rs35940137_x_4_5,Yes_rs715846_rs10025344_Q_5.5,No_rs715846_rs2691483_Q_6,Yes_rs2292051_rs692902_Q_6,No_rs2292051_rs11707443_Q_7,Yes_rs10025344_rs1704348_Q_8.5,No_rs10025344_rs5004864_Q_9.5,Yes_rs2691483_x_4_5,No_rs2691483_rs2905036_Q_8.5,Yes_rs692902_rs1858104_Q_5.5,No_rs692902_rs35958305_Q_9.5,Yes_rs11707443_x_4_5,No_rs11707443_rs2055204_Q_2,Yes_rs1704348_rs679563_Q_2,No_rs1704348_rs1926883_Q_2,Yes_rs5004864_rs9331225_Q_6,No_rs5004864_rs17128262_Q_5.5,Yes_rs2905036_x_1_5,No_rs2905036_x_8_5,Yes_rs1858104_x_2_5,No_rs1858104_rs12028663_Q_6,Yes_rs35958305_x_2_5,No_rs35958305_x_5_5,Yes_rs2055204_x_8_5,No_rs2055204_x_2_5,Yes_rs679563_x_5_5,No_rs679563_x_1_5,Yes_rs1926883_x_8_5,No_rs1926883_x_4_5,Yes_rs9331225_x_5_5,No_rs9331225_x_1_5,Yes_rs17128262_x_8_5,No_rs17128262_rs916977_Q_8.5,Yes_rs12028663_x_5_5,No_rs12028663_x_4_5,Yes_rs916977_x_2_5,No_rs916977_x_5_5,\n";
		//African 22 trees
		std::string treeInfo = "Create_rs16855615_Q_5.5,Yes_rs16855615_rs17030159_Q_2,No_rs16855615_rs199138_Q_2,Yes_rs17030159_rs9619574_Q_2,No_rs17030159_x_7_5,Yes_rs199138_rs12701555_Q_5.5,No_rs199138_rs367645_Q_5.5,Yes_rs9619574_x_7_5,No_rs9619574_rs7316060_Q_6,Yes_rs12701555_rs803137_Q_5.5,No_rs12701555_rs13081915_Q_8.5,Yes_rs367645_rs11828501_Q_8.5,No_rs367645_rs4815694_Q_8.5,Yes_rs7316060_rs4130091_Q_8.5,No_rs7316060_x_7_5,Yes_rs803137_rs6694982_Q_4.5,No_rs803137_rs4819836_Q_5.5,Yes_rs13081915_rs9970652_Q_6,No_rs13081915_rs11735775_Q_8.5,Yes_rs11828501_rs852619_Q_6,No_rs11828501_x_11_5,Yes_rs4815694_x_9_5,No_rs4815694_x_11_5,Yes_rs4130091_x_9_5,No_rs4130091_x_11_5,Yes_rs6694982_x_9_5,No_rs6694982_x_11_5,Yes_rs4819836_rs1546260_Q_8.5,No_rs4819836_rs7514979_Q_6,Yes_rs9970652_x_7_5,No_rs9970652_x_9_5,Yes_rs11735775_rs6660514_Q_8.5,No_rs11735775_rs1679012_Q_6,Yes_rs852619_x_7_5,No_rs852619_x_9_5,Yes_rs1546260_x_7_5,No_rs1546260_x_11_5,Yes_rs7514979_x_7_5,No_rs7514979_x_11_5,Yes_rs6660514_x_7_5,No_rs6660514_x_11_5,Yes_rs1679012_rs9290877_Q_8.5,No_rs1679012_x_9_5,Yes_rs9290877_x_7_5,No_rs9290877_rs12561320_Q_1.5,Yes_rs12561320_x_11_5,No_rs12561320_x_7_5,\nCreate_rs4954207_Q_2.5,Yes_rs4954207_rs1901747_Q_6,No_rs4954207_rs28464695_Q_8.5,Yes_rs1901747_rs6944302_Q_6,No_rs1901747_rs7039873_Q_6,Yes_rs28464695_rs17741623_Q_8.5,No_rs28464695_rs9486141_Q_9.5,Yes_rs6944302_rs12005198_Q_2,No_rs6944302_rs7914354_Q_2,Yes_rs7039873_rs525448_Q_5.5,No_rs7039873_rs10915430_Q_6,Yes_rs17741623_x_9_5,No_rs17741623_x_7_5,Yes_rs9486141_x_7_5,No_rs9486141_rs16855847_Q_5.5,Yes_rs12005198_rs16862376_Q_8.5,No_rs12005198_rs6657290_Q_7,Yes_rs7914354_rs7155859_Q_8.5,No_rs7914354_rs752965_Q_6,Yes_rs525448_x_9_5,No_rs525448_x_7_5,Yes_rs10915430_x_11_5,No_rs10915430_x_7_5,Yes_rs16855847_x_11_5,No_rs16855847_rs3813199_Q_2,Yes_rs16862376_rs1725501_Q_8.5,No_rs16862376_rs17007536_Q_2,Yes_rs6657290_x_11_5,No_rs6657290_x_7_5,Yes_rs7155859_x_7_5,No_rs7155859_rs12191383_Q_1.5,Yes_rs752965_x_7_5,No_rs752965_x_9_5,Yes_rs3813199_x_7_5,No_rs3813199_x_9_5,Yes_rs1725501_rs17160975_Q_8.5,No_rs1725501_rs4732511_Q_6,Yes_rs17007536_x_11_5,No_rs17007536_x_9_5,Yes_rs12191383_rs589870_Q_8.5,No_rs12191383_x_7_5,Yes_rs17160975_x_9_5,No_rs17160975_x_7_5,Yes_rs4732511_x_7_5,No_rs4732511_rs2842909_Q_6,Yes_rs589870_x_11_5,No_rs589870_x_7_5,Yes_rs2842909_x_11_5,No_rs2842909_x_7_5,\nCreate_rs12614459_Q_8.5,Yes_rs12614459_rs10205050_Q_8.5,No_rs12614459_rs2227282_Q_5.5,Yes_rs10205050_rs6687835_Q_6,No_rs10205050_rs532885_Q_7,Yes_rs2227282_rs11975980_Q_8.5,No_rs2227282_rs544870_Q_5.5,Yes_rs6687835_x_11_5,No_rs6687835_x_7_5,Yes_rs532885_x_7_5,No_rs532885_rs16900601_Q_2,Yes_rs11975980_rs3039743_Q_6,No_rs11975980_rs2227914_Q_8.5,Yes_rs544870_x_11_5,No_rs544870_x_9_5,Yes_rs16900601_x_7_5,No_rs16900601_rs6684149_Q_8.5,Yes_rs3039743_rs4142753_Q_5.5,No_rs3039743_x_7_5,Yes_rs2227914_rs2815617_Q_6,No_rs2227914_rs1459157_Q_6,Yes_rs6684149_x_9_5,No_rs6684149_x_11_5,Yes_rs4142753_x_11_5,No_rs4142753_x_7_5,Yes_rs2815617_x_7_5,No_rs2815617_x_11_5,Yes_rs1459157_rs4987672_Q_6,No_rs1459157_rs6426370_Q_9.5,Yes_rs4987672_rs10832430_Q_5.5,No_rs4987672_rs8028686_Q_8.5,Yes_rs6426370_x_7_5,No_rs6426370_x_9_5,Yes_rs10832430_x_7_5,No_rs10832430_rs3935892_Q_3.5,Yes_rs8028686_rs6691985_Q_6,No_rs8028686_rs1956593_Q_8.5,Yes_rs3935892_x_7_5,No_rs3935892_x_11_5,Yes_rs6691985_x_11_5,No_rs6691985_x_7_5,Yes_rs1956593_x_9_5,No_rs1956593_rs7753502_Q_6,Yes_rs7753502_x_11_5,No_rs7753502_rs1739855_Q_8.5,Yes_rs1739855_x_7_5,No_rs1739855_x_9_5,\nCreate_rs12135523_Q_2,Yes_rs12135523_rs6759948_Q_5.5,No_rs12135523_rs7741503_Q_5.5,Yes_rs6759948_rs1523794_Q_8.5,No_rs6759948_rs17646556_Q_8.5,Yes_rs7741503_rs4845735_Q_2,No_rs7741503_rs7589010_Q_7,Yes_rs1523794_rs9583470_Q_2,No_rs1523794_rs10828213_Q_8.5,Yes_rs17646556_rs10754901_Q_6,No_rs17646556_rs4242609_Q_5.5,Yes_rs4845735_x_7_5,No_rs4845735_x_11_5,Yes_rs7589010_rs7531583_Q_2,No_rs7589010_rs7010482_Q_2,Yes_rs9583470_rs2476949_Q_2,No_rs9583470_x_7_5,Yes_rs10828213_rs6696281_Q_6,No_rs10828213_x_7_5,Yes_rs10754901_x_9_5,No_rs10754901_x_7_5,Yes_rs4242609_rs11702338_Q_6,No_rs4242609_rs6800015_Q_8.5,Yes_rs7531583_x_7_5,No_rs7531583_x_9_5,Yes_rs7010482_x_9_5,No_rs7010482_x_7_5,Yes_rs2476949_x_7_5,No_rs2476949_rs2905036_Q_6,Yes_rs6696281_x_7_5,No_rs6696281_x_11_5,Yes_rs11702338_x_9_5,No_rs11702338_rs11807848_Q_6,Yes_rs6800015_rs28499371_Q_6,No_rs6800015_rs4894197_Q_5.5,Yes_rs2905036_x_11_5,No_rs2905036_x_9_5,Yes_rs11807848_x_11_5,No_rs11807848_x_7_5,Yes_rs28499371_x_7_5,No_rs28499371_x_9_5,Yes_rs4894197_x_7_5,No_rs4894197_rs13087319_Q_5.5,Yes_rs13087319_x_7_5,No_rs13087319_rs11544855_Q_8.5,Yes_rs11544855_x_7_5,No_rs11544855_rs1443670_Q_2,Yes_rs1443670_x_7_5,No_rs1443670_x_11_5,\nCreate_rs309172_Q_5.5,Yes_rs309172_rs6591090_Q_2,No_rs309172_rs1364519_Q_2,Yes_rs6591090_rs422584_Q_2,No_rs6591090_rs11823218_Q_3.5,Yes_rs1364519_rs6734110_Q_8.5,No_rs1364519_rs2057969_Q_8.5,Yes_rs422584_rs2270013_Q_2,No_rs422584_rs875060_Q_5.5,Yes_rs11823218_x_7_5,No_rs11823218_rs4648524_Q_8.5,Yes_rs6734110_x_7_5,No_rs6734110_rs316671_Q_3.5,Yes_rs2057969_x_7_5,No_rs2057969_x_9_5,Yes_rs2270013_rs7946936_Q_8.5,No_rs2270013_x_7_5,Yes_rs875060_rs349558_Q_2.5,No_rs875060_rs1039027_Q_5.5,Yes_rs4648524_x_7_5,No_rs4648524_x_9_5,Yes_rs316671_x_9_5,No_rs316671_x_11_5,Yes_rs7946936_x_7_5,No_rs7946936_rs13403738_Q_9.5,Yes_rs349558_rs6779590_Q_5.5,No_rs349558_rs6547187_Q_5.5,Yes_rs1039027_x_9_5,No_rs1039027_rs4946158_Q_5.5,Yes_rs13403738_rs12405691_Q_2,No_rs13403738_x_7_5,Yes_rs6779590_x_11_5,No_rs6779590_rs7185017_Q_6,Yes_rs6547187_rs1776037_Q_6,No_rs6547187_x_9_5,Yes_rs4946158_x_7_5,No_rs4946158_rs6671001_Q_8.5,Yes_rs12405691_x_11_5,No_rs12405691_x_7_5,Yes_rs7185017_x_11_5,No_rs7185017_rs552006_Q_5.5,Yes_rs1776037_x_7_5,No_rs1776037_x_11_5,Yes_rs6671001_x_11_5,No_rs6671001_x_7_5,Yes_rs552006_x_7_5,No_rs552006_x_11_5,\nCreate_rs309143_Q_5.5,Yes_rs309143_rs1051388_Q_2,No_rs309143_rs6099216_Q_6,Yes_rs1051388_rs385521_Q_2,No_rs1051388_rs10022017_Q_6,Yes_rs6099216_rs7169337_Q_6,No_rs6099216_x_7_5,Yes_rs385521_rs12630974_Q_5.5,No_rs385521_rs8052388_Q_6,Yes_rs10022017_rs427811_Q_8.5,No_rs10022017_x_7_5,Yes_rs7169337_rs2191430_Q_3.5,No_rs7169337_x_7_5,Yes_rs12630974_x_7_5,No_rs12630974_rs965494_Q_6,Yes_rs8052388_rs7728894_Q_2,No_rs8052388_rs542650_Q_3.5,Yes_rs427811_x_7_5,No_rs427811_x_9_5,Yes_rs2191430_x_11_5,No_rs2191430_rs17038427_Q_7,Yes_rs965494_rs218892_Q_6,No_rs965494_x_7_5,Yes_rs7728894_rs417252_Q_8.5,No_rs7728894_rs881247_Q_2,Yes_rs542650_x_7_5,No_rs542650_rs2185886_Q_8.5,Yes_rs17038427_x_7_5,No_rs17038427_x_9_5,Yes_rs218892_x_11_5,No_rs218892_x_7_5,Yes_rs417252_rs6668399_Q_2,No_rs417252_rs404499_Q_2.5,Yes_rs881247_x_9_5,No_rs881247_x_11_5,Yes_rs2185886_x_11_5,No_rs2185886_x_7_5,Yes_rs6668399_x_9_5,No_rs6668399_rs7017705_Q_6,Yes_rs404499_rs3128689_Q_1.5,No_rs404499_rs935073_Q_2,Yes_rs7017705_x_11_5,No_rs7017705_rs12124406_Q_5.5,Yes_rs3128689_x_7_5,No_rs3128689_x_9_5,Yes_rs935073_x_9_5,No_rs935073_x_11_5,Yes_rs12124406_x_11_5,No_rs12124406_x_7_5,\nCreate_rs9953932_Q_5.5,Yes_rs9953932_rs12276848_Q_2,No_rs9953932_rs6430594_Q_5.5,Yes_rs12276848_rs2153900_Q_5.5,No_rs12276848_rs10847881_Q_5.5,Yes_rs6430594_rs11718932_Q_5.5,No_rs6430594_rs1995236_Q_5.5,Yes_rs2153900_x_11_5,No_rs2153900_x_7_5,Yes_rs10847881_rs11805412_Q_8.5,No_rs10847881_x_7_5,Yes_rs11718932_rs12758773_Q_2,No_rs11718932_rs17450822_Q_5.5,Yes_rs1995236_rs1713712_Q_8.5,No_rs1995236_x_7_5,Yes_rs11805412_x_9_5,No_rs11805412_x_11_5,Yes_rs12758773_rs9988744_Q_8.5,No_rs12758773_rs28495286_Q_8.5,Yes_rs17450822_rs10890311_Q_6,No_rs17450822_rs2180698_Q_6,Yes_rs1713712_x_9_5,No_rs1713712_x_11_5,Yes_rs9988744_rs10932521_Q_2,No_rs9988744_rs4245542_Q_6,Yes_rs28495286_x_9_5,No_rs28495286_x_7_5,Yes_rs10890311_x_7_5,No_rs10890311_x_9_5,Yes_rs2180698_rs4926853_Q_2,No_rs2180698_x_7_5,Yes_rs10932521_rs17171218_Q_6,No_rs10932521_x_9_5,Yes_rs4245542_rs3817958_Q_8.5,No_rs4245542_rs1427150_Q_8.5,Yes_rs4926853_x_11_5,No_rs4926853_x_7_5,Yes_rs17171218_x_7_5,No_rs17171218_x_11_5,Yes_rs3817958_x_7_5,No_rs3817958_rs7590763_Q_6,Yes_rs1427150_x_11_5,No_rs1427150_rs1333190_Q_6,Yes_rs7590763_x_7_5,No_rs7590763_x_11_5,Yes_rs1333190_x_9_5,No_rs1333190_x_7_5,\nCreate_rs7573555_Q_8.5,Yes_rs7573555_rs842361_Q_5.5,No_rs7573555_rs7674434_Q_9.5,Yes_rs842361_rs968365_Q_2,No_rs842361_rs7284910_Q_6,Yes_rs7674434_rs11963526_Q_2,No_rs7674434_rs11125815_Q_5.5,Yes_rs968365_rs3795521_Q_6,No_rs968365_rs2658083_Q_6,Yes_rs7284910_rs9597104_Q_5.5,No_rs7284910_rs1407893_Q_5.5,Yes_rs11963526_rs7600669_Q_2,No_rs11963526_rs10915424_Q_5.5,Yes_rs11125815_x_9_5,No_rs11125815_rs11018181_Q_8.5,Yes_rs3795521_rs4648501_Q_2,No_rs3795521_x_7_5,Yes_rs2658083_x_9_5,No_rs2658083_x_7_5,Yes_rs9597104_x_7_5,No_rs9597104_rs13236792_Q_8.5,Yes_rs1407893_rs11121090_Q_6,No_rs1407893_rs17104047_Q_2,Yes_rs7600669_rs6854489_Q_6,No_rs7600669_x_7_5,Yes_rs10915424_x_11_5,No_rs10915424_x_7_5,Yes_rs11018181_rs6700924_Q_5.5,No_rs11018181_rs6446241_Q_5.5,Yes_rs4648501_x_7_5,No_rs4648501_x_11_5,Yes_rs13236792_x_11_5,No_rs13236792_rs11836193_Q_6,Yes_rs11121090_x_11_5,No_rs11121090_x_9_5,Yes_rs17104047_x_7_5,No_rs17104047_x_11_5,Yes_rs6854489_rs7730689_Q_3.5,No_rs6854489_rs11808336_Q_6,Yes_rs6700924_x_9_5,No_rs6700924_rs12757754_Q_5.5,Yes_rs6446241_x_7_5,No_rs6446241_x_11_5,Yes_rs11836193_x_7_5,No_rs11836193_x_9_5,Yes_rs7730689_rs12122894_Q_5.5,No_rs7730689_x_7_5,Yes_rs11808336_x_11_5,No_rs11808336_x_7_5,Yes_rs12757754_x_7_5,No_rs12757754_x_11_5,Yes_rs12122894_x_7_5,No_rs12122894_x_11_5,\nCreate_rs1834640_Q_5.5,Yes_rs1834640_rs6755409_Q_5.5,No_rs1834640_rs1374808_Q_2,Yes_rs6755409_rs6854417_Q_6,No_rs6755409_rs4851391_Q_7,Yes_rs1374808_rs316598_Q_6,No_rs1374808_rs1534110_Q_8.5,Yes_rs6854417_rs7538397_Q_8.5,No_rs6854417_x_7_5,Yes_rs4851391_x_11_5,No_rs4851391_x_7_5,Yes_rs316598_rs7649861_Q_2,No_rs316598_rs7534387_Q_6,Yes_rs1534110_rs897620_Q_5.5,No_rs1534110_x_7_5,Yes_rs7538397_x_9_5,No_rs7538397_x_7_5,Yes_rs7649861_rs1995209_Q_9.5,No_rs7649861_rs11980955_Q_5.5,Yes_rs7534387_x_9_5,No_rs7534387_x_7_5,Yes_rs897620_x_11_5,No_rs897620_x_9_5,Yes_rs1995209_x_7_5,No_rs1995209_rs10429529_Q_6,Yes_rs11980955_rs11060955_Q_6,No_rs11980955_rs9650996_Q_5.5,Yes_rs10429529_rs7739132_Q_5.5,No_rs10429529_x_7_5,Yes_rs11060955_x_11_5,No_rs11060955_x_7_5,Yes_rs9650996_x_11_5,No_rs9650996_rs2951787_Q_5.5,Yes_rs7739132_x_7_5,No_rs7739132_rs17404600_Q_8.5,Yes_rs2951787_x_9_5,No_rs2951787_rs16901558_Q_8.5,Yes_rs17404600_x_11_5,No_rs17404600_x_7_5,Yes_rs16901558_rs2477703_Q_8.5,No_rs16901558_rs2753922_Q_5.5,Yes_rs2477703_x_7_5,No_rs2477703_x_11_5,Yes_rs2753922_x_11_5,No_rs2753922_rs2494640_Q_7,Yes_rs2494640_x_7_5,No_rs2494640_x_9_5,\nCreate_rs309154_Q_8.5,Yes_rs309154_rs1942518_Q_1.5,No_rs309154_rs5770567_Q_6,Yes_rs1942518_rs7783639_Q_2,No_rs1942518_rs11603486_Q_6,Yes_rs5770567_rs12191891_Q_6,No_rs5770567_rs12079672_Q_2,Yes_rs7783639_rs11564096_Q_8.5,No_rs7783639_rs1416801_Q_6,Yes_rs11603486_x_7_5,No_rs11603486_rs12086132_Q_8.5,Yes_rs12191891_rs1798246_Q_3.5,No_rs12191891_rs7536376_Q_8.5,Yes_rs12079672_x_11_5,No_rs12079672_x_9_5,Yes_rs11564096_rs4699030_Q_5.5,No_rs11564096_rs9376452_Q_6,Yes_rs1416801_rs4366501_Q_8.5,No_rs1416801_x_7_5,Yes_rs12086132_x_7_5,No_rs12086132_x_9_5,Yes_rs1798246_x_7_5,No_rs1798246_x_11_5,Yes_rs7536376_x_11_5,No_rs7536376_rs2821059_Q_6,Yes_rs4699030_x_7_5,No_rs4699030_x_9_5,Yes_rs9376452_rs2040435_Q_6,No_rs9376452_rs5999984_Q_7,Yes_rs4366501_x_7_5,No_rs4366501_rs6665912_Q_8.5,Yes_rs2821059_x_9_5,No_rs2821059_x_7_5,Yes_rs2040435_rs11584727_Q_5.5,No_rs2040435_rs6007462_Q_5.5,Yes_rs5999984_rs1233320_Q_5.5,No_rs5999984_rs34065840_Q_8.5,Yes_rs6665912_x_7_5,No_rs6665912_x_11_5,Yes_rs11584727_x_11_5,No_rs11584727_x_7_5,Yes_rs6007462_rs10492940_Q_3.5,No_rs6007462_x_11_5,Yes_rs1233320_rs641347_Q_6,No_rs1233320_x_7_5,Yes_rs34065840_rs212989_Q_5.5,No_rs34065840_x_7_5,Yes_rs10492940_x_9_5,No_rs10492940_x_7_5,Yes_rs641347_x_9_5,No_rs641347_x_11_5,Yes_rs212989_x_11_5,No_rs212989_x_9_5,\nCreate_rs309161_Q_2,Yes_rs309161_rs12885391_Q_2,No_rs309161_rs4841471_Q_2,Yes_rs12885391_rs4909055_Q_5.5,No_rs12885391_rs10137272_Q_2.5,Yes_rs4841471_rs12191877_Q_6,No_rs4841471_rs17108678_Q_5.5,Yes_rs4909055_rs9434795_Q_8.5,No_rs4909055_rs2034357_Q_5.5,Yes_rs10137272_rs16910077_Q_2,No_rs10137272_x_7_5,Yes_rs12191877_rs1077052_Q_8.5,No_rs12191877_rs7596776_Q_5.5,Yes_rs17108678_x_7_5,No_rs17108678_x_9_5,Yes_rs9434795_x_9_5,No_rs9434795_x_7_5,Yes_rs2034357_rs9803031_Q_8.5,No_rs2034357_rs542727_Q_3.5,Yes_rs16910077_rs616317_Q_1.5,No_rs16910077_x_11_5,Yes_rs1077052_rs1389583_Q_9.5,No_rs1077052_rs2672609_Q_6,Yes_rs7596776_x_9_5,No_rs7596776_rs1067344_Q_8.5,Yes_rs9803031_x_11_5,No_rs9803031_x_7_5,Yes_rs542727_x_7_5,No_rs542727_x_9_5,Yes_rs616317_x_7_5,No_rs616317_x_9_5,Yes_rs1389583_x_7_5,No_rs1389583_x_9_5,Yes_rs2672609_rs11084467_Q_8.5,No_rs2672609_rs6558059_Q_8.5,Yes_rs1067344_rs9442619_Q_6,No_rs1067344_x_11_5,Yes_rs11084467_x_9_5,No_rs11084467_rs12502827_Q_5.5,Yes_rs6558059_rs9803031_Q_8.5,No_rs6558059_rs2624459_Q_5.5,Yes_rs9442619_x_7_5,No_rs9442619_x_9_5,Yes_rs12502827_x_7_5,No_rs12502827_rs10818338_Q_5.5,Yes_rs9803031_x_11_5,No_rs9803031_x_9_5,Yes_rs2624459_x_11_5,No_rs2624459_x_7_5,Yes_rs10818338_x_7_5,No_rs10818338_rs2377417_Q_2,Yes_rs2377417_x_7_5,No_rs2377417_x_11_5,\nCreate_rs12897140_Q_7,Yes_rs12897140_rs2240099_Q_8.5,No_rs12897140_rs10498587_Q_5.5,Yes_rs2240099_rs354742_Q_2,No_rs2240099_rs17595719_Q_8.5,Yes_rs10498587_rs17042596_Q_2,No_rs10498587_rs6967965_Q_8.5,Yes_rs354742_rs7010861_Q_5.5,No_rs354742_rs28391282_Q_5.5,Yes_rs17595719_x_9_5,No_rs17595719_rs2025319_Q_5.5,Yes_rs17042596_rs9331225_Q_8.5,No_rs17042596_x_7_5,Yes_rs6967965_rs6456890_Q_8.5,No_rs6967965_rs7686272_Q_7,Yes_rs7010861_rs16972211_Q_5.5,No_rs7010861_x_7_5,Yes_rs28391282_x_11_5,No_rs28391282_x_7_5,Yes_rs2025319_rs6682184_Q_5.5,No_rs2025319_rs242050_Q_5.5,Yes_rs9331225_x_9_5,No_rs9331225_x_7_5,Yes_rs6456890_x_7_5,No_rs6456890_rs2272634_Q_6,Yes_rs7686272_rs11711134_Q_2,No_rs7686272_rs6477310_Q_8.5,Yes_rs16972211_x_7_5,No_rs16972211_x_9_5,Yes_rs6682184_x_7_5,No_rs6682184_x_11_5,Yes_rs242050_x_11_5,No_rs242050_x_7_5,Yes_rs2272634_rs6690311_Q_2,No_rs2272634_x_9_5,Yes_rs11711134_rs11102559_Q_8.5,No_rs11711134_x_7_5,Yes_rs6477310_rs12033324_Q_3.5,No_rs6477310_rs10819101_Q_6,Yes_rs6690311_x_7_5,No_rs6690311_x_11_5,Yes_rs11102559_x_11_5,No_rs11102559_x_7_5,Yes_rs12033324_x_11_5,No_rs12033324_x_9_5,Yes_rs10819101_rs12071761_Q_5.5,No_rs10819101_rs13389290_Q_6,Yes_rs12071761_x_7_5,No_rs12071761_x_11_5,Yes_rs13389290_x_11_5,No_rs13389290_rs17301591_Q_6,Yes_rs17301591_rs17160698_Q_6,No_rs17301591_x_9_5,Yes_rs17160698_x_11_5,No_rs17160698_x_7_5,\nCreate_rs2982364_Q_6,Yes_rs2982364_rs1446750_Q_5.5,No_rs2982364_rs7177754_Q_2,Yes_rs1446750_rs10461322_Q_9.5,No_rs1446750_rs6659655_Q_2,Yes_rs7177754_rs10487094_Q_2,No_rs7177754_rs542634_Q_5.5,Yes_rs10461322_rs12408533_Q_2,No_rs10461322_rs17089059_Q_5.5,Yes_rs6659655_rs824602_Q_8.5,No_rs6659655_rs17729838_Q_7,Yes_rs10487094_x_7_5,No_rs10487094_rs16824722_Q_7,Yes_rs542634_x_7_5,No_rs542634_x_11_5,Yes_rs12408533_x_7_5,No_rs12408533_x_11_5,Yes_rs17089059_x_9_5,No_rs17089059_x_7_5,Yes_rs824602_rs7700264_Q_5.5,No_rs824602_rs950220_Q_3.5,Yes_rs17729838_rs3737718_Q_2,No_rs17729838_rs16848617_Q_2,Yes_rs16824722_x_9_5,No_rs16824722_x_11_5,Yes_rs7700264_rs11466673_Q_6,No_rs7700264_rs9290610_Q_8.5,Yes_rs950220_rs1607345_Q_5.5,No_rs950220_rs1935648_Q_5.5,Yes_rs3737718_x_7_5,No_rs3737718_x_9_5,Yes_rs16848617_rs10428090_Q_5.5,No_rs16848617_rs2459994_Q_8.5,Yes_rs11466673_x_11_5,No_rs11466673_x_9_5,Yes_rs9290610_x_9_5,No_rs9290610_rs16838604_Q_6,Yes_rs1607345_x_7_5,No_rs1607345_x_11_5,Yes_rs1935648_rs11807931_Q_8.5,No_rs1935648_x_9_5,Yes_rs10428090_rs11260568_Q_7,No_rs10428090_rs8064_Q_5.5,Yes_rs2459994_x_11_5,No_rs2459994_x_7_5,Yes_rs16838604_x_7_5,No_rs16838604_x_11_5,Yes_rs11807931_x_7_5,No_rs11807931_x_11_5,Yes_rs11260568_x_9_5,No_rs11260568_x_11_5,Yes_rs8064_rs17048953_Q_6,No_rs8064_x_9_5,Yes_rs17048953_x_11_5,No_rs17048953_rs3789052_Q_6,Yes_rs3789052_x_7_5,No_rs3789052_x_11_5,\nCreate_rs123187_Q_2,Yes_rs123187_rs10872503_Q_5.5,No_rs123187_rs9958746_Q_6,Yes_rs10872503_rs2913276_Q_8.5,No_rs10872503_rs7295341_Q_2,Yes_rs9958746_rs3106146_Q_2,No_rs9958746_rs13137543_Q_2,Yes_rs2913276_rs2182160_Q_7,No_rs2913276_rs9851767_Q_5.5,Yes_rs7295341_rs12039907_Q_2,No_rs7295341_rs10028900_Q_8.5,Yes_rs3106146_rs1417592_Q_5.5,No_rs3106146_rs485618_Q_6,Yes_rs13137543_rs10748260_Q_8.5,No_rs13137543_rs4648764_Q_8.5,Yes_rs2182160_rs6778401_Q_2,No_rs2182160_rs12478385_Q_9.5,Yes_rs9851767_x_9_5,No_rs9851767_x_7_5,Yes_rs12039907_rs3790221_Q_2,No_rs12039907_x_7_5,Yes_rs10028900_x_11_5,No_rs10028900_x_7_5,Yes_rs1417592_x_7_5,No_rs1417592_rs2562831_Q_8.5,Yes_rs485618_x_7_5,No_rs485618_x_11_5,Yes_rs10748260_rs2298217_Q_6,No_rs10748260_rs2817178_Q_6,Yes_rs4648764_x_7_5,No_rs4648764_x_11_5,Yes_rs6778401_rs12142199_Q_5.5,No_rs6778401_x_7_5,Yes_rs12478385_rs925192_Q_8.5,No_rs12478385_rs1258010_Q_5.5,Yes_rs3790221_rs12141832_Q_9.5,No_rs3790221_x_7_5,Yes_rs2562831_x_11_5,No_rs2562831_x_9_5,Yes_rs2298217_x_9_5,No_rs2298217_x_11_5,Yes_rs2817178_x_7_5,No_rs2817178_x_11_5,Yes_rs12142199_x_7_5,No_rs12142199_x_11_5,Yes_rs925192_x_9_5,No_rs925192_x_11_5,Yes_rs1258010_rs9697358_Q_5.5,No_rs1258010_x_11_5,Yes_rs12141832_x_7_5,No_rs12141832_rs11581548_Q_2,Yes_rs9697358_x_7_5,No_rs9697358_x_9_5,Yes_rs11581548_x_7_5,No_rs11581548_x_11_5,\nCreate_rs4787040_Q_2.5,Yes_rs4787040_rs12136407_Q_8.5,No_rs4787040_rs8041403_Q_8.5,Yes_rs12136407_rs2370791_Q_9.5,No_rs12136407_rs10864120_Q_5.5,Yes_rs8041403_rs11943281_Q_8.5,No_rs8041403_rs880724_Q_6,Yes_rs2370791_rs6667248_Q_2,No_rs2370791_rs771307_Q_5.5,Yes_rs10864120_rs9400909_Q_2,No_rs10864120_rs2388044_Q_8.5,Yes_rs11943281_rs17144015_Q_5.5,No_rs11943281_x_7_5,Yes_rs880724_x_11_5,No_rs880724_x_7_5,Yes_rs6667248_x_7_5,No_rs6667248_x_11_5,Yes_rs771307_x_9_5,No_rs771307_x_7_5,Yes_rs9400909_rs10992623_Q_8.5,No_rs9400909_rs870171_Q_9.5,Yes_rs2388044_rs2071958_Q_6,No_rs2388044_rs699486_Q_5.5,Yes_rs17144015_x_7_5,No_rs17144015_rs10907175_Q_3.5,Yes_rs10992623_rs7534913_Q_5.5,No_rs10992623_rs34052864_Q_6,Yes_rs870171_x_7_5,No_rs870171_x_9_5,Yes_rs2071958_x_11_5,No_rs2071958_x_7_5,Yes_rs699486_rs8892_Q_5.5,No_rs699486_rs10785426_Q_6,Yes_rs10907175_x_9_5,No_rs10907175_x_11_5,Yes_rs7534913_x_9_5,No_rs7534913_x_7_5,Yes_rs34052864_rs16862821_Q_7,No_rs34052864_x_7_5,Yes_rs8892_x_7_5,No_rs8892_rs2493314_Q_8.5,Yes_rs10785426_rs2693958_Q_6,No_rs10785426_rs714816_Q_5.5,Yes_rs16862821_x_7_5,No_rs16862821_rs7536226_Q_6,Yes_rs2493314_x_9_5,No_rs2493314_x_11_5,Yes_rs2693958_x_11_5,No_rs2693958_x_7_5,Yes_rs714816_x_9_5,No_rs714816_rs12093951_Q_8.5,Yes_rs7536226_rs1815606_Q_8.5,No_rs7536226_x_7_5,Yes_rs12093951_x_7_5,No_rs12093951_x_11_5,Yes_rs1815606_x_9_5,No_rs1815606_x_11_5,\nCreate_rs12204275_Q_9.5,Yes_rs12204275_rs6119337_Q_5.5,No_rs12204275_rs10454039_Q_6,Yes_rs6119337_rs2064662_Q_5.5,No_rs6119337_rs6785796_Q_8.5,Yes_rs10454039_rs9421731_Q_5.5,No_rs10454039_rs8035628_Q_2,Yes_rs2064662_x_11_5,No_rs2064662_x_7_5,Yes_rs6785796_x_7_5,No_rs6785796_x_9_5,Yes_rs9421731_rs6742013_Q_6,No_rs9421731_rs1793891_Q_6,Yes_rs8035628_rs12124819_Q_2,No_rs8035628_x_9_5,Yes_rs6742013_x_7_5,No_rs6742013_x_9_5,Yes_rs1793891_rs388401_Q_7,No_rs1793891_rs6067491_Q_2,Yes_rs12124819_x_7_5,No_rs12124819_x_9_5,Yes_rs388401_rs6848616_Q_2,No_rs388401_rs10867230_Q_3.5,Yes_rs6067491_rs4845820_Q_2,No_rs6067491_rs16849099_Q_8.5,Yes_rs6848616_rs10873649_Q_2,No_rs6848616_rs9660710_Q_1.5,Yes_rs10867230_rs816060_Q_2,No_rs10867230_rs11257434_Q_2,Yes_rs4845820_x_11_5,No_rs4845820_x_9_5,Yes_rs16849099_x_7_5,No_rs16849099_x_11_5,Yes_rs10873649_x_11_5,No_rs10873649_rs36044796_Q_3.5,Yes_rs9660710_x_7_5,No_rs9660710_x_11_5,Yes_rs816060_x_7_5,No_rs816060_x_9_5,Yes_rs11257434_rs7923866_Q_6,No_rs11257434_x_7_5,Yes_rs36044796_x_7_5,No_rs36044796_x_9_5,Yes_rs7923866_rs10204491_Q_5.5,No_rs7923866_x_7_5,Yes_rs10204491_rs242058_Q_8.5,No_rs10204491_x_7_5,Yes_rs242058_x_11_5,No_rs242058_x_7_5,\nCreate_rs6731365_Q_2,Yes_rs6731365_rs6932992_Q_5.5,No_rs6731365_rs7605229_Q_8.5,Yes_rs6932992_rs12620050_Q_5.5,No_rs6932992_rs10513545_Q_5.5,Yes_rs7605229_rs1241988_Q_8.5,No_rs7605229_rs6770324_Q_5.5,Yes_rs12620050_rs17796342_Q_6,No_rs12620050_rs6436964_Q_6,Yes_rs10513545_rs11654128_Q_5.5,No_rs10513545_rs8051251_Q_2,Yes_rs1241988_x_11_5,No_rs1241988_rs17030353_Q_2,Yes_rs6770324_rs3128117_Q_6,No_rs6770324_rs9975332_Q_8.5,Yes_rs17796342_rs2808651_Q_6,No_rs17796342_x_7_5,Yes_rs6436964_rs10799032_Q_8.5,No_rs6436964_rs1031567_Q_5.5,Yes_rs11654128_x_7_5,No_rs11654128_rs17376559_Q_5.5,Yes_rs8051251_rs309331_Q_8.5,No_rs8051251_rs3761364_Q_6,Yes_rs17030353_rs9415758_Q_2,No_rs17030353_x_7_5,Yes_rs3128117_x_7_5,No_rs3128117_x_11_5,Yes_rs9975332_rs10910061_Q_5.5,No_rs9975332_x_7_5,Yes_rs2808651_x_11_5,No_rs2808651_x_7_5,Yes_rs10799032_x_7_5,No_rs10799032_x_9_5,Yes_rs1031567_x_11_5,No_rs1031567_x_7_5,Yes_rs17376559_x_7_5,No_rs17376559_x_11_5,Yes_rs309331_rs4605270_Q_6,No_rs309331_rs4928007_Q_5.5,Yes_rs3761364_rs2234167_Q_8.5,No_rs3761364_x_7_5,Yes_rs9415758_x_9_5,No_rs9415758_x_7_5,Yes_rs10910061_x_11_5,No_rs10910061_x_9_5,Yes_rs4605270_x_11_5,No_rs4605270_x_7_5,Yes_rs4928007_x_7_5,No_rs4928007_x_11_5,Yes_rs2234167_x_11_5,No_rs2234167_x_9_5,\nCreate_rs2237059_Q_8.5,Yes_rs2237059_rs8191431_Q_6,No_rs2237059_rs4513668_Q_9.5,Yes_rs8191431_rs16853992_Q_2,No_rs8191431_rs1123571_Q_5.5,Yes_rs4513668_rs218336_Q_8.5,No_rs4513668_rs6466823_Q_8.5,Yes_rs16853992_rs1982394_Q_6,No_rs16853992_x_11_5,Yes_rs1123571_x_7_5,No_rs1123571_x_11_5,Yes_rs218336_x_7_5,No_rs218336_rs16853407_Q_8.5,Yes_rs6466823_rs2287198_Q_5.5,No_rs6466823_rs7206635_Q_2,Yes_rs1982394_x_9_5,No_rs1982394_x_7_5,Yes_rs16853407_x_9_5,No_rs16853407_x_11_5,Yes_rs2287198_rs10916790_Q_8.5,No_rs2287198_rs10140504_Q_7,Yes_rs7206635_rs8027920_Q_2,No_rs7206635_rs12463789_Q_8.5,Yes_rs10916790_x_7_5,No_rs10916790_x_9_5,Yes_rs10140504_x_7_5,No_rs10140504_rs3795845_Q_9.5,Yes_rs8027920_rs1601745_Q_2,No_rs8027920_rs2309582_Q_5.5,Yes_rs12463789_x_7_5,No_rs12463789_x_11_5,Yes_rs3795845_x_7_5,No_rs3795845_rs6427184_Q_2,Yes_rs1601745_rs11584036_Q_2,No_rs1601745_rs3107145_Q_5.5,Yes_rs2309582_rs2147905_Q_6,No_rs2309582_rs9788651_Q_8.5,Yes_rs6427184_rs2298223_Q_6,No_rs6427184_x_7_5,Yes_rs11584036_x_9_5,No_rs11584036_x_7_5,Yes_rs3107145_x_11_5,No_rs3107145_x_9_5,Yes_rs2147905_x_9_5,No_rs2147905_x_7_5,Yes_rs9788651_x_11_5,No_rs9788651_rs8042942_Q_8.5,Yes_rs2298223_x_11_5,No_rs2298223_x_9_5,Yes_rs8042942_rs13414905_Q_8.5,No_rs8042942_x_9_5,Yes_rs13414905_x_11_5,No_rs13414905_x_7_5,\nCreate_rs8075137_Q_5.5,Yes_rs8075137_rs10937252_Q_2,No_rs8075137_rs17044602_Q_5.5,Yes_rs10937252_rs6854453_Q_6,No_rs10937252_rs7446054_Q_6,Yes_rs17044602_rs11808981_Q_8.5,No_rs17044602_rs6422427_Q_6,Yes_rs6854453_rs3749388_Q_6,No_rs6854453_rs10237182_Q_7,Yes_rs7446054_x_7_5,No_rs7446054_x_9_5,Yes_rs11808981_x_9_5,No_rs11808981_x_7_5,Yes_rs6422427_rs41513050_Q_5.5,No_rs6422427_x_11_5,Yes_rs3749388_rs1409968_Q_2,No_rs3749388_rs12058761_Q_8.5,Yes_rs10237182_x_7_5,No_rs10237182_rs17786140_Q_2,Yes_rs41513050_x_7_5,No_rs41513050_rs17139871_Q_9.5,Yes_rs1409968_rs2839509_Q_2,No_rs1409968_rs3017627_Q_6,Yes_rs12058761_x_9_5,No_rs12058761_x_7_5,Yes_rs17786140_x_7_5,No_rs17786140_x_9_5,Yes_rs17139871_x_7_5,No_rs17139871_rs9782908_Q_6,Yes_rs2839509_rs2535340_Q_8.5,No_rs2839509_x_7_5,Yes_rs3017627_x_7_5,No_rs3017627_x_9_5,Yes_rs9782908_x_9_5,No_rs9782908_x_7_5,Yes_rs2535340_rs16840287_Q_6,No_rs2535340_rs1356946_Q_8.5,Yes_rs16840287_x_11_5,No_rs16840287_x_7_5,Yes_rs1356946_x_7_5,No_rs1356946_rs4847372_Q_2,Yes_rs4847372_rs11769723_Q_6,No_rs4847372_x_7_5,Yes_rs11769723_rs6734731_Q_2,No_rs11769723_x_9_5,Yes_rs6734731_x_7_5,No_rs6734731_x_11_5,\nCreate_rs1420676_Q_6,Yes_rs1420676_rs2082331_Q_8.5,No_rs1420676_rs7669018_Q_8.5,Yes_rs2082331_rs1404756_Q_8.5,No_rs2082331_rs4344559_Q_5.5,Yes_rs7669018_rs11573205_Q_5.5,No_rs7669018_rs619345_Q_8.5,Yes_rs1404756_x_9_5,No_rs1404756_x_7_5,Yes_rs4344559_rs2325037_Q_2,No_rs4344559_rs10492377_Q_2,Yes_rs11573205_x_7_5,No_rs11573205_rs7515087_Q_8.5,Yes_rs619345_x_7_5,No_rs619345_x_11_5,Yes_rs2325037_rs2500297_Q_6,No_rs2325037_rs9575364_Q_8.5,Yes_rs10492377_rs4235448_Q_6,No_rs10492377_rs4887382_Q_8.5,Yes_rs7515087_x_7_5,No_rs7515087_x_9_5,Yes_rs2500297_x_9_5,No_rs2500297_x_7_5,Yes_rs9575364_x_9_5,No_rs9575364_x_7_5,Yes_rs4235448_rs748596_Q_8.5,No_rs4235448_rs6807580_Q_5.5,Yes_rs4887382_rs9659669_Q_2,No_rs4887382_x_9_5,Yes_rs748596_rs10764918_Q_6,No_rs748596_rs2477707_Q_6,Yes_rs6807580_x_9_5,No_rs6807580_x_7_5,Yes_rs9659669_x_11_5,No_rs9659669_x_7_5,Yes_rs10764918_rs10501858_Q_5.5,No_rs10764918_rs7512269_Q_6,Yes_rs2477707_x_9_5,No_rs2477707_x_7_5,Yes_rs10501858_x_7_5,No_rs10501858_rs10971164_Q_6,Yes_rs7512269_x_7_5,No_rs7512269_x_11_5,Yes_rs10971164_rs11265070_Q_2,No_rs10971164_x_7_5,Yes_rs11265070_rs17027039_Q_2,No_rs11265070_x_7_5,Yes_rs17027039_x_7_5,No_rs17027039_x_11_5,\nCreate_rs1536084_Q_2.5,Yes_rs1536084_rs7390989_Q_2,No_rs1536084_rs2023637_Q_6,Yes_rs7390989_rs10895512_Q_3.5,No_rs7390989_rs17210010_Q_5.5,Yes_rs2023637_rs4878051_Q_8.5,No_rs2023637_rs16949551_Q_2,Yes_rs10895512_rs6595775_Q_2,No_rs10895512_rs12487340_Q_8.5,Yes_rs17210010_rs10198116_Q_5.5,No_rs17210010_rs6882064_Q_6,Yes_rs4878051_rs7520934_Q_9.5,No_rs4878051_rs1037041_Q_5.5,Yes_rs16949551_rs1042712_Q_7,No_rs16949551_x_7_5,Yes_rs6595775_rs11688448_Q_2,No_rs6595775_rs12040683_Q_8.5,Yes_rs12487340_rs11260562_Q_2,No_rs12487340_rs1000647_Q_2,Yes_rs10198116_x_7_5,No_rs10198116_x_9_5,Yes_rs6882064_rs967094_Q_2,No_rs6882064_rs903903_Q_5.5,Yes_rs7520934_x_9_5,No_rs7520934_x_7_5,Yes_rs1037041_rs11807706_Q_5.5,No_rs1037041_rs12025026_Q_2,Yes_rs1042712_rs12074249_Q_1.5,No_rs1042712_rs12090228_Q_2,Yes_rs11688448_rs1353341_Q_2,No_rs11688448_x_11_5,Yes_rs12040683_x_9_5,No_rs12040683_x_11_5,Yes_rs11260562_x_9_5,No_rs11260562_x_7_5,Yes_rs1000647_rs2378559_Q_8.5,No_rs1000647_rs4654607_Q_6,Yes_rs967094_x_9_5,No_rs967094_x_11_5,Yes_rs903903_x_7_5,No_rs903903_x_9_5,Yes_rs11807706_x_7_5,No_rs11807706_x_11_5,Yes_rs12025026_x_7_5,No_rs12025026_x_11_5,Yes_rs12074249_x_7_5,No_rs12074249_x_9_5,Yes_rs12090228_x_7_5,No_rs12090228_x_9_5,Yes_rs1353341_x_9_5,No_rs1353341_x_7_5,Yes_rs2378559_rs6685066_Q_5.5,No_rs2378559_x_7_5,Yes_rs4654607_x_7_5,No_rs4654607_x_9_5,Yes_rs6685066_x_7_5,No_rs6685066_rs12409852_Q_2.5,Yes_rs12409852_rs3128342_Q_1.5,No_rs12409852_x_7_5,Yes_rs3128342_x_11_5,No_rs3128342_x_9_5,\nCreate_rs10825916_Q_9.5,Yes_rs10825916_rs17532826_Q_5.5,No_rs10825916_rs345981_Q_2,Yes_rs17532826_rs12305915_Q_2,No_rs17532826_rs2373262_Q_8.5,Yes_rs345981_rs11155161_Q_8.5,No_rs345981_rs12067378_Q_6,Yes_rs12305915_rs12097782_Q_6,No_rs12305915_x_7_5,Yes_rs2373262_rs10910097_Q_8.5,No_rs2373262_rs1404315_Q_8.5,Yes_rs11155161_rs2230233_Q_8.5,No_rs11155161_rs10836370_Q_8.5,Yes_rs12067378_x_7_5,No_rs12067378_x_9_5,Yes_rs12097782_x_9_5,No_rs12097782_x_7_5,Yes_rs10910097_x_9_5,No_rs10910097_x_7_5,Yes_rs1404315_rs1204826_Q_5.5,No_rs1404315_rs3845293_Q_3.5,Yes_rs2230233_rs4245756_Q_6,No_rs2230233_rs9789429_Q_5.5,Yes_rs10836370_rs16866638_Q_2,No_rs10836370_rs2839657_Q_8.5,Yes_rs1204826_x_9_5,No_rs1204826_rs615739_Q_2,Yes_rs3845293_x_11_5,No_rs3845293_x_9_5,Yes_rs4245756_x_9_5,No_rs4245756_x_7_5,Yes_rs9789429_x_7_5,No_rs9789429_x_11_5,Yes_rs16866638_rs4683973_Q_8.5,No_rs16866638_rs2794320_Q_5.5,Yes_rs2839657_rs10864504_Q_5.5,No_rs2839657_rs10487999_Q_5.5,Yes_rs615739_x_7_5,No_rs615739_x_11_5,Yes_rs4683973_x_7_5,No_rs4683973_x_11_5,Yes_rs2794320_x_11_5,No_rs2794320_x_7_5,Yes_rs10864504_x_9_5,No_rs10864504_x_7_5,Yes_rs10487999_rs6419478_Q_8.5,No_rs10487999_rs2267270_Q_5.5,Yes_rs6419478_x_11_5,No_rs6419478_x_7_5,Yes_rs2267270_x_7_5,No_rs2267270_rs2758735_Q_5.5,Yes_rs2758735_rs1393117_Q_2,No_rs2758735_x_7_5,Yes_rs1393117_x_11_5,No_rs1393117_x_7_5,\n";
		//Kenyan 31 trees
		//std::string treeInfo = "Create_rs7573555_Q_8.5,Yes_rs7573555_rs7561423_Q_6,No_rs7573555_rs13162048_Q_2,Yes_rs7561423_rs10897976_Q_3.5,No_rs7561423_rs9470872_Q_8.5,Yes_rs13162048_rs17202778_Q_8.5,No_rs13162048_rs349400_Q_8.5,Yes_rs10897976_rs495937_Q_7,No_rs10897976_x_7_5,Yes_rs9470872_x_7_5,No_rs9470872_rs7760662_Q_9.5,Yes_rs17202778_x_9_5,No_rs17202778_rs12742323_Q_8.5,Yes_rs349400_x_7_5,No_rs349400_x_9_5,Yes_rs495937_x_9_5,No_rs495937_x_7_5,Yes_rs7760662_x_7_5,No_rs7760662_rs6736379_Q_8.5,Yes_rs12742323_x_7_5,No_rs12742323_x_9_5,Yes_rs6736379_x_7_5,No_rs6736379_x_9_5,\nCreate_rs1050115_Q_2,Yes_rs1050115_rs11125815_Q_5.5,No_rs1050115_rs17044602_Q_5.5,Yes_rs11125815_rs1320565_Q_6,No_rs11125815_rs17226259_Q_5.5,Yes_rs17044602_rs2058061_Q_5.5,No_rs17044602_rs2721202_Q_6,Yes_rs1320565_x_7_5,No_rs1320565_x_9_5,Yes_rs17226259_x_9_5,No_rs17226259_x_7_5,Yes_rs2058061_x_9_5,No_rs2058061_x_7_5,Yes_rs2721202_rs869939_Q_3.5,No_rs2721202_rs392630_Q_5.5,Yes_rs869939_rs2190355_Q_8.5,No_rs869939_x_7_5,Yes_rs392630_x_9_5,No_rs392630_x_7_5,Yes_rs2190355_x_7_5,No_rs2190355_x_9_5,\nCreate_rs7581814_Q_5.5,Yes_rs7581814_rs17685410_Q_5.5,No_rs7581814_rs1990796_Q_1.5,Yes_rs17685410_rs4908925_Q_1.5,No_rs17685410_rs2284767_Q_2,Yes_rs1990796_rs4721216_Q_8.5,No_rs1990796_rs7548984_Q_7,Yes_rs4908925_x_9_5,No_rs4908925_x_7_5,Yes_rs2284767_x_7_5,No_rs2284767_x_9_5,Yes_rs4721216_rs1110052_Q_9.5,No_rs4721216_rs9292857_Q_8.5,Yes_rs7548984_x_9_5,No_rs7548984_x_7_5,Yes_rs1110052_x_7_5,No_rs1110052_x_9_5,Yes_rs9292857_x_7_5,No_rs9292857_rs2188301_Q_3.5,Yes_rs2188301_x_7_5,No_rs2188301_rs12095221_Q_8.5,Yes_rs12095221_x_9_5,No_rs12095221_x_7_5,\nCreate_rs2015532_Q_9.5,Yes_rs2015532_rs2944776_Q_6,No_rs2015532_rs4658560_Q_2,Yes_rs2944776_rs6880683_Q_8.5,No_rs2944776_rs10908849_Q_8.5,Yes_rs4658560_rs1597178_Q_2,No_rs4658560_rs12031557_Q_2,Yes_rs6880683_rs2515542_Q_6,No_rs6880683_rs17298420_Q_9.5,Yes_rs10908849_x_9_5,No_rs10908849_rs13303106_Q_2,Yes_rs1597178_x_9_5,No_rs1597178_x_7_5,Yes_rs12031557_x_9_5,No_rs12031557_x_7_5,Yes_rs2515542_x_7_5,No_rs2515542_x_9_5,Yes_rs17298420_x_9_5,No_rs17298420_rs10915360_Q_6,Yes_rs13303106_x_7_5,No_rs13303106_x_9_5,Yes_rs10915360_x_9_5,No_rs10915360_x_7_5,\nCreate_rs6724569_Q_5.5,Yes_rs6724569_rs8140370_Q_9.5,No_rs6724569_rs9516890_Q_8.5,Yes_rs8140370_rs9576822_Q_1.5,No_rs8140370_rs12064015_Q_9.5,Yes_rs9516890_rs11805516_Q_8.5,No_rs9516890_rs12739022_Q_8.5,Yes_rs9576822_x_9_5,No_rs9576822_x_7_5,Yes_rs12064015_x_7_5,No_rs12064015_rs9874060_Q_2,Yes_rs11805516_x_7_5,No_rs11805516_x_9_5,Yes_rs12739022_x_9_5,No_rs12739022_x_7_5,Yes_rs9874060_rs6685064_Q_6,No_rs9874060_rs11547493_Q_8.5,Yes_rs6685064_x_9_5,No_rs6685064_x_7_5,Yes_rs11547493_x_7_5,No_rs11547493_rs12059640_Q_8.5,Yes_rs12059640_x_9_5,No_rs12059640_x_7_5,\nCreate_rs6430594_Q_2,Yes_rs6430594_rs2315523_Q_6,No_rs6430594_rs5770567_Q_6,Yes_rs2315523_rs992133_Q_5.5,No_rs2315523_rs3813199_Q_5.5,Yes_rs5770567_rs12204275_Q_9.5,No_rs5770567_rs2744677_Q_8.5,Yes_rs992133_x_9_5,No_rs992133_x_7_5,Yes_rs3813199_x_7_5,No_rs3813199_x_9_5,Yes_rs12204275_x_9_5,No_rs12204275_rs10520997_Q_5.5,Yes_rs2744677_x_7_5,No_rs2744677_rs1005032_Q_6,Yes_rs10520997_rs2651906_Q_6,No_rs10520997_rs13303118_Q_9.5,Yes_rs1005032_x_7_5,No_rs1005032_rs16824500_Q_2,Yes_rs2651906_x_9_5,No_rs2651906_x_7_5,Yes_rs13303118_x_7_5,No_rs13303118_x_9_5,Yes_rs16824500_x_7_5,No_rs16824500_x_9_5,\nCreate_rs364950_Q_2,Yes_rs364950_rs6927023_Q_5.5,No_rs364950_rs13142580_Q_8.5,Yes_rs6927023_rs9309464_Q_5.5,No_rs6927023_rs9485572_Q_5.5,Yes_rs13142580_rs6735149_Q_6,No_rs13142580_x_9_5,Yes_rs9309464_rs17160698_Q_7.5,No_rs9309464_x_7_5,Yes_rs9485572_x_7_5,No_rs9485572_rs12239056_Q_6,Yes_rs6735149_rs11586404_Q_5.5,No_rs6735149_x_9_5,Yes_rs17160698_x_7_5,No_rs17160698_x_9_5,Yes_rs12239056_rs12085768_Q_6,No_rs12239056_x_7_5,Yes_rs11586404_x_9_5,No_rs11586404_x_7_5,Yes_rs12085768_x_9_5,No_rs12085768_x_7_5,\nCreate_rs404557_Q_2,Yes_rs404557_rs6096853_Q_2,No_rs404557_rs800672_Q_2,Yes_rs6096853_rs2298217_Q_6,No_rs6096853_rs312557_Q_3.5,Yes_rs800672_rs7653308_Q_6,No_rs800672_rs7745739_Q_8.5,Yes_rs2298217_x_7_5,No_rs2298217_x_9_5,Yes_rs312557_rs445633_Q_6,No_rs312557_rs4233931_Q_8.5,Yes_rs7653308_x_9_5,No_rs7653308_x_7_5,Yes_rs7745739_x_7_5,No_rs7745739_x_9_5,Yes_rs445633_rs672138_Q_2.5,No_rs445633_x_7_5,Yes_rs4233931_x_9_5,No_rs4233931_x_7_5,Yes_rs672138_x_7_5,No_rs672138_x_9_5,\nCreate_rs1440463_Q_6,Yes_rs1440463_rs8070885_Q_8.5,No_rs1440463_rs2227282_Q_5.5,Yes_rs8070885_rs477882_Q_5.5,No_rs8070885_rs13319626_Q_7,Yes_rs2227282_rs790660_Q_7,No_rs2227282_x_9_5,Yes_rs477882_x_9_5,No_rs477882_x_7_5,Yes_rs13319626_x_7_5,No_rs13319626_rs1379602_Q_9.5,Yes_rs790660_x_9_5,No_rs790660_rs4750058_Q_5.5,Yes_rs1379602_x_7_5,No_rs1379602_rs16937924_Q_5.5,Yes_rs4750058_x_9_5,No_rs4750058_rs6671889_Q_1.5,Yes_rs16937924_x_7_5,No_rs16937924_x_9_5,Yes_rs6671889_x_9_5,No_rs6671889_x_7_5,\nCreate_rs973332_Q_6,Yes_rs973332_rs30534_Q_6,No_rs973332_rs7710375_Q_2,Yes_rs30534_rs1956593_Q_8.5,No_rs30534_rs1772890_Q_8.5,Yes_rs7710375_rs11915247_Q_5.5,No_rs7710375_rs262656_Q_1.5,Yes_rs1956593_rs6694982_Q_2,No_rs1956593_rs1206810_Q_6,Yes_rs1772890_x_7_5,No_rs1772890_x_9_5,Yes_rs11915247_x_7_5,No_rs11915247_rs12404555_Q_5.5,Yes_rs262656_x_7_5,No_rs262656_x_9_5,Yes_rs6694982_x_9_5,No_rs6694982_x_7_5,Yes_rs1206810_rs4648819_Q_2,No_rs1206810_x_9_5,Yes_rs12404555_x_7_5,No_rs12404555_x_9_5,Yes_rs4648819_x_7_5,No_rs4648819_x_9_5,\nCreate_rs309172_Q_2,Yes_rs309172_rs6737636_Q_6,No_rs309172_rs6794557_Q_5.5,Yes_rs6737636_rs7553178_Q_5.5,No_rs6737636_x_9_5,Yes_rs6794557_rs1891231_Q_5.5,No_rs6794557_rs7770679_Q_2,Yes_rs7553178_x_7_5,No_rs7553178_x_9_5,Yes_rs1891231_x_9_5,No_rs1891231_rs6424639_Q_8.5,Yes_rs7770679_rs2430341_Q_6,No_rs7770679_x_7_5,Yes_rs6424639_x_7_5,No_rs6424639_x_9_5,Yes_rs2430341_x_7_5,No_rs2430341_rs9745005_Q_2,Yes_rs9745005_rs12994558_Q_6,No_rs9745005_x_7_5,Yes_rs12994558_x_7_5,No_rs12994558_rs17754897_Q_2,Yes_rs17754897_x_7_5,No_rs17754897_x_9_5,\nCreate_rs309143_Q_2,Yes_rs309143_rs10497029_Q_5.5,No_rs309143_rs5743612_Q_5.5,Yes_rs10497029_x_9_5,No_rs10497029_rs9943244_Q_1.5,Yes_rs5743612_rs2237835_Q_2,No_rs5743612_rs1567049_Q_6,Yes_rs9943244_x_7_5,No_rs9943244_x_9_5,Yes_rs2237835_x_7_5,No_rs2237835_rs3766191_Q_6,Yes_rs1567049_rs12022654_Q_5.5,No_rs1567049_rs1844959_Q_5.5,Yes_rs3766191_x_9_5,No_rs3766191_x_7_5,Yes_rs12022654_x_9_5,No_rs12022654_x_7_5,Yes_rs1844959_x_7_5,No_rs1844959_rs17055737_Q_5.5,Yes_rs17055737_x_7_5,No_rs17055737_rs8057684_Q_2,Yes_rs8057684_rs3737721_Q_5.5,No_rs8057684_x_7_5,Yes_rs3737721_x_9_5,No_rs3737721_x_7_5,\nCreate_rs309154_Q_6,Yes_rs309154_rs4142221_Q_6,No_rs309154_rs1595422_Q_2,Yes_rs4142221_rs12119558_Q_5.5,No_rs4142221_x_9_5,Yes_rs1595422_rs11660396_Q_2,No_rs1595422_rs1366457_Q_9.5,Yes_rs12119558_x_9_5,No_rs12119558_x_7_5,Yes_rs11660396_rs6424976_Q_6,No_rs11660396_x_9_5,Yes_rs1366457_x_7_5,No_rs1366457_rs12601516_Q_2,Yes_rs6424976_x_7_5,No_rs6424976_x_9_5,Yes_rs12601516_x_7_5,No_rs12601516_rs1792959_Q_5.5,Yes_rs1792959_x_7_5,No_rs1792959_rs17030159_Q_2,Yes_rs17030159_x_9_5,No_rs17030159_x_7_5,\nCreate_rs3769012_Q_5.5,Yes_rs3769012_rs35487582_Q_3.5,No_rs3769012_rs12438284_Q_2,Yes_rs35487582_rs4402506_Q_8.5,No_rs35487582_rs7741503_Q_5.5,Yes_rs12438284_rs17263039_Q_8.5,No_rs12438284_rs11808276_Q_6,Yes_rs4402506_x_9_5,No_rs4402506_rs10890041_Q_8.5,Yes_rs7741503_rs1175549_Q_1.5,No_rs7741503_rs12069196_Q_6,Yes_rs17263039_x_9_5,No_rs17263039_x_7_5,Yes_rs11808276_x_9_5,No_rs11808276_x_7_5,Yes_rs10890041_x_9_5,No_rs10890041_x_7_5,Yes_rs1175549_x_9_5,No_rs1175549_x_7_5,Yes_rs12069196_rs10075371_Q_6,No_rs12069196_x_7_5,Yes_rs10075371_rs2274264_Q_2,No_rs10075371_x_7_5,Yes_rs2274264_x_7_5,No_rs2274264_x_9_5,\nCreate_rs10072084_Q_6,Yes_rs10072084_rs936663_Q_5.5,No_rs10072084_rs17028457_Q_8.5,Yes_rs936663_rs2067022_Q_8.5,No_rs936663_rs648378_Q_5.5,Yes_rs17028457_rs6429800_Q_2,No_rs17028457_rs17095806_Q_5.5,Yes_rs2067022_rs28707307_Q_8.5,No_rs2067022_rs4269034_Q_8.5,Yes_rs648378_x_9_5,No_rs648378_x_7_5,Yes_rs6429800_x_7_5,No_rs6429800_x_9_5,Yes_rs17095806_rs16923264_Q_1.5,No_rs17095806_x_7_5,Yes_rs28707307_x_7_5,No_rs28707307_x_9_5,Yes_rs4269034_x_9_5,No_rs4269034_x_7_5,Yes_rs16923264_rs7523842_Q_8.5,No_rs16923264_x_7_5,Yes_rs7523842_x_7_5,No_rs7523842_rs11120876_Q_6,Yes_rs11120876_x_9_5,No_rs11120876_x_7_5,\nCreate_rs10242455_Q_5.5,Yes_rs10242455_rs809825_Q_8.5,No_rs10242455_rs12885270_Q_5.5,Yes_rs809825_rs2488479_Q_8.5,No_rs809825_rs12135523_Q_2,Yes_rs12885270_rs11916051_Q_8.5,No_rs12885270_rs6458997_Q_8.5,Yes_rs2488479_x_9_5,No_rs2488479_x_7_5,Yes_rs12135523_x_7_5,No_rs12135523_rs4631721_Q_5.5,Yes_rs11916051_rs6673393_Q_6,No_rs11916051_rs16934647_Q_8.5,Yes_rs6458997_x_9_5,No_rs6458997_x_7_5,Yes_rs4631721_x_9_5,No_rs4631721_x_7_5,Yes_rs6673393_x_7_5,No_rs6673393_x_9_5,Yes_rs16934647_x_9_5,No_rs16934647_x_7_5,\nCreate_rs12472293_Q_8.5,Yes_rs12472293_rs6862681_Q_5.5,No_rs12472293_rs17823777_Q_2,Yes_rs6862681_rs201729_Q_8.5,No_rs6862681_rs1347957_Q_6,Yes_rs17823777_rs770308_Q_6,No_rs17823777_rs2803310_Q_6,Yes_rs201729_x_7_5,No_rs201729_rs6667248_Q_5.5,Yes_rs1347957_rs11884415_Q_6,No_rs1347957_rs11260595_Q_3.5,Yes_rs770308_x_9_5,No_rs770308_x_7_5,Yes_rs2803310_x_7_5,No_rs2803310_x_9_5,Yes_rs6667248_x_9_5,No_rs6667248_x_7_5,Yes_rs11884415_rs17086113_Q_5.5,No_rs11884415_x_7_5,Yes_rs11260595_x_9_5,No_rs11260595_x_7_5,Yes_rs17086113_x_7_5,No_rs17086113_rs11799924_Q_5.5,Yes_rs11799924_x_9_5,No_rs11799924_x_7_5,\nCreate_rs699486_Q_5.5,Yes_rs699486_rs11759220_Q_5.5,No_rs699486_rs4646457_Q_3.5,Yes_rs11759220_rs13303010_Q_2,No_rs11759220_rs2720710_Q_7,Yes_rs4646457_rs10474381_Q_8.5,No_rs4646457_rs12541188_Q_2,Yes_rs13303010_x_9_5,No_rs13303010_x_7_5,Yes_rs2720710_x_7_5,No_rs2720710_rs7527194_Q_8.5,Yes_rs10474381_rs3125677_Q_2,No_rs10474381_rs595541_Q_2,Yes_rs12541188_rs12752801_Q_7.5,No_rs12541188_x_9_5,Yes_rs7527194_x_9_5,No_rs7527194_x_7_5,Yes_rs3125677_x_9_5,No_rs3125677_x_7_5,Yes_rs595541_x_7_5,No_rs595541_rs7523732_Q_6,Yes_rs12752801_x_7_5,No_rs12752801_x_9_5,Yes_rs7523732_x_7_5,No_rs7523732_x_9_5,\nCreate_rs16855615_Q_5.5,Yes_rs16855615_rs10137272_Q_2.5,No_rs16855615_rs6677662_Q_2,Yes_rs10137272_rs532885_Q_7,No_rs10137272_x_7_5,Yes_rs6677662_rs6963345_Q_5.5,No_rs6677662_rs7539166_Q_8.5,Yes_rs532885_x_7_5,No_rs532885_rs13404079_Q_1.5,Yes_rs6963345_rs28635343_Q_5.5,No_rs6963345_rs17286578_Q_8.5,Yes_rs7539166_x_9_5,No_rs7539166_x_7_5,Yes_rs13404079_x_7_5,No_rs13404079_x_9_5,Yes_rs28635343_x_7_5,No_rs28635343_x_9_5,Yes_rs17286578_x_9_5,No_rs17286578_rs11208579_Q_2,Yes_rs11208579_x_9_5,No_rs11208579_x_7_5,\nCreate_rs2241883_Q_8.5,Yes_rs2241883_rs7168199_Q_5.5,No_rs2241883_rs12188101_Q_2,Yes_rs7168199_rs9992661_Q_1.5,No_rs7168199_rs7216396_Q_8.5,Yes_rs12188101_rs3935821_Q_6,No_rs12188101_rs10075720_Q_9.5,Yes_rs9992661_rs67746_Q_5.5,No_rs9992661_x_7_5,Yes_rs7216396_x_7_5,No_rs7216396_x_9_5,Yes_rs3935821_rs12943500_Q_6,No_rs3935821_rs2181484_Q_2,Yes_rs10075720_x_7_5,No_rs10075720_rs28504611_Q_8.5,Yes_rs67746_x_9_5,No_rs67746_x_7_5,Yes_rs12943500_rs7415927_Q_5.5,No_rs12943500_x_9_5,Yes_rs2181484_x_7_5,No_rs2181484_x_9_5,Yes_rs28504611_x_9_5,No_rs28504611_x_7_5,Yes_rs7415927_x_9_5,No_rs7415927_x_7_5,\nCreate_rs1545223_Q_2,Yes_rs1545223_rs2423334_Q_6,No_rs1545223_rs2551320_Q_6,Yes_rs2423334_rs6584646_Q_8.5,No_rs2423334_rs4661748_Q_9.5,Yes_rs2551320_rs4912106_Q_2,No_rs2551320_x_7_5,Yes_rs6584646_rs2376821_Q_8.5,No_rs6584646_rs1206088_Q_8.5,Yes_rs4661748_x_9_5,No_rs4661748_x_7_5,Yes_rs4912106_rs17047458_Q_5.5,No_rs4912106_x_7_5,Yes_rs2376821_x_9_5,No_rs2376821_x_7_5,Yes_rs1206088_x_9_5,No_rs1206088_rs4972277_Q_8.5,Yes_rs17047458_x_7_5,No_rs17047458_x_9_5,Yes_rs4972277_x_7_5,No_rs4972277_x_9_5,\nCreate_rs2740566_Q_5.5,Yes_rs2740566_rs16905958_Q_7,No_rs2740566_rs875044_Q_6,Yes_rs16905958_rs12645079_Q_8.5,No_rs16905958_rs16870510_Q_1.5,Yes_rs875044_rs2415306_Q_8.5,No_rs875044_rs4648764_Q_6,Yes_rs12645079_x_9_5,No_rs12645079_x_7_5,Yes_rs16870510_rs6938518_Q_6,No_rs16870510_x_7_5,Yes_rs2415306_x_9_5,No_rs2415306_rs16863858_Q_1.5,Yes_rs4648764_x_7_5,No_rs4648764_x_9_5,Yes_rs6938518_rs6676442_Q_8.5,No_rs6938518_x_7_5,Yes_rs16863858_rs4314833_Q_8.5,No_rs16863858_x_9_5,Yes_rs6676442_x_9_5,No_rs6676442_x_7_5,Yes_rs4314833_x_9_5,No_rs4314833_x_7_5,\nCreate_rs6975220_Q_5.5,Yes_rs6975220_rs1005608_Q_8.5,No_rs6975220_rs10001947_Q_7,Yes_rs1005608_rs4431782_Q_6,No_rs1005608_rs17241648_Q_6,Yes_rs10001947_rs7874475_Q_5.5,No_rs10001947_rs11210640_Q_6,Yes_rs4431782_x_7_5,No_rs4431782_x_9_5,Yes_rs17241648_rs4310281_Q_2,No_rs17241648_x_9_5,Yes_rs7874475_rs28399555_Q_5.5,No_rs7874475_x_7_5,Yes_rs11210640_x_7_5,No_rs11210640_x_9_5,Yes_rs4310281_rs13288508_Q_8.5,No_rs4310281_x_9_5,Yes_rs28399555_x_7_5,No_rs28399555_x_9_5,Yes_rs13288508_x_7_5,No_rs13288508_x_9_5,\nCreate_rs6742013_Q_6,Yes_rs6742013_rs3103736_Q_6,No_rs6742013_rs1399357_Q_8.5,Yes_rs3103736_rs947347_Q_5.5,No_rs3103736_x_9_5,Yes_rs1399357_x_9_5,No_rs1399357_rs6731365_Q_2,Yes_rs947347_x_7_5,No_rs947347_x_9_5,Yes_rs6731365_rs7136627_Q_5.5,No_rs6731365_rs683966_Q_8.5,Yes_rs7136627_rs2341362_Q_8.5,No_rs7136627_rs11583332_Q_8.5,Yes_rs683966_rs12117343_Q_6,No_rs683966_x_9_5,Yes_rs2341362_x_9_5,No_rs2341362_x_7_5,Yes_rs11583332_x_9_5,No_rs11583332_x_7_5,Yes_rs12117343_x_7_5,No_rs12117343_x_9_5,\nCreate_rs7605229_Q_8.5,Yes_rs7605229_rs10792608_Q_2,No_rs7605229_rs1125954_Q_5.5,Yes_rs10792608_rs2061517_Q_2,No_rs10792608_x_9_5,Yes_rs1125954_rs12069909_Q_5.5,No_rs1125954_rs12145658_Q_8.5,Yes_rs2061517_rs17369470_Q_5.5,No_rs2061517_rs16886536_Q_5.5,Yes_rs12069909_x_7_5,No_rs12069909_x_9_5,Yes_rs12145658_x_7_5,No_rs12145658_x_9_5,Yes_rs17369470_x_9_5,No_rs17369470_rs6572913_Q_5.5,Yes_rs16886536_x_7_5,No_rs16886536_rs897469_Q_8.5,Yes_rs6572913_x_7_5,No_rs6572913_x_9_5,Yes_rs897469_x_9_5,No_rs897469_x_7_5,\nCreate_rs3806502_Q_8.5,Yes_rs3806502_rs6968676_Q_8.5,No_rs3806502_rs2359377_Q_6,Yes_rs6968676_rs3131972_Q_5.5,No_rs6968676_rs350130_Q_2,Yes_rs2359377_rs6697095_Q_9.5,No_rs2359377_rs2503701_Q_8.5,Yes_rs3131972_x_7_5,No_rs3131972_x_9_5,Yes_rs350130_rs6015825_Q_5.5,No_rs350130_rs4674632_Q_5.5,Yes_rs6697095_x_9_5,No_rs6697095_x_7_5,Yes_rs2503701_x_9_5,No_rs2503701_x_7_5,Yes_rs6015825_rs3820250_Q_9.5,No_rs6015825_rs2028723_Q_9.5,Yes_rs4674632_rs28625223_Q_8.5,No_rs4674632_x_7_5,Yes_rs3820250_x_7_5,No_rs3820250_x_9_5,Yes_rs2028723_x_7_5,No_rs2028723_rs16838922_Q_2.5,Yes_rs28625223_x_7_5,No_rs28625223_x_9_5,Yes_rs16838922_x_7_5,No_rs16838922_x_9_5,\nCreate_rs1411088_Q_2,Yes_rs1411088_rs6760326_Q_1.5,No_rs1411088_rs17082523_Q_5.5,Yes_rs6760326_rs985365_Q_8.5,No_rs6760326_rs7586145_Q_8.5,Yes_rs17082523_x_7_5,No_rs17082523_rs6556382_Q_6,Yes_rs985365_rs9697358_Q_2,No_rs985365_rs12722820_Q_8.5,Yes_rs7586145_x_7_5,No_rs7586145_x_9_5,Yes_rs6556382_rs11166028_Q_6,No_rs6556382_rs10910099_Q_3.5,Yes_rs9697358_x_9_5,No_rs9697358_x_7_5,Yes_rs12722820_x_9_5,No_rs12722820_x_7_5,Yes_rs11166028_rs16851168_Q_3.5,No_rs11166028_x_7_5,Yes_rs10910099_x_7_5,No_rs10910099_x_9_5,Yes_rs16851168_x_7_5,No_rs16851168_x_9_5,\nCreate_rs776746_Q_8.5,Yes_rs776746_rs11842930_Q_6,No_rs776746_rs2373262_Q_8.5,Yes_rs11842930_rs9948548_Q_5.5,No_rs11842930_rs1925704_Q_5.5,Yes_rs2373262_rs9660718_Q_7,No_rs2373262_rs1330684_Q_6,Yes_rs9948548_rs11190458_Q_1.5,No_rs9948548_x_7_5,Yes_rs1925704_x_9_5,No_rs1925704_x_7_5,Yes_rs9660718_x_7_5,No_rs9660718_rs7537756_Q_5.5,Yes_rs1330684_rs11176729_Q_8.5,No_rs1330684_x_9_5,Yes_rs11190458_x_7_5,No_rs11190458_rs6428392_Q_1.5,Yes_rs7537756_x_9_5,No_rs7537756_x_7_5,Yes_rs11176729_x_7_5,No_rs11176729_x_9_5,Yes_rs6428392_x_9_5,No_rs6428392_x_7_5,\nCreate_rs2054788_Q_2,Yes_rs2054788_rs7565410_Q_6,No_rs2054788_rs9832923_Q_5.5,Yes_rs7565410_rs316598_Q_6,No_rs7565410_rs4875671_Q_5.5,Yes_rs9832923_rs6681741_Q_8.5,No_rs9832923_rs17775439_Q_8.5,Yes_rs316598_rs704737_Q_8.5,No_rs316598_rs3002685_Q_2,Yes_rs4875671_x_7_5,No_rs4875671_rs1998759_Q_2,Yes_rs6681741_rs5001924_Q_8.5,No_rs6681741_x_7_5,Yes_rs17775439_x_9_5,No_rs17775439_x_7_5,Yes_rs704737_x_7_5,No_rs704737_x_9_5,Yes_rs3002685_x_7_5,No_rs3002685_x_9_5,Yes_rs1998759_x_7_5,No_rs1998759_x_9_5,Yes_rs5001924_x_7_5,No_rs5001924_x_9_5,\nCreate_rs6730036_Q_6,Yes_rs6730036_rs7094900_Q_8.5,No_rs6730036_rs4725499_Q_5.5,Yes_rs7094900_rs1534110_Q_8.5,No_rs7094900_rs2493214_Q_2,Yes_rs4725499_rs6696281_Q_6,No_rs4725499_rs2861641_Q_6,Yes_rs1534110_rs8177963_Q_2.5,No_rs1534110_rs10753376_Q_5.5,Yes_rs2493214_x_9_5,No_rs2493214_x_7_5,Yes_rs6696281_x_7_5,No_rs6696281_x_9_5,Yes_rs2861641_rs10965215_Q_2,No_rs2861641_rs11552172_Q_8.5,Yes_rs8177963_rs17048353_Q_5.5,No_rs8177963_x_7_5,Yes_rs10753376_x_9_5,No_rs10753376_x_7_5,Yes_rs10965215_x_9_5,No_rs10965215_x_7_5,Yes_rs11552172_x_7_5,No_rs11552172_x_9_5,Yes_rs17048353_x_7_5,No_rs17048353_rs7554078_Q_5.5,Yes_rs7554078_x_9_5,No_rs7554078_x_7_5,\nCreate_rs2237059_Q_8.5,Yes_rs2237059_rs11618950_Q_2,No_rs2237059_rs11203815_Q_7,Yes_rs11618950_x_7_5,No_rs11618950_rs7358097_Q_5.5,Yes_rs11203815_rs8027732_Q_2,No_rs11203815_rs9953932_Q_5.5,Yes_rs7358097_x_7_5,No_rs7358097_x_9_5,Yes_rs8027732_rs3935066_Q_2,No_rs8027732_rs9782908_Q_6,Yes_rs9953932_rs4651330_Q_1.5,No_rs9953932_rs2776822_Q_8.5,Yes_rs3935066_x_9_5,No_rs3935066_x_7_5,Yes_rs9782908_x_9_5,No_rs9782908_x_7_5,Yes_rs4651330_x_9_5,No_rs4651330_x_7_5,Yes_rs2776822_x_9_5,No_rs2776822_rs11260568_Q_5.5,Yes_rs11260568_x_9_5,No_rs11260568_x_7_5,\n";
		//East Asian 47 trees
		//std::string treeInfo = "Create_rs2860580_Q_5.5,Yes_rs2860580_rs16961283_Q_5.5,No_rs2860580_rs9603756_Q_6,Yes_rs16961283_rs2663018_Q_8.5,No_rs16961283_rs3765764_Q_5.5,Yes_rs9603756_rs4244129_Q_6,No_rs9603756_rs3117002_Q_2,Yes_rs2663018_x_6_5,No_rs2663018_rs6694632_Q_5.5,Yes_rs3765764_x_6_5,No_rs3765764_x_3_5,Yes_rs4244129_rs6671527_Q_2,No_rs4244129_x_6_5,Yes_rs3117002_rs1670357_Q_9.5,No_rs3117002_x_3_5,Yes_rs6694632_x_3_5,No_rs6694632_x_6_5,Yes_rs6671527_rs4654522_Q_7,No_rs6671527_x_6_5,Yes_rs1670357_rs1288503_Q_6,No_rs1670357_x_3_5,Yes_rs4654522_x_3_5,No_rs4654522_x_6_5,Yes_rs1288503_x_3_5,No_rs1288503_x_6_5,\nCreate_rs2975042_Q_9.5,Yes_rs2975042_rs1567074_Q_5.5,No_rs2975042_rs6901221_Q_1.5,Yes_rs1567074_rs1885865_Q_5.5,No_rs1567074_rs2663027_Q_8.5,Yes_rs6901221_rs7705687_Q_8.5,No_rs6901221_x_3_5,Yes_rs1885865_x_6_5,No_rs1885865_x_3_5,Yes_rs2663027_x_6_5,No_rs2663027_rs2465136_Q_6,Yes_rs7705687_rs982790_Q_6,No_rs7705687_rs11236209_Q_5.5,Yes_rs2465136_x_6_5,No_rs2465136_x_3_5,Yes_rs982790_x_6_5,No_rs982790_x_3_5,Yes_rs11236209_x_3_5,No_rs11236209_rs9562578_Q_5.5,Yes_rs9562578_x_3_5,No_rs9562578_rs2036564_Q_6,Yes_rs2036564_x_3_5,No_rs2036564_rs10494055_Q_8.5,Yes_rs10494055_x_3_5,No_rs10494055_x_6_5,\nCreate_rs12698186_Q_2,Yes_rs12698186_rs1184774_Q_5.5,No_rs12698186_rs7503887_Q_8.5,Yes_rs1184774_rs12104625_Q_8.5,No_rs1184774_rs3889723_Q_6,Yes_rs7503887_rs4937070_Q_6,No_rs7503887_rs1074739_Q_3.5,Yes_rs12104625_rs13014047_Q_5.5,No_rs12104625_x_6_5,Yes_rs3889723_x_6_5,No_rs3889723_x_3_5,Yes_rs4937070_x_6_5,No_rs4937070_rs1887284_Q_2,Yes_rs1074739_rs12085319_Q_8.5,No_rs1074739_rs10933005_Q_2,Yes_rs13014047_rs7523549_Q_8.5,No_rs13014047_x_6_5,Yes_rs1887284_x_6_5,No_rs1887284_x_3_5,Yes_rs12085319_x_6_5,No_rs12085319_x_3_5,Yes_rs10933005_x_3_5,No_rs10933005_rs12124819_Q_2,Yes_rs7523549_x_3_5,No_rs7523549_x_6_5,Yes_rs12124819_x_6_5,No_rs12124819_x_3_5,\nCreate_rs4939526_Q_6,Yes_rs4939526_rs17385747_Q_2,No_rs4939526_rs12023372_Q_5.5,Yes_rs17385747_rs931250_Q_8.5,No_rs17385747_rs412763_Q_8.5,Yes_rs12023372_x_3_5,No_rs12023372_x_6_5,Yes_rs931250_rs3771848_Q_9.5,No_rs931250_x_6_5,Yes_rs412763_x_3_5,No_rs412763_x_6_5,Yes_rs3771848_x_6_5,No_rs3771848_rs12295314_Q_2,Yes_rs12295314_rs6927568_Q_5.5,No_rs12295314_x_6_5,Yes_rs6927568_x_6_5,No_rs6927568_rs6860288_Q_6,Yes_rs6860288_rs11804222_Q_2,No_rs6860288_x_6_5,Yes_rs11804222_x_6_5,No_rs11804222_x_3_5,\nCreate_rs11974206_Q_7,Yes_rs11974206_rs16843306_Q_5.5,No_rs11974206_rs2838699_Q_6,Yes_rs16843306_rs178932_Q_5.5,No_rs16843306_rs17040351_Q_2,Yes_rs2838699_rs17207681_Q_2,No_rs2838699_rs13251780_Q_6,Yes_rs178932_x_3_5,No_rs178932_x_6_5,Yes_rs17040351_rs1535682_Q_9.5,No_rs17040351_x_3_5,Yes_rs17207681_rs2072978_Q_5.5,No_rs17207681_rs2275819_Q_5.5,Yes_rs13251780_x_6_5,No_rs13251780_x_3_5,Yes_rs1535682_rs17398063_Q_5.5,No_rs1535682_rs904927_Q_6,Yes_rs2072978_x_6_5,No_rs2072978_rs2682107_Q_2,Yes_rs2275819_x_6_5,No_rs2275819_x_3_5,Yes_rs17398063_x_3_5,No_rs17398063_x_6_5,Yes_rs904927_x_3_5,No_rs904927_x_6_5,Yes_rs2682107_x_6_5,No_rs2682107_x_3_5,\nCreate_rs11104947_Q_5.5,Yes_rs11104947_rs3130244_Q_3.5,No_rs11104947_rs9600325_Q_8.5,Yes_rs3130244_rs1498016_Q_3.5,No_rs3130244_rs9549215_Q_7,Yes_rs9600325_x_6_5,No_rs9600325_rs17029445_Q_6,Yes_rs1498016_rs6699975_Q_1.5,No_rs1498016_x_3_5,Yes_rs9549215_rs11260542_Q_5.5,No_rs9549215_x_6_5,Yes_rs17029445_rs7760235_Q_7,No_rs17029445_x_6_5,Yes_rs6699975_x_3_5,No_rs6699975_x_6_5,Yes_rs11260542_x_3_5,No_rs11260542_x_6_5,Yes_rs7760235_x_6_5,No_rs7760235_rs9901316_Q_5.5,Yes_rs9901316_rs770698_Q_7,No_rs9901316_rs41471147_Q_5.5,Yes_rs770698_x_6_5,No_rs770698_x_3_5,Yes_rs41471147_x_6_5,No_rs41471147_rs3785624_Q_5.5,Yes_rs3785624_x_6_5,No_rs3785624_x_3_5,\nCreate_rs11224783_Q_3.5,Yes_rs11224783_rs9970652_Q_8.5,No_rs11224783_rs10508158_Q_6,Yes_rs9970652_x_6_5,No_rs9970652_x_3_5,Yes_rs10508158_rs9530164_Q_2,No_rs10508158_rs2133620_Q_3.5,Yes_rs9530164_rs17471932_Q_5.5,No_rs9530164_x_6_5,Yes_rs2133620_rs10924366_Q_6,No_rs2133620_rs2439292_Q_5.5,Yes_rs17471932_rs1107910_Q_8.5,No_rs17471932_rs946617_Q_9.5,Yes_rs10924366_x_6_5,No_rs10924366_x_3_5,Yes_rs2439292_x_3_5,No_rs2439292_rs9729550_Q_1.5,Yes_rs1107910_x_6_5,No_rs1107910_x_3_5,Yes_rs946617_x_6_5,No_rs946617_rs6732743_Q_2,Yes_rs9729550_x_3_5,No_rs9729550_x_6_5,Yes_rs6732743_rs17120485_Q_5.5,No_rs6732743_x_6_5,Yes_rs17120485_x_6_5,No_rs17120485_x_3_5,\nCreate_rs3217805_Q_5.5,Yes_rs3217805_rs17633478_Q_2,No_rs3217805_rs3130235_Q_5.5,Yes_rs17633478_rs16947802_Q_3.5,No_rs17633478_x_6_5,Yes_rs3130235_x_3_5,No_rs3130235_rs6886932_Q_5.5,Yes_rs16947802_x_6_5,No_rs16947802_rs7935178_Q_2,Yes_rs6886932_x_3_5,No_rs6886932_x_6_5,Yes_rs7935178_rs17676033_Q_6,No_rs7935178_x_6_5,Yes_rs17676033_rs4840510_Q_5.5,No_rs17676033_x_6_5,Yes_rs4840510_rs662353_Q_5.5,No_rs4840510_x_6_5,Yes_rs662353_rs11677624_Q_2,No_rs662353_x_6_5,Yes_rs11677624_x_6_5,No_rs11677624_x_3_5,\nCreate_rs11224762_Q_2.5,Yes_rs11224762_rs13064974_Q_8.5,No_rs11224762_rs717187_Q_5.5,Yes_rs13064974_rs2465126_Q_2,No_rs13064974_rs12788223_Q_8.5,Yes_rs717187_x_3_5,No_rs717187_rs12063386_Q_8.5,Yes_rs2465126_x_6_5,No_rs2465126_x_3_5,Yes_rs12788223_rs1780160_Q_6,No_rs12788223_rs12080410_Q_7,Yes_rs12063386_rs12034613_Q_5.5,No_rs12063386_x_3_5,Yes_rs1780160_rs2209831_Q_6,No_rs1780160_x_6_5,Yes_rs12080410_x_6_5,No_rs12080410_x_3_5,Yes_rs12034613_x_3_5,No_rs12034613_x_6_5,Yes_rs2209831_rs10244477_Q_8.5,No_rs2209831_x_6_5,Yes_rs10244477_x_6_5,No_rs10244477_rs4654354_Q_6,Yes_rs4654354_rs12740262_Q_5.5,No_rs4654354_x_6_5,Yes_rs12740262_x_3_5,No_rs12740262_x_6_5,\nCreate_rs11224765_Q_6,Yes_rs11224765_rs7626152_Q_8.5,No_rs11224765_rs10765099_Q_2,Yes_rs7626152_rs10910061_Q_2,No_rs7626152_rs11034713_Q_3.5,Yes_rs10765099_x_3_5,No_rs10765099_rs6971267_Q_5.5,Yes_rs10910061_x_3_5,No_rs10910061_x_6_5,Yes_rs11034713_rs10927559_Q_9.5,No_rs11034713_rs3756531_Q_7,Yes_rs6971267_x_3_5,No_rs6971267_x_6_5,Yes_rs10927559_x_6_5,No_rs10927559_x_3_5,Yes_rs3756531_x_6_5,No_rs3756531_rs10496977_Q_8.5,Yes_rs10496977_x_6_5,No_rs10496977_rs12480230_Q_8.5,Yes_rs12480230_rs6926826_Q_2,No_rs12480230_x_6_5,Yes_rs6926826_rs2119320_Q_8.5,No_rs6926826_x_6_5,Yes_rs2119320_x_3_5,No_rs2119320_x_6_5,\nCreate_rs1490742_Q_8.5,Yes_rs1490742_rs1891275_Q_6,No_rs1490742_rs6779452_Q_5.5,Yes_rs1891275_rs10017946_Q_6,No_rs1891275_rs13387193_Q_8.5,Yes_rs6779452_rs7540486_Q_6,No_rs6779452_rs1407448_Q_5.5,Yes_rs10017946_rs6668819_Q_8.5,No_rs10017946_rs13085028_Q_8.5,Yes_rs13387193_rs4490524_Q_8.5,No_rs13387193_x_6_5,Yes_rs7540486_x_3_5,No_rs7540486_x_6_5,Yes_rs1407448_x_6_5,No_rs1407448_rs16850259_Q_8.5,Yes_rs6668819_x_3_5,No_rs6668819_x_6_5,Yes_rs13085028_x_3_5,No_rs13085028_rs7213911_Q_2,Yes_rs4490524_x_3_5,No_rs4490524_x_6_5,Yes_rs16850259_x_6_5,No_rs16850259_x_3_5,Yes_rs7213911_rs4648468_Q_5.5,No_rs7213911_x_3_5,Yes_rs4648468_x_3_5,No_rs4648468_x_6_5,\nCreate_rs2261033_Q_5.5,Yes_rs2261033_rs7122010_Q_6,No_rs2261033_rs1351499_Q_5.5,Yes_rs7122010_rs615625_Q_1.5,No_rs7122010_rs2840531_Q_8.5,Yes_rs1351499_rs10013441_Q_8.5,No_rs1351499_rs2499714_Q_8.5,Yes_rs615625_rs2388746_Q_2,No_rs615625_rs10915307_Q_2,Yes_rs2840531_x_6_5,No_rs2840531_x_3_5,Yes_rs10013441_x_6_5,No_rs10013441_rs2651902_Q_6,Yes_rs2499714_rs7859023_Q_5.5,No_rs2499714_x_3_5,Yes_rs2388746_x_6_5,No_rs2388746_rs9497981_Q_2,Yes_rs10915307_x_3_5,No_rs10915307_x_6_5,Yes_rs2651902_x_3_5,No_rs2651902_x_6_5,Yes_rs7859023_x_6_5,No_rs7859023_x_3_5,Yes_rs9497981_rs10159030_Q_5.5,No_rs9497981_x_6_5,Yes_rs10159030_x_6_5,No_rs10159030_x_3_5,\nCreate_rs10865278_Q_5.5,Yes_rs10865278_rs2961739_Q_8.5,No_rs10865278_rs11223548_Q_8.5,Yes_rs2961739_rs27433_Q_9.5,No_rs2961739_rs6018084_Q_5.5,Yes_rs11223548_rs2275595_Q_5.5,No_rs11223548_rs608210_Q_2,Yes_rs27433_rs13042833_Q_8.5,No_rs27433_rs12073172_Q_5.5,Yes_rs6018084_x_6_5,No_rs6018084_rs12403351_Q_5.5,Yes_rs2275595_x_6_5,No_rs2275595_rs13322517_Q_2,Yes_rs608210_x_3_5,No_rs608210_x_6_5,Yes_rs13042833_rs379717_Q_8.5,No_rs13042833_x_3_5,Yes_rs12073172_x_3_5,No_rs12073172_x_6_5,Yes_rs12403351_x_6_5,No_rs12403351_x_3_5,Yes_rs13322517_rs12467106_Q_5.5,No_rs13322517_x_6_5,Yes_rs379717_x_3_5,No_rs379717_rs6581191_Q_2,Yes_rs12467106_x_6_5,No_rs12467106_x_3_5,Yes_rs6581191_x_3_5,No_rs6581191_x_6_5,\nCreate_rs9530168_Q_5.5,Yes_rs9530168_rs2794860_Q_6,No_rs9530168_rs9497982_Q_2,Yes_rs2794860_x_3_5,No_rs2794860_x_6_5,Yes_rs9497982_rs17137253_Q_2,No_rs9497982_x_6_5,Yes_rs17137253_rs12532805_Q_8.5,No_rs17137253_x_6_5,Yes_rs12532805_rs6717406_Q_9.5,No_rs12532805_rs10954494_Q_2,Yes_rs6717406_x_6_5,No_rs6717406_rs10803583_Q_3.5,Yes_rs10954494_x_3_5,No_rs10954494_x_6_5,Yes_rs10803583_x_6_5,No_rs10803583_rs11563201_Q_6,Yes_rs11563201_rs11586974_Q_8.5,No_rs11563201_x_6_5,Yes_rs11586974_x_3_5,No_rs11586974_x_6_5,\nCreate_rs1508594_Q_8.5,Yes_rs1508594_rs12615002_Q_6,No_rs1508594_rs770576_Q_2,Yes_rs12615002_rs211605_Q_5.5,No_rs12615002_rs3768337_Q_2,Yes_rs770576_rs13203813_Q_6,No_rs770576_rs17069519_Q_3.5,Yes_rs211605_rs11254106_Q_5.5,No_rs211605_x_3_5,Yes_rs3768337_x_3_5,No_rs3768337_x_6_5,Yes_rs13203813_rs16968045_Q_5.5,No_rs13203813_x_6_5,Yes_rs17069519_x_3_5,No_rs17069519_x_6_5,Yes_rs11254106_x_3_5,No_rs11254106_x_6_5,Yes_rs16968045_x_6_5,No_rs16968045_rs12219674_Q_8.5,Yes_rs12219674_x_6_5,No_rs12219674_rs4637726_Q_2,Yes_rs4637726_x_3_5,No_rs4637726_x_6_5,\nCreate_rs10176837_Q_2.5,Yes_rs10176837_rs313243_Q_2,No_rs10176837_rs7985210_Q_9.5,Yes_rs313243_rs11224773_Q_2,No_rs313243_x_6_5,Yes_rs7985210_x_3_5,No_rs7985210_x_6_5,Yes_rs11224773_rs1817653_Q_5.5,No_rs11224773_rs7832879_Q_5.5,Yes_rs1817653_rs4648745_Q_6,No_rs1817653_rs3809250_Q_1.5,Yes_rs7832879_rs4648782_Q_5.5,No_rs7832879_x_3_5,Yes_rs4648745_x_3_5,No_rs4648745_x_6_5,Yes_rs3809250_rs17783275_Q_5.5,No_rs3809250_x_6_5,Yes_rs4648782_x_3_5,No_rs4648782_x_6_5,Yes_rs17783275_x_6_5,No_rs17783275_rs667907_Q_5.5,Yes_rs667907_rs2298225_Q_1.5,No_rs667907_x_6_5,Yes_rs2298225_x_6_5,No_rs2298225_x_3_5,\nCreate_rs7644875_Q_2,Yes_rs7644875_rs17799178_Q_2,No_rs7644875_rs16823350_Q_2,Yes_rs17799178_rs17286171_Q_6,No_rs17799178_rs1994851_Q_5.5,Yes_rs16823350_x_3_5,No_rs16823350_x_6_5,Yes_rs17286171_rs12136921_Q_5.5,No_rs17286171_rs2092595_Q_3.5,Yes_rs1994851_x_3_5,No_rs1994851_rs1749951_Q_2,Yes_rs12136921_rs4074197_Q_2,No_rs12136921_rs17150469_Q_6,Yes_rs2092595_x_6_5,No_rs2092595_x_3_5,Yes_rs1749951_x_3_5,No_rs1749951_x_6_5,Yes_rs4074197_x_6_5,No_rs4074197_x_3_5,Yes_rs17150469_rs11703828_Q_6,No_rs17150469_x_6_5,Yes_rs11703828_rs1222144_Q_2,No_rs11703828_x_6_5,Yes_rs1222144_rs9504229_Q_6,No_rs1222144_x_6_5,Yes_rs9504229_x_3_5,No_rs9504229_x_6_5,\nCreate_rs41385746_Q_6,Yes_rs41385746_rs7928922_Q_6,No_rs41385746_rs9379827_Q_3.5,Yes_rs7928922_rs10849181_Q_8.5,No_rs7928922_rs7544659_Q_2,Yes_rs9379827_rs7640543_Q_5.5,No_rs9379827_rs3088182_Q_6,Yes_rs10849181_rs10493770_Q_6,No_rs10849181_rs6656160_Q_2,Yes_rs7544659_x_3_5,No_rs7544659_x_6_5,Yes_rs7640543_x_6_5,No_rs7640543_x_3_5,Yes_rs3088182_rs7219975_Q_2,No_rs3088182_rs2390135_Q_8.5,Yes_rs10493770_x_6_5,No_rs10493770_rs12092254_Q_2,Yes_rs6656160_x_3_5,No_rs6656160_x_6_5,Yes_rs7219975_x_3_5,No_rs7219975_rs7547028_Q_2,Yes_rs2390135_x_6_5,No_rs2390135_rs13129_Q_6,Yes_rs12092254_x_6_5,No_rs12092254_x_3_5,Yes_rs7547028_rs2645072_Q_1.5,No_rs7547028_x_3_5,Yes_rs13129_x_3_5,No_rs13129_x_6_5,Yes_rs2645072_x_3_5,No_rs2645072_x_6_5,\nCreate_rs12697189_Q_6,Yes_rs12697189_rs7935581_Q_2,No_rs12697189_rs9277027_Q_2,Yes_rs7935581_rs2224609_Q_2,No_rs7935581_rs12027396_Q_8.5,Yes_rs9277027_rs4935640_Q_3.5,No_rs9277027_rs8135343_Q_2,Yes_rs2224609_rs4755957_Q_8.5,No_rs2224609_rs10910017_Q_2,Yes_rs12027396_x_3_5,No_rs12027396_x_6_5,Yes_rs4935640_x_3_5,No_rs4935640_x_6_5,Yes_rs8135343_x_3_5,No_rs8135343_x_6_5,Yes_rs4755957_x_6_5,No_rs4755957_rs13392175_Q_9.5,Yes_rs10910017_x_3_5,No_rs10910017_x_6_5,Yes_rs13392175_rs11120989_Q_2,No_rs13392175_rs11770368_Q_2,Yes_rs11120989_x_6_5,No_rs11120989_x_3_5,Yes_rs11770368_x_3_5,No_rs11770368_x_6_5,\nCreate_rs6436971_Q_8.5,Yes_rs6436971_rs953184_Q_3.5,No_rs6436971_rs12765118_Q_5.5,Yes_rs953184_x_3_5,No_rs953184_rs28414855_Q_1.5,Yes_rs12765118_rs1883472_Q_6,No_rs12765118_rs7378826_Q_9.5,Yes_rs28414855_x_3_5,No_rs28414855_x_6_5,Yes_rs1883472_rs10915396_Q_6,No_rs1883472_rs11132199_Q_6,Yes_rs7378826_rs16824860_Q_8.5,No_rs7378826_rs34136796_Q_3.5,Yes_rs10915396_x_6_5,No_rs10915396_x_3_5,Yes_rs11132199_x_3_5,No_rs11132199_x_6_5,Yes_rs16824860_x_6_5,No_rs16824860_x_3_5,Yes_rs34136796_rs4654468_Q_6,No_rs34136796_rs333851_Q_2,Yes_rs4654468_x_3_5,No_rs4654468_x_6_5,Yes_rs333851_rs17599139_Q_5.5,No_rs333851_x_6_5,Yes_rs17599139_x_6_5,No_rs17599139_rs17389948_Q_8.5,Yes_rs17389948_x_3_5,No_rs17389948_x_6_5,\nCreate_rs360710_Q_5.5,Yes_rs360710_rs12036857_Q_7,No_rs360710_rs12658762_Q_8.5,Yes_rs12036857_x_6_5,No_rs12036857_x_3_5,Yes_rs12658762_rs16957364_Q_8.5,No_rs12658762_rs4298263_Q_2,Yes_rs16957364_rs7512482_Q_6,No_rs16957364_rs3739477_Q_7,Yes_rs4298263_rs1376444_Q_6,No_rs4298263_rs7537756_Q_2,Yes_rs7512482_x_3_5,No_rs7512482_x_6_5,Yes_rs3739477_x_6_5,No_rs3739477_rs1288742_Q_5.5,Yes_rs1376444_rs17358956_Q_1.5,No_rs1376444_x_3_5,Yes_rs7537756_x_3_5,No_rs7537756_x_6_5,Yes_rs1288742_rs17737466_Q_6,No_rs1288742_x_6_5,Yes_rs17358956_x_6_5,No_rs17358956_x_3_5,Yes_rs17737466_rs1845017_Q_5.5,No_rs17737466_x_6_5,Yes_rs1845017_rs11126130_Q_2.5,No_rs1845017_x_6_5,Yes_rs11126130_x_3_5,No_rs11126130_x_6_5,\nCreate_rs3749946_Q_3.5,Yes_rs3749946_rs321125_Q_5.5,No_rs3749946_rs17140182_Q_2,Yes_rs321125_rs7512133_Q_5.5,No_rs321125_rs11120837_Q_8.5,Yes_rs17140182_rs1569307_Q_5.5,No_rs17140182_rs10797386_Q_2,Yes_rs7512133_x_6_5,No_rs7512133_x_3_5,Yes_rs11120837_x_3_5,No_rs11120837_x_6_5,Yes_rs1569307_rs919688_Q_2,No_rs1569307_rs191708_Q_2,Yes_rs10797386_x_3_5,No_rs10797386_x_6_5,Yes_rs919688_x_6_5,No_rs919688_x_3_5,Yes_rs191708_rs12006467_Q_8.5,No_rs191708_x_6_5,Yes_rs12006467_x_6_5,No_rs12006467_rs914958_Q_2,Yes_rs914958_rs828316_Q_2,No_rs914958_x_6_5,Yes_rs828316_x_6_5,No_rs828316_x_3_5,\nCreate_rs13414393_Q_6,Yes_rs13414393_rs10895109_Q_6,No_rs13414393_rs353887_Q_8.5,Yes_rs10895109_rs7918954_Q_6,No_rs10895109_rs4652992_Q_8.5,Yes_rs353887_rs4298709_Q_5.5,No_rs353887_rs1998759_Q_2,Yes_rs7918954_rs7563543_Q_5.5,No_rs7918954_x_6_5,Yes_rs4652992_x_3_5,No_rs4652992_x_6_5,Yes_rs4298709_rs10804925_Q_2,No_rs4298709_rs3815073_Q_8.5,Yes_rs1998759_x_6_5,No_rs1998759_x_3_5,Yes_rs7563543_x_6_5,No_rs7563543_rs17854636_Q_6,Yes_rs10804925_x_6_5,No_rs10804925_rs2379143_Q_6,Yes_rs3815073_rs284243_Q_2,No_rs3815073_rs31300_Q_6,Yes_rs17854636_x_3_5,No_rs17854636_x_6_5,Yes_rs2379143_x_6_5,No_rs2379143_x_3_5,Yes_rs284243_x_3_5,No_rs284243_x_6_5,Yes_rs31300_x_3_5,No_rs31300_x_6_5,\nCreate_rs6562748_Q_1.5,Yes_rs6562748_rs4571809_Q_9.5,No_rs6562748_rs10060821_Q_8.5,Yes_rs4571809_rs6737431_Q_2,No_rs4571809_rs7640145_Q_2,Yes_rs10060821_x_6_5,No_rs10060821_x_3_5,Yes_rs6737431_rs342136_Q_6,No_rs6737431_rs582322_Q_8.5,Yes_rs7640145_rs3930233_Q_8.5,No_rs7640145_x_6_5,Yes_rs342136_rs4131141_Q_6,No_rs342136_rs6665000_Q_1.5,Yes_rs582322_x_6_5,No_rs582322_x_3_5,Yes_rs3930233_rs4455137_Q_5.5,No_rs3930233_rs4646329_Q_6,Yes_rs4131141_x_3_5,No_rs4131141_x_6_5,Yes_rs6665000_x_6_5,No_rs6665000_x_3_5,Yes_rs4455137_x_6_5,No_rs4455137_x_3_5,Yes_rs4646329_rs3893319_Q_2,No_rs4646329_x_6_5,Yes_rs3893319_x_3_5,No_rs3893319_x_6_5,\nCreate_rs11841589_Q_8.5,Yes_rs11841589_rs4707130_Q_2,No_rs11841589_rs6605005_Q_8.5,Yes_rs4707130_rs17680606_Q_5.5,No_rs4707130_rs10910029_Q_2,Yes_rs6605005_x_3_5,No_rs6605005_x_6_5,Yes_rs17680606_rs9328202_Q_3.5,No_rs17680606_rs4580387_Q_2,Yes_rs10910029_x_3_5,No_rs10910029_x_6_5,Yes_rs9328202_x_6_5,No_rs9328202_rs11013746_Q_6,Yes_rs4580387_x_3_5,No_rs4580387_x_6_5,Yes_rs11013746_rs10858363_Q_6,No_rs11013746_rs9442387_Q_6,Yes_rs10858363_rs16978159_Q_8.5,No_rs10858363_x_6_5,Yes_rs9442387_x_6_5,No_rs9442387_x_3_5,Yes_rs16978159_x_6_5,No_rs16978159_rs182532_Q_8.5,Yes_rs182532_x_3_5,No_rs182532_x_6_5,\nCreate_rs3130237_Q_8.5,Yes_rs3130237_rs2765015_Q_2,No_rs3130237_rs12104489_Q_9.5,Yes_rs2765015_x_6_5,No_rs2765015_x_3_5,Yes_rs12104489_rs6940237_Q_6,No_rs12104489_rs2298464_Q_5.5,Yes_rs6940237_rs6564809_Q_2,No_rs6940237_rs12748433_Q_5.5,Yes_rs2298464_rs16933163_Q_2,No_rs2298464_rs11016442_Q_8.5,Yes_rs6564809_x_3_5,No_rs6564809_rs1369407_Q_6,Yes_rs12748433_x_3_5,No_rs12748433_x_6_5,Yes_rs16933163_x_6_5,No_rs16933163_x_3_5,Yes_rs11016442_x_6_5,No_rs11016442_rs315808_Q_9.5,Yes_rs1369407_x_3_5,No_rs1369407_rs4233033_Q_8.5,Yes_rs315808_x_6_5,No_rs315808_rs6420051_Q_6,Yes_rs4233033_x_6_5,No_rs4233033_x_3_5,Yes_rs6420051_x_6_5,No_rs6420051_x_3_5,\nCreate_rs3116996_Q_7,Yes_rs3116996_rs2291889_Q_2,No_rs3116996_rs2920297_Q_2,Yes_rs2291889_x_6_5,No_rs2291889_x_3_5,Yes_rs2920297_rs443592_Q_1.5,No_rs2920297_rs11959012_Q_6,Yes_rs443592_rs217656_Q_6,No_rs443592_rs4920386_Q_2.5,Yes_rs11959012_rs1791466_Q_5.5,No_rs11959012_rs17649182_Q_6,Yes_rs217656_rs28710181_Q_8.5,No_rs217656_x_6_5,Yes_rs4920386_x_6_5,No_rs4920386_x_3_5,Yes_rs1791466_rs16839450_Q_6,No_rs1791466_rs17561133_Q_8.5,Yes_rs17649182_x_3_5,No_rs17649182_rs2298217_Q_6,Yes_rs28710181_x_3_5,No_rs28710181_x_6_5,Yes_rs16839450_x_6_5,No_rs16839450_x_3_5,Yes_rs17561133_x_3_5,No_rs17561133_rs1999462_Q_8.5,Yes_rs2298217_x_3_5,No_rs2298217_x_6_5,Yes_rs1999462_x_6_5,No_rs1999462_x_3_5,\nCreate_rs6901830_Q_5.5,Yes_rs6901830_rs11488462_Q_5.5,No_rs6901830_rs2976392_Q_5.5,Yes_rs11488462_x_3_5,No_rs11488462_x_6_5,Yes_rs2976392_rs1960425_Q_8.5,No_rs2976392_rs9518309_Q_2,Yes_rs1960425_rs375980_Q_8.5,No_rs1960425_rs10460504_Q_6,Yes_rs9518309_rs10500071_Q_8.5,No_rs9518309_x_6_5,Yes_rs375980_rs11585587_Q_2,No_rs375980_x_6_5,Yes_rs10460504_rs8181588_Q_8.5,No_rs10460504_rs7995074_Q_5.5,Yes_rs10500071_rs4926684_Q_2,No_rs10500071_x_6_5,Yes_rs11585587_x_6_5,No_rs11585587_x_3_5,Yes_rs8181588_rs7203853_Q_5.5,No_rs8181588_x_3_5,Yes_rs7995074_x_3_5,No_rs7995074_x_6_5,Yes_rs4926684_x_6_5,No_rs4926684_x_3_5,Yes_rs7203853_x_3_5,No_rs7203853_x_6_5,\nCreate_rs4662280_Q_3.5,Yes_rs4662280_rs16895223_Q_5.5,No_rs4662280_rs1349283_Q_6,Yes_rs16895223_rs6833864_Q_8.5,No_rs16895223_rs12119711_Q_6,Yes_rs1349283_rs7244157_Q_3.5,No_rs1349283_rs662009_Q_7,Yes_rs6833864_x_3_5,No_rs6833864_rs13160949_Q_8.5,Yes_rs12119711_x_3_5,No_rs12119711_x_6_5,Yes_rs7244157_rs6694834_Q_6,No_rs7244157_rs4648805_Q_5.5,Yes_rs662009_x_6_5,No_rs662009_rs2503823_Q_1.5,Yes_rs13160949_rs1275569_Q_5.5,No_rs13160949_rs6844821_Q_5.5,Yes_rs6694834_x_6_5,No_rs6694834_x_3_5,Yes_rs4648805_x_6_5,No_rs4648805_x_3_5,Yes_rs2503823_rs12755560_Q_2,No_rs2503823_x_6_5,Yes_rs1275569_x_3_5,No_rs1275569_x_6_5,Yes_rs6844821_x_3_5,No_rs6844821_x_6_5,Yes_rs12755560_x_6_5,No_rs12755560_x_3_5,\nCreate_rs374722_Q_2,Yes_rs374722_rs485276_Q_3.5,No_rs374722_rs2418268_Q_6,Yes_rs485276_x_6_5,No_rs485276_rs2272052_Q_8.5,Yes_rs2418268_rs11580074_Q_5.5,No_rs2418268_rs12254574_Q_5.5,Yes_rs2272052_x_6_5,No_rs2272052_rs17221329_Q_5.5,Yes_rs11580074_rs3935066_Q_5.5,No_rs11580074_rs2199215_Q_8.5,Yes_rs12254574_rs2651929_Q_8.5,No_rs12254574_rs478611_Q_5.5,Yes_rs17221329_rs10932401_Q_7,No_rs17221329_x_6_5,Yes_rs3935066_x_6_5,No_rs3935066_x_3_5,Yes_rs2199215_x_3_5,No_rs2199215_x_6_5,Yes_rs2651929_x_3_5,No_rs2651929_x_6_5,Yes_rs478611_x_3_5,No_rs478611_rs710139_Q_8.5,Yes_rs10932401_rs17033865_Q_7,No_rs10932401_x_6_5,Yes_rs710139_rs760925_Q_2,No_rs710139_x_3_5,Yes_rs17033865_x_6_5,No_rs17033865_x_3_5,Yes_rs760925_x_3_5,No_rs760925_x_6_5,\nCreate_rs11104775_Q_6,Yes_rs11104775_rs174511_Q_5.5,No_rs11104775_rs17033938_Q_2,Yes_rs174511_rs1355781_Q_8.5,No_rs174511_rs3777997_Q_2,Yes_rs17033938_rs4648807_Q_6,No_rs17033938_rs10408164_Q_5.5,Yes_rs1355781_rs620950_Q_5.5,No_rs1355781_x_3_5,Yes_rs3777997_rs871952_Q_5.5,No_rs3777997_x_6_5,Yes_rs4648807_x_6_5,No_rs4648807_x_3_5,Yes_rs10408164_x_3_5,No_rs10408164_rs1011609_Q_2,Yes_rs620950_x_6_5,No_rs620950_x_3_5,Yes_rs871952_x_6_5,No_rs871952_rs566105_Q_8.5,Yes_rs1011609_x_3_5,No_rs1011609_rs11466691_Q_8.5,Yes_rs566105_rs17075791_Q_8.5,No_rs566105_x_6_5,Yes_rs11466691_x_3_5,No_rs11466691_x_6_5,Yes_rs17075791_x_6_5,No_rs17075791_rs1841241_Q_5.5,Yes_rs1841241_x_3_5,No_rs1841241_x_6_5,\nCreate_rs4525889_Q_6,Yes_rs4525889_rs9328204_Q_2,No_rs4525889_rs10843585_Q_6,Yes_rs9328204_rs8016966_Q_5.5,No_rs9328204_rs1926883_Q_5.5,Yes_rs10843585_rs3762084_Q_6,No_rs10843585_rs3820330_Q_3.5,Yes_rs8016966_rs9502295_Q_7,No_rs8016966_rs6695131_Q_8.5,Yes_rs1926883_x_6_5,No_rs1926883_x_3_5,Yes_rs3762084_rs2455107_Q_8.5,No_rs3762084_rs4040604_Q_8.5,Yes_rs3820330_rs10909872_Q_9.5,No_rs3820330_x_3_5,Yes_rs9502295_x_6_5,No_rs9502295_rs1955614_Q_8.5,Yes_rs6695131_x_6_5,No_rs6695131_x_3_5,Yes_rs2455107_x_3_5,No_rs2455107_x_6_5,Yes_rs4040604_x_6_5,No_rs4040604_x_3_5,Yes_rs10909872_x_3_5,No_rs10909872_x_6_5,Yes_rs1955614_x_6_5,No_rs1955614_rs10512019_Q_8.5,Yes_rs10512019_x_6_5,No_rs10512019_x_3_5,\nCreate_rs10073882_Q_8.5,Yes_rs10073882_rs1250544_Q_2,No_rs10073882_rs12534948_Q_5.5,Yes_rs1250544_x_3_5,No_rs1250544_rs3737728_Q_2,Yes_rs12534948_rs7235487_Q_8.5,No_rs12534948_rs1869609_Q_5.5,Yes_rs3737728_x_3_5,No_rs3737728_x_6_5,Yes_rs7235487_rs6603781_Q_5.5,No_rs7235487_rs2277317_Q_2,Yes_rs1869609_x_6_5,No_rs1869609_x_3_5,Yes_rs6603781_x_3_5,No_rs6603781_x_6_5,Yes_rs2277317_rs1900102_Q_8.5,No_rs2277317_rs11707193_Q_1.5,Yes_rs1900102_x_3_5,No_rs1900102_x_6_5,Yes_rs11707193_rs603638_Q_5.5,No_rs11707193_x_6_5,Yes_rs603638_x_6_5,No_rs603638_rs863454_Q_1.5,Yes_rs863454_x_6_5,No_rs863454_x_3_5,\nCreate_rs2622637_Q_9.5,Yes_rs2622637_rs12532116_Q_7,No_rs2622637_rs946236_Q_5.5,Yes_rs12532116_rs12547611_Q_5.5,No_rs12532116_rs10168169_Q_8.5,Yes_rs946236_rs2382019_Q_2,No_rs946236_rs1687331_Q_2,Yes_rs12547611_rs751396_Q_6,No_rs12547611_rs13084153_Q_8.5,Yes_rs10168169_rs319870_Q_5.5,No_rs10168169_x_6_5,Yes_rs2382019_rs164868_Q_6,No_rs2382019_rs1914778_Q_2,Yes_rs1687331_x_3_5,No_rs1687331_x_6_5,Yes_rs751396_x_3_5,No_rs751396_x_6_5,Yes_rs13084153_rs17028725_Q_2,No_rs13084153_x_6_5,Yes_rs319870_rs17036706_Q_9.5,No_rs319870_x_6_5,Yes_rs164868_x_6_5,No_rs164868_x_3_5,Yes_rs1914778_x_3_5,No_rs1914778_x_6_5,Yes_rs17028725_x_3_5,No_rs17028725_x_6_5,Yes_rs17036706_x_3_5,No_rs17036706_x_6_5,\nCreate_rs7938730_Q_8.5,Yes_rs7938730_rs12561942_Q_7,No_rs7938730_rs10444351_Q_5.5,Yes_rs12561942_x_6_5,No_rs12561942_x_3_5,Yes_rs10444351_rs1035582_Q_5.5,No_rs10444351_rs873525_Q_5.5,Yes_rs1035582_x_3_5,No_rs1035582_rs2611423_Q_1.5,Yes_rs873525_rs2000319_Q_5.5,No_rs873525_rs640655_Q_6,Yes_rs2611423_x_6_5,No_rs2611423_x_3_5,Yes_rs2000319_x_6_5,No_rs2000319_x_3_5,Yes_rs640655_rs742636_Q_6,No_rs640655_x_6_5,Yes_rs742636_rs12250707_Q_6,No_rs742636_rs487113_Q_8.5,Yes_rs12250707_rs3757181_Q_2,No_rs12250707_x_6_5,Yes_rs487113_x_6_5,No_rs487113_x_3_5,Yes_rs3757181_x_3_5,No_rs3757181_x_6_5,\nCreate_rs1369323_Q_8.5,Yes_rs1369323_rs4101233_Q_8.5,No_rs1369323_rs7542677_Q_6,Yes_rs4101233_x_6_5,No_rs4101233_x_3_5,Yes_rs7542677_rs10046248_Q_8.5,No_rs7542677_rs17764769_Q_8.5,Yes_rs10046248_rs10914477_Q_5.5,No_rs10046248_rs11573979_Q_5.5,Yes_rs17764769_rs10799255_Q_5.5,No_rs17764769_x_3_5,Yes_rs10914477_rs1320565_Q_8.5,No_rs10914477_rs6030932_Q_9.5,Yes_rs11573979_x_3_5,No_rs11573979_x_6_5,Yes_rs10799255_x_6_5,No_rs10799255_x_3_5,Yes_rs1320565_x_6_5,No_rs1320565_x_3_5,Yes_rs6030932_x_6_5,No_rs6030932_rs333846_Q_2,Yes_rs333846_rs642490_Q_2,No_rs333846_x_6_5,Yes_rs642490_rs7921121_Q_5.5,No_rs642490_x_6_5,Yes_rs7921121_x_6_5,No_rs7921121_rs6698924_Q_1.5,Yes_rs6698924_x_3_5,No_rs6698924_x_6_5,\nCreate_rs8093745_Q_2,Yes_rs8093745_rs10836933_Q_7,No_rs8093745_rs6577582_Q_3.5,Yes_rs10836933_rs1123571_Q_2,No_rs10836933_rs4617036_Q_1.5,Yes_rs6577582_x_3_5,No_rs6577582_x_6_5,Yes_rs1123571_x_3_5,No_rs1123571_x_6_5,Yes_rs4617036_rs2513850_Q_5.5,No_rs4617036_rs689391_Q_8.5,Yes_rs2513850_x_6_5,No_rs2513850_x_3_5,Yes_rs689391_rs1869972_Q_2,No_rs689391_rs7767039_Q_5.5,Yes_rs1869972_x_3_5,No_rs1869972_x_6_5,Yes_rs7767039_rs17018699_Q_1.5,No_rs7767039_rs2268063_Q_6,Yes_rs17018699_x_3_5,No_rs17018699_x_6_5,Yes_rs2268063_rs333859_Q_5.5,No_rs2268063_x_6_5,Yes_rs333859_x_6_5,No_rs333859_rs2273939_Q_6,Yes_rs2273939_x_3_5,No_rs2273939_x_6_5,\nCreate_rs1017783_Q_5.5,Yes_rs1017783_rs2000177_Q_8.5,No_rs1017783_rs2295615_Q_5.5,Yes_rs2000177_rs8041381_Q_2,No_rs2000177_x_3_5,Yes_rs2295615_rs3824405_Q_9.5,No_rs2295615_rs7526076_Q_5.5,Yes_rs8041381_rs202481_Q_8.5,No_rs8041381_x_3_5,Yes_rs3824405_rs2173201_Q_1.5,No_rs3824405_rs1317894_Q_6,Yes_rs7526076_x_3_5,No_rs7526076_x_6_5,Yes_rs202481_x_3_5,No_rs202481_rs7016943_Q_6,Yes_rs2173201_rs17151786_Q_8.5,No_rs2173201_x_3_5,Yes_rs1317894_rs7687912_Q_8.5,No_rs1317894_x_6_5,Yes_rs7016943_x_3_5,No_rs7016943_rs16840755_Q_1.5,Yes_rs17151786_x_3_5,No_rs17151786_x_6_5,Yes_rs7687912_x_6_5,No_rs7687912_x_3_5,Yes_rs16840755_x_3_5,No_rs16840755_x_6_5,\nCreate_rs1421617_Q_5.5,Yes_rs1421617_rs2320378_Q_8.5,No_rs1421617_rs8050818_Q_5.5,Yes_rs2320378_rs3741026_Q_5.5,No_rs2320378_rs17093760_Q_9.5,Yes_rs8050818_rs4846908_Q_5.5,No_rs8050818_rs16827628_Q_6,Yes_rs3741026_x_3_5,No_rs3741026_rs4785322_Q_6,Yes_rs17093760_rs4416143_Q_5.5,No_rs17093760_rs12090967_Q_6,Yes_rs4846908_x_3_5,No_rs4846908_x_6_5,Yes_rs16827628_rs16826345_Q_8.5,No_rs16827628_x_6_5,Yes_rs4785322_x_3_5,No_rs4785322_x_6_5,Yes_rs4416143_rs7534617_Q_8.5,No_rs4416143_rs2606414_Q_8.5,Yes_rs12090967_x_6_5,No_rs12090967_x_3_5,Yes_rs16826345_x_6_5,No_rs16826345_rs4131373_Q_5.5,Yes_rs7534617_x_3_5,No_rs7534617_x_6_5,Yes_rs2606414_x_3_5,No_rs2606414_x_6_5,Yes_rs4131373_x_6_5,No_rs4131373_x_3_5,\nCreate_rs174510_Q_8.5,Yes_rs174510_rs4969058_Q_5.5,No_rs174510_rs17821703_Q_2,Yes_rs4969058_rs11538784_Q_9.5,No_rs4969058_rs4942308_Q_8.5,Yes_rs17821703_rs11251966_Q_2,No_rs17821703_rs12738365_Q_8.5,Yes_rs11538784_x_3_5,No_rs11538784_x_6_5,Yes_rs4942308_x_6_5,No_rs4942308_x_3_5,Yes_rs11251966_rs2105606_Q_2,No_rs11251966_rs10240570_Q_6,Yes_rs12738365_x_6_5,No_rs12738365_x_3_5,Yes_rs2105606_rs1511412_Q_5.5,No_rs2105606_x_6_5,Yes_rs10240570_rs16824948_Q_6,No_rs10240570_x_6_5,Yes_rs1511412_x_6_5,No_rs1511412_rs1877351_Q_2,Yes_rs16824948_x_3_5,No_rs16824948_x_6_5,Yes_rs1877351_rs11127018_Q_6,No_rs1877351_x_6_5,Yes_rs11127018_x_6_5,No_rs11127018_x_3_5,\nCreate_rs174504_Q_9.5,Yes_rs174504_rs4937384_Q_8.5,No_rs174504_rs4255200_Q_2,Yes_rs4937384_rs7658552_Q_8.5,No_rs4937384_rs428180_Q_3.5,Yes_rs4255200_rs372440_Q_5.5,No_rs4255200_rs10752741_Q_5.5,Yes_rs7658552_x_6_5,No_rs7658552_x_3_5,Yes_rs428180_x_3_5,No_rs428180_x_6_5,Yes_rs372440_rs1398572_Q_2,No_rs372440_rs12490963_Q_5.5,Yes_rs10752741_x_6_5,No_rs10752741_x_3_5,Yes_rs1398572_rs4935397_Q_6,No_rs1398572_x_6_5,Yes_rs12490963_rs7520258_Q_6,No_rs12490963_x_3_5,Yes_rs4935397_x_6_5,No_rs4935397_rs11611632_Q_8.5,Yes_rs7520258_x_3_5,No_rs7520258_x_6_5,Yes_rs11611632_rs9287778_Q_1.5,No_rs11611632_x_6_5,Yes_rs9287778_x_3_5,No_rs9287778_x_6_5,\nCreate_rs4904385_Q_2,Yes_rs4904385_rs6560612_Q_6,No_rs4904385_rs1148214_Q_8.5,Yes_rs6560612_rs243996_Q_7,No_rs6560612_rs2348394_Q_7,Yes_rs1148214_x_3_5,No_rs1148214_rs702552_Q_8.5,Yes_rs243996_rs1571149_Q_5.5,No_rs243996_x_6_5,Yes_rs2348394_x_6_5,No_rs2348394_rs2713721_Q_2,Yes_rs702552_x_3_5,No_rs702552_x_6_5,Yes_rs1571149_x_6_5,No_rs1571149_x_3_5,Yes_rs2713721_x_6_5,No_rs2713721_rs12266901_Q_8.5,Yes_rs12266901_x_6_5,No_rs12266901_rs9559436_Q_9.5,Yes_rs9559436_x_6_5,No_rs9559436_rs4530328_Q_8.5,Yes_rs4530328_x_6_5,No_rs4530328_rs2958272_Q_9.5,Yes_rs2958272_x_3_5,No_rs2958272_x_6_5,\nCreate_rs174519_Q_8.5,Yes_rs174519_rs1874799_Q_8.5,No_rs174519_rs2423402_Q_8.5,Yes_rs1874799_rs686543_Q_6,No_rs1874799_rs6662635_Q_2,Yes_rs2423402_rs10913136_Q_2,No_rs2423402_rs2237551_Q_8.5,Yes_rs686543_x_3_5,No_rs686543_x_6_5,Yes_rs6662635_x_3_5,No_rs6662635_x_6_5,Yes_rs10913136_x_3_5,No_rs10913136_x_6_5,Yes_rs2237551_rs10863308_Q_3.5,No_rs2237551_rs2432785_Q_3.5,Yes_rs10863308_x_3_5,No_rs10863308_x_6_5,Yes_rs2432785_x_6_5,No_rs2432785_rs1868150_Q_6,Yes_rs1868150_rs6879391_Q_2.5,No_rs1868150_x_6_5,Yes_rs6879391_rs7944342_Q_8.5,No_rs6879391_x_6_5,Yes_rs7944342_x_6_5,No_rs7944342_rs953599_Q_3.5,Yes_rs953599_x_6_5,No_rs953599_x_3_5,\nCreate_rs7587849_Q_8.5,Yes_rs7587849_rs2418269_Q_2,No_rs7587849_rs11211612_Q_1.5,Yes_rs2418269_rs2046685_Q_7,No_rs2418269_rs12551119_Q_2,Yes_rs11211612_rs12412736_Q_6,No_rs11211612_rs10904962_Q_6,Yes_rs2046685_rs7530465_Q_5.5,No_rs2046685_x_3_5,Yes_rs12551119_rs41374247_Q_5.5,No_rs12551119_rs4371605_Q_6,Yes_rs12412736_rs6472787_Q_6,No_rs12412736_x_6_5,Yes_rs10904962_rs707457_Q_3.5,No_rs10904962_rs9442372_Q_2,Yes_rs7530465_x_3_5,No_rs7530465_x_6_5,Yes_rs41374247_x_3_5,No_rs41374247_x_6_5,Yes_rs4371605_x_3_5,No_rs4371605_rs4970421_Q_5.5,Yes_rs6472787_x_6_5,No_rs6472787_x_3_5,Yes_rs707457_x_3_5,No_rs707457_x_6_5,Yes_rs9442372_x_6_5,No_rs9442372_x_3_5,Yes_rs4970421_x_3_5,No_rs4970421_x_6_5,\nCreate_rs9543281_Q_5.5,Yes_rs9543281_rs4680238_Q_1.5,No_rs9543281_rs10853282_Q_8.5,Yes_rs4680238_x_6_5,No_rs4680238_x_3_5,Yes_rs10853282_rs17325821_Q_6,No_rs10853282_rs17135476_Q_1.5,Yes_rs17325821_rs133503_Q_8.5,No_rs17325821_x_3_5,Yes_rs17135476_rs1517782_Q_3.5,No_rs17135476_rs701100_Q_8.5,Yes_rs133503_rs34835780_Q_2,No_rs133503_x_3_5,Yes_rs1517782_x_6_5,No_rs1517782_rs2660563_Q_6,Yes_rs701100_x_3_5,No_rs701100_rs1317209_Q_2,Yes_rs34835780_x_3_5,No_rs34835780_x_6_5,Yes_rs2660563_rs13030338_Q_6,No_rs2660563_x_6_5,Yes_rs1317209_x_3_5,No_rs1317209_x_6_5,Yes_rs13030338_rs926244_Q_5.5,No_rs13030338_x_6_5,Yes_rs926244_x_3_5,No_rs926244_x_6_5,\nCreate_rs649640_Q_2,Yes_rs649640_rs41526051_Q_7,No_rs649640_rs6732937_Q_6,Yes_rs41526051_rs2275603_Q_2,No_rs41526051_rs7642488_Q_6,Yes_rs6732937_rs11913594_Q_8.5,No_rs6732937_x_6_5,Yes_rs2275603_x_6_5,No_rs2275603_x_3_5,Yes_rs7642488_rs16864358_Q_8.5,No_rs7642488_rs4753962_Q_8.5,Yes_rs11913594_rs7461808_Q_6,No_rs11913594_rs12760071_Q_7,Yes_rs16864358_x_6_5,No_rs16864358_x_3_5,Yes_rs4753962_x_3_5,No_rs4753962_rs13432159_Q_9.5,Yes_rs7461808_rs9930735_Q_6,No_rs7461808_x_6_5,Yes_rs12760071_x_6_5,No_rs12760071_x_3_5,Yes_rs13432159_x_3_5,No_rs13432159_x_6_5,Yes_rs9930735_rs11573970_Q_3.5,No_rs9930735_x_6_5,Yes_rs11573970_x_6_5,No_rs11573970_x_3_5,\nCreate_rs2567274_Q_6,Yes_rs2567274_rs3742672_Q_5.5,No_rs2567274_rs1113111_Q_3.5,Yes_rs3742672_rs4662834_Q_2,No_rs3742672_rs4141989_Q_8.5,Yes_rs1113111_rs10134028_Q_5.5,No_rs1113111_rs1504418_Q_2,Yes_rs4662834_x_3_5,No_rs4662834_x_6_5,Yes_rs4141989_x_6_5,No_rs4141989_rs797913_Q_6,Yes_rs10134028_rs2209477_Q_8.5,No_rs10134028_rs12922641_Q_5.5,Yes_rs1504418_x_6_5,No_rs1504418_x_3_5,Yes_rs797913_x_3_5,No_rs797913_x_6_5,Yes_rs2209477_x_3_5,No_rs2209477_x_6_5,Yes_rs12922641_rs10517011_Q_2,No_rs12922641_rs6685406_Q_2,Yes_rs10517011_x_6_5,No_rs10517011_rs4656248_Q_8.5,Yes_rs6685406_x_3_5,No_rs6685406_x_6_5,Yes_rs4656248_x_6_5,No_rs4656248_x_3_5,\n";//origin
		//Hapmap 2
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
