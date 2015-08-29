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

int findSmallValue(vector<int> inputvector){
	int a[15];
	for (int i = 0; i <= 14; i++)
		a[i] = 0;
	for (int i = 0; i < inputvector.size(); i++){
		switch (inputvector[i])
		{
		case 0: a[0] = a[0] + 1;
			break;
		case 1: a[1] = a[1] + 1;
			break;
		case 2: a[2] = a[2] + 1;
			break;
		case 3: a[3] = a[3] + 1;
			break;
		case 4: a[4] = a[4] + 1;
			break;
		case 5: a[5] = a[5] + 1;
			break;
		case 6: a[6] = a[6] + 1;
			break;
		case 7: a[7] = a[7] + 1;
			break;
		case 8: a[8] = a[8] + 1;
			break;
		case 9: a[9] = a[9] + 1;
			break;
    case 10: a[10] = a[10] + 1;
  		break;
  	case 11: a[11] = a[11] + 1;
  		break;
		case 12: a[12] = a[12] + 1;
  		break;
  	case 13: a[13] = a[13] + 1;
  		break;
  	case 14: a[14] = a[14] + 1;
  		break;

		}
	}
	while (1){
		for (int i = 0; i <= 14; i++){
			if (a[i] != 3)
				return i;
		}
	}
}

