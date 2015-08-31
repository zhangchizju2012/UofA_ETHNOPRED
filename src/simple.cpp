#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <vector>
using namespace std;

bool inTheTreeOrNot(vector<string> treevector, string a){
	for (int i = 0; i <= (treevector.size() - 1); i++){
		if (treevector[i] == a){
			return true;
		}
	}
	return false;
}

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

string readCSVFile(const char * fileName){
	std::vector<vector<string> > myvectorinitial;
	myvectorinitial.resize(2);
	std::vector<vector<string> > myvector;
	myvector.resize(2);
	ifstream file;
	stringstream ss;
	string str;
	file.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		file.open(fileName);
		ss << file.rdbuf();
		str = ss.str();
		file.close();
	}
	catch (ifstream::failure e) {
		std::cerr << "Exception opening file\n" << e.what() << endl;
		exit(1);
	}
	//std::cout << str;
	string delimiter = ",";
	string linebreak = "\n";
	string line1;
	string line2;
	string lineID;
	string lineInfo;


	size_t breakPos = str.find(linebreak);
	line1 = str.substr(0, breakPos + linebreak.length());

	return line1;
}

  int main(int argc, char *argv[]) {
    int c;
    char * inputFile = NULL;
    char * output_file = NULL;
    while ((c = getopt (argc, argv, "i:o:")) != -1){
      switch (c)
        {

        case 'i':
      //          fprintf(stderr,"[%s]-> ",optarg);
          if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
              fprintf (stderr,
                 "Found illegal or NULL parameter for the option -i.\n");
              return 1;
          }

          inputFile = optarg;

          break;

        case 'o':
      //          fprintf(stderr,"[%s]-> ",optarg);
          if (strcmp (optarg, "(null)") == 0 || optarg[0] == '-'){
              fprintf (stderr,
                 "Found illegal or NULL parameter for the option -o.\n");
              return 1;
          }

          output_file = optarg;

          break;

      case '?':
        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        return 1;
      }
    }
    if (inputFile != NULL){
      std::cout << inputFile << std::endl;
    }



	//std::vector<vector<string> > my = readCSVFile(inputFile.c_str());
	std::vector<vector<string> > myvectorinitial;
	myvectorinitial.resize(2);
	std::vector<vector<string> > myvector;
	myvector.resize(2);
	//vector<string> line;
	string delimiter = ",";
	string linebreak = "\n";
	//double count = 0;
	std::vector<size_t>posvector1;
	posvector1.push_back(-1);
	std::vector<size_t>posvector2;
	posvector2.push_back(-1);
	std::string line1 = readCSVFile(inputFile);
	std::string line2 = "34i5,3kjher,356,236,345dg,34563,22d,2356,342,567,\n";
	std::string treedata = "8,16,23,44,47,58,75,76,113,114,115,126,187,214,215,269,288,291,301,304,318,335,357,411,449,470,508,512,560,570,579,630,821,877,934,936,959,1018,1219,1223,1225,1257,1307,1362,1412,1782,2166,2271,2435,2538,2665,2742,2790,3514,3543,3856,4052,4491,5281,5435,5640,5948,6445,7197,11279,12070,12483,12738,15157,16953,17835,18415,23927,25889,26788,29025,40802,44703,48433,48909,49816,52817,55348,55583,59715,70729,71508,78955,80198,80309,85688,89765,93693,97434,104605,107205,108043,110248,110597,117992,123169,132026,134830,141983,142985,144882,146562,151309,151325,151326,158301,162357,164487,164771,165594,168363,169888,177073,178156,187769,188229,189327,191720,200247,209844,211206,215630,228650,232586,234481,234974,235974,243742,257756,258447,259728,268315,284095,294143,309646,309647,309650,309651,309654,309657,309670,310747,330658,334153,341115,392152,394428,395888,399504,399776,411344,416386,422698,428525,437011,437983,437987,455556,467319,469146,472203,485429,490109,492568,492597,495809,500469,504318,508452,509016,510842,512006,512008,513230,516702,519206,519222,520322,533749,536407,536419,537359,538849,539097,541131,541343,541346,541351,542086,565856,565972,566013,579285,579286,580376,588548,595868,595870,595900,610669,614714,620789,624578,632834,644550,644559,662692,675073,687021,687113,695833,696616,699436,708560,708563,708629,711837,723266,776430,781476,788235,799640,816397,822430,828387,836446,839535,842143,846453,857198,857205,861347,867960,873480,880768,884598,901321,909419,928594,928607,928775,932115,932163,937257,942870,943390,957278,958136,958137,958139,958142,958150,958151,958158,964000,972401,976329,977550,978748,981089,983042,1008877,1023022,1023051,1039925,1062721,1062729,1063895,1065239,1078435,1078446,1078448,1078456,1079287,1080177,1086819,1087804,1087847,1093895,1096434,1096816,1100831,1118225,1138436,1139819,1148273,1162121,1162126,1245242,1246459,1247761,1253426,1254883,1259652,1272527,1293591,1298193,1341279,1352909,1352913,1369792,1371846,1374996,1396380,1402118,1409761,1415375,1421529,\n";
	vector<string> treevector;
	vector<string> idvector;
	vector<double> idnumber;
	std::vector<size_t>postree;
	postree.push_back(-1);
	std::vector<double>dataposvector;
	for (size_t i = 0; i < treedata.length(); ++i)
	{
		if (treedata.at(i) == ','){
			postree.push_back(i);
		}
	}
	postree.push_back(treedata.find(linebreak) - linebreak.length());
	for (double j = 0; j < (postree.size() - 2); j++){
		treevector.push_back(treedata.substr(postree[j] + delimiter.length(), postree[j + 1] - postree[j] - 1));
	}

	for (size_t i = 0; i < line1.length(); ++i)
	{
		if (line1.at(i) == ','){
			posvector1.push_back(i);
		}
	}
	posvector1.push_back(line1.find(linebreak) - linebreak.length());
	for (double j = 0; j < (posvector1.size() - 2); j++){
		idvector.push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
		//idnumber.push_back(j - 2);
	}

	for (double j = 0; j < treevector.size(); j++){
		long a = stringToNum<long>(treevector[j]);
		cout <<  idvector[a + 4] << endl;
	}

	return 0;
}
