#ifndef ETHNOPRED_BASIC
#define ETHNOPRED_BASIC
#pragma once
#include "Common.hpp"
#include "DecisionTree.hpp"


namespace ETHNOPRED{
	using namespace std;
	class ETHNOPREDTree{
		public:
			ETHNOPREDTree();
			~ETHNOPREDTree();

		    //For ReadFile second parameter, isBreaklineLast is true, we are going to automatically add a breakline '\n' at the end of the string, if the end of string is not '\n'
			string ReadFile(const string&, bool isBreaklineLast);
			vector<vector<string>> AnalyzeSNIP(const string& SNIPFileAll, const string& SNIPFileSelected);
			DecisionTree* CreateEPTree(string);
			void CreateEPTreeArray();
			void MakeDecision();

			void Add2DecisionPool();
			void EmptyDecisionPool();
			string GetTreeStructure();
			void SetTreesInfo(const string&);
			void SetPersonInfo(const vector<string>&);
			void SetSNIPInfo(const vector<string>&);
			void Stat(const bool isPrintJSON=true);
		  vector<string> GetWinner();
			void PrintDecision();
			void SetClassifierType(const char*);

			map<string, pair<string, int>> GetVoteMap();

			vector<DecisionTree* > GetTreeArray();
		private:
			string m_StructureFilePath;
			string m_TreesInfo;
			vector<string> m_PersonInfo;
			vector<DecisionTree*> m_DecisionTreeArray;
			vector<string> m_SNIPInfo;
			vector<string> m_Decisions;
			vector<vector<string>> m_DecisionsPool;
			vector<string> m_WinnerGroup;
			string m_ClassifierType;
      vector<string> m_PersonId;
	};
}

#endif
