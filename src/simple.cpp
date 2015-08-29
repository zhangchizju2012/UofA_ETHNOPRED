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
	std::string treedata = "t1,536407,1162126,1062721,857198,1219,55583,541343,44,23927,687113,1362,26788,t2,536419,1162121,541351,1225,857205,485429,75,1086819,943390,1065239,513230,55348,t3,687021,1100831,1272527,164771,341115,972401,52817,177073,269,5435,228650,23,8,t4,937257,495809,1412,309647,416386,162357,976329,579286,504318,5948,t5,624578,89765,1402118,4052,411344,492597,708629,1063895,1369792,1257,936,11279,909419,t6,1023051,537359,1079287,395888,1062729,259728,301,113,520322,1246459,2790,215630,1247761,t7,958158,335,1096434,1078435,310747,867960,117992,711837,318,1118225,126,141983,699436,t8,981089,595900,541346,1087847,510842,942870,512006,696616,59715,209844,t9,958136,309646,243742,58,928594,40802,776430,2665,508,1087804,610669,15157,110597,t10,958137,309650,901321,579,928607,632834,6445,512008,191720,1352909,579285,12070,t11,816397,880768,294143,399504,234974,12483,566013,80309,257756,392152,7197,1245242,959,t12,539097,928775,708560,110248,570,399776,542086,836446,2271,877,799640,595868,48433,t13,151325,500469,977550,472203,1371846,1148273,1782,1374996,1018,357,284095,469146,164487,1008877,t14,1078446,93693,595870,519222,644550,211206,675073,189327,234481,97434,t15,1023022,142985,957278,588548,18415,580376,508452,842143,1096816,884598,614714,t16,200247,565972,1080177,958150,932115,708563,411,983042,291,455556,1341279,1307,t17,309651,1139819,821,492568,723266,16953,29025,187,304,695833,1421529,104605,516702,t18,151326,958139,533749,978748,78955,258447,1293591,44703,3543,1253426,394428,115,49816,76,560,t19,437983,958151,541131,1352913,80198,861347,1415375,932163,1223,235974,3856,620789,t20,232586,662692,839535,288,1409761,490109,2435,422698,470,268315,2166,178156,108043,4491,t21,309654,2742,437987,1259652,509016,512,822430,169888,16,1138436,71508,146562,165594,158301,t22,538849,964000,107205,2538,3514,1396380,934,144882,309657,788235,48909,428525,t23,151309,958142,1039925,873480,17835,70729,630,134830,334153,1254883,214,5640,5281,437011,t24,1078448,781476,467319,187769,309670,132026,1093895,330658,25889,47,123169,188229,12738,t25,1078456,565856,85688,644559,449,519206,168363,846453,828387,114,1298193,215,t26,541348,224,187770,533841,967453,1224472,294,872032,902322,243755,510219,619,431129,t27,541350,232,763608,918917,508645,1124550,8895,960844,1160806,387,1994,1293596,102,794023,t28,541352,237,763606,508649,1093166,1388666,146007,667511,10597,906875,1061962,28134,1201788,t29,192313,535950,254141,358485,1106,1305140,49922,476630,26681,455,520343,1017513,394061,6199,t30,192284,565858,816378,31083,22553,878978,1264413,35,2322,888,590679,222283,5337,60392,308,t31,1022944,1138398,399577,306251,580379,456,1319375,9004,763042,287619,1071207,128,512009,2254,t32,253499,519207,996067,1146894,273,846767,10339,520333,854,940,19,733,1147238,793189,t33,483879,874064,644563,85,1317927,739616,145,1008316,695296,281684,323213,74286,t34,743347,674705,599930,763131,175575,772681,249977,332246,275367,649288,6484,148738,2812,5611,t35,928611,40043,958143,632840,78792,2332,104586,942890,597517,867974,107138,535013,t36,928616,47372,55586,579385,1111503,16659,679,1984,117,1369794,178159,942892,839515,2833,t37,1317939,928511,3239,591,644569,739620,565827,779,598918,140483,926120,178153,106732,t38,781532,880757,69833,1168964,795534,78,1347472,384630,857224,702677,839040,422291,1476,t39,151306,240676,1234051,924283,1122455,107800,305568,1211612,1326221,13435,210561,328,788,1341,\n";
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
