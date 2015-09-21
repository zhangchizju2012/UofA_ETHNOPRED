#ifndef ETHNOPRED_BASIC
#define ETHNOPRED_BASIC
#pragma once
#include "Common.hpp"
#include "DecisionTree.hpp"


namespace ETHNOPRED{
	using namespace std;
	class ETHNOPREDTree{
		public:
			string ReadFile(const string&);
			void AnalyzeSNIP(const string&);
			void GetSNPID();
			void CreateETHNOPEDTree();
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