int findNewValue(vector<int> inputvector){
	int a[15];
	for (int i = 0; i <= 14; i++)
		a[i] = 0;
	for (int i = 0; i < inputvector.size(); i++){
		switch (inputvector[i])
		{
		case 0: a[0] = a[0] + 1;
			break;
		case 1: a[1] = a[1] + 1;
			break;
		case 2: a[2] = a[2] + 1;
			break;
		case 3: a[3] = a[3] + 1;
			break;
		case 4: a[4] = a[4] + 1;
			break;
		case 5: a[5] = a[5] + 1;
			break;
		case 6: a[6] = a[6] + 1;
			break;
		case 7: a[7] = a[7] + 1;
			break;
		case 8: a[8] = a[8] + 1;
			break;
		case 9: a[9] = a[9] + 1;
			break;
		case 10: a[10] = a[10] + 1;
			break;
		case 11: a[11] = a[11] + 1;
			break;
		case 12: a[12] = a[12] + 1;
			break;
		case 13: a[13] = a[13] + 1;
			break;
		case 14: a[14] = a[14] + 1;
			break;

		}
	}
	while (1){
		for (int i = 0; i <= 14; i++){
			if (a[i] == 0)
				return i;
		}
	}
}

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
	//std::string line2 = "34i5,3kjher,356,236,345dg,34563,22d,2356,342,567,\n";
  //std::string treedata = "if 536407<5.5 then node 2 elseif 536407>=5.5 then node 3 else 3,if 1162126<5.5 then node 4 elseif 1162126>=5.5 then node 5 else 3,if 1062721<6 then node 6 elseif 1062721>=6 then node 7 else 6,if 857198<8.5 then node 8 elseif 857198>=8.5 then node 9 else 3,if 1219<5.5 then node 10 elseif 1219>=5.5 then node 11 else 6,if 55583<6 then node 12 elseif 55583>=6 then node 13 else 3,if 541343<2 then node 14 elseif 541343>=2 then node 15 else 6,class = 6,if 44<5.5 then node 16 elseif 44>=5.5 then node 17 else 3,class = 6,class = 3,if 23927<2 then node 18 elseif 23927>=2 then node 19 else 3,class = 6,if 687113<9.5 then node 20 elseif 687113>=9.5 then node 21 else 6,class = 3,class = 3,class = 6,if 1362<7 then node 22 elseif 1362>=7 then node 23 else 3,class = 6,if 26788<6 then node 24 elseif 26788>=6 then node 25 else 6,class = 3,class = 3,class = 6,class = 3,class = 6,\n";
  std::string treedata = "if 536407<5.5 then node 2 elseif 536407>=5.5 then node 3 else 3,if 1162126<5.5 then node 4 elseif 1162126>=5.5 then node 5 else 3,if 1062721<6 then node 6 elseif 1062721>=6 then node 7 else 6,if 857198<8.5 then node 8 elseif 857198>=8.5 then node 9 else 3,if 1219<5.5 then node 10 elseif 1219>=5.5 then node 11 else 6,if 55583<6 then node 12 elseif 55583>=6 then node 13 else 3,if 541343<2 then node 14 elseif 541343>=2 then node 15 else 6,class = 6,if 44<5.5 then node 16 elseif 44>=5.5 then node 17 else 3,class = 6,class = 3,if 23927<2 then node 18 elseif 23927>=2 then node 19 else 3,class = 6,if 687113<9.5 then node 20 elseif 687113>=9.5 then node 21 else 6,class = 3,class = 3,class = 6,if 1362<7 then node 22 elseif 1362>=7 then node 23 else 3,class = 6,if 26788<6 then node 24 elseif 26788>=6 then node 25 else 6,class = 3,class = 3,class = 6,class = 3,class = 6,\nif 536419<9.5 then node 2 elseif 536419>=9.5 then node 3 else 3,if 1162121<5.5 then node 4 elseif 1162121>=5.5 then node 5 else 3,if 541351<1.5 then node 6 elseif 541351>=1.5 then node 7 else 6,if 1225<5.5 then node 8 elseif 1225>=5.5 then node 9 else 6,if 857205<8.5 then node 10 elseif 857205>=8.5 then node 11 else 3,if 485429<8.5 then node 12 elseif 485429>=8.5 then node 13 else 6,class = 3,class = 6,class = 3,class = 6,if 75<6 then node 14 elseif 75>=6 then node 15 else 3,if 1086819<6 then node 16 elseif 1086819>=6 then node 17 else 3,if 943390<5.5 then node 18 elseif 943390>=5.5 then node 19 else 6,class = 6,class = 3,class = 6,class = 3,class = 3,if 1065239<5.5 then node 20 elseif 1065239>=5.5 then node 21 else 6,class = 3,if 513230<6 then node 22 elseif 513230>=6 then node 23 else 6,class = 3,if 55348<8.5 then node 24 elseif 55348>=8.5 then node 25 else 6,class = 3,class = 6,\n";
  //std::string treedata = "if 9813<1.5 then node 2 else node 3,if 13640<2.5 then node 4 else node 5,if 115365<1.5 then node 6 else node 7,fit = 3,fit = 1.25,if 731<1.5 then node 8 else node 9,if 1406<1.5 then node 10 else node 11,fit = 2,fit = 1,fit = 3,if 241<2.5 then node 12 else node 13,fit = 2,fit = 1,\n";
  vector<string> treevector;
	vector<string> idvector;
	vector<double> idnumber;
	std::vector<size_t>postree;
	//postree.push_back(-1);
	std::vector<double>dataposvector;

  vector<string> treeSeperate;
	std::vector<size_t> posSeperateTree;
	posSeperateTree.push_back(-1);
	for (size_t i = 0; i < treedata.length(); ++i)
	{
		if (treedata.at(i) == '\n'){
			posSeperateTree.push_back(i);
		}
	}
	posSeperateTree.push_back(treedata.find(linebreak) - linebreak.length());
	for (int j = 0; j < (posSeperateTree.size() - 2); j++){
		treeSeperate.push_back(treedata.substr(posSeperateTree[j] + delimiter.length(), posSeperateTree[j + 1] - posSeperateTree[j] ));
	}

	for (size_t i = 0; i < line1.length(); ++i)
	{
		if (line1.at(i) == ','){
			posvector1.push_back(i);
		}
	}
	posvector1.push_back(line1.find(linebreak) - linebreak.length());
	for (int j = 0; j < (posvector1.size() - 2); j++){
		idvector.push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
		//idnumber.push_back(j - 2);
	}

	for (int x = 0; x < treeSeperate.size(); x++){
    postree.push_back(-1);

	for (size_t i = 0; i < treeSeperate[x].length(); ++i)
	{
		if (treeSeperate[x].at(i) == ','){
			postree.push_back(i);
		}
	}
	postree.push_back(treeSeperate[x].find(linebreak) - linebreak.length());
	for (double j = 0; j < (postree.size() - 2); j++){
		treevector.push_back(treeSeperate[x].substr(postree[j] + delimiter.length(), postree[j + 1] - postree[j] - 1));
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

  std::vector<std::vector<std::string> > details;
	std::vector<vector<size_t>> posdetails;
	details.resize(treevector.size());
	posdetails.resize(treevector.size());
	for (int j = 0; j < treevector.size(); j++){
		posdetails[j].push_back(-1);
	}
	string detailsbreak = " ";
	for (int j = 0; j < treevector.size(); j++){
		for (size_t i = 0; i < treevector[j].length(); ++i)
		{
			if (treevector[j].at(i) == ' '){
				posdetails[j].push_back(i);
			}
		}
		posdetails[j].push_back(treevector[j].size());
		for (int k = 0; k < (posdetails[j].size() - 1); k++){
			details[j].push_back(treevector[j].substr(posdetails[j][k] + delimiter.length(), posdetails[j][k + 1] - posdetails[j][k] - 1));
		}
	}

//  for (double j = 0; j < treevector.size(); j++){
//		long a = stringToNum<long>(treevector[j]);
//		cout <<  idvector[a + 4] << endl;
//	}

	vector<string> numberSize;
	vector<size_t> posNumberSize;
	vector<string> numberID;

	for (int j = 0; j < treevector.size(); j++){
		if (details[j][0] == "if"){
			//posNumberSize.push_back(-1);
			for (size_t i = 0; i < details[j][1].size(); ++i)
			{
				if (details[j][1].at(i) == '<'){
					posNumberSize.push_back(i);
				}
			}
			posNumberSize.push_back(details[j][1].size());
			//numberSize.push_back(details[j][1].substr(0, posNumberSize[0]));
			long a = stringToNum<long>(details[j][1].substr(0, posNumberSize[0]));
			numberID.push_back(idvector[a + 4]);
			numberSize.push_back(details[j][1].substr(posNumberSize[0] + 1, posNumberSize[1] - posNumberSize[0]));
			posNumberSize.clear();
		}
	}

	vector<int> important;
  for (int j = 0; j < treevector.size(); j++){
		important.push_back(findSmallValue(important));
		if (j != 0){
			if (details[j][0] == "if"){
				important.push_back(findNewValue(important));
			}
		}
	}
  /*
  for(int j=0; j < important.size();j++){
    cout << important[j]<<endl;
  }*/
	/*
	Create_rs4832501_Q_1.5,
	Yes_rs4832501_rs2200402_Q_2.5,
	No_rs4832501_rs931410_Q_1.5,
	*/
	int n = 0;
	int m = 0;
	for (int j = 0; j < treevector.size(); j++){
		if (j == 0){
			cout << "Create_" << numberID[important[n]] << "_Q_" << numberSize[m] <<"," <<endl;
			n = n + 1;
			m = m + 1;
		}
		else
		{
			if ((j % 2 == 1) && (details[j][0] == "if")){
				cout << "Yes_" << numberID[important[n]] << "_" << numberID[important[n + 1]] << "_Q_" << numberSize[m] << "," << endl;
				n = n + 2;
				m = m + 1;
			}
			if ((j % 2 == 0) && (details[j][0] == "if")){
				cout << "No_" << numberID[important[n]] << "_" << numberID[important[n + 1]] << "_Q_" << numberSize[m] << "," << endl;
				n = n + 2;
				m = m + 1;
			}
			if ((j % 2 == 1) && (details[j][0] == "class")){
				cout << "Yes_" << numberID[important[n]] << "_x_" <<details[j][2]<<"_5,"<<endl;
				n = n + 1;
			}
			if ((j % 2 == 0) && (details[j][0] == "class")){
				cout << "No_" << numberID[important[n]] << "_x_" << details[j][2] << "_5," << endl;
				n = n + 1;
			}
		}
	}
      cout << "Tree" << endl;
  		important.clear();
  		posdetails.clear();
  		numberID.clear();
  		details.clear();
  		numberSize.clear();
  		posvector1.clear();
  		postree.clear();
  		treevector.clear();
}
	return 0;
}
