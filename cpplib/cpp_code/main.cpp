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

  for(int count=0; count < personInfo.size(); count++){
    EPTree->SetPersonInfo(personInfo.at(count));

  }

		/*std::vector<std::string> resultOnePatient;

	  std::string treeLineBreak("\n");


		std::string treeLineInfo;
	  std::string treeWordInfo;
	  size_t treeNodePos;
	  size_t treeLinePos;
	  treeLinePos = treeInfo.find(treeLineBreak);

	  while(treeLinePos != std::string::npos){

	    treeLineInfo = treeInfo.substr(0, treeLinePos + treeLineBreak.length());

      DecisionTree* newTree = EPTree->CreateEPTree(treeLineInfo);

			std::string result;
			result = newTree->Query(my);

			resultOnePatient.push_back(result);

			treeInfo.erase(0, treeLinePos + treeLineBreak.length());
	    treeLinePos = treeInfo.find(treeLineBreak);
	  }

  resultAllPatient.push_back(resultOnePatient);
}*/

  /*ETHNOPRED::IO::getJSONResult(resultAllPatient);*/
	//system("pause");
	return 0;

}