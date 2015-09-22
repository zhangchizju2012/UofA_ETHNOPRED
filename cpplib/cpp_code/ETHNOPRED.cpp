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

	ETHNOPREDTree::ETHNOPREDTree(){}
	ETHNOPREDTree::~ETHNOPREDTree(){}

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

	void ETHNOPREDTree::CreateEPTreeArray(){
		//make a copy of the m_treesInfo
		string treesInfo = this->m_TreesInfo;
		string treeLineDelimiter("\n");
	    auto treeLinePos = treesInfo.find(treeLineDelimiter);

	    while(treeLinePos != std::string::npos){

		    auto treeInfo = treesInfo.substr(0, treeLinePos + treeLineDelimiter.length());

		    m_DecisionTreeArray.push_back(this->CreateEPTree(treeInfo));

			treesInfo.erase(0, treeLinePos + treeLineDelimiter.length());
		    treeLinePos = treesInfo.find(treeLineDelimiter);
	    }
	}

	void ETHNOPREDTree::SetTreesInfo(const string& treesInfo){
		this->m_TreesInfo = treesInfo;
	}

	vector<DecisionTree*> ETHNOPREDTree::GetTreeArray(){
		return m_DecisionTreeArray;
	}

	void ETHNOPREDTree::SetPersonInfo(const vector<string>& personInfo){
		this->m_PersonInfo = personInfo;
	}

	void ETHNOPREDTree::SetSNIPInfo(const vector<string>& SNIPInfo){
		this->m_SNIPInfo = SNIPInfo;
	}

	void ETHNOPREDTree::MakeDecision(){

		if(!m_Decisions.empty()){
			m_Decisions.clear();
		}

		for (auto & tree : m_DecisionTreeArray){
			vector<vector<string>> info;
			info.push_back(m_SNIPInfo);
			info.push_back(m_PersonInfo);
			string decision = tree->Query(info);
			m_Decisions.push_back(decision);
		}
	}

	void ETHNOPREDTree::PrintDecision(){
		for(auto & decision : m_Decisions){
			cout << decision << endl;
		}
	}

	void ETHNOPREDTree::Add2DecisionPool(){	
		this->m_DecisionsPool.push_back(this->m_Decisions);

	}

	void ETHNOPREDTree::EmptyDecisionPool(){
		if (!m_DecisionsPool.empty()){
			m_DecisionsPool.clear();
		}
	}

	void ETHNOPREDTree::PrintStat(const string& classifierType = "country"){
        //use boost property_tree lib to report final result
        using boost::property_tree::ptree;
        using boost::property_tree::basic_ptree;

        vector<map<string, pair<string, int>>> voteNumAll;

        //store the winner for each person
        vector<string> voteWinner;

        for (auto &eachPatient : this->m_DecisionsPool){

            auto votedNum = this->GetVoteMap(classifierType);

            for(auto &identifier: eachPatient){
                /* votedNum -> data structure: map<string, pair<string, int>>
                <Name_of_Human_Species, <code_number, number_of_voted>>
                e.g <"EUR", <"1", 20>>
                */
                for (auto &v : votedNum){
                   if (identifier == v.second.first){
                     v.second.second++;
                   }
                }
            }

            voteNumAll.push_back(votedNum);
        }
        
        ptree JSONResultAll;
        ptree JSONVoteForEach;
        ptree JSONWinnerForEach;

        for(auto &voteEachPatient : voteNumAll){
            ptree JSONResultEach;

            //append vote info to JSON file
            for( auto &vote : voteEachPatient){
                //vote.second.second is the final vote for the given patient
                JSONResultEach.put(vote.first, vote.second.second);
            }

            //find the most voted category (winner) for each patient
            ptree JSONWinnerEach;

            int winnerCount = 0;
            std::string winnerName("");

            for( auto &vote : voteEachPatient){
                if (winnerCount < vote.second.second){
                    winnerCount =  vote.second.second;
                    winnerName = vote.first;
                }
            }

            JSONWinnerEach.put(winnerName, winnerCount);
            JSONWinnerForEach.push_back(make_pair("", JSONWinnerEach));
            JSONVoteForEach.push_back(make_pair("", JSONResultEach));
        }

        JSONResultAll.add_child("vote", JSONVoteForEach);
        JSONResultAll.add_child("winner", JSONWinnerForEach);

        //print out json
        std::stringstream ss;
        write_json(ss, JSONResultAll);
        std::cout << ss.str() << std::endl;
	}

	map<string, pair<string, int>> ETHNOPREDTree::GetVoteMap(const string& classifierType){
        if (classifierType == "country"){
	        map<string, pair<string, int>> voteNum =
	        {
	            {"EUR", { "1", 0 }},
	            {"?", { "2", 0 }},
	            {"?", { "3", 0 }},
	            {"?", { "4", 0 }},
	            {"?", { "5", 0 }},
	            {"JPN", { "6", 0 }},
	            {"AMR", { "7", 0 }},
	            {"?", { "8", 0 }},
	            {"CHN", { "9", 0 }},
	            {"?", { "10", 0 }},
	            {"?", { "11", 0 }},
	            {"No Value", { "No Value", 0 }}
	        };
	        return voteNum;
        } else if (classifierType == "continent"){
	        map<string, pair<string, int>> voteNum =
	        {
	            {"CEU", { "1", 0 }},
	            {"CHB/JPT", { "2", 0 }},
	            {"YRI", { "3", 0 }},
	            {"NoValue", { "No Value", 0 }}
	        };

	        return voteNum;
        }
	}
}