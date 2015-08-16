// TreeNode.h: interface for the TreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREENODE_H__9D1BC16A_8BBF_47A2_81D2_9D10927220B0__INCLUDED_)
#define AFX_TREENODE_H__9D1BC16A_8BBF_47A2_81D2_9D10927220B0__INCLUDED_

#include <string>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//forward declaration
class TreeNode;

class TreeNode
{
public:
	TreeNode(string nodeID, string newQorA, double nodeValue);
	TreeNode();
	virtual ~TreeNode();
	string m_strQuestOrAns;
	string m_iNodeID;
	double m_NodeValue;
	//the pointers to the two nodes for the yes no question or answer states
	//remember the uniform design of the BDT requires two branches at each node.
	TreeNode* m_pYesBranch;
	TreeNode* m_pNoBranch;
};

#endif // !defined(AFX_TREENODE_H__9D1BC16A_8BBF_47A2_81D2_9D10927220B0__INCLUDED_)
