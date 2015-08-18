// DecisionTree.h: interface for the DecisionTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECISIONTREE_H__FCC1D907_3482_4CD4_9FB8_4352829DF1B4__INCLUDED_)
#define AFX_DECISIONTREE_H__FCC1D907_3482_4CD4_9FB8_4352829DF1B4__INCLUDED_
#include "common.hpp"
#include "TreeNode.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DecisionTree
{
public:
	void RemoveNode(TreeNode* node);
	void OutputBinaryTree(string tag, TreeNode* currentNode);
	void Output();
	string AskQuestion(TreeNode* node, std::vector<vector<string> > inputVector);
	string Query(std::vector<vector<string> > inputVector);
	string QueryBinaryTree(TreeNode* rootNode, std::vector<vector<string> > inputVector);
	bool SearchTreeAndAddNoNode(TreeNode* currentNode, string existingNodeID, string newNodeID, string newQorA, double newNodeValue);
	void AddNoNode(string existingNodeID, string newNodeID, string newQorA, double newNodeValue);
	bool SearchTreeAndAddYesNode(TreeNode* currentNode, string existingNodeID, string newNodeID, string newQorA, double newNodeValue);
	void AddYesNode(string existingNodeID, string newNodeID, string newQorA, double newNodeValue);
	void CreateRootNode(string nodeID, string newQorA, double nodeValue);
	double findPosReturnValue(std::vector<vector<string> > inputVector, string a);
	//the key root node to which all other nodes are added.
	TreeNode* m_pRootNode;
	DecisionTree();
	virtual ~DecisionTree();

};

#endif // !defined(AFX_DECISIONTREE_H__FCC1D907_3482_4CD4_9FB8_4352829DF1B4__INCLUDED_)
