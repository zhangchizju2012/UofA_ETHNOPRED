#include "ETHNOPRED.hpp"

namespace ETHNOPRED{
	using namespace std;

	string ETHNOPREDTree::ReadFile(const string& filename){

		string filepath = string("/home/paul/project/ethnopred/UofA_ETHNOPRED/cpplib/cpp_code/tree_structure/") + filename;
		cout << filepath <<endl;
    	std::ifstream file;
    	std::stringstream ss;
    	std::string str;

        file.open(filepath.c_str(), ifstream::in);
		ss << file.rdbuf();
		str = ss.str();
		file.close();

    	return str;
	}
}



