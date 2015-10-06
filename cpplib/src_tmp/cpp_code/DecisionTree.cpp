#include "DecisionTree.hpp"

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
