#include "ETHNOPRED.hpp"

namespace ETHNOPRED{
	using namespace std;

	string ETHNOPREDTree::ReadFile(const string& filename){

		string filepath = string("cpplibtree_structure/") + filename;
		
    	try {
            //lock mutex before accessing file
            static std::mutex mutex;
            std::lock_guard<std::mutex> lock(mutex);
            string str;
            stringstream ss;
            ifstream file;
            file.open(filepath.c_str());
    		ss << file.rdbuf();
    		str = ss.str();
    		file.close();
    		return str;
    	}

    	catch (std::ifstream::failure e) {
    		std::cerr << "Cannot open file" << e.what() << std::endl;
    		exit(1);
    	}

	}
}



