#include "common.hpp"
using namespace std;

string readCSVFile( const char * fileName){
  ifstream file;
  stringstream ss;
  string str;
  file.exceptions ( ifstream::failbit | ifstream::badbit );
  try {
    file.open (fileName);
    ss << file.rdbuf();
    str = ss.str();
    file.close();
  } catch (ifstream::failure e) {
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
/*
  size_t breakPos = str.find(linebreak);
  lineID = str.substr(0, breakPos);
  lineInfo = str.erase(0, breakPos + linebreak.length());
  std::cout << (breakPos == std::string::npos) << endl;
  cout << breakPos << endl;
  cout << std::string::npos << endl;
  cout << str;
  str.erase(0, breakPos + linebreak.length());
  cout << str;
  breakPos = str.find(linebreak);
  cout << breakPos << endl;
  cout << std::string::npos << endl;
  return lineID;
*/

  size_t breakPos = str.find(linebreak);
  line1 = str.substr(0, breakPos + linebreak.length());
  line2 = str.erase(0, breakPos + linebreak.length());
  cout << line1;
  cout << line2;
  breakPos = line1.find(linebreak);
  //cout << breakPos << endl;
  //cout << std::string::npos << endl;
  size_t commaPos;

  commaPos = line1.find(delimiter);
  lineID = line1.substr(0, commaPos);
  cout << lineID << endl;

  while(breakPos > 2){
  line1 = line1.erase(0, commaPos + delimiter.length());
  breakPos = line1.find(linebreak);
  //cout << breakPos << endl;
  //cout << std::string::npos << endl;
  commaPos = line1.find(delimiter);
  lineID = line1.substr(0, commaPos);
  cout << lineID << endl;
}

  breakPos = line2.find(linebreak);
  commaPos = line2.find(delimiter);
  lineID = line2.substr(0, commaPos);
  cout << lineID << endl;

  while(breakPos > 2){
  line2 = line2.erase(0, commaPos + delimiter.length());
  breakPos = line2.find(linebreak);
  //cout << breakPos << endl;
  //cout << std::string::npos << endl;
  commaPos = line2.find(delimiter);
  lineID = line2.substr(0, commaPos);
  cout << lineID << endl;
  }

  return str;
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

    // insert code here...
/*
    std::ifstream theFile(inputFile);
    int id;
    std::string name;
    double money;
    while (theFile >> id >> name >> money) {
        cout << id << ", " << name << ", " << money << endl;
    }
    std::cout << "Hello, World!\n";*/
    std::cout << readCSVFile(inputFile);
    //std::cout << name;
    return 0;
}

///Users/zhangchi/Desktop/Machine learning_1/Test_data_270_50000_markers.csv
/*
#include "common.hpp"
int main(int argc, char *argv[]){

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

if (output_file != NULL){
  std::cout << output_file << std::endl;
}
  auto str = "Hello World!!";

  return 0;
}
*/
