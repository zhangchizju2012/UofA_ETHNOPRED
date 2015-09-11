#ifndef ETHNOPRED_NODE_TREE
#define ETHNOPRED_NODE_TREE
#include "Common.hpp"

#pragma once

//forward declaration
class TreeNode;

class TreeNode
{
	public:
		TreeNode(const std::string & nodeID, const std::string & newQorA, const double & nodeValue);
		TreeNode();
		virtual ~TreeNode();
		std::string m_strQuestOrAns;
		std::string m_iNodeID;
		double m_NodeValue;
		//the pointers to the two nodes for the yes no question or answer states
		//remember the uniform design of the BDT requires two branches at each node.
		TreeNode* m_pYesBranch;
		TreeNode* m_pNoBranch;
};

#endif
