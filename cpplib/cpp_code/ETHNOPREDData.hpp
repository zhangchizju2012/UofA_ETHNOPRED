#ifndef ETHNOPRED_DATA
#define ETHNOPRED_DATA
#include "Common.hpp"

namespace ETHNOPRED {
  namespace Data {
    using namespace std;
    map<string, pair<string, int>> initVoteNum( const string & classifierType) {
      if (classifierType == "country"){
        map<string, pair<string, int>> voteNum =
        {
          {"EUR", { "1", 0 }},
          {"?", { "2", 0 }},
          {"?", { "3", 0 }},
          {"?", { "4", 0 }},
          {"?", { "5", 0 }},
          {"JPN", { "6", 0 }},
          {"AMR", { "7", 0 }},
          {"?", { "8", 0 }},
          {"CHN", { "9", 0 }},
          {"?", { "10", 0 }},
          {"?", { "11", 0 }},
          {"No Value", { "No Value", 0 }}
        };
        return voteNum;
      } else if (classifierType == "continent"){
        map<string, pair<string, int>> voteNum =
        {
          {"CEU", { "1", 0 }},
          {"YRII", { "2", 0 }},
          {"CHB/JPT", { "3", 0 }},
          {"NoValue", { "No Value", 0 }}
        };
        return voteNum;
      }
    }
  }
}

#endif
