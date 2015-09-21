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

  EPTree->AnalyzeSNIP(SNIPFile, selectedSNIPFile);

  /*personInfo strcuture:
    1st line: SNIP info
    2nd - endNth: people's DNA info
  */
  std::vector<std::vector<std::string>> personInfo = EPTree->AnalyzeSNIP(SNIPFile, selectedSNIPFile);
  std::vector<std::string> SNIPHeader = personInfo.at(0);
  /*Now personInfo is only people's DNA info*/
  personInfo.erase(personInfo.begin());

  std::vector<std::vector<std::string>> resultAllPatient;


  for(int count=0; count < personInfo.size(); count++){
    std::vector<std::vector<std::string> > my;
    my.push_back(SNIPHeader);
    my.push_back(personInfo.at(count));

		std::vector<std::string> resultOnePatient;

		std::string treeWordBreak(",");
	  std::string treeLineBreak("\n");
	  std::string treeNodeBreak("_");

    //treeName must be accordance with finename udner the tree_structure folder
    //The second parameter true make sure: here is a line break '\n' at the end
		std::string treeInfo = EPTree->ReadFile(std::string(treeName), true);
    std::cout << "treeInfo" << treeInfo.size();

		std::string treeLineInfo;
	  std::string treeWordInfo;
	  std::vector<std::string> treeNodeInfo;
	  size_t treeNodePos;
	  size_t treeWordPos;
	  size_t treeLinePos;
	  treeLinePos = treeInfo.find(treeLineBreak);

	  while(treeLinePos != std::string::npos){

	    treeLineInfo = treeInfo.substr(0, treeLinePos + treeLineBreak.length());
      DecisionTree* newTree = EPTree->CreateEPTree(treeLineInfo);
      /*
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
      */
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