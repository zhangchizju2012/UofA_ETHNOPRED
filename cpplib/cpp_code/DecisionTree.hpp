//////////////////////////////////////////////////////////////////////
//
//
//
//
//////////////////////////////////////////////////////////////////////

#ifndef ETHNOPRED_DECISION_TREE
#define ETHNOPRED_DECISION_TREE
#include "Common.hpp"
#include "TreeNode.hpp"
//#pragma once

class DecisionTree
{
	public:
		void RemoveNode(TreeNode* node);
		void OutputBinaryTree(const std::string & tag, TreeNode* currentNode);
		void Output();
		std::string AskQuestion(TreeNode* node, std::vector<std::vector<std::string> > inputVector);
		std::string Query(std::vector<std::vector<std::string> > inputVector);
		std::string QueryBinaryTree(TreeNode* rootNode, std::vector<std::vector<std::string> > inputVector);
		bool SearchTreeAndAddNoNode(TreeNode* currentNode, const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue);
		void AddNoNode(const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue);
		bool SearchTreeAndAddYesNode(TreeNode* currentNode, const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue);
		void AddYesNode(const std::string & existingNodeID, const std::string & newNodeID, const std::string & newQorA, const double & newNodeValue);
		void CreateRootNode(const std::string & nodeID, const std::string & newQorA, const double & nodeValue);
		double findPosReturnValue(std::vector<std::vector<std::string> > inputVector, const std::string & a);
		TreeNode* m_pRootNode;
		DecisionTree();
		virtual ~DecisionTree();
};

#endif
