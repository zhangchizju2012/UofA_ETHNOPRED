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
  const char * SelectedSNIPFile = NULL;
  const char * ClassifierType = NULL;

  while ((c = getopt (argc, argv, "i:s:T:o:t:")) != -1){
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

      case 's':
          if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
              fprintf (stderr,
                 "Found illegal or NULL parameter for the option -s.\n");
              return 1;
          }

          SelectedSNIPFile = optarg;

          break;

      case 'T':
          if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
              fprintf (stderr,
                 "Found illegal or NULL parameter for the option -T.\n");
              return 1;
          }

          ClassifierType = optarg;

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

  //std::string selectedSNIPFile(std::string(treeName) + std::string("_SNIP"));
  /*personInfo strcuture <vector<vector<string>>:
    1st line: SNIP info
    2nd - endNth: people's DNA info
  */
  EPTree->SetClassifierType(ClassifierType);
  auto personInfo = EPTree->AnalyzeSNIP(SNIPFile, SelectedSNIPFile);
  auto SNIPHeader = personInfo.at(0);

  /*Now personInfo is only people's DNA info*/
  personInfo.erase(personInfo.begin());
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

  EPTree->Stat();
  auto Winners = EPTree ->GetWinner();

  if(std::string(ClassifierType)=="subcontinent"){

    EPTree->SetClassifierType("country");
    std::string selectedSNIPFile(std::string(treeName) + std::string("_EuEaAf_SNIP"));
    //personInfo.clear();
    personInfo = EPTree->AnalyzeSNIP(SNIPFile, selectedSNIPFile);
    SNIPHeader = personInfo.at(0);

    personInfo.erase(personInfo.begin());

    for(auto pId = 0; pId < personInfo.size(); ++pId){

      std::cout << Winners.at(pId) << std::endl;
      if(Winners.at(pId) == "CEU"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_Euro"), true);}
      else if (Winners.at(pId) == "YRI"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_African"), true);}
      else if (Winners.at(pId) == "CHB/JPT"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_East_Asian"), true);}
      EPTree->SetTreesInfo(treeInfo);
      EPTree->CreateEPTreeArray();
      EPTree->SetSNIPInfo(SNIPHeader);
      EPTree->EmptyDecisionPool();
      EPTree->SetPersonInfo(personInfo.at(pId));
      EPTree->MakeDecision();
      EPTree->Add2DecisionPool();
      EPTree->Stat();
    }
  }
/*
  for(auto pId = 0; pId < personInfo.size(); ++pId){
    EPTree->SetClassifierType("country");
    std::cout << Winners.at(pId) << std::endl;
    if(Winners.at(pId) == "CEU"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_Euro"), true);}
    else if (Winners.at(pId) == "YRI"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_African"), true);}
    else if (Winners.at(pId) == "CHB/JPT"){treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("_East_Asian"), true);}
    EPTree->SetTreesInfo(treeInfo);
    EPTree->CreateEPTreeArray();
    EPTree->EmptyDecisionPool();
    EPTree->SetPersonInfo(personInfo.at(pId));
    EPTree->MakeDecision();
    EPTree->Add2DecisionPool();
    EPTree->Stat();
  }
*/
    //EPTree->Stat("country");
    //auto Winners = EPTree ->GetWinner();
/*
  treeInfo = EPTree->ReadFile(std::string(treeName) + std::string("map"), true);
  EPTree->SetTreesInfo(treeInfo);
  EPTree->CreateEPTreeArray();
  //EPTree->SetSNIPInfo(SNIPHeader);
  EPTree->EmptyDecisionPool();

  for(auto &p : personInfo){
    EPTree->SetPersonInfo(p);
    EPTree->MakeDecision();
    EPTree->Add2DecisionPool();
  }

  EPTree->Stat("continent");
*/
	return 0;
}
