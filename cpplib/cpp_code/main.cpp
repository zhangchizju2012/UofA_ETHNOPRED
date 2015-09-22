#include "Common.hpp"
#include "TreeNode.hpp"
#include "TreeNode.cpp"
#include "DecisionTree.hpp"
#include "DecisionTree.cpp"
#include "ETHNOPREDSystem.hpp"
#include "ETHNOPRED.hpp"
#include "ETHNOPRED.cpp"

int main(int argc, char *argv[]) {
  int c;
  char * SNIPFile = NULL;
  char * outputFile = NULL;
  char * treeName = NULL;

  while ((c = getopt (argc, argv, "i:o:t:")) != -1){
    switch (c)
      {

      case 'i':
        if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
            fprintf (stderr,
               "Found illegal or NULL parameter for the option -i.\n");
            return 1;
        }

        SNIPFile = optarg;

        break;

      case 'o':
        if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
            fprintf (stderr,
               "Found illegal or NULL parameter for the option -o.\n");
            return 1;
        }

        outputFile = optarg;

        break;

      case 't':
        if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
            fprintf (stderr,
               "Found illegal or NULL parameter for the option -t.\n -t option provides the path for the tree structure.");
            return 1;
        }

        treeName = optarg;

        break;

    case '?':
      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      return 1;
    }
  }
  
  //Create EP Tree
  std::unique_ptr<ETHNOPRED::ETHNOPREDTree> EPTree(new ETHNOPRED::ETHNOPREDTree());

  std::string selectedSNIPFile(std::string(treeName) + std::string("_SNIP"));
  /*personInfo strcuture <vector<vector<string>>:
    1st line: SNIP info 
    2nd - endNth: people's DNA info
  */
  auto personInfo = EPTree->AnalyzeSNIP(SNIPFile, selectedSNIPFile);
  auto SNIPHeader = personInfo.at(0);
  /*Now personInfo is only people's DNA info*/
  personInfo.erase(personInfo.begin());

  /*The second parameter true make sure: there is a line break '\n' at the end
  '\n' is used to seperated each tree structure
  */
  std::string treeInfo = EPTree->ReadFile(std::string(treeName), true);
  EPTree->SetTreesInfo(treeInfo);
  EPTree->CreateEPTreeArray();
  EPTree->SetSNIPInfo(SNIPHeader);
  EPTree->EmptyDecisionPool();

  for(auto &p : personInfo){
    EPTree->SetPersonInfo(p);
    EPTree->MakeDecision();
    EPTree->Add2DecisionPool();
  }

  EPTree->PrintStat();
	return 0;

}