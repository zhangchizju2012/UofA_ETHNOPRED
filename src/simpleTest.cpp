#include <iostream>
#include <sstream>	//使用stringstream需要引入这个头文件
using namespace std;

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

int main(int argc, char* argv[])
{
	string rsbreak = "rs";
	string str = "rs801";
	size_t breakPos = str.find(rsbreak);
	str = str.erase(0, breakPos + rsbreak.length());
	double a = stringToNum<int>(str);
	double b = a + 1;
	cout << stringToNum<int>(str) << endl;
	cout << b << endl;

	system("pause");
	return 0;
}
