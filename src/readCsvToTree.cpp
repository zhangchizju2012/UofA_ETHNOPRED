#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <sstream>	//使用stringstream需要引入这个头文件
using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void testfun1(string a, string b, double d){
  cout << "1" << endl;
  cout << a << endl;
  cout << b << endl;
  //cout << c << endl;
  cout << d << endl;
}

void testfun2(string a, string b, string c, double d){
  cout << "2" << endl;
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << d << endl;
}

void testfun3(string a, string b, string c, double d){
  cout << "3" << endl;
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << d << endl;
}

int main(){
  string treeWordBreak = ",";
  string treeLineBreak = "\n";
  string treeNodeBreak = "_";
  //string treeInfo = "Create_rs6437783_Q_1.5,Yes_rs6437783_rs4835141_Q_1.5,No_rs6437783_rs735480_Q_1.5,Yes_rs4835141_x_2_5,No_rs4835141_x_3_5,Yes_rs735480_x_3_5,No_rs735480_x_1_5,\n";
  string treeInfo = "Create_rs35389_Q_2.5,Yes_rs35389_rs4787645_Q_1.5,No_rs35389_rs1726254_Q_2.5,Yes_rs4787645_rs4847428_Q_1.5,No_rs4787645_x_3_5,Yes_rs1726254_x_1_5,No_rs1726254_x_2_5,Yes_rs4847428_x_1_5,No_rs4847428_x_2_5,\n";
  string treeLineInfo;
  string treeWordInfo;
  std::vector<string> treeNodeInfo;
  size_t treeNodePos;
  size_t treeWordPos;
  size_t treeLinePos;
  treeLinePos = treeInfo.find(treeLineBreak);
  while(treeLinePos < 1000000){//应该为while循环
    treeLineInfo = treeInfo.substr(0, treeLinePos + treeLineBreak.length());

    treeWordPos = treeLineInfo.find(treeWordBreak);
    while(treeWordPos < 1000000){
      treeWordInfo = treeLineInfo.substr(0, treeWordPos + treeWordBreak.length());

      treeNodePos = treeWordInfo.find(treeNodeBreak);
      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
      //cout << treeNodeInfo[0] << endl;
      treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
      treeNodePos = treeWordInfo.find(treeNodeBreak);
      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
      //cout << treeNodeInfo[1] << endl;
      treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
      treeNodePos = treeWordInfo.find(treeNodeBreak);
      treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
      //cout << treeNodeInfo[2] << endl;
      if(treeNodeInfo[0] == "Create"){
        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
        treeNodePos = treeWordInfo.find(treeNodeBreak);
        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
        double a = stringToNum<double>(treeNodeInfo[3]);
        testfun1(treeNodeInfo[1], treeNodeInfo[2], a);
        treeNodeInfo.clear();
      }
      else if (treeNodeInfo[0] == "Yes"){
        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
        treeNodePos = treeWordInfo.find(treeNodeBreak);
        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
        treeNodePos = treeWordInfo.find(treeNodeBreak);
        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
        double a = stringToNum<double>(treeNodeInfo[4]);
        testfun2(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
        treeNodeInfo.clear();
      }
      else if (treeNodeInfo[0] == "No"){
        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
        treeNodePos = treeWordInfo.find(treeNodeBreak);
        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));

        treeWordInfo.erase(0, treeNodePos + treeNodeBreak.length());
        treeNodePos = treeWordInfo.find(treeNodeBreak);
        treeNodeInfo.push_back(treeWordInfo.substr(0, treeNodePos));
        double a = stringToNum<double>(treeNodeInfo[4]);
        testfun3(treeNodeInfo[1], treeNodeInfo[2], treeNodeInfo[3], a);
        treeNodeInfo.clear();
      }

      treeLineInfo.erase(0, treeWordPos + treeWordBreak.length());
      treeWordPos = treeLineInfo.find(treeWordBreak);
    }
    treeInfo.erase(0, treeLinePos + treeLineBreak.length());
    treeLinePos = treeInfo.find(treeLineBreak);
  }

}
