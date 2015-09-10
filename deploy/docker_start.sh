# !/bin/bash
docker build -t="ethnopred/decision_tree" .
docker rm -f ethnopred
docker run -it -v /Users/zhangchi/UofA_ETHNOPRED/src:/ethnopred/src --name ethnopred ethnopred/decision_tree
