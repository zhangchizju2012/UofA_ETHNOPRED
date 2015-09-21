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

  std::shared_ptr<ETHNOPRED::ETHNOPREDTree> EPTree;
  std::string selectedSNIPFile(std::string(treeName) + std::string("_SNIP"));

  EPTree->AnalyzeSNIP(selectedSNIPFile);

  std::vector<std::vector<std::string> > myFull = ETHNOPRED::IO::analyzeCSVFile(SNIPFile);
  std::vector<std::vector<std::string>> resultAllPatient;

  for(int count=1; count < myFull.size(); count++){
    std::vector<std::vector<std::string> > my;
    my.resize(2);
    my[0]=myFull[0];
    my[1]=myFull[count];


		std::vector<std::string> resultOnePatient;

		std::string treeWordBreak(",");
	  std::string treeLineBreak("\n");
	  std::string treeNodeBreak("_");

    //treeName must be accordance with finename udner the tree_structure folder
		std::string treeInfo = EPTree->ReadFile(std::string(treeName));
    std::cout << "treeInfo" << treeInfo;

		std::string treeLineInfo;
	  std::string treeWordInfo;
	  std::vector<std::string> treeNodeInfo;
	  size_t treeNodePos;
	  size_t treeWordPos;
	  size_t treeLinePos;
	  treeLinePos = treeInfo.find(treeLineBreak);

	  while(treeLinePos != std::string::npos){

	    treeLineInfo = treeInfo.substr(0, treeLinePos + treeLineBreak.length());
			DecisionTree* newTree = new DecisionTree();
	    treeWordPos = treeLineInfo.find(treeWordBreak);

	    while(treeWordPos != std::string::npos){
	      treeWordInfo = treeLineInfo.substr(0, treeWordPos + treeWordBreak.length());
	      treeNodePos = treeWordInfo.find(treeNodeBreak);
	      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

        //Yes_rs7573555_rs7561423_Q_6 forward 4 times based on '-'
        //Create_rs7570971_Q_1.5 is still find, even if it is shorter
        for ( auto i = 0; i < 4 ; ++i){
          treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
          treeNodePos = treeWordInfo.find(treeNodeBreak);
          treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
        }

	      if(treeNodeInfo[0] == "Create"){
	        double a = std::stof(treeNodeInfo[3]);
	        newTree->CreateRootNode(treeNodeInfo[1], treeNodeInfo[2], a);
	        treeNodeInfo.clear();
	      } else if (treeNodeInfo[0] == "Yes"){
	        double a = std::stof(treeNodeInfo[4]);
	        newTree->AddYesNode(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
	        treeNodeInfo.clear();
	      } else if (treeNodeInfo[0] == "No"){
	        double a = std::stof(treeNodeInfo[4]);
	        newTree->AddNoNode(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
	        treeNodeInfo.clear();
	      } else {
          //add warning
        }

	      treeLineInfo.erase(0, treeWordPos + treeWordBreak.length());
	      treeWordPos = treeLineInfo.find(treeWordBreak);
	    }
	    //newTree->Output();
			std::string result;
			result = newTree->Query(my);

			delete newTree;
			resultOnePatient.push_back(result);

			treeInfo.erase(0, treeLinePos + treeLineBreak.length());
	    treeLinePos = treeInfo.find(treeLineBreak);
	  }

  resultAllPatient.push_back(resultOnePatient);
}

  ETHNOPRED::IO::getJSONResult(resultAllPatient);
	//system("pause");
	return 0;

}