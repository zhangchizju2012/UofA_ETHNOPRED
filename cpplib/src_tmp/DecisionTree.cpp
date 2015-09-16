// DecisionTree.cpp: implementation of the DecisionTree class.
//
//////////////////////////////////////////////////////////////////////

#include "DecisionTree.h"
#include "TreeNode.h"
#include "common.hpp"
#include <iostream>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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

void DecisionTree::QueryBinaryTree(TreeNode* currentNode, std::vector<vector<string> > inputVector)
{
	if (currentNode->m_pYesBranch == NULL)
	{
		//if both the yes and no branch pointers are NULL
		//the tree is at a decision outcome state so output
		//the string
		if (currentNode->m_pNoBranch == NULL)
			cout << currentNode->m_strQuestOrAns << endl;
		else
			cout << "Missing yes branch at " + currentNode->m_strQuestOrAns + " question\n";
		return;
	}
	if (currentNode->m_pNoBranch == NULL)
	{
		cout << "Missing no branch at " + currentNode->m_strQuestOrAns + " question\n";
		return;
	}

	//otherwise default to asking the question at the currentNode
	AskQuestion(currentNode, inputVector);
}

void DecisionTree::Query(std::vector<vector<string> > inputVector)
{
	QueryBinaryTree(m_pRootNode, inputVector);
}

void DecisionTree::AskQuestion(TreeNode *node, std::vector<vector<string> > inputVector)
{
	cout << node->m_strQuestOrAns + " (enter yes or no)\n";
	double answer;
	answer = findPosReturnValue(inputVector, (node->m_iNodeID));
	//string b = "3";
	//cout << inputVector[1][4];
	//cout << findPosReturnValue(inputVector, b);
	if (answer < (node->m_NodeValue))
		QueryBinaryTree(node->m_pYesBranch, inputVector);
	else if (answer >(node->m_NodeValue))
		QueryBinaryTree(node->m_pNoBranch, inputVector);
	else
	{
		cout << "Error please answer yes or no\n";
		AskQuestion(node, inputVector);
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
	for (int i = 0; i <= (inputVector[0].size() + 1); i++){
		if (inputVector[0][i] == a){
			if (inputVector[1][i] == "AA") return 1;
			else if (inputVector[1][i] == "Aa") return 2;
			else if (inputVector[1][i] == "aa") return 3;
		}
		//return 20;
	}
}
