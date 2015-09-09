#include <iostream>     // std::cout
#include <algorithm>    // std::find
#include <vector>       // std::vector
using namespace std;

int main () {
  // using std::find with array and pointer:

  std::vector<string> myvector;
  myvector.push_back("a");
  myvector.push_back("b");
  myvector.push_back("c");
  myvector.push_back("d");
  std::vector<string>::iterator it;

  it = find (myvector.begin(), myvector.end(), "c");
  if (it != myvector.end())
    std::cout << "Element found in myvector: " << *it << '\n';
  else
    std::cout << "Element not found in myvector\n";

  return 0;
}
