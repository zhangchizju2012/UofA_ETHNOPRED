#include <iostream>
#include <fstream>
#include <sstream>
//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int findSmallValue(vector<int> inputvector){
	int a[10];
	for (int i = 0; i <= 9; i++)
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
		}
	}
	while (1){
		for (int i = 0; i <= 9; i++){
			if (a[i] != 3)
				return i;
		}
	}
}
/*
int main(){
	vector<int> a;
	a.push_back(0);
	a.push_back(0);
	a.push_back(1);
	a.push_back(0);
	a.push_back(2);
	a.push_back(1);
	a.push_back(3);
	a.push_back(1);
	a.push_back(4);
	a.push_back(2);
	a.push_back(5);
	a.push_back(2);
	a.push_back(6);
	int c = findSmallValue(a);
	return 0;
}
*/
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
	str = str.erase(0, breakPos + linebreak.length());
	breakPos = str.find(linebreak);
	line2 = str.substr(0, breakPos + linebreak.length());

	return line1;
}

int main()
{
	int c;
	string inputFile("C:\\C++\\SimpleTest\\SimpleTest\\1.txt");
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
	std::string line1 = readCSVFile(inputFile.c_str());
	std::string line2 = "34i5,3kjher,356,236,345dg,34563,22d,2356,342,567,\n";
	std::string treedata = "if x536407<5.5 then node 2 elseif x536407>=5.5 then node 3 else 3,if x1162126<5.5 then node 4 elseif x1162126>=5.5 then node 5 else 3,if x1062721<6 then node 6 elseif x1062721>=6 then node 7 else 6,if x857198<8.5 then node 8 elseif x857198>=8.5 then node 9 else 3,if x1219<5.5 then node 10 elseif x1219>=5.5 then node 11 else 6,if x55583<6 then node 12 elseif x55583>=6 then node 13 else 3,if x541343<2 then node 14 elseif x541343>=2 then node 15 else 6,class = 6,if x44<5.5 then node 16 elseif x44>=5.5 then node 17 else 3,class = 6,class = 3,if x23927<2 then node 18 elseif x23927>=2 then node 19 else 3,class = 6,if x687113<9.5 then node 20 elseif x687113>=9.5 then node 21 else 6,class = 3,class = 3,class = 6,if x1362<7 then node 22 elseif x1362>=7 then node 23 else 3,class = 6,if x26788<6 then node 24 elseif x26788>=6 then node 25 else 6,class = 3,class = 3,class = 6,class = 3,class = 6,\n";
  vector<string> treevector;
	vector<string> idvector;
	vector<double> idnumber;
	std::vector<size_t>postree;
	postree.push_back(-1);
	std::vector<int>dataposvector;
	for (size_t i = 0; i < treedata.length(); ++i)
	{
		if (treedata.at(i) == ','){
			postree.push_back(i);
		}
	}
	postree.push_back(treedata.find(linebreak) - linebreak.length());
	for (int j = 0; j < (postree.size() - 2); j++){
		treevector.push_back(treedata.substr(postree[j] + delimiter.length(), postree[j + 1] - postree[j] - 1));
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
			double a = stringToNum<double>(details[j][1].substr(0, posNumberSize[0]));
			numberID.push_back(idvector[a + 2]);
			numberSize.push_back(details[j][1].substr(posNumberSize[0] + 1, posNumberSize[1] - posNumberSize[0]));
			posNumberSize.clear();
		}
	}

	vector<int> important;
	for (int j = 0; j < treevector.size(); j++){
		int value = findSmallValue(important);
		important.push_back(value);
		if (j != 0){
			if (details[j][0] == "if"){
				if (details[j - 1][0] == "fit"){
					important.push_back(value + 1);
				}
				else{
					important.push_back(important[important.size() - 2] + 1);
				}
			}
		}
	}

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
			if ((j % 2 == 1) && (details[j][0] == "fit")){
				cout << "Yes_" << numberID[important[n]] << "_x_" <<details[j][2]<<"_5,"<<endl;
				n = n + 1;
			}
			if ((j % 2 == 0) && (details[j][0] == "fit")){
				cout << "No_" << numberID[important[n]] << "_x_" << details[j][2] << "_5," << endl;
				n = n + 1;
			}
		}
	}



	return 0;
}


	/*
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

	for (int j = 0; j < treevector.size(); j++){
		double a = stringToNum<double>(treevector[j]);
		cout << a << ": " << idvector[a + 2] << endl;
	}
	*/
	/*
	for (int j = 0; j < (posvector1.size() - 2); j++){
	//myvectorinitial[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
	//if (inTheTreeOrNot(treevector, line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1))){
	std::vector<string>::iterator it;
	it = find(treevector.begin(), treevector.end(), (line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1)));
	if (it != treevector.end()){
	dataposvector.push_back(j);
	myvector[0].push_back(line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1));
	cout << line1.substr(posvector1[j] + delimiter.length(), posvector1[j + 1] - posvector1[j] - 1) << ": " << j << endl;
	}
	}

	for (size_t i = 0; i < line2.length(); ++i)
	{
	//std::cout << str.at(i);
	if (line2.at(i) == ','){
	posvector2.push_back(i);
	}
	}
	posvector2.push_back(line2.find(linebreak) - linebreak.length());
	for (int j = 0; j < (posvector2.size() - 2); j++){
	myvectorinitial[1].push_back(line2.substr(posvector2[j] + delimiter.length(), posvector2[j + 1] - posvector2[j] - 1));
	}
	for (int k = 0; k <= dataposvector.size() - 1; k++){
	//myvector[0].push_back(myvectorinitial[0][dataposvector[k]]);
	myvector[1].push_back(myvectorinitial[1][dataposvector[k]]);
	}*/
	//line.push_back(str.substr(posvector[0] + delimiter.length(), posvector[1] - posvector[0]));
	//line.push_back(str.substr(posvector[2] + delimiter.length(), posvector[3] - posvector[2]));




/*
int main()
{
vector<string> line;
string delimiter = ",";
string linebreak = "\n";
//double count = 0;
std::vector<size_t>posvector;
posvector.push_back(-1);
std::string str = "abc,34i5,3kjher,356,236,345dg,34563,22d,2356,342,\n";
for (size_t i = 0; i < str.length(); ++i)
{
//std::cout << str.at(i);
if (str.at(i) == ','){
count = count + 1;
if (count == 3){
posvector.push_back(i);
count = 0;
}
}
}
for (size_t i = 0; i < str.length(); ++i)
{
//std::cout << str.at(i);
if (str.at(i) == ','){
posvector.push_back(i);
}
}
posvector.push_back(str.find(linebreak)-linebreak.length());
for (int j = 0; j < (posvector.size()-1); j++){
line.push_back(str.substr(posvector[j] + delimiter.length(), posvector[j + 1] - posvector[j] -1));
}
//line.push_back(str.substr(posvector[0] + delimiter.length(), posvector[1] - posvector[0]));
//line.push_back(str.substr(posvector[2] + delimiter.length(), posvector[3] - posvector[2]));

cout << endl;
system("pause");
return 0;
}*/
