#include "ETHNOPRED.hpp"

namespace ETHNOPRED{
	using namespace std;

	string ETHNOPREDTree::ReadFile(const string& filename, bool isBreaklineLast=false){

		//use mutex to protect file access
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);

    	ifstream file(filename.c_str(), ifstream::in);
    	stringstream ss;
    	string str;

        if (file.is_open()){
			ss << file.rdbuf();
			str = ss.str();
			file.close();
        } else {
        	string errMessage = string("[ Error ]  cannot openfile") + filename; 
        	throw runtime_error(errMessage.c_str());
        }

        if(isBreaklineLast){
        	//check whether the last character is '\n'
        	if( !(str.at(str.length()-1) == '\n')){
				str.push_back('\n');
        	}
        }

    	return str;
	}

	vector<vector<string>> ETHNOPREDTree::AnalyzeSNIP(const string& SNIPFileAll, const string& SNIPFileSelected){
		string SNIPAll = this->ReadFile(SNIPFileAll);
		//cout << SNIPAll;
		string SNPId = this->ReadFile(SNIPFileSelected);
		//cout << SNPId;
		string delComma(",");
    	string delLine("\n");
        vector<vector<string>> myvector;

    	auto breakPos = SNIPAll.find(delLine);
    	auto line1 = SNIPAll.substr(0, breakPos + delLine.length());
    	SNIPAll.erase(0, breakPos + delLine.length());

    	std::vector<size_t>posvector1;
    	posvector1.push_back(-1);
    	std::vector<size_t>posvector2;

    	std::vector<std::string> treevector;
    	std::vector<size_t>postree;
    	postree.push_back(-1);
    	std::vector<int> dataposvector;

    	for (size_t i = 0; i < SNPId.length(); ++i)
    	{
    		//std::cout << SNIPAll.at(i);
    		if (SNPId.at(i) == ','){
    			postree.push_back(i);
    		}
    	}
    	cout << "postree length";
    	cout << postree.size();
    	postree.push_back(SNPId.find(delLine) - delLine.length());


    	for (int j = 0; j < (postree.size() - 2); j++){
    		treevector.push_back(SNPId.substr(postree[j] + delComma.length(), postree[j + 1] - postree[j] - 1));
    	}

    	for (size_t i = 0; i < line1.length(); ++i)
    	{
    		//std::cout << str.at(i);
    		if (line1.at(i) == ','){
    			posvector1.push_back(i);
    		}
    	}

        //read first line to get the SNPId
        vector<string>SNPIdArray;

    	posvector1.push_back(line1.find(delLine) - delLine.length());
    	for (int j = 0; j < (posvector1.size() - 2); j++){
    		//myvectorinitial[0].push_back(line1.substr(posvector1[j] + delComma.length(), posvector1[j + 1] - posvector1[j] - 1));
    		//if (inTheTreeOrNot(treevector, line1.substr(posvector1[j] + delComma.length(), posvector1[j + 1] - posvector1[j] - 1))){
    		std::vector<std::string>::iterator it;


    		it = find(treevector.begin(), treevector.end(), (line1.substr(posvector1[j] + delComma.length(), posvector1[j + 1] - posvector1[j] - 1)));
    		if (it != treevector.end()){
    			dataposvector.push_back(j);
    			SNPIdArray.push_back(line1.substr(posvector1[j] + delComma.length(), posvector1[j + 1] - posvector1[j] - 1));
    		}
    	}

        myvector.push_back(SNPIdArray);

    	breakPos = SNIPAll.find(delLine);

    	while (breakPos != std::string::npos){
    		auto line2 = SNIPAll.substr(0, breakPos + delLine.length());
            vector<string> myvectorinitial;
            vector<string> geneEachPatient;
    		posvector2.push_back(-1);

    		for (size_t i = 0; i < line2.length(); ++i)
    		{
    			//std::cout << SNIPAll.at(i);
    			if (line2.at(i) == ','){
    				posvector2.push_back(i);
    			}
    		}
    		posvector2.push_back(line2.find(delLine) - delLine.length());

    		for (int j = 0; j < (posvector2.size() - 2); j++){
    			myvectorinitial.push_back(line2.substr(posvector2[j] + delComma.length(), posvector2[j + 1] - posvector2[j] - 1));
    		}
    		for (int k = 0; k <= dataposvector.size() - 1; k++){
    			//myvector[0].push_back(myvectorinitial[0][dataposvector[k]]);
    			geneEachPatient.push_back(myvectorinitial[dataposvector[k]]);
    		}

            myvector.push_back(geneEachPatient);

    		posvector2.clear();

    		SNIPAll.erase(0, breakPos + delLine.length());
    		breakPos = SNIPAll.find(delLine);
    	}

    	return myvector;
	}

	DecisionTree* ETHNOPREDTree::CreateEPTree(string treeStructure){
		//example of tree structure string
		//Yes or No branch Yes_rs7573555_rs7561423_Q_6
		//Create branch reate_rs7570971_Q_1.5 
		string wordDelimiter(",");
		string lineDelimiter("\n");
	    string treeNodeBreak("_");
	  	string treeWordInfo;

		vector<string> treeNodeInfo;

		DecisionTree* newTree = new DecisionTree();
	    auto treeWordPos = treeStructure.find(wordDelimiter);

	    while(treeWordPos != std::string::npos){
	        auto treeWordInfo = treeStructure.substr(0, treeWordPos + wordDelimiter.length());
	        auto treeNodePos = treeWordInfo.find(treeNodeBreak);
	        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

	        //Yes_rs7573555_rs7561423_Q_6 forward 4 times based on '-'
	        //Create_rs7570971_Q_1.5 is still find, even if it is shorter
	        for ( auto i = 0; i < 4 ; ++i){
	            treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
	            treeNodePos = treeWordInfo.find(treeNodeBreak);
	            treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
	        }

	        auto nodeType = treeNodeInfo[0];

		    if(nodeType == "Create"){

		      	auto branchSNIP = treeNodeInfo[1];
		        auto weight = stof(treeNodeInfo[3]);
		        newTree->CreateRootNode(branchSNIP, treeNodeInfo[2], weight);
		        treeNodeInfo.clear();

		    } else {

			    auto nodeLeftSNIP= treeNodeInfo[1];
		        auto nodeRightSNIP= treeNodeInfo[2];
			    auto weight = stof(treeNodeInfo[4]);

		      	if (nodeType == "Yes"){
			        newTree->AddYesNode(nodeLeftSNIP, nodeRightSNIP, treeNodeInfo[3], weight);
			        treeNodeInfo.clear();
			    }

			    if (nodeType == "No"){
			        double weight = stof(treeNodeInfo[4]);
			        newTree->AddNoNode(nodeLeftSNIP, nodeRightSNIP, treeNodeInfo[3], weight);
			        treeNodeInfo.clear();
			    }
		    }

	        treeStructure.erase(0, treeWordPos + wordDelimiter.length());
	        treeWordPos = treeStructure.find(wordDelimiter);
	    }

	    return newTree;
	}

}