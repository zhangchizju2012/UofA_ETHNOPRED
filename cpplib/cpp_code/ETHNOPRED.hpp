#ifndef ETHNOPRED_BASIC
#define ETHNOPRED_BASIC
#pragma once
#include "Common.hpp"
#include "DecisionTree.hpp"


namespace ETHNOPRED{
	using namespace std;
	class ETHNOPREDTree{
		public:
		    //For ReadFile second parameter, isBreaklineLast is true, we are going to automatically add a breakline '\n' at the end of the string, if the end of string is not '\n'
			string ReadFile(const string&, bool isBreaklineLast);
			vector<vector<string>> AnalyzeSNIP(const string& SNIPFileAll, const string& SNIPFileSelected);
			void GetSNPID();
			DecisionTree* CreateEPTree(string);
			void CreateEPTreeArray();
			~ETHNOPREDTree();
			vector<string> GetSNPIdVec();
			string GetTreeStructure();
			string GetTreeStructure(const string& StructurePath);
			vector<vector<string>> GetGeneAll();
			vector<vector<string>> GetVotesAll();
		private:
			string m_StructureFilePath;
			vector<string> m_SNPIdVec;
			vector<vector<string>> m_GeneAll;
			vector<vector<string>> m_VotesAll;
	};
}

#endif
