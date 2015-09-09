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
	std::string treedata = "rs3131972,rs4245756,rs4970383,rs4475691,rs13302982,rs4040604,rs3748592,rs3748593,rs28570376,rs6696281,rs9803031,rs6667248,rs4314833,rs9729550,rs11466691,rs6603781,rs6685064,rs3737721,rs3737718,rs2274264,rs12142199,rs3855955,rs17160669,rs35242196,rs1240708,rs873927,rs7290,rs3766178,rs3128342,rs7407,rs2281173,rs2235536,rs2254669,rs4648808,rs425277,rs9442619,rs2292857,rs262680,rs10910034,rs4310388,rs10752748,rs2606411,rs6681741,rs2817185,rs1798246,rs2651927,rs2651912,rs2500283,rs2483275,rs2493292,rs2244013,rs6669870,rs7367066,rs7541544,rs12132422,rs351619,rs3947662,rs367673,rs13376100,rs9329417,rs6577401,rs7517585,rs4908455,rs17031150,rs1922983,rs11582339,rs706007,rs11121722,rs7522358,rs1569635,rs41388954,rs11261025,rs841370,rs10917234,rs12410046,rs12075715,rs3767908,rs1335762,rs12097368,rs655801,rs10493067,rs522821,rs3795501,rs274751,rs11264025,rs1861,rs3768046,rs12038297,rs3737829,rs11206510,rs2793661,rs10889634,rs754054,rs10430066,rs12411125,rs1618973,rs11204853,rs16841094,rs2814778,rs7552141,rs4644548,rs1246828,rs2802774,rs910032,rs11119881,rs1439464,rs17742354,rs6541124,rs16846854,rs12467317,rs672463,rs7577460,rs4669937,rs1524007,rs10165208,rs7588439,rs1396795,rs1396797,rs17018091,rs6732285,rs4851370,rs2123694,rs13397666,rs260714,rs17654299,rs934706,rs164736,rs2059696,rs10173594,rs6717424,rs6731591,rs4668272,rs17027638,rs4073664,rs6445254,rs2083838,rs1374821,rs4678073,rs4588357,rs6439472,rs210780,rs12108234,rs10008032,rs5743567,rs4833103,rs4624679,rs17007466,rs4129117,rs11748410,rs609096,rs2303170,rs35389,rs35391,rs28117,rs35411,rs331728,rs2270068,rs3776334,rs3776329,rs4958561,rs6555755,rs2051548,rs9442996,rs7759248,rs1016101,rs1338839,rs4870227,rs41459546,rs11965097,rs10253752,rs7782345,rs1465221,rs10245220,rs2904664,rs310373,rs1384182,rs1445168,rs4871389,rs10969597,rs10961635,rs7860104,rs10962599,rs2891125,rs12685829,rs2377982,rs10749549,rs17111275,rs11192637,rs10510040,rs3213221,rs7123242,rs12294859,rs4930431,rs7964970,rs7134749,rs2519,rs12425842,rs10777469,rs1007916,rs16941717,rs13378757,rs11147417,rs17640978,rs12875618,rs9573246,rs9557355,rs7154864,rs8007618,rs12590812,rs926144,rs4906743,rs1800414,rs11636232,rs12595731,rs3848147,rs11637114,rs4436808,rs8053650,rs1133238,rs2032915,rs6500380,rs4790359,rs7214357,rs8081204,rs9907225,rs4968239,rs9893667,rs9896466,rs8078633,rs911445,rs6053122,rs1934887,rs2039242,rs2829003,rs4819094,rs917408,rs738989,rs17425081,rs12484869,rs1960182,rs5751131,rs5758402,\n";
	vector<string> treevector;
	std::vector<size_t>postree;
	postree.push_back(-1);
	std::vector<int>dataposvector;
	for (size_t i = 0; i < treedata.length(); ++i)//find the position of ','
	{
		//std::cout << str.at(i);
		if (treedata.at(i) == ','){
			postree.push_back(i);
		}
	}
	postree.push_back(treedata.find(linebreak) - linebreak.length());
	for (int j = 0; j < (postree.size() - 2); j++){//push the SNP ID
		treevector.push_back(treedata.substr(postree[j] + delimiter.length(), postree[j + 1] - postree[j] - 1));
	}

	for (size_t i = 0; i < line1.length(); ++i)
	{
		//std::cout << str.at(i);
		if (line1.at(i) == ','){
				posvector1.push_back(i);
			}
	}
	posvector1.push_back(line1.find(linebreak)-linebreak.length());
  int k = 1;
	for (int j = 0; j < (posvector1.size()-2); j++){
		//myvectorinitial[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
		if (inTheTreeOrNot(treevector, line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1))){
      dataposvector.push_back(j);
			//myvector[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
			cout << k << ": " << line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1) << ": " << j - 4 << endl;
      k = k + 1 ;
		}
    //cout << j;
	}

	return 0;
}
